#include "tetromino.h"
#include "tetris.h"
#include "textFont.h"

#include <memory>
#include <string>

/* global variables */
static bool runGame; /* game loop condition */
static GLFWwindow *windowGame; /* GLFW window context */
static openglShaders shadersGame; /* shaders program */
static openglObjects objectsGame; /* objects, vertex arrays*/
static openglShadersVar shadersVarGame; /* shader variables */
static int pointsGame; /* score throughout game */
blockType structureGame[200]; /* game structure (20 * 10) */
blockType nextStructureGame[16]; /* structure of the next Tetromino (4 * 4) */
std::unique_ptr<tetromino> tetrominoGame; /* tetromino on board */
std::unique_ptr<tetromino> nextTetrominoGame; /* tetromino to be played */
static gameKeyState getKeyState; /* key state for keyboard input  */
static double speedTimeGame; /* period between normal structure updates (sec) */
static double levelEasyTime; /* period between normal structure updates for Level Easy (sec) */
static double levelMediumTime; /* period between normal structure updates for Level Medium (sec) */
static double levelHardTime; /* period between normal structure updates for Level Hard (sec) */
static bool flagEasy; /* flags to know which level is selected */
static bool flagMedium; /* flags to know which level is selected */
static bool flagHard; /* flags to know which level is selected */
static int numRand; /* random number that selects the tetromino */
static int numRandNext; /* random number that selects the next tetromino */
static int numRandLast; /* saves the last random number */
static int numRowsClearTotal; /* saves the total number of rows cleared */
static int numRowsClear; /* saves the number of rows cleared (max 4) (resets every new tetromino) */
static bool flagGameOver; /* flag for printf Game Over */

/* global variables -> Draw Score */
std::unique_ptr<textFont> numbersScore;
blockNumber firstNumber[25];
blockNumber secondNumber[25];
blockNumber thirdNumber[25];
blockNumber fourthNumber[25];
blockNumber fifthNumber[25];
blockNumber sixthNumber[25];

/* global variables -> Draw Rows */
std::unique_ptr<textFont> letters;
blockNumber lR[25];
blockNumber lO[25];
blockNumber lW[25];
blockNumber lS[25];
blockNumber rowFirstNumber[25];
blockNumber rowSecondNumber[25];
blockNumber rowThirdNumber[25];

