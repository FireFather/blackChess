#include "Board.h"
#include "MoveValidator.h"
#include "PieceMoves.h"
#include <iostream>
#include <iomanip>

using namespace std;

unordered_map<char, PieceType> pieceChars{
    { 'p', B_PAWN },
    { 'n', B_KNIGHT },
    { 'b', B_BISHOP },
    { 'r', B_ROOK },
    { 'q', B_QUEEN },
    { 'k', B_KING },
    { 'P', W_PAWN },
    { 'N', W_KNIGHT },
    { 'B', W_BISHOP },
    { 'R', W_ROOK },
    { 'Q', W_QUEEN },
    { 'K', W_KING }
};

Board::Board(void) :
enPassant(-1),
turn(0),
whiteToMove(true),
kingDead(false)
{
    castleRights[W_KING] = INT_MAX;
    castleRights[W_QUEEN] = INT_MAX;
    castleRights[B_KING] = INT_MAX;
    castleRights[B_QUEEN] = INT_MAX;

    Place(W_ROOK, 0, 7);
    Place(W_ROOK, 7, 7);
    Place(W_KNIGHT, 1, 7);
    Place(W_KNIGHT, 6, 7);
    Place(W_BISHOP, 2, 7);
    Place(W_BISHOP, 5, 7);
    Place(W_QUEEN, 3, 7);
    Place(W_KING, 4, 7);

    Place(B_ROOK, 0, 0);
    Place(B_ROOK, 7, 0);
    Place(B_KNIGHT, 1, 0);
    Place(B_KNIGHT, 6, 0);
    Place(B_BISHOP, 2, 0);
    Place(B_BISHOP, 5, 0);
    Place(B_QUEEN, 3, 0);
    Place(B_KING, 4, 0);

    for (int i = 0; i < 8; i++)
    {
        Place(W_PAWN, i, 6);
        Place(B_PAWN, i, 1);
    }
}

Board::Board(string positionString) :
kingDead(false)

{
    castleRights[W_KING] = INT_MAX;
    castleRights[W_QUEEN] = INT_MAX;
    castleRights[B_KING] = INT_MAX;
    castleRights[B_QUEEN] = INT_MAX;

    int cursor = 0;

    int rank = 0;
    while (positionString[cursor] != ' ')
    {
        int file = 0;
        while (positionString[cursor] != '/')
        {
            char c = positionString[cursor];
            // Empty places
            if (c >= '1' && c <= '7')
            {
                file += (c - '1'); // Char to number conversion
            }
            else
            {
                Place(pieceChars[c], rank * 16 + file);
            }
            if (positionString[cursor + 1] == ' ') break;
            cursor++;
            file++;
        }
        cursor++;
        rank++;
    }
    cursor++;
    whiteToMove = positionString[cursor] == 'w';
    cursor += 2;

    while (positionString[cursor] != ' ')
    {
        switch (positionString[cursor])
        {
        case 'K':
            castleRights[W_KING] = INT_MAX;
            break;
        case 'Q':
            castleRights[W_QUEEN] = INT_MAX;
            break;
        case 'k':
            castleRights[B_KING] = INT_MAX;
            break;
        case 'q':
            castleRights[B_QUEEN] = INT_MAX;
            break;
        default:
            break;
        }
        cursor++;
    }
    cursor++;

    if (positionString[cursor] == '-')
    {
        enPassant = -1;
        cursor += 2;
    }
    else
    {
        int epFile = positionString[cursor] - 'a';
        int epRank = 8 - (positionString[cursor + 1] - '0');
        enPassant = epRank * 16 + epFile;
        Move fakeMove(enPassant + 16, enPassant - 16);
        moveHistory.push_back(fakeMove);
        fakeMove.isEnPassant = true;
        cursor += 3;
    }

    // TODO: Half-move clock
    while (positionString[cursor] != ' ')
    {
        cursor++;
    }
    cursor++;

    if (cursor == positionString.size() - 1)
    {
        turn = positionString[cursor] - '0';
    }
    else
    {
        turn = (positionString[cursor] - '0') * 10 + (positionString[cursor + 1] - '0');
    }
}

PieceType Board::operator[](int index)
{
#if DEBUG
    if (index & 0x88)
    {
        cout << "Debug: trying to access illegal position: " << index << endl;
        Print();
        throw exception();
    }
#endif
    return board[index];
}

int Board::FindKing(bool white)
{
    if (kingDead)
    {
        return -1;
    }
    vector<int>& tab = white ? whitePieces : blackPieces;
    PieceType lookingFor = white ? W_KING : B_KING;
    for (int position : tab)
    {
        if (board[position] == lookingFor)
        {
            //cout << "Found king at " << *it << endl;
            return position;
        }
    }
    Print();
    throw exception();
}

void Board::Place(PieceType type, int x, int y)
{
    Place(type, x + 16 * y);
}

