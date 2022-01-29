#pragma once
#include <string>
#include <map>
#include <nlohmann/json.hpp>
enum EventType {
    error,
    PSEUDO,
    STARTGAME
};

NLOHMANN_JSON_SERIALIZE_ENUM(EventType, {
   {error, nullptr},
   {PSEUDO, "PSEUDO"},
   {STARTGAME, "STARTGAME"}
    });


