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

Round Game::GetCurrentRound()
{
	return _currentRound;
}

std::vector<int> Game::GetPlayableColumns(int handle)
{
	std::vector<int> columnsNumber;
	std::pair<Player*, CardModel*> pair = _currentRound.getCurrentPlayerTurn();
	for (auto column : _board.GetColumns().GetList()) {
		CardModel lastCard = column.GetCards().GetList().back();
		if (pair.second->GetNumber() < lastCard.GetNumber()) {
			columnsNumber.push_back(column.GetNumber());
		}
	}
	return columnsNumber;
}

Player* Game::GetPlayerWithLessPoints()
{
	std::sort(_players.begin(), _players.end(), [](const std::pair<int, Player*>& x, const std::pair<int, Player*>& y) { return x.second->GetPoints() < y.second->GetPoints(); });
	return _players.at(0).second;
}

void Game::PlayCard(int columnNumber)
{
	std::pair<Player*, CardModel*> pair = _currentRound.getCurrentPlayerTurn();
	Column* column = _board.findColumn(columnNumber);
	CardModel lastColumnCard = column->GetCards().GetList().back();
	int columnSize = column->GetCardsNumber();
	if (columnSize >= 5 || lastColumnCard.GetNumber() > pair.second->GetNumber()) {
		int columnPoints = column->GetPoints();
		column->Reset();
		pair.first->AddPoints(columnPoints);
	}
	column->AddCard(*pair.second);
}

std::vector<std::pair<int, Player*>> Game::GetPlayers()
{
	return _players;
}

void Game::EndCurrentPlayerTurn()
{
	--_currentRound;
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
	CardModel card = p->GetCardInHand(num);
	_chosenCards.push_back(std::make_pair(handle, card));
}

void Game::StartRound()
{
	roundNumber++;
	std::vector<std::pair<Player*, CardModel*>> playersQueue;
	for (auto& card : _chosenCards)
	{
		Player* player = GetPlayer(card.first);
		CardModel* c = &card.second;

		playersQueue.push_back(std::make_pair(player, c));
	}
	_chosenCards.clear();
	Round round(roundNumber,playersQueue);
	_currentRound = round;

}
bool Game::HasEveryOneChoseCard()
{
	if (_chosenCards.size() == _players.size()) {
		return true;
	}
	return false;
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


