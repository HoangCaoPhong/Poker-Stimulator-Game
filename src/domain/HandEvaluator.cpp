#include "poker/domain/HandEvaluator.hpp"

#include <algorithm>
#include <map>

namespace poker {
namespace {

std::vector<int> ranksDescending(const std::array<Card, 5>& cards) {
    std::vector<int> ranks;
    ranks.reserve(cards.size());
    for (const Card& card : cards) {
        ranks.push_back(rankValue(card.rank));
    }
    std::sort(ranks.rbegin(), ranks.rend());
    return ranks;
}

bool isStraight(const std::vector<int>& ranks, int& highCard) {
    std::vector<int> uniqueRanks = ranks;
    uniqueRanks.erase(std::unique(uniqueRanks.begin(), uniqueRanks.end()), uniqueRanks.end());
    if (uniqueRanks.size() != 5U) {
        return false;
    }

    if (uniqueRanks.front() == 14 && uniqueRanks[1] == 5 && uniqueRanks[2] == 4 &&
        uniqueRanks[3] == 3 && uniqueRanks[4] == 2) {
        highCard = 5;
        return true;
    }

    for (std::size_t index = 1; index < uniqueRanks.size(); ++index) {
        if (uniqueRanks[index - 1] != uniqueRanks[index] + 1) {
            return false;
        }
    }
    highCard = uniqueRanks.front();
    return true;
}

}  // namespace

std::string HandScore::label() const {
    switch (category) {
        case HandCategory::HighCard: return "High card";
        case HandCategory::Pair: return "One pair";
        case HandCategory::TwoPair: return "Two pair";
        case HandCategory::ThreeOfAKind: return "Three of a kind";
        case HandCategory::Straight: return "Straight";
        case HandCategory::Flush: return "Flush";
        case HandCategory::FullHouse: return "Full house";
        case HandCategory::FourOfAKind: return "Four of a kind";
        case HandCategory::StraightFlush: return "Straight flush";
    }
    return "Unknown hand";
}

HandScore evaluateHand(const std::array<Card, 5>& cards) {
    const std::vector<int> ranks = ranksDescending(cards);
    const bool flush = std::all_of(cards.begin() + 1, cards.end(), [&cards](const Card& card) {
        return card.suit == cards.front().suit;
    });

    int straightHighCard = 0;
    const bool straight = isStraight(ranks, straightHighCard);
    if (flush && straight) {
        return {HandCategory::StraightFlush, {straightHighCard}};
    }

    std::map<int, int, std::greater<>> frequency;
    for (const int rank : ranks) {
        ++frequency[rank];
    }

    std::vector<int> fours;
    std::vector<int> threes;
    std::vector<int> pairs;
    std::vector<int> singles;
    for (const auto& [rank, count] : frequency) {
        if (count == 4) {
            fours.push_back(rank);
        } else if (count == 3) {
            threes.push_back(rank);
        } else if (count == 2) {
            pairs.push_back(rank);
        } else {
            singles.push_back(rank);
        }
    }

    if (!fours.empty()) {
        return {HandCategory::FourOfAKind, {fours.front(), singles.front()}};
    }
    if (!threes.empty() && !pairs.empty()) {
        return {HandCategory::FullHouse, {threes.front(), pairs.front()}};
    }
    if (flush) {
        return {HandCategory::Flush, ranks};
    }
    if (straight) {
        return {HandCategory::Straight, {straightHighCard}};
    }
    if (!threes.empty()) {
        std::vector<int> breakers{threes.front()};
        breakers.insert(breakers.end(), singles.begin(), singles.end());
        return {HandCategory::ThreeOfAKind, breakers};
    }
    if (pairs.size() == 2U) {
        return {HandCategory::TwoPair, {pairs[0], pairs[1], singles.front()}};
    }
    if (pairs.size() == 1U) {
        std::vector<int> breakers{pairs.front()};
        breakers.insert(breakers.end(), singles.begin(), singles.end());
        return {HandCategory::Pair, breakers};
    }
    return {HandCategory::HighCard, ranks};
}

int compareHands(const HandScore& first, const HandScore& second) noexcept {
    const int firstCategory = static_cast<int>(first.category);
    const int secondCategory = static_cast<int>(second.category);
    if (firstCategory != secondCategory) {
        return firstCategory > secondCategory ? 1 : -1;
    }

    const std::size_t breakerCount = std::min(first.tieBreakers.size(), second.tieBreakers.size());
    for (std::size_t index = 0; index < breakerCount; ++index) {
        if (first.tieBreakers[index] != second.tieBreakers[index]) {
            return first.tieBreakers[index] > second.tieBreakers[index] ? 1 : -1;
        }
    }
    if (first.tieBreakers.size() == second.tieBreakers.size()) {
        return 0;
    }
    return first.tieBreakers.size() > second.tieBreakers.size() ? 1 : -1;
}

}  // namespace poker
