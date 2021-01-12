#include "Headers/Image/Sprite_I.h"
#include "Headers/Image/Color_I.h"
#include "Headers/Object/Button/Toggle_B.h"
#include "Headers/Object/Button/Timer_B.h"
#include "Headers/Object/Other/Tile.h"
#include "Headers/Object/Group/Group.h"

int main() {

	using namespace mgl;
	
	sf::Texture T_B;
	T_B.loadFromFile("C:\\Users\\Lenovo\\Documents\\New_Game\\Textures\\Menu\\Button\\Color_B.png");

	Image** img = new Image * [4];
	for (short i = 0; i < 4; i++)
		img[i] = new Image({ 64, 64 }, { i, 0 }, &T_B);

	Button** but = new Button * [4];
	for (short i = 0; i < 4; i++)
		but[i] = new Button({ {0, 0}, {64 * (i + 2) / 2, 64 * (i + 2) / 2} }, i + 1, img[i]);

	Group grp({ {96, 96}, {2, 2} }, 0);
	for (int i = 0; i < 4; i++)
		grp.push(but[i]);

	sf::RenderWindow win(sf::VideoMode(512, 512), "test");
	sf::Event event;

	while (win.isOpen()) {

		while (win.pollEvent(event)) {

			if (event.type == sf::Event::Closed) win.close();
			if (event.type == sf::Event::MouseButtonPressed) {

				for (int i = 0; i < 4; i++)
					but[i]->update(event.mouseButton, 1);
			}
			if (event.type == sf::Event::MouseButtonReleased) {

				for (int i = 0; i < 4; i++)
					but[i]->update(event.mouseButton, 0);
			}
			if (event.type == sf::Event::Resized) {

				float h = (float)win.getSize().y;
				float w = (float)win.getSize().x;
				win.setView(sf::View(sf::Vector2f(w / 2.0, h / 2.0), sf::Vector2f(w, h)));
			}
		}

		for (int i = 0; i < 4; i++) img[i]->update();
		int i;
		if (grp.getSignal(i)) {

			if (i == 1) grp.setCoord(grp.getCoord() + coord{ -32, -32 });
			if (i == 2) grp.setCoord(grp.getCoord() + coord{ 32, -32 });
			if (i == 3) grp.setCoord(grp.getCoord() + coord{ -32, 32 });
			if (i == 4) grp.setCoord(grp.getCoord() + coord{ 32, 32 });
		}

		win.clear(sf::Color(100, 100, 200, 255));
		grp.draw(win);
		win.display();
	}

	for (int i = 0; i < 4; i++)
		delete img[i];
	delete[] img;

	for (int i = 0; i < 4; i++)
		delete but[i];
	delete[] but;

	return 0;
}