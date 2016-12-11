#include "obj.hpp"

bullet::bullet() {
	buffer_shot.loadFromFile("media/sound/shot.ogg");
	sound_shot		= new Sound(buffer_shot);
	buffer_un_shot.loadFromFile("media/sound/un_shot.ogg");
	sound_un_shot	= new Sound(buffer_un_shot);
	rect			= FloatRect(0, 0, 8, 8);
	dx	= dy		= 0.0;
	status			= false;
	rect.left		= 0;
	rect.top		= 0;
}

bullet::~bullet() {
	delete sound_shot;
	delete sound_un_shot;
}

void bullet::init(Texture &image, tank *g_other_tanks, int g_other_tanks_num, game_map *l_main_map) {
	sprite.setTexture(image);
	other_tanks		= g_other_tanks;
	other_tanks_num	= g_other_tanks_num;
	main_map		= l_main_map;
}

void bullet::update(float time) {
	if (dx	!= dy) {	// Защита от выхода за границы
		if ((dx > 0) && (((rect.left + rect.width) / 16) > main_map->getMaxX()))
			dx	= 0;

		if ((dy > 0) && (((rect.top + rect.height) / 16) > (main_map->getMaxX() - 1)))
			dy	= 0;

		if ((dx < 0) && (rect.left <= 1))
			dx	= 0;

		if ((dy < 0) && (rect.top <= 1))
			dy	= 0;

		collision();

		if ((dx == 0) && (dy == 0)) {
			sound_un_shot->play();
			status	= false;
		}

		if (status) {
			rect.left	+= dx * (time * 1.5);
			rect.top	+= dy * (time * 1.5);
			sprite.setPosition(rect.left, rect.top);
		}
	}
}

void bullet::shot(int posX, int posY, int side) {
	sound_shot->play();
	sprite.setTextureRect(IntRect(320 + ((side / 2) * 8), 100, 8, 8));
	if (side == 0) {
		rect.left	= posX + 3,
		rect.top	= posY - 4;
		dy			= -0.1;
	} else if (side == 2) {
		rect.left	= posX - 3,
		rect.top	= posY + 4;
		dx			= -0.1;
	} else if (side == 4) {
		rect.left	= posX + 3,
		rect.top	= posY + 13;
		dy			= 0.1;
	} else if (side == 6) {
		rect.left	= posX + 13,
		rect.top	= posY + 4;
		dx			= 0.1;
	}

	status	= true;
}

bool bullet::active() {
	return status;
}

void bullet::collision() {
	if (dx != 0) {
		if (main_map->getElement(int((rect.top + 3) / 16), int(rect.left / 16)) == 'w') {
			main_map->setElement(' ', int((rect.top + 3) / 16), int(rect.left / 16));
			dx	= 0;
		}

		if (main_map->getElement(int((rect.top + 3) / 16), int(rect.left / 16)) == 'a') {
			dx	= 0;
		}
	}

	if (dy != 0) {
		if (main_map->getElement(int(rect.top / 16), int((rect.left + 3) / 16)) == 'w') {
			main_map->setElement(' ', int(rect.top / 16), int((rect.left + 3) / 16));
			dy	= 0;
		}

		if (main_map->getElement(int(rect.top / 16), int((rect.left + 3) / 16)) == 'a') {
			dy	= 0;
		}
	}

	if (dx != dy) {
		for (int	i	= 0; i < other_tanks_num; ++i) {
			if (rect.intersects(other_tanks[i].getRect())) {	// Проверка, попала ли пуля в кого-нибудь

			}
		}
	}
}