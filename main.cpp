#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <iostream>

using namespace sf;
using namespace std;

#define GAME_SPEED	900

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


class bullet {
	unsigned char	side;

	bool			status;

	float			dx,
					dy;

	SoundBuffer		buffer_shot,
					buffer_un_shot;

	FloatRect		rect;
	Sound 			*sound_shot,
					*sound_un_shot;

	void collision() {
		if (dx != 0) {
			if (first_map[int((rect.top + 3) / 16)][int(rect.left / 16)] == 'w') {
				first_map[int((rect.top + 3) / 16)][int(rect.left / 16)]	= ' ';
				dx	= 0;
			}
		}

		if (dy != 0) {
			if (first_map[int(rect.top / 16)][int((rect.left + 3) / 16)] == 'w') {
				first_map[int(rect.top / 16)][int((rect.left + 3) / 16)]	= ' ';
				dy	= 0;
			}
		}
	}

public:

	Sprite			sprite;

	bullet() {
		buffer_shot.loadFromFile("media/sound/shot.ogg");
		sound_shot		= new Sound(buffer_shot);
		buffer_un_shot.loadFromFile("media/sound/un_shot.ogg");
		sound_un_shot	= new Sound(buffer_un_shot);
		rect			= FloatRect(320, 72, 8, 8);
		dx	= dy		= 0.0;
		status			= false;
		rect.left		= 0;
		rect.top		= 0;
	}

	~bullet() {
		delete sound_shot;
		delete sound_un_shot;
	}

