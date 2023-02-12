#include "components/main.hpp"
#include <vector>

int main() {
	sf::RenderWindow win(sf::VideoMode(512, 512), "test");
	sf::Event event;

	int r(0), g(0), b(0), d(0);
	MGL::Texture_I texture;
	std::vector<MGL::Object*> objects(4, nullptr);
	for (int i = 0; i < objects.size(); i++) {
		objects[i] = new MGL::Toggle_B(i + 1, (MGL::Vector<short>){100 + 100 * (i / 2), 100 + 100 * (i % 2)}, MGL::Vector<MGL::byte_2>{50, 50}, &texture);
	}

	while (win.isOpen()) {
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed) win.close();
			if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
				for (auto &i : objects) i->update(event);
				r = objects[0]->getStat() ? 255 : 0;
				g = objects[1]->getStat() ? 255 : 0;
				b = objects[2]->getStat() ? 255 : 0;
				d = objects[3]->getStat();
			}
			if (event.type == sf::Event::Resized) {
				float h = (float)win.getSize().y;
				float w = (float)win.getSize().x;
				win.setView(sf::View(sf::Vector2f(w / 2.0, h / 2.0), sf::Vector2f(w, h)));
			}
		}
		win.clear(sf::Color(abs(r - d * 20), abs(g - d * 20), abs(b - d * 20), 255));
		for (auto &i : objects) i->draw(win);
		win.display();
	}

	for (auto &i : objects) delete i;

	return 0;
}