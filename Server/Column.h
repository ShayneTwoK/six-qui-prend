#pragma once
#include <vector>
#include "CardModel.h"
#include <nlohmann/json.hpp>
using nlohmann::json;
class Column {
public:

    Column(int num) :_num(num) {};

    Deck<CardModel> GetCards() {
        return _cards;
    };

    void SetCards(Deck<CardModel> cards) {
        _cards = cards;
    }

    void AddCard(CardModel card) {
        _cards += card;
    }
    int GetCardsNumber() {
        return _cards.GetList().size();
    }
    void Reset() {
        _cards.GetList().clear();
    }
    int GetPoints() {
        int points = 0;
        
        for (auto card : _cards.GetList()) {
            points += card.GetPoints();
        }
        return points;
    }


    int GetNumber() {
        return _num;
    };

    nlohmann::json GetJson() {
        nlohmann::json j;

        j["num"] = _num;
        j["cards"] = json::array();

        for (auto card : _cards.GetList()) {
            j["cards"].push_back(card.GetJson());
        }
        return j;
    }

private:

    Deck<CardModel> _cards;
    int _num;
};