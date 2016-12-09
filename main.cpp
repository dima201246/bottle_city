#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <iostream>

using namespace sf;
using namespace std;

#define MAX_PLAYERS	2
#define MAX_EMINEMS	20

#define GAME_SPEED	900

#define UP_SIDE		0
#define LEFT_SIDE	2
#define DOWN_SIDE	4
#define RIGHT_SIDE	6

int maxX	= 13,
	maxY	= 13; 

string first_map[13]	= {
" wwwww wwwww ",
"w  w     w  w",
"   wi   iw   ",
"   wi   iw   ",
"   wi   iw   ",
"   wi w iw   ",
"   wi   iw   ",
"   wiaaaiw   ",
"vvvwgggggwvvv",
"             ",
"     www     ",
"     wews    "
};

class tank;

class bullet {
	int	side,
					other_tanks_num;

	bool			status;

	float			dx,
					dy;

	SoundBuffer		buffer_shot,
					buffer_un_shot;

	tank			*other_tanks;

	FloatRect		rect;
	Sound 			*sound_shot,
					*sound_un_shot;

	void collision();
public:

	Sprite			sprite;

	bullet() {
		buffer_shot.loadFromFile("media/sound/shot.ogg");
		sound_shot		= new Sound(buffer_shot);
		buffer_un_shot.loadFromFile("media/sound/un_shot.ogg");
		sound_un_shot	= new Sound(buffer_un_shot);
		rect			= FloatRect(0, 0, 8, 8);
		dx	= dy		= 0.0;
		status			= false;
		rect.left		= 0;
		rect.top		= 0;
	}

	~bullet() {
		delete sound_shot;
		delete sound_un_shot;
	}

	void init(Texture &image, tank *g_other_tanks, int g_other_tanks_num) {
		sprite.setTexture(image);
		other_tanks		= g_other_tanks;
		other_tanks_num	= g_other_tanks_num;
	}

	void update(float time) {
		if ((dx	!= 0) || (dy != 0)) {	// Защита от выхода за границы
			if ((dx > 0) && (((rect.left + rect.width) / 16) > maxX))
				dx	= 0;

			if ((dy > 0) && (((rect.top + rect.height) / 16) > (maxY - 1)))
				dy	= 0;

			if ((dx < 0) && (rect.left <= 1))
				dx	= 0;

			if ((dy < 0) && (rect.top <= 1))
				dy	= 0;

			collision();

			if ((dx == 0) && (dy == 0)) {
				sound_un_shot->play();
				status	= false;
			}
		}

		if (status) {
			rect.left	+= dx * (time * 1.5);
			rect.top	+= dy * (time * 1.5);
			sprite.setPosition(rect.left, rect.top);
		}


	}

	void shot(int posX, int posY, int side) {
		sound_shot->play();
		sprite.setTextureRect(IntRect(320 + ((side / 2) * 8), 100, 8, 8));
		if (side == 0) {
			rect.left	= posX + 3,
			rect.top	= posY - 4;
			dy			= -0.1;
		} else if (side == 2) {
			rect.left	= posX - 3,
			rect.top	= posY + 4;
			dx			= -0.1;
		} else if (side == 4) {
			rect.left	= posX + 3,
			rect.top	= posY + 13;
			dy			= 0.1;
		} else if (side == 6) {
			rect.left	= posX + 13,
			rect.top	= posY + 4;
			dx			= 0.1;
		}

		status	= true;
	}

	bool active() {
		return status;
	}
};

class tank {
	int				life,
					level,
					left_tank,
					currentFrame,
					num_of_player,
					side,
					other_tanks_num;

	float			dx,
					dy,
					l_time;

	tank			*other_tanks;

	FloatRect		rect;

	bool			god_mode,
					ii;

	Sprite			t_sprite;

	bullet			shell;

	void collision() {
		char	block_1, block_2;

		if (dx < 0) {
			block_1	= first_map[(int)((rect.top + 1) / 16)][(int)((rect.left - 1) / 16)];
			block_2	= first_map[(int)((rect.top + 15) / 16)][(int)((rect.left - 1) / 16)];
			side	= 2;
		} else  if (dx > 0) {
			block_1	= first_map[(int)(rect.top / 16)][(int)((rect.left + 16) / 16)];
			block_2	= first_map[(int)((rect.top + 15) / 16)][(int)((rect.left + 16) / 16)];
			side	= 6;
		} else if (dy < 0) {
			block_1	= first_map[(int)((rect.top - 1) / 16)][(int)((rect.left + 1) / 16)];
			block_2	= first_map[(int)((rect.top - 1) / 16)][(int)((rect.left + 15) / 16)];
			side	= 0;
		} else if (dy > 0) {
			block_1	= first_map[(int)((rect.top + 16) / 16)][(int)(rect.left / 16)];
			block_2	= first_map[(int)((rect.top + 16) / 16)][(int)((rect.left + 15) / 16)];
			side	= 4;
		}

		if (((block_1	== 'w') || (block_2 == 'w')) || ((block_1	== 'a') || (block_2 == 'a')) || ((block_1	== 'v') || (block_2 == 'v'))) {
			dx	= 0;
			dy	= 0;
		}
	}

public:

	tank(){}
	~tank(){}

