#include "../include/obj.hpp"
#include <cmath>

void Body::init(Texture &image, GameMap *l_main_map) {
	MainPoint::sprite.setTexture(image);
	MainPoint::sprite.scale(SCALE_X, SCALE_Y);

	side			= 0;
	rect			= FloatRect(0, 0, 16, 16);
	god_mode		= false;
	dx	= dy		= 0.0;
	main_map		= l_main_map;
}

void Body::update(float time)
{
	if ((dx != 0) && (dy != 0))			// Сброс, если косое движение
	{
		dx	= 0;
		dy	= 0;
	}

	checkMove();

	rect.left	+= dx * (time / 2.0);	// Собсно, движение
	rect.top 	+= dy * (time / 2.0);

	MainPoint::sprite.setTextureRect(IntRect(0 + (side * 16), 0, 15, 15));	// Установка текстуры в зависимомти от стороны в которую смотрит танк

	MainPoint::sprite.setPosition(rect.left * SCALE_X, rect.top * SCALE_Y);

	dx=0;
	dy=0;
}


bool Body::move(int i) {
	switch(i) {
		case 0:
			return Body::moveUp();
			break;
		case 2:
			return Body::moveLeft();
			break;
		case 4:
			return Body::moveDown();
			break;
		case 6:
			return Body::moveRight();
			break;
		case 8:
			return move(2*(rand()%4));
			break;
	}
}

bool Body::moveUp()
{
	dy	= -0.1;
	return Body::checkMove();
}

bool Body::moveDown()
{
	dy	= 0.1;
	return Body::checkMove();
}

bool Body::moveLeft() {
	dx	= -0.1;
	return Body::checkMove();
}

bool Body::moveRight()
{
	dx	= 0.1;
	return Body::checkMove();
}

int Body::getSide()
{
	return side;
}

void Body::draw(RenderWindow &window)
{
	window.draw(MainPoint::sprite);
}

void Body::setPosition(unsigned int x, unsigned int y, int getted_side)
{
	rect.left		= x * 16;
	rect.top		= y * 16;
	side			= getted_side;
}

bool Body::tankComparsion(FloatRect tank_recr)
{
	if (rect.intersects(tank_recr))
		return true;

	return false;
}

bool Body::checkMove()
{
	char	block_1, block_2;

	if (dx < 0)
	{
		block_1	= main_map->getElement((int)floor((rect.left - 1) / 16), (int)floor(rect.top / 16));
		block_2	= main_map->getElement((int)floor((rect.left - 1) / 16), (int)floor((rect.top + rect.height - 1) / 16));
		side	= 2;
	}
	else if (dx > 0)
	{
		block_1	= main_map->getElement((int)floor(((rect.left) + rect.width) / 16), (int)floor(rect.top / 16));
		block_2	= main_map->getElement((int)floor(((rect.left) + rect.width) / 16), (int)floor((rect.top + rect.height - 1) / 16));
		side	= 6;
	}
	else if (dy < 0)
	{
		block_1	= main_map->getElement((int)floor((rect.left) / 16), (int)floor((rect.top - 1) / 16));
		block_2	= main_map->getElement((int)floor((rect.left + rect.width - 1) / 16), (int)floor((rect.top - 1) / 16));
		side	= 0;
	}
	else if (dy > 0)
	{
		block_1	= main_map->getElement((int)floor(rect.left / 16), (int)floor((rect.top + rect.height) / 16));
		block_2	= main_map->getElement((int)floor((rect.left + rect.width - 1) / 16), (int)floor((rect.top + rect.height) / 16));
		side	= 4;
	}

	if ((dx > 0) && (((rect.left + rect.width) / 16) >= main_map->getMaxX()))		// Выход за границу справа
	{
		dx	= 0;
		return false;
	}

	if ((dy > 0) && (((rect.top + rect.height) / 16) >= main_map->getMaxY()))		// Выход за границу снизу
	{
		dy	= 0;
		return false;
	}

	if ((dx < 0) && (rect.left <= 1))												// Выход за границу слева
	{
		dx	= 0;
		return false;
	}

	if ((dy < 0) && (rect.top <= 1))												// Выход за границу сверху
	{
		dy	= 0;
		return false;
	}

	if (((block_1	== 'w') || (block_2 == 'w')) || ((block_1	== 'a') || (block_2 == 'a')) || ((block_1	== 'v') || (block_2 == 'v')))
	{
		dx	= 0;
		dy	= 0;
		return false;
	}

	return true;
}