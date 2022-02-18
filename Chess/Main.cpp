#include "BoardInterface.h"
#include <SFML/Graphics.hpp>
#include "Test.h"
#include <iostream>

using namespace std;

void  test()
{
	Test t;
	clock_t begin = clock();
	t.GeneratorTest();
	//t.TestMoveMaking();
	clock_t end = clock();
	std::cout << "Time: " << double(end - begin) / CLOCKS_PER_SEC << std::endl;
}

void sizes()
{
	cout << "Board: " << sizeof(Board) << endl;
	cout << "Move: " << sizeof(Move) << endl;
}

int main()
{
	//test();
	//sizes();
	sf::RenderWindow window(sf::VideoMode(700, 700), "Chess", sf::Style::Close);
	window.setFramerateLimit(30);
	BoardInterface boardInterface(window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				boardInterface.OnClick(event.mouseButton.x, event.mouseButton.y);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
			{
				boardInterface.Undo();
			}
		}

		window.clear();
		boardInterface.Draw();
		window.display();
	}

	return 0;
}