#pragma once
#include "Move.h"
#include "Board.h"

class AIPlayer
{
public:
    void MakeMove(Board board, bool* doneFlag, Move* result);
};