#pragma once
#include <vector>
#include "Player.h"
class Round {
    std::vector<std::pair<Player*, CardModel*>> playersQueue;

public:
    Round() {};
    Round(std::vector<std::pair<Player*, CardModel*>> queue) {
        playersQueue = queue;
        /*  sort(playersQueue.begin(), playersQueue.end(), &cardComparator);*/
    }

    ~Round()
    {
    }

    int GetQueueSize() {
        return playersQueue.size();
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
    bool cardComparator(std::pair<Player*, CardModel*> lhs, std::pair<Player*, CardModel*> rhs) {
        return lhs.second->GetNumber() < rhs.second->GetNumber();
    }

};