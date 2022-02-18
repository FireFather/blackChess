#pragma once
#include <vector>

#include "Board.h"
#include "Move.h"
#include "AIPlayer.h"

class Game
{
public:
	Game();
	void TryMakeMove(Move& move);
	void Undo();
    void Refresh();
    PieceType GetPiece(int position);
	std::vector<int>& GetWhitePieces();
	std::vector<int>& GetBlackPieces();
    bool MoveWasMade();
	Move& GetLastMove();

    bool dirty = false;
    Move awaitingAIMove;

	bool gameOver = false;
	Board board;
    AIPlayer aiPlayer;
};
