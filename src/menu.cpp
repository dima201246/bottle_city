#include "../include/obj.hpp"

Menu::Menu()
{
	Menu::texture_.loadFromFile("media/menu.png");	// Загрузка текстуры меню
	Menu::sprite_.setTexture(Menu::texture_);
	Menu::sprite_.setTextureRect(IntRect(0, 0, 400, 359));	// Установка текстуры в зависимомти от стороны в которую смотрит танк
}

Menu::~Menu()
{

}

int Menu::draw(RenderWindow &window, Event &event, Texture &local_texture_)
{
	int pos	= 0;

	Menu::spriteTank_.setTexture(local_texture_);
	Menu::spriteTank_.setTextureRect(IntRect(96, 0, 16, 16));	// Установка текстуры в зависимомти от стороны в которую смотрит танк

	// window.setSize(Vector2u(400, 359));

	while (Keyboard::isKeyPressed(Keyboard::Return));

	while (window.isOpen())
	{

		while (window.pollEvent(event))							// Отслеживание события закрытия окна
		{
			if (event.type == Event::Closed) {
				window.close();
				return 0;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Return))
			return pos + 1;

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			if (pos == 0)
				pos	= 1;
			else
				pos	= 0;

			while (Keyboard::isKeyPressed(Keyboard::Down));
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (pos == 1)
				pos	= 0;
			else
				pos	= 1;

			while (Keyboard::isKeyPressed(Keyboard::Up));
		}

		if (pos == 0)
			Menu::spriteTank_.setPosition(120 , 191);
		else
			Menu::spriteTank_.setPosition(120 , 217);

		window.clear(Color(0,0,0));
		window.draw(Menu::sprite_);
		window.draw(Menu::spriteTank_);
		window.display();
	}
}