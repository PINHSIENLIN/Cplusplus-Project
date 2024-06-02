#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
int main() {
	sf::RenderWindow w(sf::VideoMode(400, 200), "Hello");

	sf::Font font;
	if (font.loadFromFile("arial.ttf") == false) {
		return EXIT_FAILURE;
	}

	sf::Text text("Hello", font);

	while (w.isOpen()) {
		sf::Event evt;

		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		while (text.getPosition().x <= 400) {
				w.clear();
				w.draw(text);
				w.display();
				text.move(0.01f, 0.f);
				if (text.getPosition().x > 400) {
					text.setPosition(0, 0);
				}
			// cout << text.getPosition().x << " " << text.getPosition().y << endl;
		}
		

	}

	return EXIT_SUCCESS;



}