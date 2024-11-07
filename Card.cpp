// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;

constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
using namespace std;
//EFFECTS Initializes Card to the Two of Spades
Card::Card():rank(RANK_TWO), suit(SUIT_SPADES) { 
// default consutructor 
}
   
//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const string &rank_in, const string &suit_in): rank(rank_in), suit(suit_in) {
    // check the reuqirement 
    assert(rank_in == RANK_TWO || rank_in == RANK_THREE || rank_in == RANK_FOUR
        || rank_in == RANK_FIVE || rank_in == RANK_SIX || rank_in == RANK_SEVEN 
        || rank_in == RANK_EIGHT || rank_in == RANK_NINE || rank_in == RANK_TEN
        || rank_in == RANK_JACK || rank_in == RANK_QUEEN || rank_in == RANK_KING 
        || rank_in == RANK_ACE);

    assert(suit_in == SUIT_CLUBS || suit_in == SUIT_HEARTS 
        || suit_in == SUIT_SPADES || suit_in == SUIT_DIAMONDS);
    //non-default constructor 
}

//EFFECTS Returns the rank
std::string Card::get_rank() const {
    return rank; 
}
  
//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const {
    return suit; 
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const {

    // trunp is a valid suit 
    assert(trump == SUIT_CLUBS || trump == SUIT_HEARTS 
        || trump == SUIT_SPADES || trump == SUIT_DIAMONDS);
    
    if (is_left_bower(trump)) {
        return trump; 
    } else {
        return suit;
    }
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face_or_ace() const{
//use if function and == to check 
// long line !!
 if (get_rank() == RANK_JACK||get_rank() == RANK_QUEEN 
    ||get_rank() == RANK_KING||get_rank() == RANK_ACE) {
    return true; 
 }
 else {
    return false; 
 }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const{
    // check the requirement 
    assert(trump == SUIT_CLUBS || trump == SUIT_HEARTS 
        || trump == SUIT_SPADES || trump == SUIT_DIAMONDS);

    if (get_suit() == trump && get_rank() == RANK_JACK){
        return true; 
    }
    else {
        return false; 
    }
}
  
//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {
    // check the requirement 
    assert(trump == SUIT_CLUBS || trump == SUIT_HEARTS 
        || trump == SUIT_SPADES || trump == SUIT_DIAMONDS);

    // fulfill the effects
    if (get_suit() == Suit_next(trump) && get_rank() == RANK_JACK){
        return true; 
    }
    else {
        return false; 
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
    // check the requirement 
    assert(trump == SUIT_CLUBS || trump == SUIT_HEARTS 
        || trump == SUIT_SPADES || trump == SUIT_DIAMONDS);

    if (get_suit(trump) == trump){
        return true; 
    } 
    else {
        return false; 
    }
}


//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.

//  NOTICE: CHANGE THE FUNCTION TITLE 
bool operator<(const Card &lhs, const Card &rhs){
    //use  for loop to get the rank of each card 
    int rank_lhs_s = 0; 
    int rank_rhs_s = 0; 
    int rank_lhs_r = 0; 
    int rank_rhs_r = 0; 

    for (int i = 0; i < NUM_RANKS; ++i) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]){
            rank_lhs_r = i;  
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            rank_rhs_r = i; 
        }
    }

    for (int j = 0; j < NUM_SUITS; ++j) {
        if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[j]){
            rank_lhs_s = j;  
        }
        if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[j]) {
            rank_rhs_s = j; 
        }
    }

    // compare rank > suit 
    if (rank_lhs_r == rank_rhs_r) {
        return(rank_lhs_s < rank_rhs_s);
    }
    else {
        return (rank_lhs_r < rank_rhs_r);
    }
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs){
    if(lhs < rhs){
        return true; 
    }
    else if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else {
        return false; 
    }
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
    return (!(lhs<=rhs));
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
    return(!(lhs<rhs));
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
    if(!(lhs<rhs) && !(lhs>rhs)) {
        return true; 
    }
    else {
        return false; 
    }
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
    if(!(lhs==rhs)) {
        return true; 
    }
    else {
        return false; 
    }
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit){
// use a for loop to detect the suit OR just use 4 if statements 
// ? the idea of the suit of the same color 
// if use the if statement, how to compare 
// string or using the format below 
    assert(suit == Card::SUIT_CLUBS || suit == Card::SUIT_HEARTS 
        || suit == Card::SUIT_SPADES || suit == Card::SUIT_DIAMONDS);

    if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    }
    else {
        return Card::SUIT_DIAMONDS;
    }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){
    os << card.get_rank() << " of " << card.get_suit();
    return os; 
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){
    // requirement 
    assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_HEARTS 
        || trump == Card::SUIT_SPADES || trump == Card::SUIT_DIAMONDS);

    // if a is the trump card, b is not 
    if (a.is_trump(trump) && !b.is_trump(trump)) {
        return false; 
    }
    // if b is the trump card 
    if (!a.is_trump(trump) && b.is_trump(trump)) {
        return true; 
    }
    // if neither is 
    if (!a.is_trump(trump) && !b.is_trump(trump)){
        return (a<b);
    }
    // if both, consider the left bower and right bower 
    if (a.is_trump(trump) && b.is_trump(trump)) {
        // consider the left bower and right bower: R>L 
        // right bower case 
        if (b.is_right_bower(trump) && !a.is_right_bower(trump)){
            return true;
        }
        else if (a.is_right_bower(trump)){
            return false;
        }
        // left bower case 
        else if (!a.is_right_bower(trump) && !b.is_right_bower(trump)) {
            if (a.is_left_bower(trump)){
                return false; 
            }
            else if (!a.is_left_bower(trump) && b.is_left_bower(trump)){
                return true; 
            }
            // both in trump suit but not left bower 
            else if (!a.is_left_bower(trump) && !b.is_left_bower(trump)) {
                return(a<b);
            }
        }
    }
    return false; 
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    // if led suit is the trump suit 
    if (led_card.get_suit(trump) == trump){
        return Card_less(a,b,trump);
    }
    // if led suit is not the trump suit 
    else if (led_card.get_suit(trump) != trump) {
        if (a.is_trump(trump) && !b.is_trump(trump)) {
            return false; 
        }
        else if (!a.is_trump(trump) && b.is_trump(trump)) {
            return true; 
        }
        else if (a.is_trump(trump) && b.is_trump(trump)) {
            return (Card_less(a,b,trump));
        }
        else if (!a.is_trump(trump) && !b.is_trump(trump)) {
            if (a.get_suit(trump) == led_card.get_suit(trump) 
                && b.get_suit(trump) != led_card.get_suit(trump)) {
                return false; 
            }
            else if (a.get_suit(trump) != led_card.get_suit(trump) 
                && b.get_suit(trump) == led_card.get_suit(trump)){
                    return true; 
                }
            else if (a.get_suit(trump) == led_card.get_suit(trump) 
                && b.get_suit(trump) == led_card.get_suit(trump)) {
                    return (a<b);
                }
            else if (a.get_suit(trump) != led_card.get_suit(trump) 
                && b.get_suit(trump) != led_card.get_suit(trump)){
                    return (a<b);
                }
        }
    }
    return false; 
}


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=