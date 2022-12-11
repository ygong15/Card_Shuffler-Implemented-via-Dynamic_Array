#include "Cards.h"

#include <random>
#include <algorithm>

// Function: Constructor
// Purpose: Draws 5 cards from the supplied deck, and sorts them
// by rank
// Input: Takes in a ITPVector of cards for the deck
// Returns: Nothing
PokerHand::PokerHand(ITPVector<Card>& deck)
{
    for(int i = 0; i < 5; i++)
    {
        mHand.push_back(deck.back());
        deck.pop_back();
    }
    sortHand();
}

// Function: getBestPokerHand
// Purpose: Returns a string describing the poker hand this PokerHand
// contains
// Input: None
// Returns: The name of the best poker hand
std::string PokerHand::getBestPokerHand() const
{
    //check orderly -> from the best hand to worst hand. If a hand is found, return associate string
    if(hasStraight() && hasFlush())
    {
        return "straight flush";
    }
    else if(hasFourOfAKind())
    {
        return "four of a kind";
    }
    else if(hasFullHouse())
    {
        return "full house";
    }
    else if(hasFlush())
    {
        return "flush";
    }
    else if(hasStraight())
    {
        return "straight";
    }
    else if(hasThreeOfAKind())
    {
        return "three of a kind";
    }
    else if(hasTwoPairs())
    {
        return "two pairs";
    }
    else if(hasPair())
    {
        return "pair";
    }
    
    return "high card";
}

// Function: hasStraight
// Purpose: Determines if the hand has a straight
// Input: None
// Returns: true if there's a straight
bool PokerHand::hasStraight() const
{
    //straight means all the same number so return false if one difference is spotted
    for(int i = 0; i < mHand.size()-1; i++)
    {
        if(mHand[i].mRank != mHand[i+1].mRank-1)
        {
            return false;
        }
    }
    return true;
}

// Function: hasFlush
// Purpose: Determines if the hand has a flush
// Input: None
// Returns: true if there's a flush
bool PokerHand::hasFlush() const
{
    //flush means all suits are the same -> if one difference is spotted return false
    for(int i = 0; i < mHand.size(); i++)
    {
        if(mHand[i].mSuit != mHand[0].mSuit)
        {
            return false;
        }
    }
    return true;
}

// Function: hasFourOfAKind
// Purpose: Determines if the hand has a 4 of a kind
// Input: None
// Returns: true if there's a 4 of a kind
bool PokerHand::hasFourOfAKind() const
{
    //since a hand can has four of a kind in two different ways so we create two boolean varaibles. Either of them is true will return true
    //defualt both posibilities to true
    bool pos1 = true;
    bool pos2 = true;
    //check if pos1 if filled if not set to false
    for(int i = 0; i < mHand.size()-1; i++)
    {
        if(mHand[0].mRank != mHand[i].mRank)
        {
            pos1 = false;
        }
    }
    //check if pos2 if filled if not set to false
    for(int i = 1; i < mHand.size(); i++)
    {
        if(mHand[1].mRank != mHand[i].mRank)
        {
            pos2 = false;
        }
    }
    //only one pos has to be true for us to return true
    return pos1 || pos2;
}

// Function: hasFullHouse
// Purpose: Determines if the hand has a full house
// Input: None
// Returns: true if there's a full house
bool PokerHand::hasFullHouse() const
{
    //check the first possibiliy of a full house
    if(mHand[0].mRank == mHand[1].mRank && mHand[0].mRank == mHand[2].mRank)
    {
        //full fill the possibility will return true
        if(mHand[3].mRank == mHand[4].mRank)
        {
            return true;
        }
    }
    //check the second posibility of a full house
    else if(mHand[2].mRank == mHand[3].mRank && mHand[2].mRank == mHand[4].mRank)
    {
        //full fill the possibility will return true
        if(mHand[0].mRank == mHand[1].mRank)
        {
            return true;
        }
    }
    //return false if both possibilities are not met
    return false;
}

// Function: hasThreeOfAKind
// Purpose: Determines if the hand has a three of a kind
// Input: None
// Returns: true if there's a three of a kind
bool PokerHand::hasThreeOfAKind() const
{
    //since there are three posibilities for a hand to have three of a kind. Either of these boolean value is true we can return true
    bool pos1 = true;
    bool pos2 = true;
    bool pos3 = true;
    //check if pos1 if fullfilled
    for(int i = 0; i < 3; i++)
    {
        if(mHand[0].mRank != mHand[i].mRank)
        {
            pos1 = false;
        }
    }
    //check if pos2 if fullfilled
    for(int i = 1; i < 4; i++)
    {
        if(mHand[1].mRank != mHand[i].mRank)
        {
            pos2 = false;
        }
    }
    //check if pos3 if fullfilled
    for(int i = 2; i < mHand.size(); i++)
    {
        if(mHand[2].mRank != mHand[i].mRank)
        {
            pos3 = false;
        }
    }
    //return true if one possibiliy is true
    return pos1 || pos2 || pos3;
}

