#include "../include/obj.hpp"

game::~game() {
	delete [] players;
	delete [] eminems;
}

void game::gameStart() {

	players		= new player[MAX_PLAYERS];						// Создание игроков
	eminems		= new AIplayer[MAX_EMINEMS];					// Создание врагов

	RenderWindow window(VideoMode(512, 480), "Bottle city");	// Создание окна
	texture.loadFromFile("media/textures.png");					// Загрузка всех текстур

	game_map main_map(texture);									// Загрузка текстур в карту
	main_map.loadMap("media/maps/level1.map");					// Загрузка карты из файла

	g_pause	game_pause(texture, &main_map);

	players[0].init(texture, players, MAX_PLAYERS, eminems, MAX_EMINEMS, &main_map, 3, 1, 20, 1);	// Задача стандартных параметров для игроков
	players[1].init(texture, players, MAX_PLAYERS, eminems, MAX_EMINEMS, &main_map, 3, 1, 20, 2);

	for (int	i = 0; i < MAX_EMINEMS; ++i) {					// Задача стандартных параметров для врага
		eminems[i].init(texture, players, MAX_PLAYERS, &main_map, false, 1, 1);
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

        	window.display();
			/*Отрисовка объектов Конец*/
		}
	}
}