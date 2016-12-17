#include "../include/obj.hpp"

void body::init(Texture &image, game_map *l_main_map) {
	t_sprite.setTexture(image);
	side			= 0;
	rect			= FloatRect(0, 0, 16, 16);
	god_mode		= false;
	currentFrame	= 0;
	dx	= dy		= 0.0;
	main_map		= l_main_map;
}

void body::update(float time) {
	l_time	= time;

	checkMove();

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

bool body::move(int i) {
	switch(i) {
		case 0:
			return body::moveDown();
			break;
		case 1:
			return body::moveUp();			
			break;
		case 2:
			return body::moveLeft();
			break;
		case 3:
			return body::moveRight();
			break;
		case 4:
			return move(rand()%4);
			break;
	}
}
bool body::moveUp() {
	dy	-= 0.1;
	return body::checkMove();
}

bool body::moveDown() {
	dy	+= 0.1;
	return body::checkMove();
}

bool body::moveLeft() {
	dx	-= 0.1;
	return body::checkMove();
}

bool body::moveRight() {
	dx	+= 0.1;
	return body::checkMove();
}

int body::getSide() {
	return side;
}

FloatRect body::getRect() {
	return rect;
}

void body::draw(RenderWindow &window) {
	window.draw(t_sprite);
}

void body::setPosition(unsigned int x, unsigned int y, int getted_side) {
	rect.left		= x * 16;
	rect.top		= y * 16;
	side			= getted_side;
}

bool body::tankComparsion(FloatRect tank_recr) {
	if (rect.intersects(tank_recr))
		return true;

	return false;
}

bool body::checkMove() {
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

	if ((dx > 0) && (((rect.left + rect.width) / 16) > main_map->getMaxX())) {		// Выход за границу справа
		dx	= 0;
		return false;
	} 

	if ((dy > 0) && (((rect.top + rect.height) / 16) > main_map->getMaxY())) {		// Выход за границу снизу
		dy	= 0;
		return false;
	}

	if ((dx < 0) && (rect.left <= 1)) {												// Выход за границу слева
		dx	= 0;
		return false;
	}

	if ((dy < 0) && (rect.top <= 1)) {												// Выход за границу сверху
		dy	= 0;
		return false;
	}

	if (((block_1	== 'w') || (block_2 == 'w')) || ((block_1	== 'a') || (block_2 == 'a')) || ((block_1	== 'v') || (block_2 == 'v'))) {
		dx	= 0;
		dy	= 0;
		return false;
	}

	return true;
}