// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <string>
#include "Pack.h"

using namespace std;
  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  Pack::Pack():next(0){
  // array, for loop to insert 
  // one suit, low to high
  int suit = 4; 
  int rank = 6; 
  int index = 0; 

  for (int i = 0; i < suit; i++) {
    for (int j = 0; j < rank; j++) {
        Card card(RANK_NAMES_BY_WEIGHT[j+7],SUIT_NAMES_BY_WEIGHT[i]);
        cards[index] = card; 
        index++; 
    }
  }
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input):next(0){
  //use the for loop to insert 
  //requirement
  string suit; 
  string rank;
  string of; 

  for (int i = 0; i < PACK_SIZE; i++) {
    pack_input >> rank >> of >> suit; 
    Card card(rank, suit);
    cards[i] = card; 
  }
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    assert(!empty());
    next ++; 
    return cards[next-1];
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){
   next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){
  // one that moves the original top card to second
  // the original bottom card to second from the bottom 
  
  // split into top half and bottom half 
  std::array<Card, PACK_SIZE/2> cards_top;
  std::array<Card, PACK_SIZE/2> cards_bottom;
  // the top card of the bottom half is now the first card
  // the top card of the top half (original top card) is now the second card
  reset();
  // for loop, 7 times 
  for (int i = 0; i < 7; ++i)  {
    // deal_one will move one card to the next card 
    for (int j = 0; j < PACK_SIZE/2; ++j){
      cards_top[j] = cards[j];
      cards_bottom[j] = cards[j+12];
    }
    //12 0 13 1 14 2 15 3 16 4 17 5 18 6 19 7 20 8 21 9 22 10 23 11 
    for (int x = 0; x < PACK_SIZE; x +=2) {
      cards[x] = cards_bottom[x/2]; 
      cards[x+1] = cards_top[x/2]; 
    }
  }
  }
  

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    return (next >= PACK_SIZE);
  }