void Board::Place(const PieceType type, int position)
{
    //cout << "Placing piece: " << type << " On position: " << position << endl;

    // Remove the piece that was previously there
    if (board[position] > 0)
    {
        for (auto it = whitePieces.begin(); it != whitePieces.end(); ++it)
        {
            if (*it == position)
            {
                whitePieces.erase(it);
                break;
            }
        }
    }
    else if (board[position] < 0)
    {
        for (auto it = blackPieces.begin(); it != blackPieces.end(); ++it)
        {
            if (*it == position)
            {
                blackPieces.erase(it);
                break;
            }
        }
    }

    // Place the new piece
    board[position] = type;
    if (type > 0)
    {
        whitePieces.push_back(position);
    }
    else if (type < 0)
    {
        blackPieces.push_back(position);
    }

    if (whitePieces.size() > 17 || blackPieces.size() > 17)
    {
        int a = 0;
    }
}

Move& Board::GetLastMove()
{
    return moveHistory.back();
}

void Board::MakeMove(Move move)
{
    move.capturedPiece = board[move.to];

    // This is not valid in normal play, but it helps the AI.
    if (move.capturedPiece == B_KING || move.capturedPiece == W_KING)
    {
        kingDead = true;
    }

    for (int i = 0; i < 4; i++)
    {
        castleMoves cInfo = castleTables[i];
        if (castleRights[cInfo.type] < turn) continue;

        if (move.from == cInfo.kingFrom || move.from == cInfo.rookFrom || move.to == cInfo.rookFrom)
        {
            castleRights[cInfo.type] = turn;
        }
    }

    if (move.castleInfo != NULL)
    {
        Place(move.castleInfo->rookType, move.castleInfo->rookTo);
        Place(EMPTY, move.castleInfo->rookFrom);
    }

    PieceType movingPiece = board[move.from];
    if (move.to == enPassant && (movingPiece == W_PAWN || movingPiece == B_PAWN))
    {
        move.isEnPassant = true;
        int epPawnPosition = move.to + 16 * (whiteToMove ? 1 : -1);
        Place(EMPTY, epPawnPosition);
    }

    if (move.isPawnDoublePush)
    {
        enPassant = (move.from + move.to) / 2;
    }
    else
    {
        enPassant = -1;
    }

    if (move.promoteTo != EMPTY)
    {
        Place(move.promoteTo, move.to);
    }
    else
    {
        Place(board[move.from], move.to);
    }

    Place(EMPTY, move.from);

    moveHistory.push_back(move);
    whiteToMove = !whiteToMove;
    turn++;
}

void Board::UndoMove()
{
    Move lastMove = moveHistory.back();
    whiteToMove = !whiteToMove;
    turn--;
    kingDead = false;

    // If castle rights were lost this turn, restore them.
    for (int i = 0; i < 4; i++)
    {
        castleMoves cInfo = castleTables[i];
        if (castleRights[cInfo.type] == turn)
        {
            castleRights[cInfo.type] = INT_MAX;
        }
    }

    // If it was a castle, undo the rook move.
    if (lastMove.castleInfo != NULL)
    {
        //cout << "Undoing castle" << endl;
        Place(lastMove.castleInfo->rookType, lastMove.castleInfo->rookFrom);
        Place(EMPTY, lastMove.castleInfo->rookTo);
    }

    PieceType movingPiece = board[lastMove.to];
    if (lastMove.promoteTo != EMPTY)
    {
        Place(whiteToMove ? W_PAWN : B_PAWN, lastMove.from);
    }
    else
    {
        Place(movingPiece, lastMove.from);
    }

    if (lastMove.isEnPassant)
    {
        Place((whiteToMove ? B_PAWN : W_PAWN), lastMove.to + 16 * (whiteToMove ? 1 : -1));
    }

    Place(lastMove.capturedPiece, lastMove.to);
    moveHistory.pop_back();
    if (moveHistory.size() != 0)
    {
        Move previousMove = moveHistory.back();
        enPassant = previousMove.isPawnDoublePush ? (previousMove.from + previousMove.to) / 2 : -1;
    }
}

void Board::Print()
{
    cout << "Board:" << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << setw(2) << board[j + 16 * i] << " ";
        }
        cout << endl;
    }
    cout << "enPassant position: " << enPassant << endl;
    cout << "Move history: " << endl;
    for (Move m : moveHistory)
    {
        cout << "From: " << m.from << " to: " << m.to << endl <<
            "captured: " << m.capturedPiece << endl <<
            "is enPassant: " << m.isEnPassant << endl << "--" << endl;
        if (m.castleInfo != NULL)
        {
            cout << "Move was a castle " << m.castleInfo->type << endl;
        }
    }

}

int Board::MoveCount()
{
    return moveHistory.size();
}