#pragma once
#include "SFML\Graphics.hpp"
#include "Piece.h"

class PromoteWindow
{
public:
	PromoteWindow();
	void Draw(sf::RenderWindow& window, float posX);
	PieceType OnClick(int x, int y);
private:
	sf::Texture tx_window;
	sf::Sprite windowSprite;
	float windowPosX;
	const float windowPosY = 100;
	const float pWindowW = 340;
	const float pWindowH = 85;
};

