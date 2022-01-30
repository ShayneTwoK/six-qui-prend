#pragma once
#include <random>
#include <vector>

/**
 * Deck class
 * Represents the deck of 104 cards created for the game
 */
template <typename T>
class Deck {
    std::vector<T> elemList;

public:
    Deck() {}
    Deck(const std::vector<T>& copyList) { elemList = copyList; }

    // Shuffles the vector num times
    void shuffleDeck(int num) {
        std::random_device rd;
        std::mt19937 g(rd());

        for (int i = 0; i < num; i++) {
            std::shuffle(elemList.begin(), elemList.end(), g);
        }
    }

    std::vector<T> GetList() {
        return elemList;
    }
    // Operator += overload to add a card to the bottom of the deck
    Deck& operator+=(const T& e) {
        elemList.insert(elemList.begin(), e);
        return *this;
    }

    // Operator -- overload to remove a card from the top of the deck and return
    // it
    T operator--() {
        T val = elemList.back();
        elemList.pop_back();
        return val;
    }
};