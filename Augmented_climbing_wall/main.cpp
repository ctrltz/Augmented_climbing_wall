#include "Smash_It\Smash_It_Game.h"
#include "TimeClimb\TimeClimb_Game.h"
#include "Labyrinth\Labyrinth_Game.h"
#include "mainWindow.h"
#include "aerohockey/starter.h"
#include "server.h"
#include "Cliker.h"


int main()
{
	std::cout << "tyt&";
	myServer *server = new myServer();
	//server->InitServer();
	Cliker::Init();


	enum dataType
	{
		gameState, game, presedButton, LvL
	};

	while (true)
	{
		//switch (server->getData()[gameState])
		switch (1)
		{
		case(myServer::EXIT):
			break;
		case(myServer::PLAY):
			MainWindow::getWindow().setMouseCursorVisible(true);
			//switch (server->getData()[game])
			switch (3)
			{
			case(myServer::SMASH_IT):
			{
				std::cout << "SMASh_it started \n";
		
				Smash_It::Game smash_It(MainWindow::getWindow());
				smash_It.Start(*server);
				break;
			}
			case(myServer::LABYRINTH):
			{
				std::cout << "LABYRINTH started \n";

				Labyrinth::Game labyrinth(MainWindow::getWindow());
				//labyrinth.Start(*server, server->getData()[LvL]);
				labyrinth.Start(*server, 3);
				break;
			}
			case(myServer::TIME_CLIMB):
			{
				std::cout << "TIME_CLIMB started \n";

				TimeClimb::Game timeClimb(MainWindow::getWindow());
				timeClimb.Start(*server);
				break;
			}
			case(myServer::AEROHOCKEY):
				std::cout << "AEROHOCKEY started \n";

				starter();
				break;
			case(myServer::TERRITORY):
				std::cout << "TERRITORY started \n";
				break;
			default:
				break;
			}
			break;
		default:
			break;
		case(myServer::SCORE_BOARD):
			break;
		case(myServer::GAME_SELECTION):	
			MainWindow::getWindow().clear(sf::Color(0, 0, 0));
			MainWindow::getWindow().setMouseCursorVisible(false);
			MainWindow::getWindow().display();

			break;
		}
		
		//if (server->sendData(0) == 1) break;
	}
	
	server->endServer();

	delete(server);

	return 0;
}
