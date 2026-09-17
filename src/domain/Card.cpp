#include "poker/domain/Card.hpp"

#include <stdexcept>

namespace poker {

int rankValue(const Rank rank) noexcept {
    return static_cast<int>(rank);
}

std::string rankLabel(const Rank rank) {
    switch (rank) {
        case Rank::Two: return "2";
        case Rank::Three: return "3";
        case Rank::Four: return "4";
        case Rank::Five: return "5";
        case Rank::Six: return "6";
        case Rank::Seven: return "7";
        case Rank::Eight: return "8";
        case Rank::Nine: return "9";
        case Rank::Ten: return "10";
        case Rank::Jack: return "J";
        case Rank::Queen: return "Q";
        case Rank::King: return "K";
        case Rank::Ace: return "A";
    }
    throw std::logic_error("Unsupported card rank");
}

std::string suitLabel(const Suit suit) {
    switch (suit) {
        case Suit::Clubs: return "C";
        case Suit::Diamonds: return "D";
        case Suit::Hearts: return "H";
        case Suit::Spades: return "S";
    }
    throw std::logic_error("Unsupported card suit");
}

bool isRed(const Suit suit) noexcept {
    return suit == Suit::Diamonds || suit == Suit::Hearts;
}

}  // namespace poker
