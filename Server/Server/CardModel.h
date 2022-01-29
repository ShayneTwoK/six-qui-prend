#pragma once
#include <nlohmann/json.hpp>
class CardModel {
public:

    CardModel(int num);
    //bool Deserialize(const rapidjson::Value& obj);
    //bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

    int GetPoints();
    int GetNumber();

    nlohmann::json GetJson();
private:

    int _points;
    int _num;
};
