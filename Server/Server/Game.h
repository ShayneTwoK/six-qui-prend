#pragma once
#include <vector>
#include "Player.h"
#include "RequestBody.h"
#include "Deck.h"
#include "Round.h"
#include "Board.h"

enum GameStatus {
    CHOICE,
    TURN,
    ENDGAME
};
class Game
{
public:

    Game();

    /**
     * @Brief Destructor
     */
    ~Game();

    void StartGame();

    Deck<CardModel> DistributeCardsToPlayers();

    void addPlayer(Player*);

    Player* GetPlayer(int handle);

    void ChooseCard(int handle, int num);

    void StartRound();

    Board GetBoard();
    Player* GetPlayerWithLessPoints();
    std::vector<std::pair<int, Player*>> GetPlayers();
    void EndRound();
    Deck<CardModel> createDeck();
    GameStatus GetGameStatus();
private:

    std::vector<std::pair<int, Player*>> _players;
    Deck<CardModel> _cards;
    int _cardNumber = 104;
    Round _currentRound;
    Board _board;
    GameStatus _status;
    std::vector<std::pair<int, CardModel>> _chosenCards;
    bool pointComparator(const std::pair<int, Player*> lhs, const std::pair<int, Player*> rhs);
};