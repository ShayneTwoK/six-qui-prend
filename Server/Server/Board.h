#pragma once
#include <vector>
#include "Column.h"
class Board {


public:
    Board() {}

    Column findColumn(int num) {
        for (int i = 0; i < columns.GetList().size(); i++) {
            if (columns.GetList()[i].GetNumber() == num) {
                return columns.GetList()[i];
            }
        }
    }

    Deck<Column> GetColumns() {
        return columns;
    }
    void SetColumn(int num, Deck<CardModel> cards) {
        Column c = findColumn(num);
        c.SetCards(cards);
    }
    void AddColumn(Column column) {
        columns += column;
    }
private:
    Deck<Column> columns;
};