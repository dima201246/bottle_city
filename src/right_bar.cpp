#include "../include/obj.hpp"

right_bar::right_bar(Texture &image, unsigned int maxX, int eminem_num, int l_level, int l_p1_life, int l_p2_life) {
	sprite.setTexture(image);
	pos			= maxX * 16;
	eminems_num	= eminem_num;
	level		= l_level;
	p1_life		= l_p1_life;
	p2_life		= l_p2_life;
}

void right_bar::draw(RenderWindow &window) {
	unsigned int	j	= 0,
					k	= 0;

	sprite.setPosition(pos, 0);
	sprite.setTextureRect(IntRect(368, 16, 32, 208));
	window.draw(sprite);
	sprite.setTextureRect(IntRect(320, 192, 9, 9));

	for (int	i	= 0; i < eminems_num; ++i) {
		sprite.setPosition(pos + 8 + j, 8 + k);

		k	+= 8;

		if ((i >= 9) && (j == 0)) {
			j	= 8;
			k	= 0;
		}

		window.draw(sprite);
	}

	sprite.setPosition(pos + 16, 128);

	if (p1_life == 3) {
		sprite.setTextureRect(IntRect(352, 183, 9, 9));
	} else if (p1_life == 2) {
		sprite.setTextureRect(IntRect(344, 183, 9, 9));
	} else if (p1_life == 1) {
		sprite.setTextureRect(IntRect(336, 183, 9, 9));
	} else if (p1_life >= 0) {
		sprite.setTextureRect(IntRect(328, 183, 9, 9));
	}

	window.draw(sprite);

	sprite.setPosition(pos + 16, 152);

	if (p2_life == 3) {
		sprite.setTextureRect(IntRect(352, 183, 9, 9));
	} else if (p2_life == 2) {
		sprite.setTextureRect(IntRect(344, 183, 9, 9));
	} else if (p2_life == 1) {
		sprite.setTextureRect(IntRect(336, 183, 9, 9));
	} else if (p2_life >= 0) {
		sprite.setTextureRect(IntRect(328, 183, 9, 9));
	}

	window.draw(sprite);

}

void right_bar::setEminems(int c) {
	eminems_num	= c;
}

int right_bar::getEminems() {
	return eminems_num;
}

void right_bar::setP1Life(int c) {
	p1_life	= c;
}

int right_bar::getP1Life() {
	return p1_life;
}

void right_bar::setP2Life(int c) {
	p2_life	= c;
}

int right_bar::getP2Life() {
	return p2_life;
}

void right_bar::setLevel(int c) {
	level	= c;
}

int right_bar::getLevel() {
	return level;
}