	void init(Texture &image) {
		sprite.setTexture(image);
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

	void shot(int posX, int posY, unsigned char side) {
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

class eminem {

	unsigned char	life,
					level,
					left_tank,
					currentFrame,
					side;
					
	float			dx,
					dy;

	FloatRect		rect;


public:
	bullet			shell;
	Sprite			sprite;

	eminem(Texture &image) {
		sprite.setTexture(image);
		shell.init(image);
		side			= 0;
		life			= 3;
		level			= 1;
		rect			= FloatRect(0, 0, 16, 16);
		left_tank		= 16;
		currentFrame	= 0;
		dx	= dy		= 0.0;
		rect.left		= 144;
		rect.top		= 200;
	}
	
	/*Side
	0 - UP
	2 - LEFT
	4 - DOWN
	6 - RIGHT
	*/
	
	// ~player();

	void update(float time) {
		if ((dx	!= 0) || (dy != 0)) {	// Защита от выхода за границы
			if ((dx > 0) && (((rect.left + rect.width) / 16) > maxX)) dx	= 0;
			if ((dy > 0) && (((rect.top + rect.height) / 16) > (maxY - 1))) dy	= 0;
			if ((dx < 0) && (rect.left <= 1)) dx	= 0;
			if ((dy < 0) && (rect.top <= 1)) dy	= 0;
		}

		rect.left		+= dx * (time / 2.0);	// Собсно, движение
		rect.top 		+= dy * (time / 2.0);
		// sprite.setTextureRect(IntRect(320, 72, 16, 16));

		sprite.setTextureRect(IntRect(128 + (side * 16), 0, 16, 16));

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

		sprite.setPosition(rect.left, rect.top);

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
	
};


class player {
	unsigned char	life,
					level,
					left_tank,
					currentFrame,
					num_of_player,
					side;

	float			dx,
					dy;

	FloatRect		rect;

	bool			god_mode;

	void collision() {
/*		cout << "*****************************************" << endl;
		cout << "X: " << rect.top << " Y: " << rect.left << endl;
		cout << "X: " << int(rect.top / 16) << " Y: " << int(rect.left / 16) << endl;
		cout << "*****************************************" << endl;


*/
		if (dx < 0) {
			if ((first_map[int((rect.top + 13) / 16)][int((rect.left - 1) / 16)] == 'w') || (first_map[((int(rect.top)) / 16)][int((rect.left - 1) / 16)] == 'w'))
				dx	= 0;

			if ((first_map[int((rect.top + 13) / 16)][int((rect.left - 1) / 16)] == 'v') || (first_map[((int(rect.top)) / 16)][int((rect.left - 1) / 16)] == 'v'))
				dx	= 0;

			if ((first_map[int((rect.top + 13) / 16)][int((rect.left - 1) / 16)] == 'a') || (first_map[((int(rect.top)) / 16)][int((rect.left - 1) / 16)] == 'a'))
				dx	= 0;

			side	= 2;
		}

		if (dy < 0) {
			if ((first_map[int((rect.top - 1) / 16)][int((rect.left + 15) / 16)] == 'w') || (first_map[int((rect.top - 1) / 16)][int((rect.left + 1) / 16)] == 'w'))
				dy	= 0;

			if ((first_map[int((rect.top - 1) / 16)][int((rect.left + 15) / 16)] == 'v') || (first_map[int((rect.top - 1) / 16)][int((rect.left + 1) / 16)] == 'v'))
				dy	= 0;

			if ((first_map[int((rect.top - 1) / 16)][int((rect.left + 15) / 16)] == 'a') || (first_map[int((rect.top - 1) / 16)][int((rect.left + 1) / 16)] == 'a'))
				dy	= 0;

			side	= 0;
		}

		if (dx > 0) {
			if ((first_map[int((rect.top + 13) / 16)][int((rect.left + 17) / 16)] == 'w') || (first_map[((int(rect.top)) / 16)][int((rect.left + 17) / 16)] == 'w'))
				dx	= 0;

			if ((first_map[int((rect.top + 13) / 16)][int((rect.left + 17) / 16)] == 'v') || (first_map[((int(rect.top)) / 16)][int((rect.left + 17) / 16)] == 'v'))
				dx	= 0;

			if ((first_map[int((rect.top + 13) / 16)][int((rect.left + 17) / 16)] == 'a') || (first_map[((int(rect.top)) / 16)][int((rect.left + 17) / 16)] == 'a'))
				dx	= 0;

			side	= 6;
		}

		if (dy > 0) {
			if ((first_map[int((rect.top + 16) / 16)][int((rect.left + 1) / 16)] == 'w') || (first_map[((int(rect.top + 16)) / 16)][int((rect.left + 15) / 16)] == 'w'))
				dy	= 0;

			if ((first_map[int((rect.top + 16) / 16)][int((rect.left + 1) / 16)] == 'v') || (first_map[((int(rect.top + 16)) / 16)][int((rect.left + 15) / 16)] == 'v'))
				dy	= 0;

			if ((first_map[int((rect.top + 16) / 16)][int((rect.left + 1) / 16)] == 'a') || (first_map[((int(rect.top + 16)) / 16)][int((rect.left + 15) / 16)] == 'a'))
				dy	= 0;

			side	= 4;
		}
	}

public:
	bullet			shell;
	Sprite			sprite;

	player(Texture &image, unsigned char num) {
		sprite.setTexture(image);
		shell.init(image);
		side			= 0;
		life			= 3;
		level			= 1;
		num_of_player	= num;
		rect			= FloatRect(0, 0, 16, 16);
		god_mode		= false;
		left_tank		= 16;
		currentFrame	= 0;
		dx	= dy		= 0.0;
		rect.left		= 128;
		rect.top		= 176;
	}
	
	/*Side
	0 - UP
	2 - LEFT
	4 - DOWN
	6 - RIGHT
	*/
	
	// ~player();

	void update(float time) {
		if ((dx	!= 0) || (dy != 0)) {	// Защита от выхода за границы
			if ((dx > 0) && (((rect.left + rect.width) / 16) > maxX)) dx	= 0;
			if ((dy > 0) && (((rect.top + rect.height) / 16) > (maxY - 1))) dy	= 0;
			if ((dx < 0) && (rect.left <= 1)) dx	= 0;
			if ((dy < 0) && (rect.top <= 1)) dy	= 0;

			collision();
		}

		rect.left		+= dx * (time / 2.0);	// Собсно, движение
		rect.top 		+= dy * (time / 2.0);
		// sprite.setTextureRect(IntRect(320, 72, 16, 16));

		sprite.setTextureRect(IntRect(0 + (side * 16), 0, 16, 16));

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

		sprite.setPosition(rect.left, rect.top);

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
};

int main() {
	Clock			clock;										// Переменная, для слежения за временем
	Texture 		texture;
	RectangleShape	rectangle(Vector2f(32,32));
	Event 			event;
	float			time;

	RenderWindow window( VideoMode(512, 480), "Bottle city");	// Создание окна
	texture.loadFromFile("media/textures.png");						// Загрузка всех текстур

	Sprite			sprite(texture);
	player			p1(texture, 1);
	eminem			p2(texture);

	while (window.isOpen()) {
		time = clock.getElapsedTime().asMicroseconds();			// Получение времени
		clock.restart();										// Сброс часиков

		time = time / GAME_SPEED;

		if (time > 20)	
			time = 20;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

	    if (Keyboard::isKeyPressed(Keyboard::Left)) {
	    	p1.move_left();
	    }

	    if (Keyboard::isKeyPressed(Keyboard::Right)) {
	    	p1.move_right();
	    }

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
	    	p1.move_up();
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
	    	p1.move_down();
		}

		if (Keyboard::isKeyPressed(Keyboard::Z)) {
	    	p1.piu_piu();
	    }

		p1.update(time);
		p2.update(time);

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

		if (p1.shell.active()) {
			p1.shell.update(time);
			window.draw(p1.shell.sprite);
		}

		window.draw(p1.sprite);
		window.draw(p2.sprite);

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