#pragma once

#include <string>

namespace poker {

enum class Suit { Clubs, Diamonds, Hearts, Spades };

enum class Rank : int {
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

struct Card {
    Rank rank;
    Suit suit;
};

[[nodiscard]] int rankValue(Rank rank) noexcept;
[[nodiscard]] std::string rankLabel(Rank rank);
[[nodiscard]] std::string suitLabel(Suit suit);
[[nodiscard]] bool isRed(Suit suit) noexcept;

}  // namespace poker
