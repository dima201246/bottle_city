#include "../include/obj.hpp"

Game::Game(int int_nPlayers)
{
	texture_.loadFromFile("media/textures.png");	// Загрузка всех текстур

	mainMap_	= new GameMap(texture_);			// Загрузка текстур в карту

	mainMap_->loadMap("level1.map", maxEminems_);	// Загрузка карты из файла

	gOver		= new GameOver(texture_, mainMap_);	// Штука для вывода надписи о конце игры

	rightBar_	= new RightBar(texture_, mainMap_->getMaxX(), maxEminems_, 1, 3, (maxPlayers_ == 2 ? 3 : 0));	// Объявление правого бара

	pauseMenu_	= new GPause(texture_, mainMap_);	// Объявление паузы

	/*Инициализация действующих лиц Начало*/
	maxPlayers_	= int_nPlayers;
	players_	= new Player[int_nPlayers];			// Создание игроков
	initEminems(false);

	players_[0].init(texture_, players_, maxPlayers_, mainMap_, rightBar_, 3, 1, maxEminems_, 1);	// Задача стандартных параметров для игроков

	if (maxPlayers_	== 2)							// Инициализация второго игрока, если он нужен
		players_[1].init(texture_, players_, maxEminems_, mainMap_, rightBar_, 3, 1, maxEminems_, 2);
	/*Инициализация действующих лиц Конец*/

	watcher_	= new WatchDog(mainMap_, players_, maxPlayers_);	// Объявление следилки
}

Game::~Game()
{
	if (maxPlayers_ != 0)
	{
		delete [] players_;
		delete [] eminems_;
		delete mainMap_;
		delete watcher_;
		delete pauseMenu_;
		delete rightBar_;
		delete gOver;
	}
}

void Game::initEminems(bool clearArray)
{
	if (clearArray)									// Очистка, если она нужна
	{
		delete [] eminems_;
	}

	eminems_	= new AIplayer[maxEminems_];		// Создание врагов

	for (int	i = 0; i < maxEminems_; ++i)		// Задача стандартных параметров для врага
	{
		eminems_[i].init(texture_, eminems_, maxEminems_, mainMap_, rightBar_, 1, 1, i + 1);
		eminems_[i].setPlayersPoint(players_, maxPlayers_);
	}

	eminems_[0].activation(0, 0);	/// TEST
	eminems_[1].activation(6, 0);
	eminems_[2].activation(12, 0);

	players_[0].setEminemsPoint(eminems_, maxEminems_);

	if (maxPlayers_	== 2)
		players_[1].setEminemsPoint(eminems_, maxEminems_);
}

void Game::nextMap()
{
	mainMap_->nextLevel(maxEminems_);

	initEminems(maxEminems_);


}

GPause *Game::getPausePoint()
{
	return pauseMenu_;
}

void Game::updatePlayers(float time)
{
	for (int	i	= 0; i < maxPlayers_; ++i)		// Обновление игроков
		players_[i].update(time);
}

void Game::updateEminems(float time)
{
	for (int	i	= 0; i < maxEminems_; ++i)		// Обновление врагов
		eminems_[i].update(time);
}

void Game::drawActors(sf::RenderWindow& window)
{
	for (int	i	= 0; i < maxPlayers_; ++i)		// Отрисовка игроков
		players_[i].draw(window);

	for (int	i	= 0; i < maxEminems_; ++i)		// Отрисовка врагов
		eminems_[i].draw(window);
}

void Game::drawOthers(sf::RenderWindow& window)
{
	mainMap_->drawGrass(window);					// Отрисовка травы
	rightBar_->draw(window);						// Отрисовка правой панели
}

void Game::drawMap(sf::RenderWindow& window)
{
	mainMap_->draw(window);							// Отрисовка карты
}

GameOver *Game::getGOPoint()
{
	return gOver;
}

WatchDog *Game::getWatchPoint()
{
	return watcher_;
}

unsigned int Game::getMaxX()
{
	return mainMap_->getMaxX();
}

unsigned int Game::getMaxY()
{
	return mainMap_->getMaxY();
}