#include "poker/domain/Deck.hpp"

#include <algorithm>
#include <chrono>
#include <stdexcept>

namespace poker {

Deck::Deck()
    : randomEngine_(static_cast<std::mt19937::result_type>(
          std::chrono::high_resolution_clock::now().time_since_epoch().count())) {
    std::size_t index = 0;
    for (const auto suit : {Suit::Clubs, Suit::Diamonds, Suit::Hearts, Suit::Spades}) {
        for (int rank = rankValue(Rank::Two); rank <= rankValue(Rank::Ace); ++rank) {
            cards_[index++] = {static_cast<Rank>(rank), suit};
        }
    }
    shuffle();
}

void Deck::shuffle() {
    std::shuffle(cards_.begin(), cards_.end(), randomEngine_);
    nextCard_ = 0;
}

Card Deck::draw() {
    if (nextCard_ >= cards_.size()) {
        throw std::out_of_range("The deck is empty");
    }
    return cards_[nextCard_++];
}

std::vector<Card> Deck::drawHand(const std::size_t count) {
    if (count > remaining()) {
        throw std::out_of_range("Not enough cards remain in the deck");
    }

    std::vector<Card> hand;
    hand.reserve(count);
    for (std::size_t card = 0; card < count; ++card) {
        hand.push_back(draw());
    }
    return hand;
}

std::size_t Deck::remaining() const noexcept {
    return cards_.size() - nextCard_;
}

}  // namespace poker
