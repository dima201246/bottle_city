#include "include/obj.hpp"
#include <string>

using namespace std;

#define MAX_PLAYERS	2
#define MAX_EMINEMS	20

#define GAME_SPEED	900

#define UP_SIDE		0
#define LEFT_SIDE	2
#define DOWN_SIDE	4
#define RIGHT_SIDE	6

int main() {
	Clock			clock;										// Переменная, для слежения за временем

	Texture 		texture;

	Event 			event;

	float			time;

	bool			k_l,
					k_r,
					k_u,
					k_d;

	tank			players[MAX_PLAYERS],						// Создание игроков
					eminems[MAX_EMINEMS];

	RenderWindow window(VideoMode(512, 480), "Bottle city");	// Создание окна
	texture.loadFromFile("media/textures.png");					// Загрузка всех текстур

	game_map main_map(texture);
	main_map.loadMap("media/maps/level1.map");

	players[0].init(texture, 1, 2, eminems, MAX_EMINEMS, &main_map);
	players[1].init(texture, 2, 0, eminems, MAX_EMINEMS, &main_map);

	for (int	i = 0; i < MAX_EMINEMS; ++i) {
		eminems[i].init(texture, 0, 1, players, MAX_PLAYERS, &main_map);
	}

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

		/*Защита от диагоналей Начало*/
		k_d	= true;
		k_u	= true;
		k_r	= true;
		k_l	= true;

		if ((Keyboard::isKeyPressed(Keyboard::Left)) && (Keyboard::isKeyPressed(Keyboard::Down))) {
			if (players[0].getSide() == LEFT_SIDE)	k_d	= false;
			else k_l	= false;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left)) && (Keyboard::isKeyPressed(Keyboard::Up)))	{
			if (players[0].getSide() == LEFT_SIDE)	k_u	= false;
			else k_l	= false;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Down))) {
			if (players[0].getSide() == RIGHT_SIDE)	k_d	= false;
			else k_r	= false;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Up))) {
			if (players[0].getSide() == RIGHT_SIDE)	k_u	= false;
			else k_r	= false;
		}
		/*Защита от диагоналей Конец*/

		/*Обработка кнопок Начало*/
		if ((Keyboard::isKeyPressed(Keyboard::Left)) && (k_l)) {
			players[0].move_left();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right)) && (k_r)) {
			players[0].move_right();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (k_u)) {
			players[0].move_up();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down)) && (k_d)) {
			players[0].move_down();
		}

		if (Keyboard::isKeyPressed(Keyboard::Z)) {
			players[0].piu_piu();
		}
		/*Обработка кнопок Конец*/

		for (int	i	= 0; i < MAX_PLAYERS; ++i)				// Отрисовка игроков
			players[i].update(time);

		/*Отрисовка объектов Начало*/
		main_map.draw(window);

		for (int	i	= 0; i < MAX_PLAYERS; ++i)			// Отрисовка игроков
			players[i].draw(window);

		main_map.drawGrass(window);

        window.display();
		/*Отрисовка объектов Конец*/
	}

	return 0;
}