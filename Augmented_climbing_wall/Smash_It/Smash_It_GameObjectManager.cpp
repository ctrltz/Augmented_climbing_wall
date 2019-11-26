#include "../stdafx.h"
#include "Smash_It_GameObjectManager.h"
#include "Smash_It_Game.h"

//����� ���������� �� ��������, ���������� � �������� �������� � ��� �� �� �� ����� ��������� � ���������� 

Smash_It::GameObjectManager::GameObjectManager()
{
	sf::Image image;
	image.loadFromFile("Smash_It/images/back_ground_1.png");
	//������� ������ Texture (��������)
	logotexture.loadFromImage(image);//�������� � ���� ������ Image (�����������)
	//������� ������ Sprite(������)
	logosprite.setTexture(logotexture);//������� � ���� ������ Texture (��������)
}

Smash_It::GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void Smash_It::GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void Smash_It::GameObjectManager::RemoveAll()
{

	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());

	_gameObjects.erase(_gameObjects.begin(), _gameObjects.end());
}

void Smash_It::GameObjectManager::Remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

Smash_It::VisibleGameObject* Smash_It::GameObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;

}

int Smash_It::GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}


void Smash_It::GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{

	
	renderWindow.draw(logosprite);


	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		if (itr->second->getPlased()) itr->second->Draw(renderWindow);
		itr++;
	}
}

void Smash_It::GameObjectManager::UpdateAll(sf::Event& event)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	
	while (itr != _gameObjects.end())
	{
		
		itr->second->Update(event);
		
		if (itr->second->getClickState()) {				//���� �� �������� ����
			itr->second->setClickState(false);
			Get("counter")->countIncroment();
		}

		
		itr++;
	}
}

void Smash_It::GameObjectManager::setAllPlased()
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->setPlased(true);
		itr++;
	}
}


