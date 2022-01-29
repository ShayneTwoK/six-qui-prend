#include "GameEventHandler.h"
#include "nlohmann/json.hpp"
#include "EventType.h"
#include <iostream>
//GameEventHandler::GameEventHandler(Poco::Net::SocketReactor& reactor): _reactor(reactor)
//{
//
//}
//
//GameEventHandler::~GameEventHandler()
//{
//}
using nlohmann::json;
GameEventHandler* GameEventHandler::instance_ = nullptr;
GameEventHandler::GameEventHandler() : _game(new Game())
{
}


void GameEventHandler::handleEvent(RequestBody* request)
{

	json key = request->GetKey();
	switch (key.get<EventType>()) {
	case PSEUDO:
		handleNewPlayer(request);
		break;
	case STARTGAME:
		handleStartGame(request);
	}
}

void GameEventHandler::handleNewPlayer(RequestBody* request)
{
	std::string pseudo = request->GetBody();
	Player* player = _game->GetPlayer(request->GetHandle());
	player->SetPseudo(pseudo);
	json j;
	j["player"] = pseudo;
	std::cout << "Change PSEUDO and send message to client";
	RequestBody body("NEWPLAYER", j.dump(), player->GetHandle());
	sentToAllPlayer(&body);

}

void GameEventHandler::handleEndGame(RequestBody* request)
{
}

void GameEventHandler::handleChoice(RequestBody* request)
{
}

void GameEventHandler::handleStartGame(RequestBody* request)
{
	_game->StartGame();

	for (auto _player : _game->GetPlayers()) {
		Player* p = _player.second;
		std::vector<CardModel> cards = p->GetHand().GetList();
		json json;
		json["cards"] = json::array();
		for (auto& card : cards) {
			json["cards"].push_back(card.GetJson());
		}

		RequestBody body("PLAYERCARDS", json.dump(), _player.first);
		sendToPlayer(_player.first, &body);
	}
}

Game* GameEventHandler::GetGame()
{
	return _game;
}

void GameEventHandler::sendToPlayer(int handle, RequestBody* request)
{
	json j = request->GetJson();
	const char* message = j.dump().c_str();
	Player* player = _game->GetPlayer(handle);
	player->_socket.sendBytes(message, sizeof message);
}

void GameEventHandler::sentToAllPlayer(RequestBody* request)
{
	for (auto& player : _game->GetPlayers()) {
		json j = request->GetJson();
		const char* message = j.dump().c_str();
		Player* p = player.second;
		p->_socket.sendBytes(message, sizeof message);

	}
}