int main()
{
	/* initialize glfw, glew, opengl, game */
	init_contexts();
	init_opengl();
	init_game_globals();

	const color bg = get_other_color(groundColor::BACKGROUND); /* background color */

	/* main loop */
	do {
		double start_time = glfwGetTime(); /* frame start time */
		handle_events();
		static double prev_time = glfwGetTime(); /* time when stepped last */
		double this_time = glfwGetTime();  /* difference from prev_time */
		
		if (this_time - prev_time >= speedTimeGame) /* check whether to step */
		{
			prev_time += speedTimeGame; /* inc prev time by step time */
			tetrominoGame->move_down(); /* move tetromino down */
			if (tetrominoGame->locked) /* check if done w/ current tetromino */
			{
				score();
				clear_full_lines(); /* clear any and all full rows */
				numRowsClear = 0; /* resets the number of rows cleared */
				tetrominoGame->clear(); /* reset current tetromino */
				nextTetrominoGame->clear(); /* reset next tetromino */

				clear_next_tetromino_structure();
				tetromino_game(); /* pick the tetrominos */

				tetrominoGame->draw(); /* draw tetro to structure */
				nextTetrominoGame->drawNext(); /* draw tetro to next structure */
			}
		}
		glClearColor(bg.r, bg.g, bg.b, 0.0f); /* clear screen w/background color */
		glClear(GL_COLOR_BUFFER_BIT); /* clear gl color buffer bit */
		
		/* draw the next tetromino in next structure game */
		for (int k = 0; k < 16; k++) {
			if (nextStructureGame[k] == blockType::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			int row = (k - 4) / 4; /* row of i */
			int col = (k - 4) % 4; /* column of i */
			glm::vec2 position = glm::vec2( -310.0f + structureLeft + col * blockWidth,50.0f + row * blockHeight); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3(blockWidth, blockHeight, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color block_col_val = type_to_color(nextStructureGame[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, block_col_val.r, block_col_val.g, block_col_val.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		/* draw all blocks in structure */
		for (int i = 10; i < 200; i++) {
			if (structureGame[i] == blockType::NA) {
				/* no block in spot i */
				continue;
			}

			glm::mat4 model; /* model matrix */
			int row = (i - 10) / 10; /* row of i */
			int col = (i - 10) % 10; /* column of i */
			glm::vec2 position = glm::vec2(-200.0f + structureLeft + col * blockWidth, row * blockHeight); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3(blockWidth, blockHeight, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color block_col_val = type_to_color(structureGame[i]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, block_col_val.r, block_col_val.g, block_col_val.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		
		/* drawing row border lines */
		for (int r = 0; r < 20; r++) {
			glm::mat4 model; /* model matrix */

			/* calculate position of row border */
			glm::vec2 position = glm::vec2(structureLeft -200.0f, r * blockHeight);
			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by border size, */
			model = glm::scale(model, glm::vec3(structureWidth + border_size - 4.0f, border_size, 1.0f));
			/* send model data to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* get color of border */
			color border_col = get_other_color(groundColor::MATRIX);
			/* send color data to shader */
			glUniform3f(shadersVarGame.color, border_col.r, border_col.g, border_col.b);

			/* draw horizontal border to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		
		/* drawing column border lines */
		for (int c = 0; c < 11; c++) {
			/* same as row border lines, just vertical */
			glm::mat4 model;
			glm::vec2 position = glm::vec2(-200.0f + structureLeft + c * blockWidth, 0);

			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			model = glm::scale(model, glm::vec3(border_size, structureHeight + border_size - 6.0f, 1.0f));

			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			color bor_col = get_other_color(groundColor::MATRIX);
			glUniform3f(shadersVarGame.color, bor_col.r, bor_col.g, bor_col.b);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		
		/* -------------------- SCORE -------------------- */
		int size = std::to_string(pointsGame).length();
		int tmpNumber = 0;
		int maxNumber = 999999;
		/* clear the screen of the numbers (score) */
		numbersScore->clearScore();
		if (pointsGame < maxNumber) {
			maxNumber = pointsGame;
		}
		do {
			/* tmpNumber needs to be "+1" to get the correct index number of the enum class */
			if (size == 1) {
				tmpNumber = (maxNumber % 10) + 1;
			}
			if (size == 2) {
				tmpNumber = (maxNumber / 10 % 10) + 1;
			}
			if (size == 3) {
				tmpNumber = (maxNumber / 100 % 10) + 1;
			}
			if (size == 4) {
				tmpNumber = (maxNumber / 1000 % 10) + 1;
			}
			if (size == 5) {
				tmpNumber = (maxNumber / 10000 % 10) + 1;
			}
			if (size == 6) {
				tmpNumber = (maxNumber / 100000 % 10) + 1;
			}
			/* write the score (numbers) in the local arrays */
			numbersScore->drawNumber((blockNumber)tmpNumber, size);
			draw_score(size);
			size--;

			if (size == 0) {
				break;
			}
		} while (true);
		
		/* -------------------- ROWS CLEARED -------------------- */
		int size1 = 7;
		int tmpNumber1 = 0;
		int maxNumber1 = 999;
		/* clear the screen of the numbers (rows) */
		letters->clearLetters();
		if (numRowsClearTotal < maxNumber1) {
			maxNumber1 = numRowsClearTotal;
		}
		do {
			/* tmpNumber needs to be "+1" to get the correct index number of the enum class */
			if (size1 == 1) {
				tmpNumber1 = (maxNumber1 % 10) + 1;
			}
			if (size1 == 2) {
				tmpNumber1 = (maxNumber1 / 10 % 10) + 1;
			}
			if (size1 == 3) {
				tmpNumber1 = (maxNumber1 / 100 % 10) + 1;
			}
			if (size1 == 4) {
				tmpNumber1 = 14;
			}
			if (size1 == 5) {
				tmpNumber1 = 13;
			}
			if (size1 == 6) {
				tmpNumber1 = 12;
			}
			if (size1 == 7) {
				tmpNumber1 = 11;
			}
			/* write the score (numbers) in the local arrays */
			letters->drawLetters((blockNumber)tmpNumber1, size1);
			draw_rows(size1);
			size1--;

			if (size1 == 0) {
				break;
			}
		} while (true);

		/* draw buffer to window */
		glfwSwapBuffers(windowGame);
		/* get time between start and end frame */
		double delta_time = glfwGetTime() - start_time;
		/* sleep for remaining frame time length */
		Sleep(int(1000.0f / 24.0f - (delta_time * 1000)));

	} while (runGame);

	terminate_program();
	return 0;
}

/* end program -> Game Over */
void terminate_program_GO()
{
	if (flagGameOver) {
		printf("\n\n-----> GAME OVER <-----\n");
		runGame = false;
	}
	flagGameOver = true;
}

/* end program -> Exit */
void terminate_program() 
{
	/* clean up program (shaders, objects, glfw) */
	glDeleteVertexArrays(1, &objectsGame.vao);
    glDeleteBuffers(1, &objectsGame.vbo);
    glDeleteProgram(shadersGame.program);
    glDeleteShader(shadersGame.vertex);
    glDeleteShader(shadersGame.fragment);
    glfwTerminate();
	printf("\n\n-----> Rows Cleared: %d <-----\n", numRowsClearTotal);
	printf("-----> Final Score: %d <-----\n", pointsGame);
}

/* initialize glfw, glew, opengl contexts */
static void init_contexts()
{
	/* initialize glfw */
	glfwInit();
	/* give glfw window hints about OpenGL */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	/* initialize window, make current context */
	windowGame = glfwCreateWindow(1366, 768, "tetris", nullptr, nullptr);
	glfwMakeContextCurrent(windowGame);
	/* initialize glew */
	glewExperimental = GL_TRUE;
	glewInit();
	/* set glfw callback functions */
	glfwSetKeyCallback(windowGame, key_callback);
}

/* initialize glfw, glew, opengl */
static void init_opengl()
{
	/* 
		initialize opengl buffer objects, vertex arrays 
	*/
    glGenVertexArrays(1, &objectsGame.vao);
    glBindVertexArray(objectsGame.vao);
    glGenBuffers(1, &objectsGame.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, objectsGame.vbo);
	/* send vertex data to vertex array */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glGenBuffers(1, &objectsGame.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectsGame.ebo);
	/* send element order data to element array */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexV), indexV, GL_STATIC_DRAW);

	/* 
		initialize opengl GLSL shaders 
	*/

	/* create vertex shader */
    shadersGame.vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shadersGame.vertex, 1, &vert_source, NULL);
    glCompileShader(shadersGame.vertex);
	/* create fragment shader */
    shadersGame.fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shadersGame.fragment, 1, &frag_source, NULL);
    glCompileShader(shadersGame.fragment);
    shadersGame.program = glCreateProgram();
	/* attach shaders to program */
    glAttachShader(shadersGame.program, shadersGame.vertex);
    glAttachShader(shadersGame.program, shadersGame.fragment);
    glLinkProgram(shadersGame.program);
    glUseProgram(shadersGame.program);

	/* 
		initialize opengl shader variable locations 
	*/

	/* get shader location of "position" */
	shadersVarGame.position = glGetAttribLocation(shadersGame.program, "position");
	glEnableVertexAttribArray(shadersVarGame.position);
	/* point position data to vertex data */
	glVertexAttribPointer(shadersVarGame.position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	/* get shader location of "projection" */
	shadersVarGame.projection = glGetUniformLocation(shadersGame.program, "projection");
	/* send projection matrix to shader */
	glUniformMatrix4fv(shadersVarGame.projection, 1, GL_FALSE, glm::value_ptr(projection));
	/* get shader location of "model" */
	shadersVarGame.model = glGetUniformLocation(shadersGame.program, "model");
	/* get shader location of "in_color" */
	shadersVarGame.color = glGetUniformLocation(shadersGame.program, "in_color");
}

/* initialize game global values */
static void init_game_globals()
{
	srand((unsigned int)time(NULL)); /* set psuedo-random number gen seed */
	runGame = true;
	
	levelEasyTime = 1.5; /* 1.5 second real time */
	levelMediumTime = 0.75; /* 0.75 second real time */
	levelHardTime = 0.25; /* 0.25 second real time */
	flagEasy = false;
	flagMedium = true;
	flagHard = false;
	flagGameOver = false;

	speedTimeGame = levelMediumTime; /* Starts game in Level Medium */
	pointsGame = 0;
	numRowsClearTotal = 0;
	numRowsClear = 1;
	
	numRand = 0;
	numRandNext = 0;
	numRandLast = 0;

	/*
		Same thing that:
		-> allocate memory for tetro { (tetromino*)malloc(sizeof(tetrominoGame)); }
		Make_unique doesn't need to free memory
	*/
	tetrominoGame = std::make_unique<tetromino>();
	nextTetrominoGame = std::make_unique<tetromino>();
	numbersScore = std::make_unique<textFont>();

	tetromino_game();

	clear_structure();
	tetrominoGame->draw();
	nextTetrominoGame->drawNext();
}

/* clear individual row of structure */
static void clear_line(int row)
{
	// clear row to NA
	for (int c = 0; c < 10; c++) {
		structureGame[row * 10 + c] = blockType::NA;
	}

	// move previous rows down
	for (int r = row - 1; r >= 0; r--) {
		for (int c = 0; c < 10; c++) {
			structureGame[(r + 1) * 10 + c] = (blockType)structureGame[r * 10 + c];
		}
	}
	numRowsClearTotal++;
	numRowsClear++;
}

/* clear all full lines in structure */
static void clear_full_lines()
{
	bool flag = false;
	/* check for full lines */
	for (int r = 19; r > 0; r--) {
		bool full = true;

		/* check for empty block in row */
		for (int c = 0; c < 10; c++) {
			if (structureGame[r * 10 + c] == blockType::NA) {
				full = false;
			}
		}

		/* clear line if full */
		if (full) {
			flag = true;
			clear_line(r);
			r++;
		}
	}
	if (flag) {
		score_line();
	}
}

/* clear entire structure's values to 0 */
static void clear_structure()
{
	/* clear entire structure to NA */
	for (int i = 10; i < 200; i++) {
		structureGame[i] = blockType::NA;
	}
}

/* clear entire structure's values to 0 */
static void clear_next_tetromino_structure()
{
	/* clear entire structure to NA */
	for (int i = 0; i < 16; i++) {
		nextStructureGame[i] = blockType::NA;
	}
}

/* pick the tetrominos */
static void tetromino_game()
{
	/* When the game begins */
	if (numRand == 0) {
		while (true) {
			numRand = (rand() % 7) + 1;
			if (numRand != numRandLast) {
				break;
			}
		}
	}
	else {
		numRand = numRandNext;
	}

	/* Next Piece (random) (always different from the Last one) */
	while (true) {
		numRandNext = (rand() % 7) + 1;
		if (numRand != numRandNext) {
			break;
		}
	}
	tetrominoGame->init(blockType(numRand)); /* new tetro */
	nextTetrominoGame->init(blockType(numRandNext)); /* next tetro */
	numRandLast = numRandNext;
}

/* Score for tetromino */
static void score()
{
	if (flagEasy) {
		pointsGame += 5;
	}
	else if (flagMedium) {
		pointsGame += 10;
	}
	else if (flagHard) {
		pointsGame += 20;
	}
}

/* Score for clear_line() */
static void score_line()
{
	if (flagEasy) {
		if (numRowsClear > 1) {
			pointsGame += (25 * numRowsClear * 2);
		}
		else {
			pointsGame += 25;
		}
	}
	else if (flagMedium) {
		if (numRowsClear > 1) {
			pointsGame += (50 * numRowsClear + 25 * numRowsClear);
		}
		else {
			pointsGame += 50;
		}
	}
	else if (flagHard) {
		if (numRowsClear > 1) {
			pointsGame += (100 * numRowsClear + 25 * numRowsClear);
		}
		else {
			pointsGame += 100;
		}
	}
}

/* Draw the numbers in the window */
static void draw_score(int size)
{
	int row, col;
	if (size == 1) {
		for (int k = 0; k < 25; k++) {
			if (firstNumber[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */
			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(600.0f + structureRight + col * (blockWidth / 2), 50.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 2) / 2, (blockHeight / 2) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(firstNumber[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	if (size == 2) {
		for (int k = 0; k < 25; k++) {
			if (secondNumber[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(530.0f + structureRight + col * (blockWidth / 2), 50.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 2) / 2, (blockHeight / 2) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(secondNumber[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	if (size == 3) {
		for (int k = 0; k < 25; k++) {
			if (thirdNumber[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(460.0f + structureRight + col * (blockWidth / 2), 50.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 2) / 2, (blockHeight / 2) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(thirdNumber[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	if (size == 4) {
		for (int k = 0; k < 25; k++) {
			if (fourthNumber[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(375.0f + structureRight + col * (blockWidth / 2), 50.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 2) / 2, (blockHeight / 2) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(fourthNumber[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	if (size == 5) {
		for (int k = 0; k < 25; k++) {
			if (fifthNumber[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(310.0f + structureRight + col * (blockWidth / 2), 50.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 2) / 2, (blockHeight / 2) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(fifthNumber[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	if (size == 6) {
		for (int k = 0; k < 25; k++) {
			if (sixthNumber[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(245.0f + structureRight + col * (blockWidth / 2), 50.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 2) / 2, (blockHeight / 2) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(sixthNumber[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}

/* Draw the numbers of Rows Cleared in the window */
static void draw_rows(int size)
{
	int row, col;
	if (size == 1) {
		for (int k = 0; k < 25; k++) {
			if (rowFirstNumber[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */
			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(280.0f + structureRight + col * (blockWidth / 2), 350.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 3) / 2, (blockHeight / 3) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(rowFirstNumber[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	if (size == 2) {
		for (int k = 0; k < 25; k++) {
			if (rowSecondNumber[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(220.0f + structureRight + col * (blockWidth / 2), 350.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 3) / 2, (blockHeight / 3) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(rowSecondNumber[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	if (size == 3) {
		for (int k = 0; k < 25; k++) {
			if (rowThirdNumber[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(160.0f + structureRight + col * (blockWidth / 2), 350.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 3) / 2, (blockHeight / 3) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(rowThirdNumber[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	if (size == 4) {
		for (int k = 0; k < 25; k++) {
			if (lS[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(80.0f + structureRight + col * (blockWidth / 2), 350.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 2) / 2, (blockHeight / 2) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(lS[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	if (size == 5) {
		for (int k = 0; k < 25; k++) {
			if (lW[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(0.0f + structureRight + col * (blockWidth / 2), 350.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 2) / 2, (blockHeight / 2) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(lW[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	if (size == 6) {
		for (int k = 0; k < 25; k++) {
			if (lO[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(-85.0f + structureRight + col * (blockWidth / 2), 350.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 2) / 2, (blockHeight / 2) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(lO[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	if (size == 7) {
		for (int k = 0; k < 25; k++) {
			if (lR[k] == blockNumber::NA) {
				/* no block in spot k */
				continue;
			}
			glm::mat4 model; /* model matrix */

			if (k > 4) {
				row = (k - 5) / 5; /* row of i */
				col = (k - 5) % 5; /* column of i */
			}
			else {
				row = -1;
				col = k;
			}
			glm::vec2 position = glm::vec2(-140.0f + structureRight + col * (blockWidth / 2), 350.0f + row * (blockHeight / 2)); /* calculate block position */

			/* move model to position */
			model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			/* scale model by block size */
			model = glm::scale(model, glm::vec3((blockWidth / 2) / 2, (blockHeight / 2) / 2, 1.0f));

			/* send model matrix to shader */
			glUniformMatrix4fv(shadersVarGame.model, 1, GL_FALSE, glm::value_ptr(model));

			/* find color of block */
			color number_col = number_to_color(lR[k]);
			/* send block color to shader */
			glUniform3f(shadersVarGame.color, number_col.r, number_col.g, number_col.b);

			/* draw block to screen */
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}

/* handle global key state */
static void handle_events()
{
	/* get any new keyboard events */
    glfwPollEvents(); 

    if (glfwWindowShouldClose(windowGame)) {
		runGame = false;
    }

    if (getKeyState.space) {
		/* execute action if pressed but not held */
		if (!getKeyState.space_pressed) {
	    	tetrominoGame->rotate();
	    	getKeyState.space_pressed = true;
        }
    }

	if (getKeyState.left) {
		tetrominoGame->move_left();
	}

	if (getKeyState.right) {
		tetrominoGame->move_right();
	}

    if (getKeyState.down) {
        speedTimeGame = 0.05; /* faster step time */
    }
    else {
		if (flagEasy) {
			speedTimeGame = levelEasyTime; /* stay with the selected level */
		}
		else if (flagMedium) {
			speedTimeGame = levelMediumTime; /* stay with the selected level */
		}
		else if (flagHard) {
			speedTimeGame = levelHardTime; /* stay with the selected level */
		}
    }

    if (getKeyState.up) {
		/* execute action if pressed but not held */
		if (!getKeyState.up_pressed) {
	    	tetrominoGame->blast();
	    	getKeyState.up_pressed = true;
		}
    }

	/* Level 1: Easy */
	if (getKeyState.one) {
		/* execute action if pressed but not held */
		if (!getKeyState.one_pressed) {
			speedTimeGame = levelEasyTime;
			getKeyState.one_pressed = true;
			flagEasy = true;
			flagMedium = false;
			flagHard = false;
		}
	}

	/* Level 2: Medium */
	if (getKeyState.two) {
		/* execute action if pressed but not held */
		if (!getKeyState.two_pressed) {
			speedTimeGame = levelMediumTime;
			getKeyState.two_pressed = true;
			flagEasy = false;
			flagMedium = true;
			flagHard = false;
		}
	}

	/* Level 3: Hard */
	if (getKeyState.three) {
		/* execute action if pressed but not held */
		if (!getKeyState.three_pressed) {
			speedTimeGame = levelHardTime;
			getKeyState.three_pressed = true;
			flagEasy = false;
			flagMedium = false;
			flagHard = true;
		}
	}
}

/* key callback function */
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	/* modify getKeyState */
    switch (key)
    {
		case GLFW_KEY_ESCAPE:
		{
			runGame = false;
			break;
		}
		case GLFW_KEY_SPACE:
		{
			if (action == GLFW_RELEASE) {
				getKeyState.space_pressed = false;
			}
			getKeyState.space = action;
			break;
		}
		case GLFW_KEY_LEFT:
		{
			getKeyState.left = action;
			break;
		}
		case GLFW_KEY_RIGHT:
		{
			getKeyState.right = action;
			break;
		}
		case GLFW_KEY_DOWN:
		{
			if (action == GLFW_RELEASE) {
				getKeyState.down_pressed = false;
			}
			getKeyState.down = action;
			break;
		}
		case GLFW_KEY_UP:
		{
			if (action == GLFW_RELEASE) {
				getKeyState.up_pressed = false;
			}
			getKeyState.up = action;
			break;
		}
		case GLFW_KEY_1:
		{
			if (action == GLFW_RELEASE) {
				getKeyState.one_pressed = false;
			}
			getKeyState.one = action;
			break;
		}
		case GLFW_KEY_2:
		{
			if (action == GLFW_RELEASE) {
				getKeyState.up_pressed = false;
			}
			getKeyState.two = action;
			break;
		}
		case GLFW_KEY_3:
		{
			if (action == GLFW_RELEASE) {
				getKeyState.three_pressed = false;
			}
			getKeyState.three = action;
			break;
		}
    }
}
