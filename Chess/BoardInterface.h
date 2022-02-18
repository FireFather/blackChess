#pragma once
#include <SFML/Graphics.hpp>

#include "SpriteSet.h"
#include "Board.h"
#include "Move.h"
#include "Piece.h"
#include "Game.h"
#include "PromoteWindow.h"


class BoardInterface
{
public:
	BoardInterface(sf::RenderWindow&);
	void OnClick(int x, int y);
	void Draw();
	void Undo();
private:
	void BoardInterface::DrawPiece(PieceType type, int boardPosition);
	int ScreenToBoard(int screenX, int screenY);
	void BoardToScreen(int board, int& x, int& y);

	Game game;
	int tileSize;
	static const int border = 50;
	int selectedPosition = -1;
	bool pendingPromote = false;
	int promoteTo;
	PromoteWindow promoteWindow;

	void DrawGizmo(int boardPosition);
	void DrawGizmo(int x, int y);

	sf::RenderWindow& window;
    SpriteSet spriteSet;
};
