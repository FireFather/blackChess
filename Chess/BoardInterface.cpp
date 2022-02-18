#include "BoardInterface.h"
#include <vector>

using namespace std;

void BoardInterface::DrawGizmo(int boardPosition)
{
	int x, y;
	BoardToScreen(boardPosition, x, y);
	DrawGizmo(x, y);
}

void BoardInterface::DrawGizmo(int x, int y)
{
	static sf::CircleShape shape(25);
	shape.setFillColor(sf::Color(100, 250, 50));
	shape.setPosition(static_cast<float>(x), static_cast<float>(y));
	window.draw(shape);
}

BoardInterface::BoardInterface(sf::RenderWindow& _window) :
game(),
window(_window)
{
	sf::Vector2u size = window.getSize();
	tileSize = (min(size.x, size.y) - 2 * border) / 8;
    spriteSet.Init();
}

void BoardInterface::Undo()
{
	game.Undo();
	game.Undo();
}

void BoardInterface::OnClick(int x, int y)
{
	if (!game.board.whiteToMove)
	{
		return;
	}

	if (pendingPromote)
	{
		PieceType p = promoteWindow.OnClick(x, y);
		if (p != EMPTY)
		{
			//cout << "Promotion to: " << p << endl;
			Move move(selectedPosition, promoteTo);
			move.promoteTo = p;

			game.TryMakeMove(move);
			pendingPromote = false;
			selectedPosition = -1;
			return;
		}
	}

	int clickedPosition = ScreenToBoard(x, y);
	if (clickedPosition & 0x88)
		return; // clicked outside of the board

	PieceType clickedType = game.GetPiece(clickedPosition);

	if (selectedPosition == -1 && clickedType <= 0)
	{
		return;
	}
    if (selectedPosition == -1 && clickedType > 0)
    {
        //cout << "Selected was NULL, selecting: " << clickedPosition << endl;
        selectedPosition = clickedPosition;
        return;
    }
    if (selectedPosition == clickedPosition)
    {
        //cout << "Canceling selection" << endl;
        selectedPosition = -1;
        return;
    }
    if (game.GetPiece(selectedPosition) == W_PAWN && clickedPosition / 16 == 0)
    {
        pendingPromote = true;
        promoteTo = clickedPosition;
    }
    else
    {
        //cout << "Trying to move from: " << selectedPosition << " to: " << clickedPosition << endl;
        Move move(selectedPosition, clickedPosition);

        game.TryMakeMove(move);
        selectedPosition = -1;
    }
}

void BoardInterface::Draw()
{
    window.draw(spriteSet.boardTexture);

    if (game.dirty)
    {
        game.Refresh();
    }

    // Draw last move if we are not at move 0
    if (game.MoveWasMade())
    {
        Move lastMove = game.GetLastMove();
        int fromX, fromY, toX, toY;
        BoardToScreen(lastMove.from, fromX, fromY);
        BoardToScreen(lastMove.to, toX, toY);
        spriteSet.highlightLastFrom.setPosition(static_cast<float>(fromX), static_cast<float>(fromY));
        spriteSet.highlightLastTo.setPosition(static_cast<float>(toX), static_cast<float>(toY));
        window.draw(spriteSet.highlightLastFrom);
        window.draw(spriteSet.highlightLastTo);
	}

    // Draw move suggestion if a piece was selected
	if (selectedPosition != -1)
	{
        sf::Vector2i position = sf::Mouse::getPosition(window);
        int mouseX = position.x - (position.x - border) % tileSize;
        int mouseY = position.y - (position.y - border) % tileSize;
        if (border <= position.x && position.x < window.getSize().x - border && border <= position.y && position.y < window.getSize().y - border)
        {
            spriteSet.highlightMoveSuggestion.setPosition(static_cast<float>(mouseX), static_cast<float>(mouseY));
            window.draw(spriteSet.highlightMoveSuggestion);
        }

        int selectedX, selectedY;
        BoardToScreen(selectedPosition, selectedX, selectedY);
        spriteSet.highlightPiece.setPosition(static_cast<float>(selectedX), static_cast<float>(selectedY));

        window.draw(spriteSet.highlightPiece);
	}

	vector<int>& whitePieces = game.GetWhitePieces();
	for (int pos: whitePieces)
	{
		DrawPiece(game.GetPiece(pos), pos);
	}

	vector<int>& blackPieces = game.GetBlackPieces();
	for (int pos : blackPieces)
	{
		DrawPiece(game.GetPiece(pos), pos);
	}

	if (pendingPromote)
	{
		promoteWindow.Draw(window, static_cast<float>(selectedPosition * tileSize) + 0.5f);
	}
}

void BoardInterface::DrawPiece(PieceType type, int boardPosition)
{
	if (type == EMPTY)
		return;
	int delta = 5;

	int pieceX;
	int pieceY;
	BoardToScreen(boardPosition, pieceX, pieceY);

	sf::Sprite sprite = spriteSet.GetSprite(type);
	sprite.setPosition(static_cast<float>(pieceX + delta), static_cast<float>(pieceY + delta));
	window.draw(sprite);
}

void BoardInterface::BoardToScreen(int boardPosition, int& x, int& y)
{
	x = boardPosition % 16 * tileSize + border;
	y = boardPosition / 16 * tileSize + border;
}

int BoardInterface::ScreenToBoard(int x, int y)
{
	return  (y - border) / tileSize * 16 + (x - border) / tileSize;
}