#include "Test.h"
#include "Board.h"
#include "MoveGenerator.h"
#include <iostream>
#include <vector>
#include "MoveValidator.h"

string positionToString(int pos)
{
	string res = "  ";
	res[0] = (pos % 16) + 'a';
	res[1] = (8 - pos / 16) + '0';
	return res;
}

int countPossibilities(Board& b, int depth, bool printPartial = false)
{
	int poss = 0;
	vector<Move> possibleMoves;
	possibleMoves.reserve(100);
	GenerateAll(b, possibleMoves);
	if (depth == 0)
	{
		for (Move move : possibleMoves)
		{
			if (IsMoveLegal(b, move))
			{
				poss++;
			}
		}
	}
	else
	{
		for (Move move : possibleMoves)
		{
			if (IsMoveLegal(b, move))
			{
				b.MakeMove(move);
				//cout << endl << "Move from " << movePtr->from << " to " << movePtr->to << endl;
				//b.Print();
				int possibilities = countPossibilities(b, depth - 1);
				if (printPartial)
				{
					cout << "Partial perft after move " << positionToString(move.from) << " to " << positionToString(move.to) << " : " << possibilities << endl;
				}
				poss += possibilities;
				b.UndoMove();
			}
		}
	}
	return poss;
}

void Test::GeneratorTest()
{
	Board b;
	cout << "Starting board: " << endl;
	//Move testMove(7, 55);
	//testMove.isPawnDoublePush = true;
	//b.MakeMove(testMove);
	//Move testMove2(102, 70);
	//testMove2.isPawnDoublePush = true;
	//b.MakeMove(testMove2);
	//Move testMove3(71, 86);
	//b.MakeMove(testMove3);
	b.Print();
	cout << "Testing Move generator" << endl;

	int depth = 4;
	cout << "Depth: " << depth << " Possibilities: " << countPossibilities(b, depth, true) << endl;

}

void Test::TestMoveMaking()
{
	Board b("r3k2r/p1ppqpb1/bn1Ppnp1/4N3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b KQkq - 0 1");
	Move m(7, 23);
	b.MakeMove(m);
	b.Print();
}