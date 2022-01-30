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
		handleStartGame();
		break;
	case CHOOSECARD:
		handleChoice(request);
		break;
	case PLAY:
		handlePlayCard(request);
		break;
	}
}

void GameEventHandler::handleNewPlayer(RequestBody* request)
{
	json playerUsername = json::parse(request->GetBody());
	std::string pseudo = playerUsername["username"];
	Player* player = _game->GetPlayer(request->GetHandle());
	player->SetPseudo(pseudo);
	json j;
	j["players"] = json::array();
	for (auto& player : _game->GetPlayers()) {
		json player_json;
		player_json["pseudo"] = player.second->GetPseudo();
		j["players"].push_back(player_json);
	}
	std::cout << "Change PSEUDO and send message to client";
	RequestBody body("NEWPLAYER", j.dump(), player->GetHandle());
	sentToAllPlayer(&body);

}

void GameEventHandler::handleEndGame()
{
	Player* winner = _game->GetPlayerWithLessPoints();

	json winnerJson;
	json player;
	player["pseudo"] = winner->GetPseudo();
	player["points"] = winner->GetPoints();
	winnerJson["winner"] = player;
	RequestBody body("ENDGAME", player.dump(), winner->GetHandle());
	sentToAllPlayer(&body);
	_game = new Game();

}

void GameEventHandler::handleChoice(RequestBody* request)
{
	int handle = request->GetHandle();
	std::string body = request->GetBody();
	json card = json::parse(body);
	int cardNumber = card["num"];
	_game->ChooseCard(handle, cardNumber);

	if (_game->HasEveryOneChoseCard()) {
		_game->StartRound();
		handleStartTurn();
	}
}

void GameEventHandler::handleStartGame()
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

	handleInitColumns();
	json state;
	state["state"] = "CHOOSING";
	RequestBody body("CHANGESTATE", state.dump(), 0);
	sentToAllPlayer(&body);
}

void GameEventHandler::handleStartTurn()
{
	Player* player =_game->GetCurrentRound().getCurrentPlayerTurn().first;
	int handle = player->GetHandle();
	json playerJson;
	playerJson["username"] = player->GetPseudo();
	RequestBody body("TURN", playerJson.dump(), player->GetHandle());
	sentToAllPlayer(&body);


	json playableColumns = json::array();
	playableColumns["columns"] = _game->GetPlayableColumns(handle);
	RequestBody playerTurn("PLAYERTURN", playableColumns.dump(), handle);
	sendToPlayer(handle, &playerTurn);
}

void GameEventHandler::handleEndTurn()
{
	_game->EndCurrentPlayerTurn();
	int roundNumber = _game->GetCurrentRound().GetRoundNumber();
	if (_game->GetCurrentRound().GetQueueSize() == 0) {
		json state;
		state["state"] = "CHOOSING";
		RequestBody body("CHANGESTATE", state.dump(), 0);
		sentToAllPlayer(&body);
	}
	else if(roundNumber>=10) {
		handleEndGame();
	}
	else {
		handleStartTurn();
	}
}

void GameEventHandler::handlePlayCard(RequestBody* request)
{
	std::string body = request->GetBody();
	Player* player = _game->GetPlayer(request->GetHandle());
	json bodyjson = json::parse(request->GetBody());
	int columnNumber = bodyjson["column"];
	_game->PlayCard(columnNumber);
	
	json setColumn;
	setColumn["column"] = _game->GetBoard().findColumn(columnNumber)->GetJson();
	RequestBody requestBody("SETCOLUMNS", setColumn.dump(), request->GetHandle());
	sentToAllPlayer(&requestBody);

	json setPoints;
	setPoints["points"] = player->GetPoints();
	RequestBody sendPointsRequest("SETPOINTS ", setPoints.dump(), request->GetHandle());

	sendToPlayer(request->GetHandle(), &requestBody);

	handleEndTurn();
	
}

void GameEventHandler::handleInitColumns()
{
	json json;
	json["columns"] = json::array();
	for (auto column : _game->GetBoard().GetColumns().GetList()) {
		json["columns"].push_back(column.GetJson());
	}
	RequestBody body("INITCOLUMNS", json.dump(), 0);
	sentToAllPlayer(&body);

}

Game* GameEventHandler::GetGame()
{
	return _game;
}

void GameEventHandler::sendToPlayer(int handle, RequestBody* request)
{
	json r;
	r["key"] = request->GetKey();
	r["body"] = json::parse(request->GetBody());
	std::string stringMessage = r.dump();
	const char* message = stringMessage.c_str();
	Player* player = _game->GetPlayer(handle);
	player->_socket.sendBytes(message, stringMessage.size());
}

void GameEventHandler::sentToAllPlayer(RequestBody* request)
{
	for (auto& player : _game->GetPlayers()) {
		json r;
		r["key"] = request->GetKey();
		r["body"] = json::parse(request->GetBody());
		std::string stringMessage = r.dump();
		const char* message = stringMessage.c_str();
		Player* p = player.second;
		p->_socket.sendBytes(message, stringMessage.size());

	}
}