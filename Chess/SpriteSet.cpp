#include "SpriteSet.h"


 void SpriteSet::Init()
{
    if (!(
        tx_boardTexture.loadFromFile("img/board.png") &&
        tx_highlightlast.loadFromFile("img/highlightlast.png") &&
        tx_highlight.loadFromFile("img/highlight.png") &&

        tx_wking.loadFromFile("img/wking.png") &&
        tx_wqueen.loadFromFile("img/wqueen.png") &&
        tx_wbishop.loadFromFile("img/wbishop.png") &&
        tx_wknight.loadFromFile("img/wknight.png") &&
        tx_wrook.loadFromFile("img/wrook.png") &&
        tx_wpawn.loadFromFile("img/wpawn.png") &&

        tx_bking.loadFromFile("img/bking.png") &&
        tx_bqueen.loadFromFile("img/bqueen.png") &&
        tx_bbishop.loadFromFile("img/bbishop.png") &&
        tx_bknight.loadFromFile("img/bknight.png") &&
        tx_brook.loadFromFile("img/brook.png") &&
        tx_bpawn.loadFromFile("img/bpawn.png")
        ))
    {
        fprintf(stderr, "Failed to load images");
    }

    boardTexture.setTexture(tx_boardTexture);
    highlightLastFrom.setTexture(tx_highlightlast);
    highlightLastTo.setTexture(tx_highlightlast);
    highlightPiece.setTexture(tx_highlight);
    highlightMoveSuggestion.setTexture(tx_highlight);

    wking.setTexture(tx_wking);
    wqueen.setTexture(tx_wqueen);
    wbishop.setTexture(tx_wbishop);
    wknight.setTexture(tx_wknight);
    wrook.setTexture(tx_wrook);
    wpawn.setTexture(tx_wpawn);

    bking.setTexture(tx_bking);
    bqueen.setTexture(tx_bqueen);
    bbishop.setTexture(tx_bbishop);
    bknight.setTexture(tx_bknight);
    brook.setTexture(tx_brook);
    bpawn.setTexture(tx_bpawn);
}


 sf::Sprite& SpriteSet::GetSprite(PieceType piece)
 {
     switch (piece)
     {
     case B_BISHOP:
         return bbishop;
     case B_KING:
         return bking;
     case B_KNIGHT:
         return bknight;
     case B_PAWN:
         return bpawn;
     case B_QUEEN:
         return bqueen;
     case B_ROOK:
         return brook;
     case W_BISHOP:
         return wbishop;
     case W_KING:
         return wking;
     case W_KNIGHT:
         return wknight;
     case W_PAWN:
         return wpawn;
     case W_QUEEN:
         return wqueen;
     case W_ROOK:
         return wrook;
     default:
         break;
     }
     // this is an error
     return bking;
 }