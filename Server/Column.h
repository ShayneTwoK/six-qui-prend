#pragma once
#include <vector>
#include "CardModel.h"
class Column {
public:

    Column(int num):_num(num) {};
    //bool Deserialize(const rapidjson::Value& obj);
    //bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

    Deck<CardModel> GetCards() {
        return _cards;
    };

    void SetCards(Deck<CardModel> cards) {
        _cards = cards;
    }

    void AddCard(CardModel card) {
        _cards += card;
    }


    int GetNumber() {
        return _num;
    };

private:

    Deck<CardModel> _cards;
    int _num;
};
