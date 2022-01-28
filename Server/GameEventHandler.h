#pragma once
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketNotification.h>
#include "Game.h"
#include "Singleton.h"
#include "RequestBody.h"
#include "Event.h"
class GameEventHandler: public Singleton<GameEventHandler>
{

    //GameEventHandler(Poco::Net::SocketReactor& reactor, Game game);

    ///**
    // * @Brief Destructor
    // */
    //~GameEventHandler();
public:
    GameEventHandler();
    void registerAction(const std::string &actionName, IEventCallback* action);

    void notify();
    void handleEvent(RequestBody* request);
    void handleNewPlayer(RequestBody* request);
    void handleEndGame(RequestBody* request);
    void handleChoice(RequestBody* request);
    void handleStartGame(RequestBody* request);
    void sendToPlayer(int handle, RequestBody* request);
    void sentToAllPlayer(RequestBody* request);
    Game* GetGame();
private:
    Game* _game;
    std::map<std::string, Event*> inputEvents;

    /// Socket Reactor-Notifier
    //Poco::Net::SocketReactor& _reactor;
};
