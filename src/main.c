/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:35:36 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/09 19:57:37 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_env(void)
{
	int iter;

	g_env.c_pos = vec_new(0, 0, 2);
	g_env.front = vec_new(0, 0, -1);
	iter = 0;
	while (iter < 1024)
		g_env.input[iter++] = 0;
	g_env.start = 1;
	g_env.last_x = WIDTH / 2;
	g_env.last_y = HEIGHT / 2;
	g_env.fov = 45.0f;
	g_env.yaw = -90.0f;
	g_env.pitch = 0.0f;
	g_env.rot_x = 0.0f;
	g_env.rot_y = 0.0f;
}

int		main(int ac, char **av)
{
	GLfloat	shader_program;
	t_vec3	up = vec_new(0, 1, 0);
	int			width;
	int			height;
	t_obj		*obj;

	init_env();
	// Start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: Could not start GLFW3\n");
		return (-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "scop_2.0", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: Could not open window with GLFW3\n");
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// Get version info
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST); // Enable depth-testing
	glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE);

	shader_program = init_shaders();

	/* OTHER STUFF GOES HERE NEXT */
	if (ac != 2) {
		fprintf(stderr, "ERROR: Obj missing in command line\n");
		glfwTerminate();
		return (-1);
	}
	obj = load_obj(av[1]);
	if (obj == NULL) {
		fprintf(stderr, "ERROR: Obj not parsed correctly, try to import and export it with Blender\n");
		glfwTerminate();
		return (-1);
	}
	GLuint vbo_obj, vao_obj;
	glGenVertexArrays(1, &vao_obj);
	glGenBuffers(1, &vbo_obj);
	glBindVertexArray(vao_obj);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_obj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * obj->data_index * DATA_SIZE, obj->data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, DATA_SIZE * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, DATA_SIZE * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
    {
		GLfloat frame = glfwGetTime();
		g_env.delta_time = frame - g_env.last_frame;
		g_env.last_frame = frame;
        glfwPollEvents();
		use_key();
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_program);
		GLfloat *view = look_at4x4(g_env.c_pos, vec_add(g_env.c_pos, g_env.front), up);
		GLfloat *projection = perspective_projection(g_env.fov,
		(float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		GLuint projection_loc = glGetUniformLocation(shader_program, "projection");
		GLint light_pos_loc = glGetUniformLocation(shader_program, "t_light.position");
		GLint obj_color_loc = glGetUniformLocation(shader_program, "obj_color");
		GLint light_color_loc = glGetUniformLocation(shader_program, "t_light.color");
		// GLint c_pos_loc = glGetUniformLocation(shader_program, "c_pos");
		glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection);
		free(projection);
		glUniform3f(obj_color_loc, 0.8f, 0.8f, 0.5f);
		glUniform3f(light_color_loc,  0.9f, 0.9f, 0.9f);
		glUniform3f(light_pos_loc, g_env.c_pos.x, g_env.c_pos.y, g_env.c_pos.z);
		// glUniform3f(c_pos_loc, g_env.c_pos.x, g_env.c_pos.y, g_env.c_pos.z);
        glBindVertexArray(vao_obj);
		GLuint view_location = glGetUniformLocation(shader_program, "view");
		glUniformMatrix4fv(view_location, 1, GL_FALSE, view);
		GLfloat *rotate_x = rotate4x4_x(g_env.rot_x);
		GLfloat *rotate_y = rotate4x4_y(g_env.rot_y);
		GLfloat *model_obj = mult_matrice4x4(rotate_x, rotate_y);
		free(rotate_x);
		free(rotate_y);
		GLuint model_location = glGetUniformLocation(shader_program, "model");
		glUniformMatrix4fv(model_location, 1, GL_FALSE, model_obj);
		glDrawArrays(GL_TRIANGLES, 0, obj->data_index * DATA_SIZE);
		free(model_obj);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
		free(view);
    }
    glDeleteVertexArrays(1, &vao_obj);
    glDeleteBuffers(1, &vbo_obj);
    glfwTerminate();
	free(obj);
    return (0);
}
