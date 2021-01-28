#include "Sprite_I.h"
#include "Edit_B.h"

int main() {

	sf::RenderWindow win(sf::VideoMode(512, 512), "test");
	sf::Event event;

	sf::Texture t;
	t.loadFromFile("C:\\Users\\Lenovo\\Documents\\New_Game\\Textures\\Color\\Color_B.png");

	sf::Font f;
	f.loadFromFile("C:\\GameRes\\fonts\\comic.ttf");

	std::string str = "";

	mgl::Label l(str, sf::Color{0, 0, 0, 255}, &f);
	l.setKeg(32);
	mgl::Image i({ 64, 64 }, { 2, 0 }, &t);
	mgl::Edit_B b(0, { 128, 128 }, { 240, 48 }, &i, &l);
	b.setColor(sf::Color{ 30, 180, 150, 255 });

	while (win.isOpen()) {

		while (win.pollEvent(event)) {

			if (event.type == sf::Event::Closed) win.close();
			if (event.type == sf::Event::MouseButtonPressed) {

				b.update(event);
			}
			if (event.type == sf::Event::MouseButtonReleased) {

				b.update(event);
			}
			if (event.type == sf::Event::KeyPressed) {

				b.update(event);
			}
			if (event.type == sf::Event::KeyReleased) {

				b.update(event);
			}
			if (event.type == sf::Event::TextEntered) {

				b.update(event);
			}
			if (event.type == sf::Event::Resized) {

				float h = (float)win.getSize().y;
				float w = (float)win.getSize().x;
				win.setView(sf::View(sf::Vector2f(w / 2.0, h / 2.0), sf::Vector2f(w, h)));
			}
		}

		win.clear(sf::Color(100, 100, 200, 255));
		b.draw(win);
		win.display();
	}

	return 0;
}