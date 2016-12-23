#include "../include/obj.hpp"

Game::Game(const Game &oGame)	// Копиконструктор
{
	players_	= new Player[oGame.maxPlayers_];					// Создание игроков
	eminems_	= new AIplayer[oGame.maxEminems_];				// Создание врагов

	for (int	i	= 0; i < oGame.maxPlayers_; ++i)
		players_[i]	= oGame.players_[i];

	for (int	i	= 0; i < oGame.maxEminems_; ++i)
		eminems_[i]	= oGame.eminems_[i];
}

Game::~Game() {
	if (maxPlayers_ != 0)
	{
		delete [] eminems_;
		delete [] players_;
	}
}

void Game::gameStart() {
	maxEminems_	= 20;
	Menu menu;

	bool first_interapt	= true;

	sf::RenderWindow window(sf::VideoMode(400, 359), "Bottle city");	// Создание окна

	window.setVerticalSyncEnabled(true);						// Вертикальная синхронизация

	texture_.loadFromFile("media/textures.png");				// Загрузка всех текстур

	maxPlayers_	= menu.draw(window, event_, texture_);			// Открытие меню и получение колличества игроков

	if (maxPlayers_ == 0)										// Выход из игры, если окно было закрыто
		return;

	GameMap main_map(texture_);									// Загрузка текстур в карту
	main_map.loadMap("media/maps/level1.map");					// Загрузка карты из файла

	window.create(sf::VideoMode((16 * (main_map.getMaxX() + 2)) * SCALE_X, (16 * main_map.getMaxY()) * SCALE_Y), "Bootle city");	// Создание нового окна для начала игры

	players_		= new Player[maxPlayers_];					// Создание игроков
	eminems_		= new AIplayer[maxEminems_];				// Создание врагов

	WachDog		wacher(&main_map, players_, maxPlayers_);		// Объявление следилки

	RightBar	r_b(texture_, main_map.getMaxX(), maxEminems_, 1, 3, 3);	// Объявление правого бара
	GPause		game_pause(texture_, &main_map);				// Объявление паузы

	players_[0].init(texture_, players_, maxPlayers_, eminems_, maxEminems_, &main_map, &r_b, 3, 1, maxEminems_, 1);	// Задача стандартных параметров для игроков

	if (maxPlayers_	== 2)										// Инициализация второго игрока, если он нужен
		players_[1].init(texture_, players_, maxPlayers_, eminems_, maxEminems_, &main_map, &r_b, 3, 1, maxEminems_, 2);

	for (int	i = 0; i < maxEminems_; ++i)					// Задача стандартных параметров для врага
	{
		eminems_[i].init(texture_, players_, maxPlayers_, eminems_, maxEminems_, &main_map, &r_b, 1, 1, i + 1);
	}

		eminems_[0].activation(0, 0);	/// TEST
		eminems_[1].activation(6, 0);
		eminems_[2].activation(12, 0);


	while (window.isOpen())
	{
		time_ = clock_.getElapsedTime().asMicroseconds();		// Получение времени
		clock_.restart();										// Сброс часиков

		time_ = time_ / GAME_SPEED;								// Установка скорости игры

		if (time_ > 20)
			time_ = 20;

		while (window.pollEvent(event_))						// Отслеживание события закрытия окна
		{
			if (event_.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			game_pause.paused(window);

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::P));
		}

		if (!game_pause.status())
		{
			for (int	i	= 0; i < maxPlayers_; ++i)			// Обновление игроков
				players_[i].update(time_);

			for (int	i	= 0; i < maxEminems_; ++i)			// Обновление врагов
				eminems_[i].update(time_);

			/*Отрисовка объектов Начало*/

			main_map.draw(window);								// Отрисовка карты

			for (int	i	= 0; i < maxPlayers_; ++i)			// Отрисовка игроков
				players_[i].draw(window);

			for (int	i	= 0; i < maxEminems_; ++i)			// Отрисовка врагов
				eminems_[i].draw(window);

			if ((wacher.wach() == WIN_PLAYER) || (wacher.wach() == WIN_EMINEM))
				return;

			main_map.drawGrass(window);							// Отрисовка травы

			r_b.draw(window);

			/*Отрисовка объектов Конец*/
		}

		window.display();
	}
}