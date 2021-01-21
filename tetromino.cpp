#include "tetris.h"
#include "tetromino.h"

extern blockType structureGame[200];
extern blockType nextStructureGame[16];
/* ------------------------ tetromino orientations ------------------------ */
/* I */
const int I_0[16] = {
	0, 0, 0, 0,
	1, 1, 1, 1,
	0, 0, 0, 0,
	0, 0, 0, 0
};
const int I_1[16] = {
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0
};

/* O (square) */
const int O_0[4] = {
	2, 2,
	2, 2
};

/* T */
const int T_0[9] = {
	0, 0, 0,
	3, 3, 3,
	0, 3, 0
};
const int T_1[9] = {
	0, 3, 0,
	3, 3, 0,
	0, 3, 0
};
const int T_2[9] = {
	0, 3, 0,
	3, 3, 3,
	0, 0, 0
};
const int T_3[9] = {
	0, 3, 0,
	0, 3, 3,
	0, 3, 0
};

/* Z */
const int Z_0[9] = {
	0, 0, 0,
	4, 4, 0,
	0, 4, 4
};
const int Z_1[9] = {
	0, 0, 4,
	0, 4, 4,
	0, 4, 0
};

/* S */
const int S_0[9] = {
	0, 0, 0,
	0, 5, 5,
	5, 5, 0
};
const int S_1[9] = {
	5, 0, 0,
	5, 5, 0,
	0, 5, 0
};

/* J */
const int J_0[9] = {
	0, 0, 0,
	6, 6, 6,
	0, 0, 6
};
const int J_1[9] = {
	0, 6, 0,
	0, 6, 0,
	6, 6, 0
};
const int J_2[9] = {
	6, 0, 0,
	6, 6, 6,
	0, 0, 0
};
const int J_3[9] = {
	0, 6, 6,
	0, 6, 0,
	0, 6, 0
};

/* L */
const int L_0[9] = {
	0, 0, 0,
	7, 7, 7,
	7, 0, 0
};
const int L_1[9] = {
	7, 7, 0,
	0, 7, 0,
	0, 7, 0
};
const int L_2[9] = {
	0, 0, 7,
	7, 7, 7,
	0, 0, 0
};
const int L_3[9] = {
	0, 7, 0,
	0, 7, 0,
	0, 7, 7
};
/* ------------------------------------------------------------------------ */

/* clear tetromino to empty vales */
void tetromino::clear()
{
	type = blockType::NA;
	structureLocal = NULL;
	structureSize = 0;
	structureDoubleSize = 0;
	orientations = 0;
	direction = 0;
	centerTetromino = 0;
	structureX = 0;
	structureY = 0;
	drawn = false;
	drawnNext = false;
	bottom = false;
	locked = false;
}

/* initialize tetro to specific block type */
void tetromino::init(blockType bType)
{
	if (bType == blockType::NA) {
		return;
	}
	
    type = bType;
    structureSize = 3;
	structureDoubleSize = 9;
	centerTetromino = 1;
    direction = 0;
    structureX = 4;
    structureY = 0;
    drawn = false;
	drawnNext = false;
    locked = false;
    bottom = false;
	structureLocal = get_local_structure(type, direction);

	/* initialize block type specfic members */
    switch (type)
    {
		case blockType::I:
		{
			structureSize = 4;
			structureDoubleSize = 16;
			orientations = 2;
			structureY = 1;
			break;
		}
		case blockType::O:
		{
			structureSize = 2;
			structureDoubleSize = 4;
			orientations = 1;
			centerTetromino = 0;
			break;
		}
		case blockType::T:
		{
			orientations = 4;
			break;
		}
		case blockType::Z:
		{
			orientations = 2;
			break;
		}
		case blockType::S:
		{
			orientations = 2;
			break;
		}
		case blockType::J:
		{
			orientations = 4;
			break;
		}
		case blockType::L:
		{
			orientations = 4;
			break;
		}
    }

	if (!valid()) {
		terminate_program_GO();
	}
}

/* if drawn, erase tetromino from structure */
void tetromino::erase()
{
	if (!drawn) {
		/* return if already erased */
		return;
	}

    int top = structureY - centerTetromino;
    int left = structureX - centerTetromino;

	/* take tetromino off structure */
    for (int i = 0; i < structureDoubleSize; i++) {
		if (structureLocal[i] != 0) {
			/* reset spot in the Game Structure to empty */
			structureGame[(top+i/structureSize)*10 + (left+i%structureSize)] = blockType::NA;
		}
    }
    drawn = false;
}

/* if not drawn, draw tetromino onto structure */
void tetromino::draw()
{
	if (drawn) {
		/* return if already drawn */
		return;
	}

    int top = structureY - centerTetromino;
    int left = structureX - centerTetromino;

	/* draw tetromino onto structure */
    for (int i = 0; i < structureDoubleSize; i++) {
		if (structureLocal[i] != 0) {
			/* draw structureLocal[i] onto the Game Structure */
			structureGame[(top + i / structureSize) * 10 + (left + i % structureSize)] = (blockType)structureLocal[i];
		}
    }
    drawn = true;
}

