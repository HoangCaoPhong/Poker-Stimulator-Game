#pragma once

#include "poker/domain/Deck.hpp"
#include "poker/domain/HandEvaluator.hpp"

#include <SFML/Graphics.hpp>

#include <array>
#include <string>

namespace poker {

class GameApp {
public:
    GameApp();
    int run();

private:
    void processEvents();
    void dealRound();
    void render();
    void drawCard(const Card& card, sf::Vector2f position, sf::Vector2f size);
    void drawLabel(const std::string& value, unsigned int size, sf::Vector2f position,
                   sf::Color color, bool centered = false);
    [[nodiscard]] bool loadFont();

    sf::RenderWindow window_;
    sf::Font font_;
    Deck deck_;
    std::array<Card, 5> playerOne_{};
    std::array<Card, 5> playerTwo_{};
    HandScore playerOneScore_{};
    HandScore playerTwoScore_{};
    int winner_ = -1;
    unsigned int round_ = 0;
    bool hasFont_ = false;
};

}  // namespace poker
