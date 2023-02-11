#include "button.hpp"

mgl::Button::Button() : Object() {

	static Texture_I default_img;
	image = &default_img;
	size = { 64, 64 };
	key = -1;
	stat = { 0, 0 };
};

mgl::Button::Button(int i, vect<short> p, vect<byte_2> s, Texture_I* im) : Object(i, p) {

	image = im;
	size = s;
	key = -1;
	stat = { 0, 0 };
};

void mgl::Button::setSize(vect<byte_2> s) {

	size = s;
}

mgl::vect<mgl::byte_2> mgl::Button::getSize() {

	return size;
}

void mgl::Button::setImage(Texture_I* im) {

	image = im;
}

mgl::Texture_I* mgl::Button::getImage() {

	return image;
}

void mgl::Button::setKey(short k) {

	key = k;
}

short mgl::Button::getKey() {

	return key;
}