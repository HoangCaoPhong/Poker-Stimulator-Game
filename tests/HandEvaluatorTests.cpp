#include "poker/domain/HandEvaluator.hpp"

#include <array>
#include <cstdlib>
#include <iostream>

namespace {

using poker::Card;
using poker::HandCategory;
using poker::Rank;
using poker::Suit;

Card card(const Rank rank, const Suit suit) {
    return {rank, suit};
}

bool expect(const bool condition, const char* message) {
    if (!condition) {
        std::cerr << "Test failed: " << message << '\n';
        return false;
    }
    return true;
}

}  // namespace

int main() {
    const std::array<Card, 5> royalFlush{
        card(Rank::Ten, Suit::Hearts), card(Rank::Jack, Suit::Hearts), card(Rank::Queen, Suit::Hearts),
        card(Rank::King, Suit::Hearts), card(Rank::Ace, Suit::Hearts)};
    const std::array<Card, 5> wheel{
        card(Rank::Ace, Suit::Clubs), card(Rank::Two, Suit::Hearts), card(Rank::Three, Suit::Spades),
        card(Rank::Four, Suit::Clubs), card(Rank::Five, Suit::Diamonds)};
    const std::array<Card, 5> twoPair{
        card(Rank::Ace, Suit::Clubs), card(Rank::Ace, Suit::Hearts), card(Rank::King, Suit::Spades),
        card(Rank::King, Suit::Clubs), card(Rank::Two, Suit::Diamonds)};
    const std::array<Card, 5> lowerTwoPair{
        card(Rank::Queen, Suit::Clubs), card(Rank::Queen, Suit::Hearts), card(Rank::Jack, Suit::Spades),
        card(Rank::Jack, Suit::Clubs), card(Rank::Ace, Suit::Diamonds)};

    const poker::HandScore royalScore = poker::evaluateHand(royalFlush);
    const poker::HandScore wheelScore = poker::evaluateHand(wheel);
    const poker::HandScore twoPairScore = poker::evaluateHand(twoPair);
    const poker::HandScore lowerTwoPairScore = poker::evaluateHand(lowerTwoPair);

    const bool passed =
        expect(royalScore.category == HandCategory::StraightFlush, "royal flush category") &&
        expect(wheelScore.category == HandCategory::Straight, "wheel straight category") &&
        expect(wheelScore.tieBreakers.front() == 5, "wheel high card") &&
        expect(twoPairScore.category == HandCategory::TwoPair, "two pair category") &&
        expect(poker::compareHands(twoPairScore, lowerTwoPairScore) > 0, "two-pair tie breaker") &&
        expect(poker::compareHands(royalScore, wheelScore) > 0, "hand category ordering");

    return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
