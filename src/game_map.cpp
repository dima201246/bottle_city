#include "../include/configurator.h"
#include "../include/obj.hpp"

GameMap::GameMap(Texture &image) {
	sprite_.setTexture(image);
	sprite_.scale(SCALE_X, SCALE_Y);
	maxX_	= maxY_	= grassNum_	= 0;
}

GameMap::~GameMap() {
	for (unsigned int	i	= 0; i <= maxX_; ++i)
		delete [] pMap_[i];

	for (unsigned int	i	= 0; i <= grassNum_; ++i)
		delete [] gMap_[i];

	delete [] pMap_;
	delete [] gMap_;
}

bool GameMap::loadMap(std::string path) {
	std::string	tempMap_;

	unsigned int	count		= 0;

	maxX_			= atoi(configurator(path, "max_x", "", false).c_str());
	maxY_			= atoi(configurator(path, "max_y", "", false).c_str());
	nextLevelPath_	= configurator(path, "next_level", "", false);
	tempMap_		= configurator(path, "map", "", false);

	pMap_	= new char* [maxX_ + 1];

	for (unsigned int	i	= 0; i <= maxX_; ++i)
		pMap_[i] = new char [maxY_ + 1];

	for (unsigned int	j	= 0; j < maxY_; ++j)				// Загрузка карты в массив
		for (unsigned int	i	= 0; i < maxX_; ++i)
		{
			while ((tempMap_[count] < 'a') || (tempMap_[count] > 'z'))	// Чтобы не влезла разная кака на карту
				count++;

			if (tempMap_[count] == 'g')						// Подсчёт кол-ва травы
				grassNum_++;

			if (tempMap_[count] == 'e')
			{
				eaglePos_.posX	= i;
				eaglePos_.posY	= j;
			}

			pMap_[i][j]	= tempMap_[count];
			count++;
		}

	gMap_	= new unsigned int* [grassNum_ + 1];

	for (unsigned int	i	= 0; i <= grassNum_; ++i)
		gMap_[i] = new unsigned int [2];

	count	= 0;

	for (unsigned int	i	= 0; i < maxX_; ++i)
		for (unsigned int	j	= 0; j < maxY_; ++j)
			if (pMap_[i][j] == 'g')
			{
				gMap_[count][0]	= i;
				gMap_[count][1]	= j;
				count++;
			}

	return true;
}

char GameMap::getElement(unsigned int x, unsigned int y)
{
	return pMap_[x][y];
}

void GameMap::draw(RenderWindow &window)
{
	window.clear(Color(0,0,0));

	for (unsigned int	j	= 0; j < maxY_; ++j)
	{
		for (unsigned int	i	= 0; i < maxX_; ++i)
		{
			if (pMap_[i][j] == 'w')							// Кирпичная стена
				sprite_.setTextureRect(IntRect(256, 0, 16, 16));
			else if (pMap_[i][j] == 'a')					// Бронь
				sprite_.setTextureRect(IntRect(256, 16, 16, 16));
			else if (pMap_[i][j] == 'v')					// Вода
				sprite_.setTextureRect(IntRect(256, 32, 16, 16));
			else if (pMap_[i][j] == 'i')					// Лёд, я полагаю...
				sprite_.setTextureRect(IntRect(288, 32, 16, 16));
			else if (pMap_[i][j] == 'e')					// Орёл
				sprite_.setTextureRect(IntRect(304, 32, 16, 16));
			else
				continue;

			sprite_.setPosition(i * (16 * SCALE_X), j * (16 * SCALE_Y)) ;
			window.draw(sprite_);
		}
	}
}

void GameMap::drawGrass(RenderWindow &window)
{
	sprite_.setTextureRect(IntRect(272, 32, 16, 16));

	for (unsigned int	i	= 0; i < grassNum_; ++i)
	{
		sprite_.setPosition(gMap_[i][0] * (16 * SCALE_X), gMap_[i][1] * (16 * SCALE_Y)) ; 
		window.draw(sprite_);
	}
}

unsigned int GameMap::getMaxX()
{
	return maxX_;
}

unsigned int GameMap::getMaxY()
{
	return maxY_;
}

void GameMap::setElement(char l_char, unsigned int x, unsigned int y)
{
	pMap_[x][y]	= l_char;
}

coordinate GameMap::getEaglePos()
{
	return eaglePos_;
}