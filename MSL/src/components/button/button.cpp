#include "button.hpp"

MGL::Button::Button() : Object() {
	static Texture_I default_img;
	image = &default_img;
	size = { 64, 64 };
	key = -1;
	stat = { 0, 0 };
};

MGL::Button::Button(int i, Vector<short> p, Vector<byte_2> s, Texture_I* im) : Object(i, p) {
	image = im;
	size = s;
	key = -1;
	stat = { 0, 0 };
};

void MGL::Button::setSize(Vector<byte_2> s) {
	size = s;
}

MGL::Vector<MGL::byte_2> MGL::Button::getSize() {
	return size;
}

void MGL::Button::setImage(Texture_I* im) {
	image = im;
}

MGL::Texture_I* MGL::Button::getImage() {
	return image;
}

void MGL::Button::setKey(short k) {
	key = k;
}

short MGL::Button::getKey() {
	return key;
}