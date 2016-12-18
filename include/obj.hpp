#ifndef OBJ_H
#define OBJ_H

	#include <stdlib.h>
	#include <unistd.h>
	#include <string>
	#include <SFML/Graphics.hpp>
	#include <SFML/Audio.hpp>

	#define MAX_PLAYERS	2
	#define MAX_EMINEMS	20

	#define GAME_SPEED	6000

	#define UP_SIDE		0
	#define LEFT_SIDE	2
	#define DOWN_SIDE	4
	#define RIGHT_SIDE	6

	using namespace sf;

	class AIplayer;
	class player;
	class tank;
	class bullet;
	class body;
	class game_map;
	class game;
	class g_pause;

	class game {
	public:

		game(){}
		~game();

		void gameStart();

	private:

		player		*players;

		AIplayer	*eminems;

		Event 		event;

		Texture 	texture;

		Clock		clock;

		float		time;
	};

	class g_pause {
	public:

		g_pause(Texture&, game_map*);
		~g_pause(){}

		void paused(RenderWindow&);
		bool status();

	private:

		Sprite	p_sprite;

		bool 	status_game;

	};

	class game_map {
	public:

		game_map(Texture&);
		~game_map();

		bool loadMap(std::string);
		char getElement(unsigned int, unsigned int);
		void draw(RenderWindow &);
		void drawGrass(RenderWindow &);
		void setElement(char, unsigned int, unsigned int);
		unsigned int getMaxX();
		unsigned int getMaxY();

	private:

		char	**p_map;				// Вся игровая карта

		int		maxX,
				maxY,
				grass_num;				// Кол-во травы на карте

		unsigned int	**g_map;		// Координаты травы

		Sprite	sprite;

		std::string	next_level_path;	// Путь к файлу со следующей картой
	};

	class main_point {
	public:

		FloatRect getRect() {
			return rect;
		}

		float		dx,
					dy;

		FloatRect	rect;
	};

	class bullet : public main_point {
	public:

		Sprite			bullet_sprite;

		bullet(Texture&, game_map*);
		~bullet();

		void update(float);
		void shot(int, int, int);
		bool bulletComparsion(FloatRect);
		bool active();
		void destroy();
		void draw(RenderWindow&);

	private:

		int				bullet_side;	// Сторона в которую летит пуля

		bool			bullet_status;

		SoundBuffer		buffer_shot,
						buffer_un_shot;

		Sound 			*sound_shot,
						*sound_un_shot;

		game_map		*bullet_main_map;

		void collision();
	};

	class body : public main_point {
	public:

		body(Texture&, game_map*);
		~body(){}

		void update(float);
		bool moveUp();
		bool moveDown();
		bool moveLeft();
		bool moveRight();
		bool tankComparsion(FloatRect);
		bool move(int);
		void setPosition(unsigned int, unsigned int, int);
		int getSide();
		void draw(RenderWindow&) ;

	private:

		int				currentFrame,
						side;

		float			l_time;

		bool			god_mode;

		Sprite			t_sprite;

		game_map		*main_map;

		bool checkMove();
	};

	class tank {
	public:

		tank(){}
		~tank();

		void init(Texture&, game_map*);
		void setPosition(unsigned int, unsigned int, int);
		void update(float);
		void piu_piu();
		bool moveUp();
		bool moveDown();
		bool moveLeft();
		bool moveRight();
		bool tankComparsion(FloatRect);
		bool bulletComparsion(FloatRect);
		void bulletDestroy();
		FloatRect getBulletRect();
		bool bulletStatus();
		bool move(int);
		int getSide();
		FloatRect getRect();
		void draw(RenderWindow&);

	private:

		body	*t_body;

		bullet	*t_bullet;
	};

	class player : protected tank {
		public:

			player():tank(){}
			~player(){}

			void init(Texture&, player*, int, AIplayer*, int, game_map*, int, int, int, int);
			void update(float);
			void draw(RenderWindow&);
			void bax_bax();
			int getLife();
			FloatRect getRect();

		private:

			game_map	*main_map;

			player		*players_tanks;

			AIplayer	*AIplayers_tanks;

			int			life,			// Кол-во жизней
						level,			// Уровень
						left_tank,		// Сколько танков осталось
						num_of_player,	// Номер игрока
						players_num,	// Общее кол-во игроков
						AIplayers_num;	// Общее кол-во врагов

			bool tankCollision(int);
			void bulletCollision();
	};

	class AIplayer : protected tank {
		public:

			AIplayer():tank(){}
			~AIplayer(){}

			void init(Texture&, player*, int, game_map*, bool, int, int);
			void update(float);
			void draw(RenderWindow&);
			void activation(unsigned int, unsigned int);
			void bulletDestroy();
			void bax_bax();
			FloatRect	getBulletRect();
			FloatRect	getRect();
			int			getLife();

		private:

			player	*players_tanks;

			game_map	*main_map;

			AIplayer	*AIplayers_tanks;

			FloatRect	startPosition; // Респаун конкретного танка

			bool	active;			// Активирован ли танк

			int		life,			// Кол-во жизней
					type,			// Тип танка
					players_num,	// Общее кол-во игроков
					AIplayers_num,	// Общее кол-во врагов
					currentSide;	// Направление движения
	};
#endif