/* if not drawn, draw tetromino onto structure */
void tetromino::drawNext()
{
	if (drawnNext) {
		/* return if already drawn */
		return;
	}

	int top = structureY - centerTetromino;
	int left = structureX - centerTetromino;

	/* draw tetromino onto structure */
	for (int i = 0; i < structureDoubleSize; i++) {
		if (structureLocal[i] != 0) {
			/* correction for Tetromino I */
			if (structureDoubleSize == 16) {
				nextStructureGame[i] = (blockType)structureLocal[i];
			}
			/* correction for Tetromino S */
			else if (structureLocal[i] == 5) {
				if (i < 6) {
					nextStructureGame[i + 1] = (blockType)structureLocal[i];
				}
				else {
					nextStructureGame[i + 2] = (blockType)structureLocal[i];
				}
			}
			/* correction for Tetromino L */
			else if (structureLocal[i] == 7) {
				if (i < 6) {
					nextStructureGame[i + 1] = (blockType)structureLocal[i];
				}
				else {
					nextStructureGame[i + 2] = (blockType)structureLocal[i];
				}
			}
			/* draw structureLocal[i] onto the next Game Structure */
			else {
				nextStructureGame[(top + i / structureSize) * 4 + (left + i % structureSize)] = (blockType)structureLocal[i];
			}
			
		}
	}
	drawnNext = true;
}

/* check if tetromino is valid on structure */
bool tetromino::valid()
{
	if (drawn) {
		return true;
	}

    int top = structureY - centerTetromino;
    int left = structureX - centerTetromino;

	/* loop through local structure */
    for (int i = 0; i < structureDoubleSize; i++) {
		/* only check filled spots in local structure */
		if (structureLocal[i] != 0) {
			int y = top + i / structureSize;
			int x = left + i % structureSize;

			/* check if out of Game Structure */
			if (x < 0 || x > 9 || y < 0 || y > 19) {
				return false;
			}
			/* check if conflicts with Game Structure */
			if (structureGame[y * 10 + x] != blockType::NA) {
				return false;
			}
		}
    }
    return true;
}

/* rotate tetromino clock-wise */
void tetromino::rotate()
{
	if (locked) {
		/* ignore if locked */
		return;
	}

    erase();
    const int *prev_grid = structureLocal;
    int new_dir = (direction + 1) % orientations;
	structureLocal = get_local_structure(type, new_dir);
	
	/* check if new rotated tetro is valid */
    if (!valid()) {
		/* save old structure's x and y */
		int old_grid_x = structureX;
		int old_grid_y = structureY;

		/* check if one spot to left is valid */
		{
			structureX -= 1;
			if (valid()) {
				direction = new_dir;
				draw();
				return;
			}
			structureX = old_grid_x;
		}

		/* check if one spot to right is valid */
		{
			structureX += 1;
			if (valid()) {
				direction = new_dir;
				draw();
				return;
			}
			structureX = old_grid_x;
		}

		//otherwise erase and reset to prev structure
		erase();
		structureLocal = prev_grid;
		draw();
		return;
    }

    bottom = false;
    direction = new_dir;
    draw();
}

/* move tetromino one space left */
void tetromino::move_left()
{
	if (locked) {
		/* ignore if locked */
		return;
	}

    erase();
    structureX--;

	/* check if not valid to move left */
    if (!valid()) {
		structureX++; /* move back to old spot */
		draw();
		return;
    }

    bottom = false;
    draw();
}

/* move tetromino one space right */
void tetromino::move_right()
{
	if (locked) {
		/* ignore if locked */
		return;
	}

    erase();
    structureX++;

	/* check if not valid to move right */
    if (!valid()) {
		structureX--; /* move back to old spot */
		draw();
		return;
    }

    bottom = false;
    draw();
}

/* move tetromino one space down */
void tetromino::move_down()
{
	if (locked) {
		/* ignore if locked */
		return;
	}

    erase();
    structureY++;
	
	/* check if tetro is hitting bottom */
    if (!valid()) {
		structureY--;
		if (bottom == true) {
			locked = true;
		}
		bottom = true;
    }

    draw();
}

/* move tetromino down until floor, lock in place */
void tetromino::blast()
{
	if (locked) {
		/* ignore if locked */
		return;
	}
	
    erase();

	/* move to bottom */
    while (!bottom) {
		move_down();
    }

    draw();
    locked = true;
}

/* find new local structure from specifc type and direction */ 
const int *get_local_structure(blockType bType, int newOrientation)
{
	if (bType == blockType::NA) {
		return NULL;
	}
	switch (bType)
    {
		case blockType::I:
		{
			if (newOrientation == 0) {
				return I_0;
			}
			if (newOrientation == 1) {
				return I_1;
			}
			break;
		}
		case blockType::O:
		{
			return O_0;
			break;
		}
		case blockType::T:
		{
			if (newOrientation == 0) {
				return T_0;
			}
			if (newOrientation == 1) {
				return T_1;
			}
			if (newOrientation == 2) {
				return T_2;
			}
			if (newOrientation == 3) {
				return T_3;
			}
			break;
		}
		case blockType::Z:
		{
			if (newOrientation == 0) {
				return Z_0;
			}
			if (newOrientation == 1) {
				return Z_1;
			}
			break;
		}
		case blockType::S:
		{
			if (newOrientation == 0) {
				return S_0;
			}
			if (newOrientation == 1) {
				return S_1;
			}
			break;
		}
		case blockType::J:
		{
			if (newOrientation == 0) {
				return J_0;
			}
			if (newOrientation == 1) {
				return J_1;
			}
			if (newOrientation == 2) {
				return J_2;
			}
			if (newOrientation == 3) {
				return J_3;
			}
			break;
		}
		case blockType::L:
		{
			if (newOrientation == 0) {
				return L_0;
			}
			if (newOrientation == 1) {
				return L_1;
			}
			if (newOrientation == 2) {
				return L_2;
			}
			if (newOrientation == 3) {
				return L_3;
			}
			break;
		}
    }
	return NULL;
}
