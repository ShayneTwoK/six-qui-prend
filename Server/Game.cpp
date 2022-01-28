#include "Game.h"
#include <charconv>
#include <nlohmann/json.hpp>
#include "Board.h"


Game::Game()
{
}

Game::~Game()
{
}

Board Game::GetBoard()
{
	return Board();
}

Player* Game::GetPlayerWithLessPoints()
{
	return 0;
}

std::vector<std::pair<int, Player*>> Game::GetPlayers()
{
	return _players;
}

void Game::EndRound()
{
}

/**
 * createDeck()
 * creates a deck of 104 Cards and returns it
 */
Deck<CardModel> Game::createDeck() {
	std::vector<CardModel> cardList;
	for (int i = 1; i <= _cardNumber; i++) {
		CardModel c(i);
		cardList.push_back(c);
	}

	Deck<CardModel> deck(cardList);
	deck.shuffleDeck(rand() % 100 + 1);
	return deck;
}

GameStatus Game::GetGameStatus()
{
	return _status;
}

bool Game::pointComparator(const std::pair<int, Player*> lhs, const std::pair<int, Player*> rhs)
{
	return lhs.second -> GetPoints() < rhs.second->GetPoints();
}

void Game::StartGame()
{
	//create game deck
	_cards = createDeck();
	Board board;
	_board = board;
	for (int i = 1; i <= 4; i++) {
		CardModel cardModel = --_cards;
		Column c(i);
		c.AddCard(cardModel);
		board.AddColumn(c);
	}
	//distribute all cards to players
	DistributeCardsToPlayers();
}

Deck<CardModel> Game::DistributeCardsToPlayers()
{
	for (auto& player : _players) {

		std::vector<CardModel> cardList;
		// Deal 10 cards to each player
		for (int i = 0; i < 10; i++) {
			 CardModel cardModel = --_cards;
			cardList.push_back(cardModel);
		}
		Player* p = player.second;
		Deck<CardModel> hand(cardList);
		p->SetHand(hand);
		return hand;
	}

}

void Game::addPlayer(Player* p)
{
	_players.push_back(std::make_pair(p->GetHandle(), p));
}

void Game::ChooseCard(int handle, int num)
{
	Player* p = GetPlayer(handle);
	CardModel card  = p->GetCardInHand(num);
	_chosenCards.push_back(std::make_pair(handle, card));
}

void Game::StartRound()
{
	std::vector<std::pair<Player*, CardModel*>> playersQueue;
	for (auto& card: _chosenCards)
	{
		Player* player = GetPlayer(card.first);
		CardModel* c = &card.second;

		playersQueue.push_back(std::make_pair(player, c));
	}
	//Round round(playersQueue);
	//_currentRound = round;

	//if (_currentRound.GetQueueSize() <= 0) {
	//	_status = TURN;
	//}
}

Player* Game::GetPlayer(int handle)
{
	//auto ret = std::find(_players.begin(), _players.end(), handle);
	//return ret->second;
	for (auto& player : _players) {
		// if the map value is equal to given value then
		// print the key
		// and set boolean value to false
		if (player.first == handle) {
			return player.second;
		}
	}
	return 0;
}


