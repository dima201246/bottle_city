#include "../include/obj.hpp"

void Bullet::init(Texture &image, GameMap *l_main_map) {
	buffer_shot.loadFromFile("media/sound/shot.ogg");		// Подгрузка звуков
	sound_shot				= new Sound(buffer_shot);

	buffer_un_shot.loadFromFile("media/sound/un_shot.ogg");
	sound_un_shot			= new Sound(buffer_un_shot);

	MainPoint::rect		= FloatRect(0, 0, 8, 8);
	MainPoint::dx	= MainPoint::dy	= 0.0;

	bullet_status			= false;

	MainPoint::rect.left	= 0;
	MainPoint::rect.top	= 0;

	MainPoint::sprite.setTexture(image);
	MainPoint::sprite.scale(SCALE_X, SCALE_Y);

	bullet_main_map			= l_main_map;
}

Bullet::~Bullet() {
	delete sound_shot;
	delete sound_un_shot;
}

void Bullet::update(float time) {
	if ((MainPoint::dx != 0) && (MainPoint::dy != 0)) {
		bullet_status	= false;
		sound_un_shot->play();
		MainPoint::dx	= 0;
		MainPoint::dy	= 0;
		return;
	}

	if (MainPoint::dx	!= MainPoint::dy) {																					// Защита от выхода за границы
		if ((MainPoint::dx > 0) && (((MainPoint::rect.left + MainPoint::rect.width) / 16) > bullet_main_map->getMaxX()))
			MainPoint::dx	= 0;

		if ((MainPoint::dy > 0) && (((MainPoint::rect.top + MainPoint::rect.height) / 16) > bullet_main_map->getMaxX()))
			MainPoint::dy	= 0;

		if ((MainPoint::dx < 0) && (MainPoint::rect.left <= 1))
			MainPoint::dx	= 0;

		if ((MainPoint::dy < 0) && (MainPoint::rect.top <= 1))
			MainPoint::dy	= 0;

		collision();

		if ((MainPoint::dx == 0) && (MainPoint::dy == 0)) {			// Если пуля куда-нибудь угадила - воспроизвести звук
			sound_un_shot->play();
			bullet_status	= false;						// "Убить пулю"
		}

		if (bullet_status) {
			MainPoint::rect.left	+= MainPoint::dx * (time * 1.5);
			MainPoint::rect.top		+= MainPoint::dy * (time * 1.5);
			MainPoint::sprite.setPosition(MainPoint::rect.left * SCALE_X, MainPoint::rect.top * SCALE_Y);
		}
	}
}

void Bullet::shot(int posX, int posY, int bullet_side) {
	sound_shot->play();										// Воспроизведение звука выстрела
	MainPoint::sprite.setTextureRect(IntRect(320 + ((bullet_side / 2) * 8), 100, 8, 8));
	if (bullet_side == 0) {
		MainPoint::rect.left	= posX + 3,
		MainPoint::rect.top		= posY - 4;
		MainPoint::dy			= -0.1;
	} else if (bullet_side == 2) {
		MainPoint::rect.left	= posX - 3,
		MainPoint::rect.top		= posY + 4;
		MainPoint::dx			= -0.1;
	} else if (bullet_side == 4) {
		MainPoint::rect.left	= posX + 3,
		MainPoint::rect.top		= posY + 13;
		MainPoint::dy			= 0.1;
	} else if (bullet_side == 6) {
		MainPoint::rect.left	= posX + 13,
		MainPoint::rect.top		= posY + 4;
		MainPoint::dx			= 0.1;
	}

	bullet_status			= true;
}

bool Bullet::active() {
	return bullet_status;
}

bool Bullet::bulletComparsion(FloatRect other_recr) {
	if ((bullet_status) && (MainPoint::rect.intersects(other_recr)))
		return true;

	return false;
}

void Bullet::collision() {
	if (MainPoint::dx != 0) {
		if (bullet_main_map->getElement(int((MainPoint::rect.left + 3) / 16), int(MainPoint::rect.top / 16)) == 'w') {
			bullet_main_map->setElement(' ', int((MainPoint::rect.left + 3) / 16), int(MainPoint::rect.top / 16));
			MainPoint::dx	= 0;
			bullet_status	= false;
		}

		if (bullet_main_map->getElement(int((MainPoint::rect.left + 3) / 16), int(MainPoint::rect.top / 16)) == 'a') {
			MainPoint::dx	= 0;
			bullet_status	= false;
		}

		if (bullet_main_map->getElement(int((MainPoint::rect.left + 3) / 16), int(MainPoint::rect.top / 16)) == 'e') {
			bullet_main_map->setElement(' ', int((MainPoint::rect.left + 3) / 16), int(MainPoint::rect.top / 16));
			MainPoint::dx	= 0;
			bullet_status	= false;
		}
	}

	if (MainPoint::dy != 0) {
		if (bullet_main_map->getElement(int(MainPoint::rect.left / 16), int((MainPoint::rect.top + 3) / 16)) == 'w') {
			bullet_main_map->setElement(' ', int(MainPoint::rect.left / 16), int((MainPoint::rect.top + 3) / 16));
			MainPoint::dy	= 0;
			bullet_status	= false;
		}

		if (bullet_main_map->getElement(int(MainPoint::rect.left / 16), int((MainPoint::rect.top + 3) / 16)) == 'a') {
			MainPoint::dy	= 0;
			bullet_status	= false;
		}

		if (bullet_main_map->getElement(int(MainPoint::rect.left / 16), int((MainPoint::rect.top + 3) / 16)) == 'e') {
			bullet_main_map->setElement(' ', int(MainPoint::rect.left / 16), int((MainPoint::rect.top + 3) / 16));
			MainPoint::dy	= 0;
			bullet_status	= false;
		}
	}
}

void Bullet::bulletDestroy() {
	sound_un_shot->play();
	bullet_status	= false;
}

void Bullet::draw(RenderWindow& window) {
	window.draw(MainPoint::sprite);
}

bool Bullet::bulletStatus() {
	return bullet_status;
}

FloatRect Bullet::getBulletRect() {
	return rect;
}