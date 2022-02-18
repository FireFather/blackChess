#pragma once
#include <SFML/Graphics.hpp>

#include "Piece.h"

struct SpriteSet
{
    void Init();
    sf::Sprite& GetSprite(PieceType piece);

    sf::Sprite boardTexture;
    sf::Sprite highlightLastFrom;
    sf::Sprite highlightLastTo;
    sf::Sprite highlightPiece;
    sf::Sprite highlightMoveSuggestion;

    sf::Sprite wking;
    sf::Sprite wqueen;
    sf::Sprite wbishop;
    sf::Sprite wknight;
    sf::Sprite wrook;
    sf::Sprite wpawn;

    sf::Sprite bking;
    sf::Sprite bqueen;
    sf::Sprite bbishop;
    sf::Sprite bknight;
    sf::Sprite brook;
    sf::Sprite bpawn;

private:

    sf::Texture tx_boardTexture;
    sf::Texture tx_highlightlast;
    sf::Texture tx_highlight;

    sf::Texture tx_wking;
    sf::Texture tx_wqueen;
    sf::Texture tx_wbishop;
    sf::Texture tx_wknight;
    sf::Texture tx_wrook;
    sf::Texture tx_wpawn;

    sf::Texture tx_bking;
    sf::Texture tx_bqueen;
    sf::Texture tx_bbishop;
    sf::Texture tx_bknight;
    sf::Texture tx_brook;
    sf::Texture tx_bpawn;
};

