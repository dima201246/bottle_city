#include "../include/configurator.h"
#include "../include/obj.hpp"

GameMap::GameMap(sf::Texture &image, sf::RenderWindow &window)
{
	texture_	= &image;
	window_		= &window;
	sprite_.setTexture(image);
	sprite_.scale(SCALE_X, SCALE_Y);
	maxX_	= maxY_	= grassNum_	= 0;
}

/*GameMap::GameMap(sf::Texture &image)
{
	sprite_.setTexture(image);
	sprite_.scale(SCALE_X, SCALE_Y);
	maxX_	= maxY_	= grassNum_	= 0;
}*/

GameMap::~GameMap() {
	for (unsigned int	i	= 0; i <= maxX_; ++i)
		delete [] pMap_[i];

	for (unsigned int	i	= 0; i <= grassNum_; ++i)
		delete [] gMap_[i];

	delete [] pMap_;
	delete [] gMap_;
}

std::string fixBug(std::string line)
{
	std::string temp;
	temp.clear();

	for (unsigned int i = 0; i < line.length(); ++i)	// Для того, чтобы случайно не съело каку
		if (line[i] != 13)
			temp += line[i];

	return	temp;
}

bool GameMap::loadMap(std::string path, int &nEminems)
{
	std::string	tempMap_;

	path			= MAIN_PATH_MAP + fixBug(path);

	unsigned int	count		= 0;
	grassNum_					= 0;

	nEminems		= atoi(configurator(path, "nEnemy", "", false).c_str());

	eSpawn_[0].posX	= atoi(configurator(path, "enemy1X", "", false).c_str());
	eSpawn_[0].posY	= atoi(configurator(path, "enemy1Y", "", false).c_str());
	eSpawn_[1].posX	= atoi(configurator(path, "enemy2X", "", false).c_str());
	eSpawn_[1].posY	= atoi(configurator(path, "enemy2Y", "", false).c_str());
	eSpawn_[2].posX	= atoi(configurator(path, "enemy3X", "", false).c_str());
	eSpawn_[2].posY	= atoi(configurator(path, "enemy3Y", "", false).c_str());

	pSpawn_[0].posX	= atoi(configurator(path, "player1X", "", false).c_str());
	pSpawn_[0].posY	= atoi(configurator(path, "player1Y", "", false).c_str());
	pSpawn_[1].posX	= atoi(configurator(path, "player2X", "", false).c_str());
	pSpawn_[1].posY	= atoi(configurator(path, "player2Y", "", false).c_str());

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
	if ((x > maxX_) || (y > maxY_))
		return ' ';

	return pMap_[x][y];
}

void GameMap::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(0,0,0));

	for (unsigned int	j	= 0; j < maxY_; ++j)
	{
		for (unsigned int	i	= 0; i < maxX_; ++i)
		{
			if (pMap_[i][j] == 'w')							// Кирпичная стена
				sprite_.setTextureRect(sf::IntRect(256, 0, 16, 16));
			else if (pMap_[i][j] == 'a')					// Бронь
				sprite_.setTextureRect(sf::IntRect(256, 16, 16, 16));
			else if (pMap_[i][j] == 'v')					// Вода
				sprite_.setTextureRect(sf::IntRect(256, 32, 16, 16));
			else if (pMap_[i][j] == 'i')					// Лёд, я полагаю...
				sprite_.setTextureRect(sf::IntRect(288, 32, 16, 16));
			else if (pMap_[i][j] == 'e')					// Орёл
				sprite_.setTextureRect(sf::IntRect(304, 32, 16, 16));
			else if (pMap_[i][j] == 'd')					// Мёртвый орёл
				sprite_.setTextureRect(sf::IntRect(320, 32, 16, 16));
			else
				continue;

			sprite_.setPosition(i * (16 * SCALE_X), j * (16 * SCALE_Y)) ;
			window.draw(sprite_);
		}
	}
}

void GameMap::drawGrass(sf::RenderWindow &window)
{
	sprite_.setTextureRect(sf::IntRect(272, 32, 16, 16));

	for (unsigned int	i	= 0; i < grassNum_; ++i)
	{
		sprite_.setPosition(gMap_[i][0] * (16 * SCALE_X), gMap_[i][1] * (16 * SCALE_Y)) ; 
		window.draw(sprite_);
	}
}

void GameMap::randomMap(){
	char block;
	unsigned int	arm 	= 5,
					grass 	= 7,
					wall	= 50,
					ice 	= 10,
					water	= 10;
					// eagle	= 1;

	bool temp;
	int rnd;
	gMap_	= new unsigned int* [grass + 1];

	for (unsigned int	i	= 0; i <= grass; ++i)
		gMap_[i] = new unsigned int [2];


	for (unsigned int j = 0; j < maxY_; ++j)
	{
		for (unsigned int i = 0; i < maxX_; ++i)
		{
			GameMap::setElement('s', j, i); // очистка карты
		}
	}
	for (unsigned int j = 0; j < maxY_; ++j)
	{
		for (unsigned int i = 0; i < maxX_; ++i)
		{
			temp = true;
			if (((j == 0) && (i==0)) || ((j == 6) && (i==0)) || ((j == 12) && (i == 0)) || ((j == 4) && (i == 12)) || ((j == 8) && (i == 12))) // точки респа стандартно пусты
			{
				block = 's';
			} else {
				while(temp) { // пока чем-то не заполним (если рандом выпал, а блоков этого типа уже не надо)
					rnd = rand()%6;
					switch(rnd){ // рандомно заполняем карту
						case 0:
						if (arm >0)
						{	
							arm--;
							block = 'a';
							temp = false;
						}
						break;
						case 1:
						if (grass >0)
						{
							grass--;
							block = 'g';
							temp = false;
						}
						break;
						case 2:
						if (wall >0)
						{
							wall--;
							block = 'w';
							temp = false;
						}
						break;
						case 3:
						if (ice >0)
						{
							ice--;
							block = 'i';
							temp = false;
						}
						break;
						case 4:
						if (water >0)
						{
							water--;
							block = 'w';
							temp = false;
						}
						break;
						case 5:
						block = 's';
						temp = false;
						break;
					}
				}
			}
			GameMap::setElement(block, j, i);
		}
	}
	GameMap::setElement('e', (rand()%(maxY_-2)+1), (rand()%maxX_)); // спавн орла, верняя и нижняя линии не используются чтоб не пересекться с спавнами остальных

	rnd	= 0;

	for (unsigned int	i	= 0; i < maxX_; ++i)
		for (unsigned int	j	= 0; j < maxY_; ++j)
			if (pMap_[i][j] == 'g')
			{
				gMap_[rnd][0]	= i;
				gMap_[rnd][1]	= j;
				rnd++;
			}
}

