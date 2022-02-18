#include "Board.h"
#include "Move.h"

bool ValidateMove(Board& board, Move& move);
bool ValidateCastle(Board& board, Move& move);
bool IsAttacked(Board& board, int position, bool byBlack);
bool IsMoveLegal(Board& board, Move& move);