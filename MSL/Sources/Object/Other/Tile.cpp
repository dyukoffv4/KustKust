#include "../../../Headers/Object/Other/Tile.h"
#include "../../../Headers/Image/Image.h"

mgl::Tile::Tile(coord c, int i, Image* i_l) : Object(c, i) {

	image_line = i_l;
}

char mgl::Tile::getName() {

	return TIL;
}

void mgl::Tile::setImage(Image* i_l) {

	image_line = i_l;
}

void mgl::Tile::draw(sf::RenderWindow& win) {

	sf::Sprite spr;
	if (image_line) spr = image_line->getSpr();
	else spr = standart.getSpr();

	spr.setPosition(pos.x, pos.y);
	win.draw(spr);
}