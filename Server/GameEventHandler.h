#pragma once
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketNotification.h>
#include "Game.h"
#include "Singleton.h"
#include "RequestBody.h"

class GameEventHandler : public Singleton<GameEventHandler>
{

    //GameEventHandler(Poco::Net::SocketReactor& reactor, Game game);

    ///**
    // * @Brief Destructor
    // */
    //~GameEventHandler();
public:
    GameEventHandler();

    void handleEvent(RequestBody* request);
    void handleNewPlayer(RequestBody* request);
    void handleEndGame(RequestBody* request);
    void handleChoice(RequestBody* request);
    void handleStartGame();
    void handleStartTurn();
    void handleEndTurn();
    void handleInitColumns();
    void sendToPlayer(int handle, RequestBody* request);
    void sentToAllPlayer(RequestBody* request);
    Game* GetGame();
private:
    Game* _game;

    /// Socket Reactor-Notifier
    //Poco::Net::SocketReactor& _reactor;
};