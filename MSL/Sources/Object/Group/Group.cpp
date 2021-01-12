#include "../../../Headers/Object/Group/Group.h"
#include "../../../Headers/Object/Button/Button.h"
#include "../../../Headers/Image/Image.h"

mgl::Group::Group(rect r, int i, bool c, bool e) : Object(r.pos, i) {

	center = c;
	expand = e;
	size = r.size;
	cont = new Object * [size.x * size.y];
	for (int i = 0; i < size.x * size.y; i++) cont[i] = nullptr;
}

void mgl::Group::push(Object* o) {

	for (int i = 0; i < size.x * size.y; i++)
		if (cont[i] == nullptr) {

			cont[i] = o;
			break;
		}
}

void mgl::Group::resize() {

	short w = size.x, h = size.y;
	coord* map = new coord[(w + 1) * (h + 1)];

	for (int i = 0; i < (h + 1) * (w + 1); i++)
		map[i] = { 0, 0 };

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {

			if (cont[i * w + j]) {

				if (cont[i * w + j]->getSize().x > map[j + 1].x)
					map[j + 1] = coord{ cont[i * w + j]->getSize().x, 0 };

				if (cont[i * w + j]->getSize().y > map[(i + 1) * (w + 1)].y)
					map[(i + 1) * (w + 1)] = coord{ 0, cont[i * w + j]->getSize().y };
			}
		}

	for (int i = 0; i < w; i++) map[i + 1] += map[i];
	for (int i = 0; i < h; i++) map[(i + 1) * (w + 1)] += map[i * (w + 1)];

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {

			map[(i + 1) * (w + 1) + (j + 1)] = map[j + 1] + map[(i + 1) * (w + 1)];

			if (cont[i * w + j]) {

				coord _pos = map[i * (w + 1) + j] + pos;
				if (expand)
					cont[i * w + j]->setSize(map[(i + 1) * (w + 1) + (j + 1)] - map[i * (w + 1) + j]);
				else if (center)
					_pos += map[(i + 1) * (w + 1) + (j + 1)] - map[i * (w + 1) + j] - cont[i * w + j]->getSize() / 2;
				cont[i * w + j]->setCoord(_pos);
			}
		}

	delete[] map;
}

char mgl::Group::getName() {

	return SIM_G;
}

bool mgl::Group::getSignal(int& id) {

	for (int i = 0; i < size.y * size.x; i++)
		if (cont[i] && cont[i]->getName() & SIM_B)
			if (dynamic_cast<Button*>(cont[i])->getSignal()) {

				id = cont[i]->getId();
				return true;
			}
	return false;
}

void mgl::Group::setSize(coord s) {}

mgl::coord mgl::Group::getSize() {

	coord c = cont[size.x * size.y - 1]->getCoord() - pos + cont[size.x * size.y - 1]->getSize();
	coord s = { c.x, c.y };
	return s;
}

void mgl::Group::draw(sf::RenderWindow& win) {

	resize();
	for (int i = 0; i < size.y * size.x; i++) cont[i]->draw(win);
}