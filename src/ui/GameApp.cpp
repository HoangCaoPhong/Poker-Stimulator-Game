#include "poker/ui/GameApp.hpp"

#include <algorithm>
#include <array>
#include <filesystem>
#include <stdexcept>
#include <vector>

namespace poker {
namespace {

const sf::Color kFelt{19, 103, 74};
const sf::Color kFeltDark{9, 60, 45};
const sf::Color kGold{232, 190, 81};
const sf::Color kCream{247, 242, 225};
const sf::Color kInk{31, 38, 48};
const sf::Color kRed{194, 56, 56};

bool contains(const sf::FloatRect& bounds, const sf::Vector2i& point) {
    return bounds.contains(static_cast<float>(point.x), static_cast<float>(point.y));
}

}  // namespace

GameApp::GameApp()
    : window_(sf::VideoMode(1280, 720), "Poker Simulator", sf::Style::Titlebar | sf::Style::Close) {
    window_.setFramerateLimit(60);
    hasFont_ = loadFont();
    dealRound();
}

int GameApp::run() {
    while (window_.isOpen()) {
        processEvents();
        render();
    }
    return 0;
}

bool GameApp::loadFont() {
    const std::array<std::filesystem::path, 3> candidates{
        "assets/fonts/LiberationSans-Regular.ttf",
        "../assets/fonts/LiberationSans-Regular.ttf",
        "../../assets/fonts/LiberationSans-Regular.ttf",
    };
    for (const auto& candidate : candidates) {
        if (font_.loadFromFile(candidate.string())) {
            return true;
        }
    }
    return false;
}

void GameApp::processEvents() {
    sf::Event event{};
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window_.close();
            }
            if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space ||
                event.key.code == sf::Keyboard::R) {
                dealRound();
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            const sf::FloatRect dealButton{540.0F, 624.0F, 200.0F, 54.0F};
            if (contains(dealButton, sf::Mouse::getPosition(window_))) {
                dealRound();
            }
        }
    }
}

void GameApp::dealRound() {
    if (deck_.remaining() < 10U) {
        deck_.shuffle();
    }

    const std::vector<Card> first = deck_.drawHand(5);
    const std::vector<Card> second = deck_.drawHand(5);
    std::copy(first.begin(), first.end(), playerOne_.begin());
    std::copy(second.begin(), second.end(), playerTwo_.begin());

    playerOneScore_ = evaluateHand(playerOne_);
    playerTwoScore_ = evaluateHand(playerTwo_);
    winner_ = compareHands(playerOneScore_, playerTwoScore_);
    ++round_;
}

void GameApp::drawLabel(const std::string& value, const unsigned int size, const sf::Vector2f position,
                        const sf::Color color, const bool centered) {
    if (!hasFont_) {
        return;
    }
    sf::Text text(value, font_, size);
    text.setFillColor(color);
    if (centered) {
        const sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.0F, bounds.top + bounds.height / 2.0F);
    }
    text.setPosition(position);
    window_.draw(text);
}

void GameApp::drawCard(const Card& card, const sf::Vector2f position, const sf::Vector2f size) {
    sf::RectangleShape shadow(size);
    shadow.setPosition(position + sf::Vector2f{5.0F, 6.0F});
    shadow.setFillColor(sf::Color(0, 0, 0, 65));
    window_.draw(shadow);

    sf::RectangleShape body(size);
    body.setPosition(position);
    body.setFillColor(kCream);
    body.setOutlineColor(kGold);
    body.setOutlineThickness(2.0F);
    window_.draw(body);

    const sf::Color color = isRed(card.suit) ? kRed : kInk;
    drawLabel(rankLabel(card.rank), 30, position + sf::Vector2f{11.0F, 7.0F}, color);
    drawLabel(suitLabel(card.suit), 30, position + sf::Vector2f{11.0F, 42.0F}, color);
    drawLabel(suitLabel(card.suit), 52, position + size / 2.0F, color, true);
}

void GameApp::render() {
    window_.clear(kFeltDark);

    sf::CircleShape table(550.0F);
    table.setScale(1.08F, 0.52F);
    table.setPosition(46.0F, 166.0F);
    table.setFillColor(kFelt);
    table.setOutlineColor(kGold);
    table.setOutlineThickness(5.0F);
    window_.draw(table);

    drawLabel("POKER SIMULATOR", 38, {640.0F, 44.0F}, kGold, true);
    drawLabel("Five-card showdown", 20, {640.0F, 84.0F}, kCream, true);
    drawLabel("Round " + std::to_string(round_), 18, {640.0F, 116.0F}, kCream, true);

    const sf::Color firstColor = winner_ >= 0 ? kGold : kCream;
    const sf::Color secondColor = winner_ <= 0 ? kGold : kCream;
    drawLabel("PLAYER ONE", 23, {214.0F, 202.0F}, firstColor, true);
    drawLabel(playerOneScore_.label(), 18, {214.0F, 230.0F}, kCream, true);
    drawLabel("PLAYER TWO", 23, {1066.0F, 202.0F}, secondColor, true);
    drawLabel(playerTwoScore_.label(), 18, {1066.0F, 230.0F}, kCream, true);

    const sf::Vector2f cardSize{100.0F, 145.0F};
    for (std::size_t index = 0; index < playerOne_.size(); ++index) {
        drawCard(playerOne_[index], {44.0F + static_cast<float>(index) * 82.0F, 286.0F}, cardSize);
        drawCard(playerTwo_[index], {792.0F + static_cast<float>(index) * 82.0F, 286.0F}, cardSize);
    }

    std::string result = "Draw";
    if (winner_ > 0) {
        result = "Player One wins";
    } else if (winner_ < 0) {
        result = "Player Two wins";
    }
    drawLabel(result, 28, {640.0F, 506.0F}, kGold, true);

    const sf::FloatRect buttonBounds{540.0F, 624.0F, 200.0F, 54.0F};
    sf::RectangleShape dealButton({buttonBounds.width, buttonBounds.height});
    dealButton.setPosition(buttonBounds.left, buttonBounds.top);
    dealButton.setFillColor(kGold);
    dealButton.setOutlineColor(kCream);
    dealButton.setOutlineThickness(2.0F);
    window_.draw(dealButton);
    drawLabel("DEAL ROUND", 21, {640.0F, 651.0F}, kInk, true);
    drawLabel("Space / Enter / R to deal   |   Esc to close", 16, {640.0F, 583.0F}, kCream, true);

    if (!hasFont_) {
        sf::RectangleShape warning({1280.0F, 44.0F});
        warning.setFillColor(sf::Color(130, 34, 34));
        window_.draw(warning);
    }
    window_.display();
}

}  // namespace poker
