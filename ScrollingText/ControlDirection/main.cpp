#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
int main() {
	sf::RenderWindow w(sf::VideoMode(500, 250), "Hello");

	sf::Font font;
	if (font.loadFromFile("arial.ttf") == false) {
		return EXIT_FAILURE;
	}

	// Prevent same variable names, so we include enum class
	enum class Direction {LEFT_TO_RIGHT, RIGHT_TO_LEFT};
	enum class Speed {FAST, SLOW };

	Direction direction = Direction::RIGHT_TO_LEFT;
	Speed speed = Speed::FAST;

	sf::Text text("Hello", font, 200);
	// change color of text
	text.setFillColor(sf::Color(0,255,0));
	// Add black dot
	sf::CircleShape circle(2);
	circle.setFillColor(sf::Color(0, 0, 0));

	// set text position on the most right of window and then convert it to float
	// text.setPosition((float)w.getSize().x, 0);
	if (direction == Direction::RIGHT_TO_LEFT) {
		text.setPosition((float)w.getSize().x, 0);
	}
	
	while (w.isOpen()) {
		sf::Event evt;

		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
			// Press any key to change direction
			// if (evt.type == sf::Event::KeyPressed) {
				// switch (direction) {
				// case Direction::LEFT_TO_RIGHT:
					// direction = Direction::RIGHT_TO_LEFT;
					// break;
				// case Direction::RIGHT_TO_LEFT:
					// direction = Direction::LEFT_TO_RIGHT;
					// break;
				// }
			// }
			// Press left or right key to change the direction
			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Key::Left) {
					direction = Direction::RIGHT_TO_LEFT;
				}
				if (evt.key.code == sf::Keyboard::Key::Right) {
					direction = Direction::LEFT_TO_RIGHT;
				}
			}

			// Press s or f key to change the speed
			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Key::F) {
					speed = Speed::FAST;
				}
				if (evt.key.code == sf::Keyboard::Key::S) {
					speed = Speed::SLOW;
				}
			}


		}


			w.clear();
			w.draw(text);
			for (unsigned int i = 0; i < w.getSize().x; i += 4) {
				for (unsigned int j = 0; j < w.getSize().y; j += 4) {
					circle.setPosition((float)i, (float)j);
					w.draw(circle);
				}
			}
			w.display();
			
			float diff;
			switch (speed)
			{
			case Speed::FAST:
				diff = 0.1f * 40;
				break;
			case Speed::SLOW:
				diff = 0.01f * 40;
				break;
			}

			switch (direction)
			{
			case Direction::LEFT_TO_RIGHT:
				text.move(diff, 0.f);
				break;
			case Direction::RIGHT_TO_LEFT:
				text.move(-diff, 0.f);
				break;
			}

			

	}

	return EXIT_SUCCESS;



}