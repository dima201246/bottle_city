#include "../include/obj.hpp"

Menu::Menu()
{
	Menu::texture_.loadFromFile("media/menu.png");	// Загрузка текстуры меню
	Menu::sprite_.setTexture(Menu::texture_);
	Menu::sprite_.setTextureRect(sf::IntRect(0, 0, 400, 359));	// Установка текстуры в зависимомти от стороны в которую смотрит танк
}

Menu::~Menu()
{

}

int Menu::draw(sf::RenderWindow &window, sf::Event &event, sf::Texture &local_texture_)
{
	int pos	= 0;

	window.create(sf::VideoMode(400, 359), "Bootle city");	// Создание нового окна для начала игры

	Menu::spriteTank_.setTexture(local_texture_);
	Menu::spriteTank_.setTextureRect(sf::IntRect(96, 0, 16, 16));	// Установка текстуры в зависимомти от стороны в которую смотрит танк

	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return));

	while (window.isOpen())
	{

		while (window.pollEvent(event))							// Отслеживание события закрытия окна
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
			return 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			return pos + 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (pos == 0)
				pos	= 1;
			else
				pos	= 0;

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (pos == 1)
				pos	= 0;
			else
				pos	= 1;

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
		}

		if (pos == 0)
			Menu::spriteTank_.setPosition(120 , 191);
		else
			Menu::spriteTank_.setPosition(120 , 217);

		window.clear(sf::Color(0,0,0));
		window.draw(Menu::sprite_);
		window.draw(Menu::spriteTank_);
		window.display();
	}
}