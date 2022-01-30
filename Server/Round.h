#pragma once
#include <vector>
#include "Player.h"
class Round {
    std::vector<std::pair<Player*, CardModel*>> playersQueue;

public:
    Round() {

    }
    Round(int roundNumber,std::vector<std::pair<Player*, CardModel*>> queue) {
        _round = roundNumber;
        playersQueue = queue;
          std::sort(playersQueue.begin(), playersQueue.end(), [](const std::pair<Player*, CardModel*>& x, const std::pair<Player*, CardModel*>& y) { return x.second->GetNumber() < y.second->GetNumber(); });
    }

    ~Round()
    {
    }

    int GetQueueSize() {
        return playersQueue.size();
    }
    int GetRoundNumber() {
        return _round;
    }
    
    std::pair<Player*, CardModel*> getCurrentPlayerTurn() {
        return playersQueue.back();
    }

    //// Operator -- overload to remove a card from the top of the deck and return
    //// it
    std::pair<Player*, CardModel*> operator--() {
        std::pair<Player*, CardModel*> val = playersQueue.back();
        playersQueue.pop_back();
        return val;
    }
private:
    //define the function:
    int _round;
};