#include "colors.h"
#ifndef TETROMINO_H 
#define TETROMINO_H

struct tetromino {
    blockType type;
    const int *structureLocal; /* storage of tetromino blocks */
    int structureSize; /* will be 2 (O), 3(T,Z,S,J,L), or 4(I) */
    int structureDoubleSize; /* will be 4 (O), 9(T,Z,S,J,L), or 16(I) */
    int orientations; /* number of diff directions of tetromino */
    int direction; /* current direction */
	int centerTetromino; /* centerTetromino of local structure */
    int structureX; /* x coord of tetro on Game Structure */
    int structureY; /* y coord of tetro on Game Structure */
    bool drawn; /* true if drawn currently on structureGame */
    bool drawnNext; /* true if drawn currently on nextStructureGame */
    bool bottom; /* touching blocks below */
    bool locked; /* locked in place, no further movement */
	
    // methods
	void clear();
    void init(blockType);
    void draw();
    void drawNext();
    void erase();
    bool valid();
    void rotate();
    void move_left();
    void move_right();
    void move_down();
    void blast();
};

/* function declarations */
extern const int *get_local_structure(blockType, int );

#endif
