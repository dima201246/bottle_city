#include "../include/obj.hpp"

bullet::bullet(Texture &image, game_map *l_main_map) {
	buffer_shot.loadFromFile("media/sound/shot.ogg");		// Подгрузка звуков
	sound_shot			= new Sound(buffer_shot);

	buffer_un_shot.loadFromFile("media/sound/un_shot.ogg");
	sound_un_shot		= new Sound(buffer_un_shot);

	main_point::rect			= FloatRect(0, 0, 8, 8);
	main_point::dx	= main_point::dy	= 0.0;
	bullet_status		= false;
	main_point::rect.left	= 0;
	main_point::rect.top		= 0;
	bullet_sprite.setTexture(image);
	bullet_main_map			= l_main_map;
}

bullet::~bullet() {
	delete sound_shot;
	delete sound_un_shot;
}

void bullet::update(float time) {
	if ((main_point::dx != 0) && (main_point::dy != 0)) {
		bullet_status	= false;
		sound_un_shot->play();
		main_point::dx	= 0;
		main_point::dy	= 0;
		return;
	}

	if (main_point::dx	!= main_point::dy) {																					// Защита от выхода за границы
		if ((main_point::dx > 0) && (((main_point::rect.left + main_point::rect.width) / 16) > bullet_main_map->getMaxX()))
			main_point::dx	= 0;

		if ((main_point::dy > 0) && (((main_point::rect.top + main_point::rect.height) / 16) > bullet_main_map->getMaxX()))
			main_point::dy	= 0;

		if ((main_point::dx < 0) && (main_point::rect.left <= 1))
			main_point::dx	= 0;

		if ((main_point::dy < 0) && (main_point::rect.top <= 1))
			main_point::dy	= 0;

		collision();

		if ((main_point::dx == 0) && (main_point::dy == 0)) {			// Если пуля куда-нибудь угадила - воспроизвести звук
			sound_un_shot->play();
			bullet_status	= false;						// "Убить пулю"
		}

		if (bullet_status) {
			main_point::rect.left	+= main_point::dx * (time * 1.5);
			main_point::rect.top		+= main_point::dy * (time * 1.5);
			bullet_sprite.setPosition(main_point::rect.left, main_point::rect.top);
		}
	}
}

void bullet::shot(int posX, int posY, int bullet_side) {
	sound_shot->play();										// Воспроизведение звука выстрела
	bullet_sprite.setTextureRect(IntRect(320 + ((bullet_side / 2) * 8), 100, 8, 8));
	if (bullet_side == 0) {
		main_point::rect.left	= posX + 3,
		main_point::rect.top		= posY - 4;
		main_point::dy			= -0.1;
	} else if (bullet_side == 2) {
		main_point::rect.left	= posX - 3,
		main_point::rect.top		= posY + 4;
		main_point::dx			= -0.1;
	} else if (bullet_side == 4) {
		main_point::rect.left	= posX + 3,
		main_point::rect.top		= posY + 13;
		main_point::dy			= 0.1;
	} else if (bullet_side == 6) {
		main_point::rect.left	= posX + 13,
		main_point::rect.top		= posY + 4;
		main_point::dx			= 0.1;
	}

	bullet_status			= true;
}

bool bullet::active() {
	return bullet_status;
}

bool bullet::bulletComparsion(FloatRect other_recr) {
	if ((bullet_status) && (main_point::rect.intersects(other_recr)))
		return true;

	return false;
}

void bullet::collision() {
	if (main_point::dx != 0) {
		if (bullet_main_map->getElement(int((main_point::rect.top + 3) / 16), int(main_point::rect.left / 16)) == 'w') {
			bullet_main_map->setElement(' ', int((main_point::rect.top + 3) / 16), int(main_point::rect.left / 16));
			main_point::dx	= 0;
		}

		if (bullet_main_map->getElement(int((main_point::rect.top + 3) / 16), int(main_point::rect.left / 16)) == 'a') {
			main_point::dx	= 0;
		}
	}

	if (main_point::dy != 0) {
		if (bullet_main_map->getElement(int(main_point::rect.top / 16), int((main_point::rect.left + 3) / 16)) == 'w') {
			bullet_main_map->setElement(' ', int(main_point::rect.top / 16), int((main_point::rect.left + 3) / 16));
			main_point::dy	= 0;
		}

		if (bullet_main_map->getElement(int(main_point::rect.top / 16), int((main_point::rect.left + 3) / 16)) == 'a') {
			main_point::dy	= 0;
		}
	}

/*	if (main_point::dx != main_point::dy) {
		for (int	i	= 0; i < bullet_other_tanks_num; ++i) {
			if (main_point::rect.intersects(bullet_other_tanks[i].getRect())) {	// Проверка, попала ли пуля в кого-нибудь

			}
		}
	}*/
}

void bullet::destroy() {
	sound_un_shot->play();
	bullet_status	= false;
}

void bullet::draw(RenderWindow& window) {
	window.draw(bullet_sprite);
}