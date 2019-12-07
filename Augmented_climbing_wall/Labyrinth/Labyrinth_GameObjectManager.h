#pragma once
#include "../stdafx.h"
#include "Labyrinth_VisibleGameObject.h"
#include "Labyrinth_Timer.h"
//#include "Game.h"


namespace Labyrinth
{
	class GameObjectManager
	{
	public:
		GameObjectManager();
		~GameObjectManager();

		void Add(std::string name, VisibleGameObject* gameObject);
		void Remove(std::string name);
		void RemoveAll();
		int GetObjectCount() const;
		VisibleGameObject* Get(std::string name) const;

		void DrawAll(sf::RenderWindow& renderWindow);
		void UpdateAll(sf::Event& event);
		void setAllPlased();


	private:
		std::map<std::string, VisibleGameObject*> _gameObjects;

		struct GameObjectDeallocator
		{
			void operator()(const std::pair<std::string, VisibleGameObject*> & p) const
			{
				delete p.second;
			}
		};
	};
}
