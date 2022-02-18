#include "Game.h"
#include "MoveGenerator.h"
#include "MoveValidator.h"
#include "AIPlayer.h"
#include <iostream>
#include <thread>

using namespace std;

Game::Game():
board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")
{
}

PieceType Game::GetPiece(int position)
{
	return board[position];
}

vector<int>& Game::GetWhitePieces()
{
	return board.whitePieces;
}

vector<int>& Game::GetBlackPieces()
{
	return board.blackPieces;
}

bool Game::MoveWasMade()
{
    return board.MoveCount() > 0;
}

Move& Game::GetLastMove()
{
	return board.GetLastMove();
}

void Game::Undo()
{
	board.UndoMove();
}

void Game::TryMakeMove(Move& move)
{
	//cout << "Asked to move from: " << move.from << " to: " << move.to << endl;
	if (!ValidateMove(board, move))
	{
		//cout << "Move invalid";
		return;
	}
	if (!IsMoveLegal(board, move))
	{
		//cout << "Move leaves king in check";
		return;
	}
	//cout << "Move valid" << endl;
	board.MakeMove(move);
	if (!IsMovePossible(board))
	{
		cout << "Game Over" << endl;
		gameOver = true;
		return;
	}

	if (!board.whiteToMove)
	{
		thread t(&AIPlayer::MakeMove, aiPlayer, board, &dirty, &awaitingAIMove);
		t.detach();
	}
	
}

void Game::Refresh()
{
    TryMakeMove(awaitingAIMove);
    dirty = false;
}