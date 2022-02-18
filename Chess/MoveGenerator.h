#pragma once
#include <vector>
#include "Board.h"

using namespace std;

bool IsMovePossible(Board& board);
void Generate(int position, Board& board, vector<Move>& result);
void GenerateAll(Board& board, vector<Move>& result);
