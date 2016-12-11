#include "obj.hpp"

void tank::init(Texture &image, game_map *l_main_map) {
	bullet::init(image, l_main_map);
	t_sprite.setTexture(image);
	side			= 0;
	rect			= FloatRect(0, 0, 16, 16);
	god_mode		= false;
	currentFrame	= 0;
	dx	= dy		= 0.0;
	main_map		= l_main_map;
}

void tank::update(float time) {
	l_time	= time;

	if ((dx	!= 0) || (dy != 0)) {	// Защита от выхода за границы
		if ((dx > 0) && (((rect.left + rect.width) / 16) > main_map->getMaxX())) dx	= 0;
		if ((dy > 0) && (((rect.top + rect.height) / 16) > (main_map->getMaxY() - 1))) dy	= 0;
		if ((dx < 0) && (rect.left <= 1)) dx	= 0;
		if ((dy < 0) && (rect.top <= 1)) dy	= 0;

		collision();
	}

	rect.left		+= dx * (time / 2.0);	// Собсно, движение
	rect.top 		+= dy * (time / 2.0);

	t_sprite.setTextureRect(IntRect(0 + (side * 16), 0, 16, 16));

	if ((dx	!= 0) || (dy != 0)) {
		currentFrame	!= currentFrame;

		if (dy < 0)
			side	= 0 + currentFrame;

		if (dx < 0)
			side	= 2 + currentFrame;

		if (dy > 0)
			side	= 4 + currentFrame;
		
		if (dx > 0)
			side	= 6 + currentFrame;

	}

	t_sprite.setPosition(rect.left, rect.top);

	dx=0;
	dy=0;
}

void tank::piu_piu() {
	if (!bullet::active()) {
		bullet::shot(rect.left, rect.top, side);
	}
}

void tank::moveUp() {
	dy	-= 0.1;
}

void tank::moveDown() {
	dy	+= 0.1;
}

void tank::moveLeft() {
	dx	-= 0.1;
}

void tank::moveRight() {
	dx	+= 0.1;
}

int tank::getSide() {
	return side;
}

FloatRect tank::getRect() {
	return rect;
}

void tank::draw(RenderWindow &window) {
	window.draw(t_sprite);

	if (bullet::active()) {
		bullet::update(l_time);
		window.draw(bullet_sprite);
	}
}

void tank::setPosition(unsigned int x, unsigned int y) {
	rect.left		= x * 16;
	rect.top		= y * 16;
}

bool tank::bulletComparsion(FloatRect &tank_recr) {
	if ((bullet::active()) && (rectComparison(tank_recr)))
		return true;

	return false;
}

bool tank::tankComparsion(FloatRect &tank_recr) {
	if (rect.intersects(tank_recr))
		return true;

	return false;
}

void tank::collision() {
	char	block_1, block_2;

	if (dx < 0) {
		block_1	= main_map->getElement((int)((rect.top + 1) / 16), (int)((rect.left - 1) / 16));
		block_2	= main_map->getElement((int)((rect.top + 15) / 16), (int)((rect.left - 1) / 16));
		side	= 2;
	} else  if (dx > 0) {
		block_1	= main_map->getElement((int)(rect.top / 16), (int)((rect.left + 16) / 16));
		block_2	= main_map->getElement((int)((rect.top + 15) / 16), (int)((rect.left + 16) / 16));
		side	= 6;
	} else if (dy < 0) {
		block_1	= main_map->getElement((int)((rect.top - 1) / 16), (int)((rect.left + 1) / 16));
		block_2	= main_map->getElement((int)((rect.top - 1) / 16), (int)((rect.left + 15) / 16));
		side	= 0;
	} else if (dy > 0) {
		block_1	= main_map->getElement((int)((rect.top + 16) / 16), (int)(rect.left / 16));
		block_2	= main_map->getElement((int)((rect.top + 16) / 16), (int)((rect.left + 15) / 16));
		side	= 4;
	}

	if (((block_1	== 'w') || (block_2 == 'w')) || ((block_1	== 'a') || (block_2 == 'a')) || ((block_1	== 'v') || (block_2 == 'v'))) {
		dx	= 0;
		dy	= 0;
	}
}