	void init(Texture &image, int num, bool g_ii, int g_life, tank *g_other_tanks, int g_other_tanks_num) {
		t_sprite.setTexture(image);
		shell.init(image, g_other_tanks, g_other_tanks_num);
		side			= 0;
		life			= g_life;
		level			= 1;
		other_tanks		= g_other_tanks;
		other_tanks_num	= g_other_tanks_num;
		ii				= g_ii;
		num_of_player	= num;
		rect			= FloatRect(0, 0, 16, 16);
		god_mode		= false;
		left_tank		= 16;
		currentFrame	= 0;
		dx	= dy		= 0.0;
		rect.left		= 128;
		rect.top		= 176;
	}

	void update(float time) {
		l_time	=time;

		if ((dx	!= 0) || (dy != 0)) {	// Защита от выхода за границы
			if ((dx > 0) && (((rect.left + rect.width) / 16) > maxX)) dx	= 0;
			if ((dy > 0) && (((rect.top + rect.height) / 16) > (maxY - 1))) dy	= 0;
			if ((dx < 0) && (rect.left <= 1)) dx	= 0;
			if ((dy < 0) && (rect.top <= 1)) dy	= 0;

			collision();
		}

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

	void piu_piu() {
		if (!shell.active()) {
			shell.shot(rect.left, rect.top, side);
		}
	}

	void move_up() {
		dy	-= 0.1;
	}

	void move_down() {
		dy	+= 0.1;
	}

	void move_left() {
		dx	-= 0.1;
	}

	void move_right() {
		dx	+= 0.1;
	}

	int getSide() {
		return side;
	}

	FloatRect getRect() {
		return rect;
	}

	int getLeft_tank() {
		return left_tank;
	}

	int getLife() {
		return life;
	}

	void draw(RenderWindow &window) {
		if (life == 0)
			return;

		window.draw(t_sprite);

		if (shell.active()) {
			shell.update(l_time);
			window.draw(shell.sprite);
		}
	}
};

void bullet::collision() {
		if (dx != 0) {
			if (first_map[int((rect.top + 3) / 16)][int(rect.left / 16)] == 'w') {
				first_map[int((rect.top + 3) / 16)][int(rect.left / 16)]	= ' ';
				dx	= 0;
			}

			if (first_map[int((rect.top + 3) / 16)][int(rect.left / 16)] == 'a') {
				dx	= 0;
			}
		}

		if (dy != 0) {
			if (first_map[int(rect.top / 16)][int((rect.left + 3) / 16)] == 'w') {
				first_map[int(rect.top / 16)][int((rect.left + 3) / 16)]	= ' ';
				dy	= 0;
			}

			if (first_map[int(rect.top / 16)][int((rect.left + 3) / 16)] == 'a') {
				dy	= 0;
			}
		}

		if (dx != dy) {
			for (int	i	= 0; i < other_tanks_num; ++i) {
				if (rect.intersects(other_tanks[i].getRect())) {	// Проверка, попала ли пуля в кого-нибудь

				}
			}
		}
	}

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

	Sprite			sprite(texture);							// Загрузка спрайта

	players[0].init(texture, 1, false, 2, eminems, MAX_EMINEMS);
	players[1].init(texture, 2, false, 0, eminems, MAX_EMINEMS);

	for (int	i = 0; i < MAX_EMINEMS; ++i) {
		eminems[i].init(texture, 0, true, 1, players, MAX_PLAYERS);
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

		players[0].update(time);
		// p2.update(time);

		window.clear(Color(0,0,0));
		for (int	i	= 0; i < maxX; ++i) {
			for (int	j	= 0; j < maxY; ++j) {
				if (first_map[i][j] == 'w')							// Кирпичная стена
					sprite.setTextureRect(IntRect(256, 0, 16, 16));
				else if (first_map[i][j] == 'a')					// Бронь
					sprite.setTextureRect(IntRect(256, 16, 16, 16));
				// else if (first_map[i][j] == 'g')					// Трава
					// sprite.setTextureRect(IntRect(272, 32, 16, 16));
				else if (first_map[i][j] == 'v')					// Вода
					sprite.setTextureRect(IntRect(256, 32, 16, 16));
				else if (first_map[i][j] == 'i')					// Лёд, я полагаю...
					sprite.setTextureRect(IntRect(288, 32, 16, 16));
				else if (first_map[i][j] == 'e')					// Орёл
					sprite.setTextureRect(IntRect(304, 32, 16, 16));
				else
					continue;

				sprite.setPosition(j * 16, i * 16) ; 
				window.draw(sprite);
			}
		}
		
		sprite.setTextureRect(IntRect(368, 16, 32, 192));
		sprite.setPosition(208, 0) ; 
		window.draw(sprite);

		for (int	i	= 0; i < MAX_PLAYERS; ++i) {			// Отрисовка игроков
			players[i].draw(window);
		}

		for (int	i	= 0; i < maxX; ++i) {
			for (int	j	= 0; j < maxY; ++j) {
				if (first_map[i][j] == 'g') {					// Трава
					sprite.setTextureRect(IntRect(272, 32, 16, 16));
					sprite.setPosition(j * 16, i * 16) ; 
					window.draw(sprite);
				}
			}
		}

        window.display();
	}

	return 0;
}