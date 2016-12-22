#ifndef OBJ_H
#define OBJ_H

	#include <stdlib.h>
	#include <unistd.h>
	#include <string>
	#include <SFML/Graphics.hpp>
	#include <SFML/Audio.hpp>

	#define GAME_SPEED	900

	#define UP_SIDE		0
	#define LEFT_SIDE	2
	#define DOWN_SIDE	4
	#define RIGHT_SIDE	6

	#define SCALE_X	2.0f
	#define SCALE_Y	2.0f

	using namespace sf;

	class Game;
	class Body;
	class Tank;
	class Menu;
	class Player;
	class Bullet;
	class GPause;
	class AIplayer;
	class GameMap;
	class RightBar;
	class MainPoint;

	class Game
	{
	public:
		Game(){}
		~Game();

		void gameStart();

	private:
		int			maxPlayers_,
					maxEminems_;

		float		time_;

		Event 		event_;

		Clock		clock_;

		Player		*players_;

		Texture 	texture_;

		AIplayer	*eminems_;
	};

	class GPause
	{
	public:

		GPause(Texture&, GameMap*);
		~GPause(){}

		void paused(RenderWindow&);
		bool status();

	private:
		bool 	status_game;

		Sprite	p_sprite;
	};

	class GameMap
	{
	public:
		GameMap(Texture&);
		~GameMap();

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

	class RightBar
	{
	public:
		RightBar(Texture&, unsigned int, int, int, int, int);
		~RightBar(){}

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
		int				nEminems,
						level,
						p1_life,
						p2_life;

		Sprite			sprite;

		unsigned int	pos;
	};

	class MainPoint
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

	class Bullet : public MainPoint
	{
	public:
		Bullet(){}
		~Bullet();

		bool active();
		bool bulletStatus();
		bool bulletComparsion(FloatRect);
		void update(float);
		void bulletDestroy();
		void draw(RenderWindow&);
		void shot(int, int, int);
		void init(Texture&, GameMap*);
		FloatRect getBulletRect();

	private:
		int			bullet_side;	// Сторона в которую летит пуля

		bool		bullet_status;

		SoundBuffer	buffer_shot,
					buffer_un_shot;

		Sound 		*sound_shot,
					*sound_un_shot;

		GameMap	*bullet_main_map;

	protected:
		void collision();
	};

	class Body : public MainPoint
	{
	public:
		Body(){}
		~Body(){}

		int getSide();
		bool moveUp();
		bool move(int);
		bool moveDown();
		bool moveLeft();
		bool moveRight();
		bool tankComparsion(FloatRect);
		void setSide(int);
		void update(float);
		void draw(RenderWindow&) ;
		void init(Texture&, GameMap*);
		void setPosition(unsigned int, unsigned int, int);

	private:
		int			side;

		bool		god_mode;

		GameMap	*main_map;

	protected:
		bool checkMove();
	};

	class Tank : public Bullet, public Body
	{
	public:
		Tank(){}
		~Tank(){}

		int getID();
		int getLife();
		void piu_piu();
		void setID(int);
		void setLife(int);
		void update(float);
		void draw(RenderWindow&);
		void init(Texture&, GameMap*, RightBar*);
		FloatRect getRect();

		RightBar	*r_b;

	private:
		int 		life,
					id;
	};

	class Player : public Tank
	{
	public:
		Player(){}
		~Player(){}

		void bax_bax();
		void update(float);
		void draw(RenderWindow&);
		void init(Texture&, Player*, int, AIplayer*, int, GameMap*, RightBar*, int, int, int, int);

	private:
		GameMap	*main_map;

		Player		*players_tanks;

		AIplayer	*AIplayers_tanks;

		int			level,		// Уровень
					left_tank,	// Сколько танков осталось
					nPlayers,	// Общее кол-во игроков
					nAIPlayers;	// Общее кол-во врагов

		bool tankCollision(int, int);
		void bulletCollision();
	};

	class AIplayer : public Tank
	{
	public:
		AIplayer(){}
		~AIplayer(){}

		void bax_bax();
		void update(float);
		void draw(RenderWindow&);
		void activation(unsigned int, unsigned int);
		void init(Texture&, Player*, int, AIplayer*, int, GameMap*, RightBar*, int, int, int);

	private:
		Player		*players_tanks_;

		GameMap		*main_map_;

		AIplayer	*AIplayers_tanks_;

		FloatRect	startPosition_;	// Респаун конкретного танка

		bool		active_;		// Активирован ли танк

		int			type_,			// Тип танка
					nPlayers_,		// Общее кол-во игроков
					nAIPlayers_,	// Общее кол-во танков с ИИ
					currentSide_;	// Направление движения

		bool tankCollision_(int, int);
		bool checkWallX_(int, int, int);
		bool checkWallY_(int, int, int);
		void bulletCollision_();
	};

	class Menu
	{
	public:
		Menu();
		~Menu();

		int draw(RenderWindow&, Event&, Texture&);

	private:
		Texture		texture_;

		Sprite		sprite_,
					spriteTank_;

		SoundBuffer	buffer_shot_,
					buffer_un_shot_;

		Sound		*sound_shot_,
					*sound_un_shot_;
	};
#endif