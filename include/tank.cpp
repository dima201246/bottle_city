#include "obj.hpp"

void tank::init(Texture &image, int num, int g_life, tank *g_other_tanks, int g_other_tanks_num, game_map *l_main_map) {
	bullet_sprite.setTexture(image);
	bullet_other_tanks		= g_other_tanks;
	bullet_other_tanks_num	= g_other_tanks_num;
	bullet_main_map			= l_main_map;

	t_sprite.setTexture(image);
	side			= 0;
	life			= g_life;
	level			= 1;
	other_tanks		= g_other_tanks;
	other_tanks_num	= g_other_tanks_num;
	num_of_player	= num;
	rect			= FloatRect(0, 0, 16, 16);
	god_mode		= false;
	left_tank		= 16;
	currentFrame	= 0;
	dx	= dy		= 0.0;
	rect.left		= 128;
	rect.top		= 176;
	main_map		= l_main_map;
}

void tank::update(float time) {
	l_time	=time;

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

void tank::move_up() {
	dy	-= 0.1;
}

void tank::move_down() {
	dy	+= 0.1;
}

void tank::move_left() {
	dx	-= 0.1;
}

void tank::move_right() {
	dx	+= 0.1;
}

int tank::getSide() {
	return side;
}

FloatRect tank::getRect() {
	return rect;
}

int tank::getLeft_tank() {
	return left_tank;
}

int tank::getLife() {
	return life;
}

void tank::draw(RenderWindow &window) {
	if (life == 0)
		return;

	window.draw(t_sprite);

	if (bullet::active()) {
		bullet::update(l_time);
		window.draw(bullet_sprite);
	}
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
		// block_2	= ' ';
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