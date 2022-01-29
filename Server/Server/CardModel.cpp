#include "CardModel.h"
#include <nlohmann/json.hpp>
using nlohmann::json;
CardModel::CardModel(int num) : _num(num) {
    if (num % 11 == 0) {
        _points = num == 55 ? 7 : 5;
    }
    else if (num % 10 == 0) {
        _points = 3;
    }
    else if (num % 5 == 0) {
        _points = 2;
    }
    else {
        _points = 1;
    }
}
int CardModel::GetPoints() {
    return _points;
}
int CardModel::GetNumber()
{
    return _num;
}

json CardModel::GetJson()
{
    json j;
    j["num"] = _num;
    j["points"] = _points;
    return j;
}
