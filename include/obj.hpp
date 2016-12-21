#ifndef OBJ_H
#define OBJ_H

	#include <stdlib.h>
	#include <unistd.h>
	#include <string>
	#include <SFML/Graphics.hpp>
	#include <SFML/Audio.hpp>

	#define MAX_PLAYERS	2
	#define MAX_EMINEMS	20

	#define GAME_SPEED	900

	#define UP_SIDE		0
	#define LEFT_SIDE	2
	#define DOWN_SIDE	4
	#define RIGHT_SIDE	6

	#define SCALE_X	2.0f
	#define SCALE_Y	2.0f

	using namespace sf;

	class game;
	class body;
	class tank;
	class player;
	class bullet;
	class g_pause;
	class AIplayer;
	class game_map;
	class right_bar;
	class main_point;

	class game
	{
	public:

		game(){}
		~game();

		void gameStart();

	private:

		float		time;

		Event 		event;

		Clock		clock;

		player		*players;

		Texture 	texture;

		AIplayer	*eminems;
	};

	class g_pause
	{
	public:

		g_pause(Texture&, game_map*);
		~g_pause(){}

		void paused(RenderWindow&);
		bool status();

	private:

		bool 	status_game;

		Sprite	p_sprite;
	};

	class game_map
	{
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

		char			**p_map;			// Вся игровая карта

		int				maxX,
						maxY,
						grass_num;			// Кол-во травы на карте

		Sprite			sprite;

		std::string		next_level_path;	// Путь к файлу со следующей картой

		unsigned int	**g_map;			// Координаты травы
	};

	class right_bar
	{
	public:

		right_bar(Texture&, unsigned int, int, int, int, int);
		~right_bar(){}

		int getEminems();
		int getP1Life();
		int getP2Life();
		int getLevel();
		void setEminems(int);
		void setP1Life(int);
		void setP2Life(int);
		void setLevel(int);
		void draw(RenderWindow&);

	private:

		int				eminems_num,
						level,
						p1_life,
						p2_life;

		Sprite			sprite;

		unsigned int	pos;
	};

	class main_point
	{
	public:

		FloatRect getRect()
		{
			return rect;
		}

		float		dx,
					dy;

		Sprite		sprite;

		FloatRect	rect;
	};

	class bullet : public main_point
	{
	public:

		bullet(){}
		~bullet();

		bool active();
		bool bulletStatus();
		bool bulletComparsion(FloatRect);
		void update(float);
		void bulletDestroy();
		void draw(RenderWindow&);
		void shot(int, int, int);
		void init(Texture&, game_map*);
		FloatRect getBulletRect();

	private:

		int			bullet_side;	// Сторона в которую летит пуля

		bool		bullet_status;

		SoundBuffer	buffer_shot,
					buffer_un_shot;

		Sound 		*sound_shot,
					*sound_un_shot;

		game_map	*bullet_main_map;

	protected:

		void collision();
	};

	class body : public main_point
	{
	public:

		body(){}
		~body(){}

		int getSide();
		bool moveUp();
		bool moveDown();
		bool moveLeft();
		bool moveRight();
		bool tankComparsion(FloatRect);
		bool move(int);
		void init(Texture&, game_map*);
		void update(float);
		void draw(RenderWindow&) ;
		void setPosition(unsigned int, unsigned int, int);

	private:

		int			side;

		bool		god_mode;

		game_map	*main_map;

	protected:

		bool checkMove();
	};

	class tank : public bullet, public body
	{
	public:

		tank(){}
		~tank(){}

		int getID();
		int getLife();
		void piu_piu();
		void setID(int);
		void setLife(int);
		void update(float);
		void draw(RenderWindow&);
		void init(Texture&, game_map*, right_bar*);
		FloatRect getRect();

		right_bar	*r_b;

	private:

		int 		life,
					id;
	};

	class player : public tank
	{
	public:

		player(){}
		~player(){}

		void bax_bax();
		void update(float);
		void draw(RenderWindow&);
		void init(Texture&, player*, int, AIplayer*, int, game_map*, right_bar*, int, int, int, int);

	private:

		game_map	*main_map;

		player		*players_tanks;

		AIplayer	*AIplayers_tanks;

		int			level,			// Уровень
					left_tank,		// Сколько танков осталось
					players_num,	// Общее кол-во игроков
					AIplayers_num;	// Общее кол-во врагов

		bool tankCollision(int, int);
		void bulletCollision();
	};

	class AIplayer : public tank
	{
	public:

		AIplayer(){}
		~AIplayer(){}

		void bax_bax();
		void update(float);
		void draw(RenderWindow&);
		void activation(unsigned int, unsigned int);
		void init(Texture&, player*, int, AIplayer*, int, game_map*, right_bar*, int, int, int);

	private:

		player		*players_tanks;

		game_map	*main_map;

		AIplayer	*AIplayers_tanks;

		FloatRect	startPosition;	// Респаун конкретного танка

		bool		active;			// Активирован ли танк

		int			type,			// Тип танка
					players_num,	// Общее кол-во игроков
					AIplayers_num,	// Общее кол-во танков с ИИ
					currentSide;	// Направление движения

		bool tankCollision(int, int);
		bool checkWallX(int, int, int);
		bool checkWallY(int, int, int);
		void bulletCollision();
	};
#endif