#pragma once
#include "Piece.h"
#include "PieceMoves.h"
struct Move
{
public:
	Move();
	Move(int _from, int _to);
	short int from;
	short int to;

	castleMoves* castleInfo = nullptr;

	PieceType capturedPiece;
	PieceType promoteTo = EMPTY;
	short int enPassantPosition;
	bool isPawnDoublePush;
	bool isEnPassant;
};
