/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:28:24 by fdel-car          #+#    #+#             */
/*   Updated: 2018/09/19 14:56:19 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
#define SCOP_H

#define START_SIZE 8192
#define DATA_SIZE 12
#define EPSILON 0.0001
#define SQ(x) ((x) * (x))

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "libft.h"

typedef struct s_vec3
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} t_vec3;

typedef struct s_text
{
	int tex_w;
	int tex_h;
	int size[2];
	unsigned char buff[4];
	unsigned char *img;
} t_text;

typedef struct s_obj
{
	GLint sampler2d[16];
	GLfloat *vertices;
	GLfloat *textures;
	GLfloat *normals;
	GLfloat *data;
	GLint nb_vertices;
	GLint nb_textures;
	GLint nb_normals;
	GLint size_normals;
	GLint size_textures;
	GLint size_vertices;
	GLint size_data;
	GLint data_index;
	GLfloat half_width;
	GLfloat half_height;
	GLfloat half_depth;
	GLfloat min_x;
	GLfloat min_y;
	GLfloat min_z;
	GLfloat max_x;
	GLfloat max_y;
	GLfloat max_z;
	GLfloat range;
	t_vec3 current_color;
	GLint tex_indice;
	GLint last_indice;
	short use_mtl;
	char item_textured;
	char *path;
} t_obj;

typedef struct s_env
{
	t_vec3 c_pos;
	t_vec3 up;
	t_vec3 front;
	char input[1024];
	char initialized;
	GLfloat *rotate_x;
	GLfloat *rotate_y;
	GLfloat *model_obj;
	GLfloat *projection;
	GLfloat *view;
	GLfloat delta_time;
	GLfloat last_frame;
	GLfloat frame;
	GLfloat pitch;
	GLfloat yaw;
	GLfloat fov;
	GLfloat last_x;
	GLfloat last_y;
	GLfloat rot_x;
	GLfloat rot_y;
	GLuint shader_program;
	GLuint vbo_obj;
	GLuint vao_obj;
	GLfloat coeff_texture;
	GLint textured;
	GLuint projection_loc;
	GLuint view_location;
	GLuint model_location;
} t_env;

t_env g_env;

void change_coeff_texture(void);
void set_texture(t_obj *obj);
t_text *load_texture(char *path);
int generate_texture(char *path);
t_obj *load_obj(char *str);
void init_shaders(void);
void load_data(char *line, t_obj *obj);
t_vec3 vec_scalaire(t_vec3 u, float value);
t_vec3 vec_mult(t_vec3 u, t_vec3 v);
t_vec3 vec_sub(t_vec3 u, t_vec3 v);
t_vec3 vec_add(t_vec3 u, t_vec3 v);
t_vec3 vec_norm(t_vec3 u);
GLfloat *vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
float vec_dotp(t_vec3 u, t_vec3 v);
t_vec3 vec_new(float x, float y, float z);
float dist_p(t_vec3 u, t_vec3 v);
int vec_is_null(t_vec3 u);
t_vec3 cross_product(t_vec3 u, t_vec3 v);
GLfloat *identity_4x4(GLfloat *matrice);
GLfloat *matrice_4x4(GLfloat *u, ...);
GLfloat *scale_4x4(float scale);
void perspective_projection(float fov, float aspect, float far, GLfloat *u);
char *material_path(char *path);
void load_material(char *str, t_obj *obj, char *path);
GLfloat *translate4x4(float x, float y, float z);
void rotate4x4_z(float theta, GLfloat *u);
void rotate4x4_y(float theta, GLfloat *u);
void rotate4x4_x(float theta, GLfloat *u);
void look_at4x4(t_vec3 cam, t_vec3 target, t_vec3 up, GLfloat *u);
void mult_matrice4x4(GLfloat *u, GLfloat *v, GLfloat *w);
void use_key(void);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow *window, double xpos, double ypos);
void get_version(GLFWwindow *window);
int unload_main(GLFWwindow *window, char **av);
void throw_error(char *error);
void load_vertices(char *line, t_obj *obj);
void load_textures(char *line, t_obj *obj);
void load_normals(char *line, t_obj *obj);
void load_data_vertices(t_obj *obj, int index);
void free_tab(char **tab, int iter);
void load_data_textures(t_obj *obj, int index);
void load_data_normals(t_obj *obj, int index);
void pre_compute_data(char *path, t_obj *obj);
void handle_texture(char *line, t_obj *obj);
void init_normals(t_obj *obj, int iter);

#endif
