#ifndef TETRIS_H
#define TETRIS_H

#include <windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <time.h>

/* if expression not true, write to null ptr (will halt program) */
#define ASSERT(expression) {if (!expression) {*(char *)0 = 0;}}

/* C macro for inline GLSL shaders */
#define GLSL(src) "#version 330 core\n" #src

/* program window width, height */
#define SCREEN_WIDTH 1000.0f
#define SCREEN_HEIGHT 500.0f

/* structure width/height, block width/height in pixels */
const float structureWidth = float(round(SCREEN_HEIGHT/1.9f));
const float structureHeight = float(round(SCREEN_HEIGHT));
const float blockWidth = float(round(structureWidth/10));
const float blockHeight = float(round(structureHeight/19));

/* 
	structure left and right boundaries on screen
    in pixels with (0,0) being top left corner
*/	
const float structureLeft = float((SCREEN_WIDTH/2)-(structureWidth/2));
const float structureRight = float((SCREEN_WIDTH/2)+(structureWidth/2));

/* border thickness in pixels */
const float border_size = 3.0f;

/*
	constant projection matrix, to calculate between
	typical OpenGL coordinates and screen pixel coordinates
*/
const glm::mat4 projection = glm::ortho(0.0f, 1366.0f, 768.0f, 0.0f);

/* OpenGL vertex array, vertex buffer, element buffer */
struct openglObjects {
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
};

/* OpenGL shaders + shader program */
struct openglShaders {
	GLuint vertex;
	GLuint fragment;
	GLuint program;
};

/* OpenGL GLSL variable locations */
struct openglShadersVar {
	GLint position;
	GLint projection;
	GLint model;
	GLint color;
};

/* keyboard state */
struct gameKeyState {
    int up;
    bool up_pressed;
    int down;
    bool down_pressed;
    int left;
    int right;
    int space;
	bool space_pressed;
	int one;
	bool one_pressed;
	int two;
	bool two_pressed;
	int three;
	bool three_pressed;
};

/* GLSL vertex shader */
static const GLchar *vert_source = GLSL( 
	in vec2 position; 
	uniform mat4 model; 
	uniform mat4 projection;
	void main()
	{
	    gl_Position = projection * model * vec4(position, 0.0, 1.0);
	}
);

/* GLSL fragment shader */
static const GLchar *frag_source = GLSL(
	out vec4 out_color;
	uniform vec3 in_color;
	void main()
	{
	    out_color = vec4(in_color, 1.0);
	}
);

/* vertex data */
const GLfloat vertex[] = {
		0.0f, 0.0f, /* top left */
		1.0f, 0.0f, /* top right */
		1.0f, 1.0f, /* bottom right */
		0.0f, 1.0f  /* bottom left */
};

/* Indices order data */
const GLuint indexV[] = {
    	0, 1, 2,
    	2, 3, 0
};

/* function declarations */
extern void terminate_program();
extern void terminate_program_GO();
extern void init_contexts();
extern void init_game_globals();
extern void init_opengl();
extern void clear_line(int);
extern void clear_full_lines();
extern void clear_structure();
extern void clear_next_tetromino_structure();
extern void tetromino_game();
extern void score();
extern void score_line();
extern void draw_score(int);
extern void draw_rows(int);
extern void handle_events();
extern void key_callback(GLFWwindow*, int, int, int, int);

#endif