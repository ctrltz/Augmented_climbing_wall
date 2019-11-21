#pragma once
#include "../stdafx.h"
#include "Labyrinth_VisibleGameObject.h"

namespace Labyrinth
{
	class Timer : public VisibleGameObject
	{
	public:
		Timer();
		~Timer();

		void Load(std::string filename);
		void Draw(sf::RenderWindow & renderWindow);
		void Restart();
		sf::Time GetTime();
		void setFinished(bool res);		//��������� finished � true
		bool getFinished();
		void reInit();


	private:
		sf::Clock gameTimeClock;
		sf::Time t1;
		sf::Font font;
		sf::Text text;
		bool finished;
		float finishedTime;
	};
}

