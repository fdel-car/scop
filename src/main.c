/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:35:36 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/07 20:22:49 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int main(int ac, char **av) {
	GLfloat	shader_program;
	t_obj	*obj;

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
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "scop_2.0", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: Could not open window with GLFW3\n");
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(window);

	// Start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// Get version info
	// const GLubyte* renderer = glGetString(GL_RENDERER);
	// const GLubyte* version = glGetString(GL_VERSION);
	// printf("Renderer: %s\n", renderer);
	// printf("OpenGL version supported %s\n", version);

	// Tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // Enable depth-testing
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(obj->data), obj->data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	int i = 0;
	// Print vertices
	// while (i < obj->nb_vertices) {
	// 	printf("%f", obj->vertices[i]);
	// 	if (i % 3 == 2) {
	// 		printf("\n");
	// 	} else {
	// 		printf(" | ");;
	// 	}
	// 	i++;
	// }

	// Print all data
	i = 0;
	// while (i < obj->data_index) {
	// 	printf("%f | ", obj->data[i * 3]);
	// 	printf("%f | ", obj->data[i * 3 + 1]);
	// 	printf("%f\n", obj->data[i * 3 + 2]);
	// 	i++;
	// }
	// ft_putnbr(obj->data_index);
	while(!glfwWindowShouldClose(window)) {
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_program);
		glBindVertexArray(vao_obj);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, obj->data_index * 3);
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}

	// Close GL context and any other GLFW resources
	glfwTerminate();
	return (0);
}
