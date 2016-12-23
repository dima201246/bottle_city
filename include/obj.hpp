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

	#define TANK_KILL	0
	#define TANK_WOUND	1
	#define TANK_NONE	2

	#define WIN_NONE	0
	#define WIN_PLAYER	1
	#define WIN_EMINEM	2

	#define SCALE_X	2.0f
	#define SCALE_Y	2.0f

	class Game;
	class Body;
	class Tank;
	class Menu;
	class Player;
	class Bullet;
	class GPause;
	class WachDog;
	class GameMap;
	class AIplayer;
	class RightBar;
	class MainPoint;

	struct coordinate
	{
		unsigned int	posX,
						posY;
	};

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

		Player		*players_;

		AIplayer	*eminems_;

		sf::Clock	clock_;

		sf::Event	event_;

		sf::Texture texture_;
	};

	class GPause
	{
	public:

		GPause(sf::Texture&, GameMap*);
		~GPause(){}

		bool status();
		void paused(sf::RenderWindow&);

	private:
		bool 	status_game;

		sf::Sprite	p_sprite;
	};

	class GameMap
	{
	public:
		GameMap(sf::Texture&);
		~GameMap();

		bool loadMap(std::string);
		char getElement(unsigned int, unsigned int);
		void randomMap();
		void draw(sf::RenderWindow &);
		void drawGrass(sf::RenderWindow &);
		void setElement(char, unsigned int, unsigned int);
		coordinate getEaglePos();
		unsigned int getMaxX();
		unsigned int getMaxY();

	private:
		char			**pMap_;			// Вся игровая карта

		sf::Sprite		sprite_;

		coordinate		eaglePos_,			// Координаты орла
						pSpawn_[2],			// Координаты спавна игроков
						eSpawn_[3];			// Координаты спавна врагов

		std::string		nextLevelPath_;		// Путь к файлу со следующей картой

		unsigned int	maxX_,
						maxY_,
						**gMap_,			// Координаты травы
						grassNum_;			// Кол-во травы на карте
	};

	class RightBar
	{
	public:
		RightBar(sf::Texture&, unsigned int, int, int, int, int);
		~RightBar(){}

		int getEminems();
		int getP1Life();
		int getP2Life();
		int getLevel();
		void setLevel(int);
		void setP1Life(int);
		void setP2Life(int);
		void setEminems(int);
		void draw(sf::RenderWindow&);

	private:
		int				nEminems,
						level,
						p1_life,
						p2_life;

		sf::Sprite		sprite;

		unsigned int	pos;
	};

	class MainPoint
	{
	public:
		sf::FloatRect getRect()
		{
			return rect;
		}

		float		dx,
					dy;

		sf::Sprite	sprite;

		sf::FloatRect	rect;
	};

	class Bullet : public MainPoint
	{
	public:
		Bullet(){}
		~Bullet();

		bool active();
		bool bulletStatus();
		bool bulletComparsion(sf::FloatRect);
		void update(float);
		void bulletDestroy();
		void shot(int, int, int);
		void draw(sf::RenderWindow&);
		void init(sf::Texture&, GameMap*);
		sf::FloatRect getBulletRect();

	private:
		int			bullet_side;	// Сторона в которую летит пуля

		bool		bullet_status;

		sf::Sound 	*sound_shot,
					*sound_un_shot;

		sf::SoundBuffer	buffer_shot,
						buffer_un_shot;

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
		bool tankComparsion(sf::FloatRect);
		void setSide(int);
		void update(float);
		void draw(sf::RenderWindow&);
		void init(sf::Texture&, GameMap*);
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
		void draw(sf::RenderWindow&);
		void init(sf::Texture&, GameMap*, RightBar*);
		sf::FloatRect getRect();

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

		int getLeftTank();
		void bax_bax();
		void update(float);
		void draw(sf::RenderWindow&);
		void init(sf::Texture&, Player*, int, AIplayer*, int, GameMap*, RightBar*, int, int, int, int);

	private:
		GameMap		*main_map;

		Player		*players_tanks;

		AIplayer	*AIplayers_tanks;

		int			level,		// Уровень
					left_tank,	// Сколько танков осталось
					nPlayers,	// Общее кол-во игроков
					nAIPlayers;	// Общее кол-во врагов

		bool tankCollision(int, int);
		void killAI();
		void bulletCollision();
	};

	class AIplayer : public Tank
	{
	public:
		AIplayer(){}
		~AIplayer(){}

		int bax_bax();			// Если вернул true - танк убит
		void update(float);
		void draw(sf::RenderWindow&);
		void activation(unsigned int, unsigned int);
		void init(sf::Texture&, Player*, int, AIplayer*, int, GameMap*, RightBar*, int, int, int);

	private:
		// bool		active_;		// Активирован ли танк

		int			type_,			// Тип танка
					nPlayers_,		// Общее кол-во игроков
					nAIPlayers_,	// Общее кол-во танков с ИИ
					currentSide_;	// Направление движения

		Player		*playersTanks_;

		GameMap		*mainMap_;

		AIplayer	*AIplayersTanks_;

		sf::FloatRect	startPosition_;	// Респаун конкретного танка

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

		int draw(sf::RenderWindow&, sf::Event&, sf::Texture&);

	private:

		sf::Sound	*sound_shot_,
					*sound_un_shot_;

		sf::Sprite	sprite_,
					spriteTank_;

		sf::Texture	texture_;

		sf::SoundBuffer	buffer_shot_,
						buffer_un_shot_;
	};

	class WachDog
	{
	public:
		WachDog(GameMap*, Player*, int);
		~WachDog(){}

		int wach();				// Если вернёт true - значит вы проиграли/выиграли

	private:
		int			nPlayer_;

		Player		*player_;

		GameMap		*mainMap_;

		coordinate	eaglePos_;
	};
#endif