#pragma once

#include "poker/domain/Card.hpp"

#include <array>
#include <cstddef>
#include <random>
#include <vector>

namespace poker {

class Deck {
public:
    Deck();

    void shuffle();
    [[nodiscard]] Card draw();
    [[nodiscard]] std::vector<Card> drawHand(std::size_t count);
    [[nodiscard]] std::size_t remaining() const noexcept;

private:
    std::array<Card, 52> cards_{};
    std::size_t nextCard_ = 0;
    std::mt19937 randomEngine_;
};

}  // namespace poker
