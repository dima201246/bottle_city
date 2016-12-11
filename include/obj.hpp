#ifndef OBJ_H
#define OBJ_H

	#include <stdlib.h>
	#include <string>
	#include <SFML/Graphics.hpp>
	#include <SFML/Audio.hpp>

	using namespace sf;

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

		Sprite			sprite;

		bullet();
		~bullet();

		void init(Texture&, tank*, int, game_map*);
		void update(float);
		void shot(int, int, int);
		bool active();

	private:

		int				side,
						other_tanks_num;

		bool			status;

		float			dx,
						dy;

		tank			*other_tanks;

		FloatRect		rect;

		SoundBuffer		buffer_shot,
						buffer_un_shot;

		Sound 			*sound_shot,
						*sound_un_shot;

		game_map		*main_map;

		void collision();
	};

	class tank {
	public:

		tank();
		~tank();

		void init(Texture&, int, int, tank*, int, game_map*);
		void update(float);
		void piu_piu();
		void move_up();
		void move_down();
		void move_left();
		void move_right();
		int getSide();
		FloatRect getRect();
		int getLeft_tank();
		int getLife();
		void draw(RenderWindow &) ;

	private:

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

		bool			god_mode;

		Sprite			t_sprite;

		bullet			shell;

		game_map		*main_map;

		void collision();
	};
#endif