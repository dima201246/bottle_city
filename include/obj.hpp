#ifndef OBJ_H
#define OBJ_H

	#include <stdlib.h>
	#include <string>
	#include <SFML/Graphics.hpp>
	#include <SFML/Audio.hpp>

	#define UP_SIDE		0
	#define LEFT_SIDE	2
	#define DOWN_SIDE	4
	#define RIGHT_SIDE	6

	using namespace sf;

	class AIplayer;
	class player;
	class tank;
	class bullet;

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

		char	**p_map;	// Вся игровая карта

		int		maxX,
				maxY,
				grass_num;	// Кол-во травы на карте

		unsigned int	**g_map;	// Координаты травы

		Sprite	sprite;

		std::string	next_level_path;
	};

	class bullet {
	public:

		Sprite			bullet_sprite;

		bullet();
		~bullet();

		void init(Texture&, tank*, int, game_map*);
		void update(float);
		void shot(int, int, int);
		bool active();

	private:

		int				bullet_side,
						bullet_other_tanks_num;

		bool			bullet_status;

		float			bullet_dx,
						bullet_dy;

		tank			*bullet_other_tanks;

		FloatRect		bullet_rect;

		SoundBuffer		buffer_shot,
						buffer_un_shot;

		Sound 			*sound_shot,
						*sound_un_shot;

		game_map		*bullet_main_map;

		void collision();
	};

	class tank : private bullet {
	public:

		tank():bullet(){}
		~tank(){}

		void init(Texture&, tank*, int, game_map*);
		void update(float);
		void piu_piu();
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void setPosition(unsigned int, unsigned int);
		int getSide();
		FloatRect getRect();
		void draw(RenderWindow&) ;

	private:

		int				currentFrame,
						side,
						other_tanks_num;

		float			dx,
						dy,
						l_time;

		tank			*other_tanks;

		FloatRect		rect;

		bool			god_mode;

		Sprite			t_sprite;

		game_map		*main_map;

		void collision();
	};

	class player : protected tank {
		public:

			player():tank(){}
			~player(){}

			void init(Texture&, tank*, int, game_map*, int, int, int, int);
			void update(float);
			void draw(RenderWindow&);

		private:

			int		life,
					level,
					left_tank,
					num_of_player;
	};

	class AIplayer : protected tank {
		public:

			AIplayer():tank(){}
			~AIplayer(){}

			void init(Texture&, tank*, int, game_map*, bool, int, int);
			void update(float);
			void draw(RenderWindow&);
			void activation(unsigned int, unsigned int);

		private:

			bool	active,
					dead;

			int		life,
					type;
	};
#endif