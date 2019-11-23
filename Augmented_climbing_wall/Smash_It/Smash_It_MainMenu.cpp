#include "Smash_It_MainMenu.h"

Smash_It::MainMenu::MenuItem::MenuItem(sf::Vector2f position, MenuResult action)
	:_position(position), text("", font, 120), _action(action)
{
	font.loadFromFile("Smash_It/font/18123.ttf");
	//text.setFillColor(sf::Color(0, 0, 0));
	sf::Image image;
	image.loadFromFile("Smash_It/images/menu/1.png");
	image.createMaskFromColor(sf::Color(255, 255, 255));
	_texture.loadFromImage(image);
	_sprite.setTexture(_texture);
	_sprite.setPosition(_position);
	animationFrame = 0;
	_radius = 150;
	
	_center = sf::Vector2f(position.x + _sprite.getTexture()->getSize().x / 2, position.y + _sprite.getTexture()->getSize().y / 2);


	image.loadFromFile("Smash_It/images/menu/string-1.png");
	image.createMaskFromColor(sf::Color(255, 255, 255));
	_stringTexture.loadFromImage(image);
	_stringSprite.setTexture(_stringTexture);
	_stringSprite.setPosition(_center + sf::Vector2f(-30, 150));
}

Smash_It::MainMenu::MenuResult Smash_It::MainMenu::Show(sf::RenderWindow& window, std::set<std::pair<float, std::string>>& TOP_List, myServer &server)
{
	MainMenu::velocity = sf::Vector2f(0, 0.01);
	//Load menu image from file
	sf::Image image;
	image.loadFromFile("Smash_It/images/back_ground_1.png");
	sf::Texture texture;//������� ������ Texture (��������)
	texture.loadFromImage(image);//�������� � ���� ������ Image (�����������)
	//������� ������ Sprite(������)
	sprite.setTexture(texture);//������� � ���� ������ Texture (��������)




	//Play menu item coordinates
	MenuItem playButton(sf::Vector2f(300,100), Play);
	std::ostringstream play_buttonStr;
	play_buttonStr << "Play";
	playButton.text.setString(play_buttonStr.str());
	playButton.text.setPosition(playButton._center - sf::Vector2f(110, 80));

	//Exit menu item coordinates
	//MenuItem exitButton(sf::Vector2f(1750, -200), Exit);

	MenuItem topScore_Button(sf::Vector2f(800, 100), Score_board);
	std::ostringstream topScore_buttonStr;
	topScore_buttonStr << "TOP \n list";
	topScore_Button.text.setString(topScore_buttonStr.str());
	topScore_Button.text.setPosition(topScore_Button._center - sf::Vector2f(105, 145));


	_menuItems.push_back(playButton);
	_menuItems.push_back(topScore_Button);

	Draw(window);
	
	MenuResult clicResult = GetMenuResponse(window, server);
	
	if (clicResult == Score_board)
	{
		int scoresCount = 1;
		//std::set<std::string, float>::const_iterator itr = TOP_List.begin();
		std::vector<sf::Text> plaersScore;
		sf::Font font;
		font.loadFromFile("Smash_It/font/11583.ttf");



		std::set<std::pair<float, std::string>>::reverse_iterator rit;

		for (rit = TOP_List.rbegin(); rit != TOP_List.rend(); ++rit)
		{

			std::string plaerScore_str = std::to_string(scoresCount) + ". " + rit->second + "       " + std::to_string((int)rit->first);
			sf::Text plaerScore(plaerScore_str, font, 150);
			plaerScore.setPosition(window.getSize().x / 2 - 400, 200 + 100 * scoresCount);
			plaersScore.push_back(plaerScore);

			scoresCount++;
		}

		
		bool flag = true;
		while (flag)
		{
			sf::Text topScore("TOP SCORE", font, 150);
			topScore.setPosition(window.getSize().x / 2 - 400, 100);


			window.clear(sf::Color(0, 0, 0));
			window.draw(topScore);
			for (int i = 0; i < plaersScore.size(); i++)
			{
				window.draw(plaersScore[i]);
			}
			
			window.display();

			//delay for no frizing 
			if (serverDelayClock.getElapsedTime().asMilliseconds() > 500) {
				std::vector<int> data = server.getData();
				//2 - byte contains information about presed buttons (magick number from client)
				// +=5 need becose with time delation we stack more then one message, and information about prest button will be only in one message
				for (int i = 2; i < data.size(); i += 5)
				{
					if (data[i] == 4) flag = false;
					serverDelayClock.restart();
				}
			}

		}

		
	}

	return clicResult;
}



void Smash_It::MainMenu::Draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(0, 0, 0)); 
	window.draw(sprite);
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		window.draw((*it)._stringSprite);
		window.draw((*it)._sprite);
		window.draw((*it).text);
	}
	window.display();
}

void Smash_It::MainMenu::Update(sf::RenderWindow& window)
{
	std::list<MenuItem>::iterator it;
	
	

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		(*it).Move(velocity);
		
	}
	k++;
	if (k > 5000)
	{
		velocity = -velocity;
		k = 0;
	}
}



Smash_It::MainMenu::MenuResult Smash_It::MainMenu::HandleClick(sf::RenderWindow& window, int x, int y)				//�������� ���� �������� �����
{
	std::list<MenuItem>::iterator it;
	
	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		float radius = (*it)._radius;
		if (dist2((*it)._center, sf::Vector2f(x,y)) < radius*radius)
		{
			return (*it)._action;										//���������� ����� "�����" (���������)
		}
	}

	return Nothing;
}

Smash_It::MainMenu::MenuResult  Smash_It::MainMenu::GetMenuResponse(sf::RenderWindow& window, myServer &server)
{
	sf::Event menuEvent;
	

	while (true)
	{
		MainMenu::Update(window);
		MainMenu::Draw(window);

		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(window, menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
		//delay for no frizing 
		if (serverDelayClock.getElapsedTime().asMilliseconds() > 500) {
			std::vector<int> data = server.getData();
			//2 - byte contains information about presed buttons (magick number from client)
			// +=5 need becose with time delation we stack more then one message, and information about prest button will be only in one message
			for (int i = 2; i < data.size(); i += 5)
			{
				if (data[i] == 4) return Exit;  //4 - BACK button presed (magick number from client)
				if (data[i] == 5) return Score_board;
				serverDelayClock.restart();
			}
		}
	}
}

float Smash_It::MainMenu::dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void Smash_It::MainMenu::MenuItem::Move(sf::Vector2f pos)
{
	_sprite.move(pos);
	_stringSprite.move(pos);
	text.move(pos);
}