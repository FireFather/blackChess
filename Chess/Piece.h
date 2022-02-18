#pragma once

enum PieceType : char
{
	EMPTY = 0,

	W_KING = 6,
	W_QUEEN = 5,
	W_BISHOP = 4,
	W_KNIGHT = 3,
	W_ROOK = 2,
	W_PAWN = 1,

	B_KING = -6,
	B_QUEEN = -5,
	B_BISHOP = -4,
	B_KNIGHT = -3,
	B_ROOK = -2,
	B_PAWN = -1
};
