#include "obj.hpp"

bullet::bullet() {
	buffer_shot.loadFromFile("media/sound/shot.ogg");		// Подгрузка звуков
	sound_shot			= new Sound(buffer_shot);
	buffer_un_shot.loadFromFile("media/sound/un_shot.ogg");
	sound_un_shot		= new Sound(buffer_un_shot);
	bullet_rect			= FloatRect(0, 0, 8, 8);
	bullet_dx	= bullet_dy		= 0.0;
	bullet_status		= false;
	bullet_rect.left	= 0;
	bullet_rect.top		= 0;
}

bullet::~bullet() {
	delete sound_shot;
	delete sound_un_shot;
}

void bullet::init(Texture &image, game_map *l_main_map) {
	bullet_sprite.setTexture(image);
	bullet_main_map			= l_main_map;
}

void bullet::update(float time) {
	if (bullet_dx	!= bullet_dy) {																					// Защита от выхода за границы
		if ((bullet_dx > 0) && (((bullet_rect.left + bullet_rect.width) / 16) > bullet_main_map->getMaxX()))
			bullet_dx	= 0;

		if ((bullet_dy > 0) && (((bullet_rect.top + bullet_rect.height) / 16) > (bullet_main_map->getMaxX() - 1)))
			bullet_dy	= 0;

		if ((bullet_dx < 0) && (bullet_rect.left <= 1))
			bullet_dx	= 0;

		if ((bullet_dy < 0) && (bullet_rect.top <= 1))
			bullet_dy	= 0;

		collision();

		if ((bullet_dx == 0) && (bullet_dy == 0)) {			// Если пуля куда-нибудь угадила - воспроизвести звук
			sound_un_shot->play();
			bullet_status	= false;						// "Убить пулю"
		}

		if (bullet_status) {
			bullet_rect.left	+= bullet_dx * (time * 1.5);
			bullet_rect.top		+= bullet_dy * (time * 1.5);
			bullet_sprite.setPosition(bullet_rect.left, bullet_rect.top);
		}
	}
}

void bullet::shot(int posX, int posY, int bullet_side) {
	sound_shot->play();										// Воспроизведение звука выстрела
	bullet_sprite.setTextureRect(IntRect(320 + ((bullet_side / 2) * 8), 100, 8, 8));
	if (bullet_side == 0) {
		bullet_rect.left	= posX + 3,
		bullet_rect.top		= posY - 4;
		bullet_dy			= -0.1;
	} else if (bullet_side == 2) {
		bullet_rect.left	= posX - 3,
		bullet_rect.top		= posY + 4;
		bullet_dx			= -0.1;
	} else if (bullet_side == 4) {
		bullet_rect.left	= posX + 3,
		bullet_rect.top		= posY + 13;
		bullet_dy			= 0.1;
	} else if (bullet_side == 6) {
		bullet_rect.left	= posX + 13,
		bullet_rect.top		= posY + 4;
		bullet_dx			= 0.1;
	}

	bullet_status			= true;
}

bool bullet::active() {
	return bullet_status;
}

bool bullet::rectComparison(FloatRect &tank_recr) {
	if ((bullet_status) && (bullet_rect.intersects(tank_recr)))
		return true;

	return false;
}

void bullet::collision() {
	if (bullet_dx != 0) {
		if (bullet_main_map->getElement(int((bullet_rect.top + 3) / 16), int(bullet_rect.left / 16)) == 'w') {
			bullet_main_map->setElement(' ', int((bullet_rect.top + 3) / 16), int(bullet_rect.left / 16));
			bullet_dx	= 0;
		}

		if (bullet_main_map->getElement(int((bullet_rect.top + 3) / 16), int(bullet_rect.left / 16)) == 'a') {
			bullet_dx	= 0;
		}
	}

	if (bullet_dy != 0) {
		if (bullet_main_map->getElement(int(bullet_rect.top / 16), int((bullet_rect.left + 3) / 16)) == 'w') {
			bullet_main_map->setElement(' ', int(bullet_rect.top / 16), int((bullet_rect.left + 3) / 16));
			bullet_dy	= 0;
		}

		if (bullet_main_map->getElement(int(bullet_rect.top / 16), int((bullet_rect.left + 3) / 16)) == 'a') {
			bullet_dy	= 0;
		}
	}

/*	if (bullet_dx != bullet_dy) {
		for (int	i	= 0; i < bullet_other_tanks_num; ++i) {
			if (bullet_rect.intersects(bullet_other_tanks[i].getRect())) {	// Проверка, попала ли пуля в кого-нибудь

			}
		}
	}*/
}