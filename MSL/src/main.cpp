#include "components/main.hpp"

int main() {
	sf::RenderWindow win(sf::VideoMode(512, 512), "test");
	sf::Event event;

	while (win.isOpen()) {
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed) win.close();
			if (event.type == sf::Event::MouseButtonPressed) {}
			if (event.type == sf::Event::MouseButtonReleased) {}
			if (event.type == sf::Event::Resized) {
				float h = (float)win.getSize().y;
				float w = (float)win.getSize().x;
				win.setView(sf::View(sf::Vector2f(w / 2.0, h / 2.0), sf::Vector2f(w, h)));
			}
		}
		win.clear(sf::Color(100, 100, 200, 255));
		win.display();
	}

	return 0;
}