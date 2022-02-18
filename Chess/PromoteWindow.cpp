#include "PromoteWindow.h"

PromoteWindow::PromoteWindow()
{
	tx_window.loadFromFile("img/PromoteWindow.png");
	windowSprite.setTexture(tx_window);

}

void PromoteWindow::Draw(sf::RenderWindow& window, float posX)
{
	sf::Vector2u windowSize = window.getSize();
	float sizeX = static_cast<float>(windowSize.x);
	if (posX > sizeX + pWindowW / 2)
	{
		windowPosX = sizeX - pWindowW;
	}
	else if (posX < pWindowW / 2)
	{
		windowPosX = 0;
	}
	else
	{
		windowPosX = posX - pWindowW / 2;
	}

	windowSprite.setPosition(windowPosX, windowPosY);
	window.draw(windowSprite);
}


PieceType PromoteWindow::OnClick(int x, int y)
{
	if (y < windowPosY || y > windowPosY + pWindowH)
	{
		return EMPTY;
	}
	return static_cast<PieceType>(((x - (int)windowPosX) / 85) + 2);
}