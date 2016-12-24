#include "../include/obj.hpp"

void BottleCity::gameStart() {
	Menu menu;													// Объявление главного меню

	int		typeEnd	= 0;

	bool	gamePlay	= true;

	Game	*mainGame;

	sf::Time timePerFrame			= sf::seconds(1.f / 60.f);	// Длительность кадра (Честно стырено у Вити)
	sf::Time timeSinceLastUpdate	= sf::Time::Zero;
	sf::Clock clock2;

	sf::RenderWindow window(sf::VideoMode(400, 359), "Bottle city");	// Создание окна
	window.setVerticalSyncEnabled(true);							// Вертикальная синхронизация
	texture_.loadFromFile("media/textures.png");					// Загрузка всех текстур

	while (window.isOpen())
	{
		int	maxPlayers	= menu.draw(window, event_, texture_);		// Открытие меню и получение колличества игроков

		if (maxPlayers == 0)										// Выход из игры, если окно было закрыто
			return;

		mainGame	= new Game(maxPlayers);


		window.create(sf::VideoMode((16 * (mainGame->getMaxX() + 2)) * SCALE_X, (16 * mainGame->getMaxY()) * SCALE_Y), "Bootle city");	// Создание нового окна для начала игры

		GPause		*game_pause	= mainGame->getPausePoint();
		GameOver	*gOver 		= mainGame->getGOPoint();
		WatchDog	*watcher	= mainGame->getWatchPoint();

		while (window.isOpen())
		{
			gamePlay	= true;

			while (window.isOpen())
			{
				timeSinceLastUpdate += clock2.restart();
				time_ = clock_.getElapsedTime().asMicroseconds();	// Получение времени
				time_ = time_ / GAME_SPEED;							// Установка скорости игры

				clock_.restart();									// Сброс часиков

				if (time_ > 20)
					time_ = 20;

				while (window.pollEvent(event_))					// Отслеживание события закрытия окна
				{
					if (event_.type == sf::Event::Closed)
						window.close();
				}

				if (((sf::Keyboard::isKeyPressed(sf::Keyboard::P)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) && (!gOver->getStatus()))
				{
					game_pause->paused(window);

					while ((sf::Keyboard::isKeyPressed(sf::Keyboard::P)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)));
				}

				if (!game_pause->status())
				{
					if (!gOver->getStatus())						// Если не конец игры - обновлять игрока
						mainGame->updatePlayers(time_);

					mainGame->updateEminems(time_);

					if (!gamePlay)
						break;

					/*Отрисовка объектов Начало*/
					while (timeSinceLastUpdate > timePerFrame)
					{
						timeSinceLastUpdate -= timePerFrame;

						mainGame->drawMap(window);
						mainGame->drawActors(window);
						mainGame->drawOthers(window);

						if (gOver->getStatus())						// Если была вызвана обработка надписи Game Over
						{
							gOver->draw(window, time_);

							if (!gOver->getStatus())				// Обрабатывать надпись пока статус не изменится
								gamePlay	= false;				// Выход из цыкла
						}

						window.display();
					}
					/*Отрисовка объектов Конец*/

					if (!gOver->getStatus())						// Если не была вызвана обработка надписи Game Over
						typeEnd	= watcher->wach();					// Проверка всех составляющих победы

					if (typeEnd == WIN_PLAYER)						// Если выиграл игрок, то сразу сменить уровень
						gamePlay	= false;

					if (typeEnd == WIN_EMINEM)						// Если выиграл враг, то вызвать обработку надписи Game Over
						gOver->gameEnd();
				}

			}

			if (typeEnd == WIN_PLAYER)
			{
				mainGame->nextMap();								// Смена карты и уровня
				gamePlay	= true;
			}
			else
			{
				break;
			} 
		}

		mainGame->~Game();
	}
}