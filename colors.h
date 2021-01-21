#ifndef COLORS_H
#define COLORS_H

/* block types (NA is "empty") */
enum class blockType {NA, I, O, T, Z, S, J, L };

/* different colors blocks can be */
enum class tetrominoColor {LIME_GREEN, GOLD, DEEP_PINK, CRIMSON, CYAN, DARKVIOLET, ORANGE_RED };

/* colors used for other things */
enum class groundColor {BACKGROUND, MATRIX, WHITE, CYAN, STEEL_BLUE };

/* block numbers */
enum class blockNumber {NA, N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, LR, LO, LW, LS };

/* stores rgb data */
struct color {
    float r; /* red val */
    float g; /* green val */
    float b; /* blue val */
};

/* function declarations */
extern color type_to_color(blockType);
extern color number_to_color(blockNumber);
extern color get_block_color(tetrominoColor);
extern color get_other_color(groundColor);

/* get color for a specific block type */
static color type_to_color(blockType bt)
{
   switch (bt)
   {
		case blockType::NA:
		{
			return get_other_color(groundColor::BACKGROUND);
			break;
		}
		case blockType::I:
		{
			return get_block_color(tetrominoColor::LIME_GREEN);
			break;
		}
		case blockType::O:
		{
			return get_block_color(tetrominoColor::GOLD);
			break;
		}
		case blockType::T:
		{
			return get_block_color(tetrominoColor::DEEP_PINK);
			break;
		}
		case blockType::Z:
		{
			return get_block_color(tetrominoColor::CRIMSON);
			break;
		}
		case blockType::S:
		{
			return get_block_color(tetrominoColor::CYAN);
			break;
		}
		case blockType::J:
		{
			return get_block_color(tetrominoColor::DARKVIOLET);
			break;
		}
		case blockType::L:
		{
			return get_block_color(tetrominoColor::ORANGE_RED);
			break;
		}
		default:
		{
			return get_block_color(tetrominoColor(-1));
			break;
		}
   }
}

/* get color for a specific block number */
static color number_to_color(blockNumber bn)
{
	switch (bn)
	{
		case blockNumber::NA:
		{
			return get_other_color(groundColor::BACKGROUND);
			break;
		}
		case blockNumber::N0:
		{
			return get_other_color(groundColor::WHITE);
			break;
		}
		case blockNumber::N1:
		{
			return get_other_color(groundColor::WHITE);
			break;
		}
		case blockNumber::N2:
		{
			return get_other_color(groundColor::WHITE);
			break;
		}
		case blockNumber::N3:
		{
			return get_other_color(groundColor::WHITE);
			break;
		}
		case blockNumber::N4:
		{
			return get_other_color(groundColor::WHITE);
			break;
		}
		case blockNumber::N5:
		{
			return get_other_color(groundColor::WHITE);
			break;
		}
		case blockNumber::N6:
		{
			return get_other_color(groundColor::WHITE);
			break;
		}
		case blockNumber::N7:
		{
			return get_other_color(groundColor::WHITE);
			break;
		}
		case blockNumber::N8:
		{
			return get_other_color(groundColor::WHITE);
			break;
		}
		case blockNumber::N9:
		{
			return get_other_color(groundColor::WHITE);
			break;
		}
		case blockNumber::LR:
		{
			return get_other_color(groundColor::STEEL_BLUE);
			break;
		}
		case blockNumber::LO:
		{
			return get_other_color(groundColor::STEEL_BLUE);
			break;
		}
		case blockNumber::LW:
		{
			return get_other_color(groundColor::STEEL_BLUE);
			break;
		}
		case blockNumber::LS:
		{
			return get_other_color(groundColor::STEEL_BLUE);
			break;
		}
		default:
		{
			return get_other_color(groundColor(-1));
			break;
		}
	}
}

/* get color struct from a block color */
static color get_block_color(tetrominoColor tc)
{
    color colorVertex;
    switch (tc)
    {
		case tetrominoColor::LIME_GREEN:
		{
			colorVertex.r = float(50)/255;
			colorVertex.g = float(205)/255;
			colorVertex.b = float(50)/255; 
			break;
		}
		case tetrominoColor::GOLD:
		{
			colorVertex.r = float(255)/255;
			colorVertex.g = float(215)/255;
			colorVertex.b = float(0)/255; 
			break;
		}
		case tetrominoColor::DEEP_PINK:
		{
			colorVertex.r = float(255)/255;
			colorVertex.g = float(20)/255;
			colorVertex.b = float(147)/255; 
			break;
		}
		case tetrominoColor::CRIMSON:
		{
			colorVertex.r = float(220)/255;
			colorVertex.g = float(20)/255;
			colorVertex.b = float(60)/255; 
			break;
		}
		case tetrominoColor::CYAN:
		{
			colorVertex.r = float(0)/255;
			colorVertex.g = float(255)/255;
			colorVertex.b = float(255)/255; 
			break;
		}
		case tetrominoColor::DARKVIOLET:
		{
			colorVertex.r = float(148)/255;
			colorVertex.g = float(0)/255;
			colorVertex.b = float(211)/255; 
			break;
		}
		case tetrominoColor::ORANGE_RED:
		{
			colorVertex.r = float(255)/255;
			colorVertex.g = float(69)/255;
			colorVertex.b = float(0)/255; 
			break;
		}
		default:
		{
			colorVertex.r = -1.0f;
			colorVertex.g = -1.0f;
			colorVertex.b = -1.0f;
			break;
		}
    }
    return colorVertex;
}

/* get color struct from "other" color */
static color get_other_color(groundColor gc)
{
    color colorVertex;
    switch (gc)
    {
		case groundColor::BACKGROUND:
		{
			colorVertex.r = float(28)/255;
			colorVertex.g = float(28)/255;
			colorVertex.b = float(28)/255; 
			break;
		}
		case groundColor::MATRIX:
		{
			colorVertex.r = float(128)/255;
			colorVertex.g = float(128)/255;
			colorVertex.b = float(128)/255; 
			break;
		}
		case groundColor::WHITE:
		{
			colorVertex.r = float(255)/255;
			colorVertex.g = float(255)/255;
			colorVertex.b = float(255)/255;
			break;
		}
		case groundColor::STEEL_BLUE:
		{
			colorVertex.r = float(70)/255;
			colorVertex.g = float(130)/255;
			colorVertex.b = float(180)/255;
			break;
		}
		default:
		{
			colorVertex.r = -1.0f;
			colorVertex.g = -1.0f;
			colorVertex.b = -1.0f;
			break;
		}
    }
    return colorVertex;
}

#endif