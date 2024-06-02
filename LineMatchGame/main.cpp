#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

sf::Vector2f getPixelPosition(const sf::Vector2i& pos, const sf::Vector2u& blockSize) {
	return sf::Vector2f(float(pos.x * blockSize.x), float(pos.y * blockSize.y));
}


int main() {

	const int fieldWidth = 6;
	const int fieldHeight = 10;

	bool field[fieldWidth][fieldHeight] = {};
	// Set barrier randomly in the begining
	for (int y = 3; y < fieldHeight; y++) {
		// Threee barriers in a row starting from 4th row
		for (int k = 1; k <= 3; k++) {
			field[rand() % fieldWidth][y] = true;
		}
	}

	// [F, F, F, F, F, F]
	// [F, F, F, F, F, F]
	// [F, F, F, F, F, F]
	// [F, F, F, F, F, F]
	// [F, F, F, F, F, F]
	// [F, F, F, F, F, F]
	// [F, F, F, F, F, F]
	// [F, F, F, F, F, F]
	// [F, F, F, F, F, F]
	// [F, F, F, F, F, F]
	// [F, F, F, F, F, F]
	// block.png
	sf::Texture blockTexture;
	blockTexture.loadFromFile("block.png");
	sf::Vector2u blockSize(blockTexture.getSize());

	const int windowWidth = blockSize.x * fieldWidth;
	const int windowHeight = blockSize.y * fieldHeight;
	sf::String title(L"簡易消行遊戲");

	sf::VideoMode mode(windowWidth, windowHeight);
	sf::RenderWindow window(mode, title);

	sf::Sprite block(blockTexture);

	// Add position of block
	// Initial Position
	
	sf::Vector2i origin(fieldWidth / 2, 0);
	sf::Vector2i pos(origin);


	// block.setPosition(float(pos.x * blockSize.x), float(pos.y * blockSize.y));
	block.setPosition(getPixelPosition(pos,blockSize));

	// Add clock
	sf::Clock clock;

	while (window.isOpen()) {
		
		enum class Action {Hold, MoveLeft, MoveRight, MoveDown};

		Action action = Action::Hold;
		
		sf::Event evt;

		if (window.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				window.close();
			}

		if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Left) {
					// pos.x--;
					action = Action::MoveLeft;
				}
				if (evt.key.code == sf::Keyboard::Right) {
					// pos.x++;
					action = Action::MoveRight;
				}
				if (evt.key.code == sf::Keyboard::Down) {
					// pos.x++;
					action = Action::MoveDown;
				}
			
		 }

		}
		if (clock.getElapsedTime().asSeconds() >= 0.5f) {
			action = Action::MoveDown;
			// pos.y++;
			// block.setPosition(getPixelPosition(pos, blockSize));
			clock.restart();
		}

		sf::Vector2i nextPos = pos;
		switch (action) {
			case Action::Hold:
				break;
			case Action::MoveLeft:
				nextPos.x--;
				break;
			case Action::MoveRight:
				nextPos.x++;
				break;
			case Action::MoveDown:
				nextPos.y++;
				break;
		}

		// Determine if next position is reasonable 
		if (nextPos.x >= 0 && nextPos.x < fieldWidth && nextPos.y < fieldHeight 
			&& field[nextPos.x][nextPos.y] == false) {
			// Assign to previous variable
			pos = nextPos;
		}
		else {
			if (action == Action::MoveDown) {
				field[pos.x][pos.y] = true;
				bool isFull = true;
				for (int x = 0; x < fieldWidth; x++) {
					if (field[x][pos.y] == false) {
						isFull = false;
					}
				}

				if (isFull) {
					// Move previous y-row to the next y-row
					for (int y = pos.y; y > 0; y--) {
						for (int x = 0; x < fieldWidth; x++) {
							field[x][y] = field[x][y - 1];
						}
					}

					// Fill the top row with false
					for (int x = 0; x < fieldWidth; x++) {
						field[x][0] = false;
					}
				}


				pos = origin;
			}
		}


		window.clear();
		// Control the block
		block.setPosition(getPixelPosition(pos, blockSize));
		window.draw(block);

		// Display the field
		for (int x = 0; x < fieldWidth; x++) {
			for (int y = 0; y < fieldHeight; y++) {
				if (field[x][y] == true) {
					sf::Vector2i p(x, y);
					block.setPosition(getPixelPosition(p, blockSize));
					window.draw(block);
				}
			}
		}
		window.display();
	}
		
	return EXIT_SUCCESS;
}