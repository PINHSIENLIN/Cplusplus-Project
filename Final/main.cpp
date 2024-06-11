#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <windows.h>
using namespace std;
int main() {
	float delay = 0.4f;
	bool isDead = false;

	sf::Vector2<int> fieldSize(20, 15);
	// int fieldWidth = 20;
	// int fieldHeight = 15;

	sf::Texture blockTexture;
	if (!blockTexture.loadFromFile("block.png")) {
		return EXIT_FAILURE;
	}
	// Head
	// sf::Vector2i head(3, 4);
	
    vector<sf::Vector2i> snake = { sf::Vector2i(3, 4) };
	
	// Bait by generate randomly
	sf::Vector2i food(rand() % fieldSize.x, rand() % fieldSize.y);
	sf::Sprite block(blockTexture);

	sf::Vector2<int> blockSize(block.getLocalBounds().width, block.getLocalBounds().height);

	// float blockWidth = block.getLocalBounds().width;
	// float blockHeight = block.getLocalBounds().height;

	sf::VideoMode mode(unsigned int(fieldSize.x * blockSize.x), unsigned int(fieldSize.y * blockSize.y));
	sf::RenderWindow w(mode, "Snake Game");
	
	enum class Direction {UP, DOWN, LEFT, RIGHT};
	Direction direction = Direction::RIGHT;

	// Update frame every one second
	// w.setFramerateLimit(1);
	sf::Clock clock;

	
	while (w.isOpen()) {
		sf::Event evt;

		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
			// Press any left, right,down, up
			if(evt.type == sf::Event::KeyPressed){
				if (evt.key.code == sf::Keyboard::Up) {
					direction = Direction::UP;
				}
				if (evt.key.code == sf::Keyboard::Down) {
					direction = Direction::DOWN;
				}
				if (evt.key.code == sf::Keyboard::Left) {
					direction = Direction::LEFT;
				}
				if (evt.key.code == sf::Keyboard::Right) {
					direction = Direction::RIGHT;
				}
			
			}
			
		

		}

		// - - - - (20) - - - -
		// | (i,j)
		// |
		// |
		// (15)
		// |

		// typedef Vector2<float> Vector2f;
		// using  Vector2f = Vector2<float>;

		// Move x += 1
		//if (clock.getElapsedTime().asSeconds() >= 1.0f) {
			//head.x += 1;
			//clock.restart();
		// }

	
		if (clock.getElapsedTime().asSeconds() >= delay) {
			// snake = {3,4}
			
			// get the head
			sf::Vector2i head = snake[0];

			if (direction == Direction::UP) {
				head.y--;
			}
			if (direction == Direction::DOWN) {
				head.y++;
			}
			if (direction == Direction::LEFT) {
				head.x--;
			}
			if (direction == Direction::RIGHT) {
				head.x++;
			}

			// Determine if out-of-bound
			if (head.x < 0 || head.x >= fieldSize.x ||
				head.y < 0 || head.y >= fieldSize.y) {
				isDead = true;
			}

			// change the position of head
			snake.insert(snake.begin(), head);
			if (!isDead) {
				// If bait is eaten
				if (food == head) {
					cout << "Eaten" << endl;
					// Grow if the bait is eaten
					food.x = rand() % fieldSize.x;
					food.y = rand() % fieldSize.y;
					delay -= 0.1f;
					if (delay < 0.1f) delay = 0.1f;
				}
				else {
					snake.pop_back();
				}
			} 
			
			clock.restart();
		}

		if (isDead) {
			w.clear(sf::Color::Red);
		}
		else {
			w.clear();
		}
		

		// Bait
		sf::Vector2<float> foodpos(food.x * blockSize.x, food.y * blockSize.y);
		block.setPosition(foodpos);
		w.draw(block);


		// Head of Snake
		// sf::Vector2<float> pos(head.x * blockSize.x, head.y * blockSize.y);
		// block.setPosition(pos.x, pos.y);
		// w.draw(block);

		// Draw the whole snake
		for (const sf::Vector2i& body : snake) {
			sf::Vector2<float> bodyPos(body.x * blockSize.x, body.y * blockSize.y);
			block.setPosition(bodyPos.x, bodyPos.y);
			w.draw(block);
		}
		
		w.display();
			
		//for (int i = 0; i < fieldSize.x; i++) {
			//for (int j = 0; j < fieldSize.y; j++) {
				//sf::Vector2<float> pos(i * blockSize.x, j * blockSize.y);
				//block.setPosition(pos.x, pos.y);
				//w.draw(block);
			//}
		//}

		
		
		
	}



	return EXIT_SUCCESS;
}