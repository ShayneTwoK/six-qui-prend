#include "Player.h"
#include "Deck.h"
#include <iostream>
Player::Player(Poco::Net::SocketReactor& reactor, Poco::Net::StreamSocket& socket) :_reactor(reactor), _socket(socket)
{
}

Player::~Player()
{
}

void Player::SetPseudo(std::string psd)
{
	std::cout << "Set mon pseudo à" + psd;
	_pseudo = psd;
}

int Player::GetHandle()
{
	return _socket.impl()->sockfd();
}

int Player::GetPoints()
{
	return _points;
}

Deck<CardModel> Player::GetHand()
{
	return _hand;
}

void Player::SetHand(Deck<CardModel> hand)
{
	_hand = hand;
}

CardModel Player::GetCardInHand(int num)
{
	for (auto& card : _hand.GetList()) {
		// if the map value is equal to given value then
		// print the key
		// and set boolean value to false
		if (card.GetNumber() == num) {
			return card;
		}
	}
	return 0;
}

