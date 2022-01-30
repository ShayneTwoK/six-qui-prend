#pragma once
#include <string>
#include <Poco/Net/SocketReactor.h>
#include "CardModel.h"
#include "Deck.h"
#include <Poco/Net/StreamSocket.h>
class Player
{
public:

    /**
     * @Brief Constructor of the Connection Handler
     * @Note Each object is unique to an accepted connection
     * @Param SteamSocket is the socket accepting the connections
     * @Param SocketReactor is the reacting engine (threaded) which creates notifications about the socket
     */
    Player(Poco::Net::SocketReactor& reactor, Poco::Net::StreamSocket& socket);

    /**
     * @Brief Destructor
     */
    ~Player();

    void SetPseudo(std::string psd);

    int GetHandle();
    int GetPoints();
    void AddPoints(int number);
    std::string GetPseudo();
    Deck<CardModel> GetHand();
    void SetHand(Deck<CardModel>);
    CardModel GetCardInHand(int num);
    Poco::Net::StreamSocket& _socket;

private:
    Deck<CardModel> _hand;
    int _points = 0;
    std::string _pseudo;

    /// Socket Reactor-Notifier
    Poco::Net::SocketReactor& _reactor;

    int _handle = 0;
    bool turn = false;
};