void GameMap::nextLevel(int &nEminems)
{
	for (unsigned int	i	= 0; i <= maxX_; ++i)		// Очистка перед загрузкой новой карты
		delete [] pMap_[i];

	for (unsigned int	i	= 0; i <= grassNum_; ++i)
		delete [] gMap_[i];

	delete [] pMap_;
	delete [] gMap_;


	nextLevelPath_	= fixBug(nextLevelPath_);

	if (nextLevelPath_ != "none")
		loadMap(nextLevelPath_, nEminems);
	else
		randomMap();
}

void GameMap::levelHeadpiece(int level)	// Это писалось в 7 утра, абсолютный говнокод, НЕ СМОТРЕТЬ!!!
{
	unsigned int	i			= 0;

	sf::Sprite		stageSprite;

	stageSprite.setTexture(*texture_);
	stageSprite.scale(SCALE_X, SCALE_Y) ;

	sf::RectangleShape rectangle(sf::Vector2f((((maxX_ + 2) * 16) * SCALE_X), 10));// определяем прямоугольник размером 120x50
 
 	rectangle.setFillColor (sf::Color(99, 99, 99));

	while (i < (((maxY_) * 16) * SCALE_Y))
	{
		rectangle.setSize(sf::Vector2f((((maxX_ + 2) * 16) * SCALE_X), i));
		i += 10;
		window_->draw(rectangle);
		window_->display();
	}

	stageSprite.setPosition((maxX_ * 16 * SCALE_X) / 2 - (12 * SCALE_X), (maxY_ * 16 * SCALE_Y) / 2 - (4 * SCALE_Y)) ;
	stageSprite.setTextureRect(sf::IntRect(328, 175, 40, 9));

	window_->draw(stageSprite);
	stageSprite.setPosition(((maxX_ * 16 * SCALE_X) / 2) + (30 * SCALE_X), (maxY_ * 16 * SCALE_Y) / 2 - (4 * SCALE_Y)) ;

	switch (level / 10)
	{
		case 0:	stageSprite.setTextureRect(sf::IntRect(328, 183, 8, 8)); break;
		case 1:	stageSprite.setTextureRect(sf::IntRect(336, 183, 8, 8)); break;
		case 2:	stageSprite.setTextureRect(sf::IntRect(344, 183, 8, 8)); break;
		case 3:	stageSprite.setTextureRect(sf::IntRect(352, 183, 8, 8)); break;
		case 4:	stageSprite.setTextureRect(sf::IntRect(360, 183, 8, 8)); break;
		case 5:	stageSprite.setTextureRect(sf::IntRect(328, 191, 8, 8)); break;
		case 6:	stageSprite.setTextureRect(sf::IntRect(336, 191, 8, 8)); break;
		case 7:	stageSprite.setTextureRect(sf::IntRect(344, 191, 8, 8)); break;
		case 8:	stageSprite.setTextureRect(sf::IntRect(352, 191, 8, 8)); break;
		case 9:	stageSprite.setTextureRect(sf::IntRect(360, 191, 8, 8)); break;
	}

	window_->draw(stageSprite);
	stageSprite.setPosition((((maxX_ + 1) * 16 * SCALE_X) / 2) + (30 * SCALE_X), (maxY_ * 16 * SCALE_Y) / 2 - (4 * SCALE_Y)) ;

	switch (level % 10)
	{
		case 0:	stageSprite.setTextureRect(sf::IntRect(328, 183, 8, 8)); break;
		case 1:	stageSprite.setTextureRect(sf::IntRect(336, 183, 8, 8)); break;
		case 2:	stageSprite.setTextureRect(sf::IntRect(344, 183, 8, 8)); break;
		case 3:	stageSprite.setTextureRect(sf::IntRect(352, 183, 8, 8)); break;
		case 4:	stageSprite.setTextureRect(sf::IntRect(360, 183, 8, 8)); break;
		case 5:	stageSprite.setTextureRect(sf::IntRect(328, 191, 8, 8)); break;
		case 6:	stageSprite.setTextureRect(sf::IntRect(336, 191, 8, 8)); break;
		case 7:	stageSprite.setTextureRect(sf::IntRect(344, 191, 8, 8)); break;
		case 8:	stageSprite.setTextureRect(sf::IntRect(352, 191, 8, 8)); break;
		case 9:	stageSprite.setTextureRect(sf::IntRect(360, 191, 8, 8)); break;
	}

	window_->draw(stageSprite);
	window_->display();
	sleep(2);
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

coordinate *GameMap::getEminemsPos()
{
	return eSpawn_;
}

coordinate *GameMap::getPlayersPos()
{
	return pSpawn_;
}