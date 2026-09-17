#pragma once

#include "poker/domain/Card.hpp"

#include <array>
#include <string>
#include <vector>

namespace poker {

enum class HandCategory : int {
    HighCard,
    Pair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush
};

struct HandScore {
    HandCategory category = HandCategory::HighCard;
    std::vector<int> tieBreakers;

    [[nodiscard]] std::string label() const;
};

[[nodiscard]] HandScore evaluateHand(const std::array<Card, 5>& cards);
[[nodiscard]] int compareHands(const HandScore& first, const HandScore& second) noexcept;

}  // namespace poker