// Function: hasTwoPairs
// Purpose: Determines if the hand has two pairs
// Input: None
// Returns: true if there's two pairs
bool PokerHand::hasTwoPairs() const
{
    //check the first possibility
    if(mHand[0].mRank == mHand[1].mRank && mHand[2].mRank == mHand[3].mRank)
    {
        return true;
    }
    //check the second possibility
    else if(mHand[1].mRank == mHand[2].mRank && mHand[3].mRank == mHand[4].mRank)
    {
        return true;
    }
    //check the third possibility
    else if(mHand[0].mRank == mHand[1].mRank && mHand[3].mRank == mHand[4].mRank)
    {
        return true;
    }
    //return false if none of the possibilites are met
    return false;
}

// Function: hasPair
// Purpose: Determines if there's a pair
// Input: None
// Returns: true if there's a pair
bool PokerHand::hasPair() const
{
    //loop through the hand and see if each pair is the same
    for(int i = 0; i < mHand.size()-1; i++)
    {
        if(mHand[i].mRank == mHand[i+1].mRank)
        {
            //return true if one pair is spotted
            return true;
        }
    }
    //looping to the end means no pairs are spotted
    return false;
}

void PokerHand::sortHand()
{
    //1st for i-loop to set minimum index to i
    for(int i = 0; i < mHand.size(); i++)
    {
        int minIdx = i;
        //2nd for j-loop (start at i+1) to compare mHand[j] with minimum element. if mHand[j] < mHand[i] minIdx = j
        for(int j = i+1; j < mHand.size(); j++)
        {
            if(mHand[j] < mHand[minIdx])
            {
                minIdx = j;
            }
        }
        //after for j-loop, swap mHand[minIdx] with mHand[i]
        Card temp = mHand[i];
        mHand[i] = mHand[minIdx];
        mHand[minIdx] = temp;
    }
}

// Function: createDeck
// Purpose: Given an empty ITPVector of Cards, inserts a
// standard 52 card deck and shuffles it
// Input: An ITPVector of Cards (by reference)
// Returns: nothing
void createDeck(ITPVector<Card>& deck)
{
    //4 four loops to differs of Suit
    //in each four loop, 15 cards (from 2-A) are created and push into the vector
    for(int i = 2; i < 15; i++)
    {
        Card temp(i, CLUBS);
        deck.push_back(temp);
    }
    for(int i = 2; i < 15; i++)
    {
        Card temp(i, DIAMONDS);
        deck.push_back(temp);
    }
    for(int i = 2; i < 15; i++)
    {
        Card temp(i, HEARTS);
        deck.push_back(temp);
    }
    for(int i = 2; i < 15; i++)
    {
        Card temp(i, SPADES);
        deck.push_back(temp);
    }
    //sort the hand first
    std::sort(&deck[0], &deck[0] + deck.size());
    //randomly shuffled the sorted hand
    std::random_shuffle(&deck[0], &deck[0] + deck.size());
}

// Function: << operator for Card
// Purpose: Outputs the name and suit of the card
// Input: ostream and card
// Returns: ostream, with card data output to it
std::ostream& operator<<(std::ostream& os, const Card& card)
{
    //we first check for special value (those greater than 11 since they will not return numerically)
    if(card.mRank == 11)
    {
        os << "Jack";
    }
    else if(card.mRank == 12)
    {
        os << "Queen";
    }
    else if(card.mRank == 13)
    {
        os << "King";
    }
    else if(card.mRank == 14)
    {
        os << "Ace";
    }
    //if the rank if less than 10 then simply display the number
    else
    {
        os << card.mRank;
    }
    os << " of ";
    //after figuring out the rank of a card, we attach the suit of the card to it
    switch (card.mSuit) {
        case CLUBS:
            os << "Clubs";
            break;
        case DIAMONDS:
            os << "Diamonds";
            break;
        case HEARTS:
            os << "Hearts";
            break;
        case SPADES:
            os << "Spades";
        default:
            break;
    }
    return os;
}


// Function: < comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left < right
bool operator<(const Card& left, const Card& right)
{
    //compare suit if the rank is the same
    if(left.mRank == right.mRank)
    {
        return left.mSuit < right.mSuit;
    }
    //compare rank if they are not the same
    return left.mRank < right.mRank;
}

// Function: > comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left > right
bool operator>(const Card& left, const Card& right)
{
    //compare suit if the ranks are the same
    if(left.mRank == right.mRank)
    {
        return left.mSuit > right.mSuit;
    }
    //compare ranks if they are not the same
    return left.mRank > right.mRank;
}

// Function: << operator
// Purpose: Prints out the hand
std::ostream& operator<<(std::ostream& os, const PokerHand& hand)
{
    //put int the first {
    os << "{ ";
    //loop until the last element in the hand
    for(int i = 0; i < hand.mHand.size()-1; i++)
    {
        //all of these elements have a SUIT RANK, format
        os << hand.mHand[i] << ", ";
    }
    //add in the last element but do not add the ,
    os << hand.mHand[hand.mHand.size()-1] << " ";
    //add in the end }
    os << "}";
    //return the os stream
    return os;
}
