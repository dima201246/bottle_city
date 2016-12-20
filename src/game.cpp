#include "../include/obj.hpp"

game::~game() {
	delete [] players;
	delete [] eminems;
}

void game::gameStart() {
	bool first_interapt	= true;

	players		= new player[MAX_PLAYERS];						// Создание игроков
	eminems		= new AIplayer[MAX_EMINEMS];					// Создание врагов

	RenderWindow window(VideoMode((16 * 15) * SCALE_X, (16 * 13) * SCALE_Y), "Bottle city");	// Создание окна

	window.setVerticalSyncEnabled(true);						// Вертикальная синхронизация

	texture.loadFromFile("media/textures.png");					// Загрузка всех текстур

	game_map main_map(texture);									// Загрузка текстур в карту
	main_map.loadMap("media/maps/level1.map");					// Загрузка карты из файла

	right_bar	r_b(texture, main_map.getMaxX(), MAX_EMINEMS, 1, 3, 3);
	g_pause	game_pause(texture, &main_map);

	players[0].init(texture, players, MAX_PLAYERS, eminems, MAX_EMINEMS, &main_map, &r_b, 3, 1, MAX_EMINEMS, 1);	// Задача стандартных параметров для игроков
	players[1].init(texture, players, MAX_PLAYERS, eminems, MAX_EMINEMS, &main_map, &r_b, 3, 1, MAX_EMINEMS, 2);

	for (int	i = 0; i < MAX_EMINEMS; ++i) {					// Задача стандартных параметров для врага
		eminems[i].init(texture, players, MAX_PLAYERS, eminems, MAX_EMINEMS, &main_map, &r_b, 1, 1, i + 1);
	}

		eminems[0].activation(0, 0);	/// TEST
		eminems[1].activation(6, 0);
		eminems[2].activation(12, 0);


	while (window.isOpen()) {
		time = clock.getElapsedTime().asMicroseconds();			// Получение времени
		clock.restart();										// Сброс часиков

		time = time / GAME_SPEED;								// Установка скорости игры

		if (time > 20)
			time = 20;

		while (window.pollEvent(event)) {						// Отслеживание события закрытия окна
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::P)) {
			game_pause.paused(window);
			usleep(100000);
		}

		if (!game_pause.status()) {
			for (int	i	= 0; i < MAX_PLAYERS; ++i)				// Обновление игроков
				players[i].update(time);

			for (int	i	= 0; i < MAX_EMINEMS; ++i)				// Обновление врагов
				eminems[i].update(time);

			/*Отрисовка объектов Начало*/

			main_map.draw(window);									// Отрисовка карты

			for (int	i	= 0; i < MAX_PLAYERS; ++i)				// Отрисовка игроков
				players[i].draw(window);

			for (int	i	= 0; i < MAX_EMINEMS; ++i)				// Отрисовка врагов
				eminems[i].draw(window);

			main_map.drawGrass(window);								// Отрисовка травы

			r_b.draw(window);

        	window.display();
			/*Отрисовка объектов Конец*/
		}

		// usleep(10000);												// Оптимизация
	}
}