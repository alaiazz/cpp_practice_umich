// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>
#include <cassert>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}

TEST(test_simple_player_make_trump) { //1normal
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_player_lead_card_1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_SPADES);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card
  delete bob;
}

/*TEST(test_simple_player_lead_card_6) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ten_spades); //check led card
  delete bob;
} */

TEST(test_simple_player_lead_card_6) { //did not change suit of jack
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_JACK, Card::SUIT_DIAMONDS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ten_spades); //check led card

  delete bob;
}

TEST(test_simple_player_lead_card_8) { //did not consider left bower in adddiscard
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_QUEEN, Card::SUIT_HEARTS) // upcard
  );

  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Diamonds"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

  delete bob;
}

TEST(test_simple_player_lead_card_4) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_SPADES);

  // Verify the card Bob selected to lead
  Card ace_clubs(Card::RANK_ACE, Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_led, ace_clubs); //check led card
  delete bob;
}

TEST(test_simple_player_lead_card_5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card queen_spades(Card::RANK_QUEEN, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, queen_spades); //check led card
  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_lead_card_3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_JACK, Card::SUIT_SPADES) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_SPADES);

  // Verify the card Bob selected to lead
  Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, jack_spades); //check led card

  delete bob;
}

TEST(test_simple_player_lead_card_7) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_JACK, Card::SUIT_CLUBS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_SPADES);

  // Verify the card Bob selected to lead
  Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_led, jack_clubs); //check led card

  delete bob;
}

TEST(test_simple_player_play_card) { //normal
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_simple_player_play_card_1) { //normal
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(test_simple_player_play_card_3) { //normal
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(test_simple_player_play_card_4) { //normal
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_simple_player_play_card_5) { //normal
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_simple_player_play_card_6) { //normal
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_simple_player_play_card_7) { //normal
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  delete bob;
}

TEST(test_simple_player_play_card_8) { //consider left bower
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_simple_player_play_card_2) { //only one
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_simple_player_play_card_9) { //consider left bower& follow suit
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Diamonds"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  delete bob;
}

TEST(test_simple_player_play_card_10) { //consider left bower &follow the largest suit
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  Card card_played = bob->play_card(
    nine_spades,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  delete bob;
}

TEST(test_simple_player_make_trump2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump=Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
    nine_diamonds,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(!orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump=Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
    nine_diamonds,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(!orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump4) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump=Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
    nine_diamonds,    // Upcard
    true,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

  delete bob;
}

TEST(test_simple_player_make_trump5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump=Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
    nine_diamonds,    // Upcard
    false,           // Bob is not the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(!orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump6) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump=Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
    nine_diamonds,    // Upcard
    false,           // Bob is not the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

  delete bob;
}

TEST(test_simple_player_make_trump7) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump=Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
    nine_diamonds,    // Upcard
    false,           // Bob is not the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);

  delete bob;
}

TEST(test_simple_player_make_trump8) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump=Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
    nine_diamonds,    // Upcard
    false,           // Bob is not the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(!orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump9) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump=Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
    nine_diamonds,    // Upcard
    false,           // Bob is not the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

  delete bob;
}

TEST(test_simple_player_lead_card2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, king_spades); //check led card

  delete bob;
}

TEST(test_simple_player_add_and_discard2) { //only discard the first or the last
    // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_QUEEN, Card::SUIT_HEARTS) // upcard
  );

  Card card_played = bob->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  card_played = bob->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  card_played = bob->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  card_played = bob->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  card_played = bob->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  delete bob;

  Player * dan = Player_factory("dan", "Simple");
  dan->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  dan->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  dan->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  dan->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  dan->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  // Bob adds a card to his hand and discards one card
  dan->add_and_discard(
    Card(Card::RANK_QUEEN, Card::SUIT_HEARTS) // upcard
  );

  card_played = dan->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  card_played = dan->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  card_played = dan->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  card_played = dan->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  card_played = dan->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  delete dan;

}

TEST(test_simple_player_add_and_discard3) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_QUEEN, Card::SUIT_HEARTS) // upcard
  );

  Card card_played = bob->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  card_played = bob->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  card_played = bob->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  card_played = bob->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  card_played = bob->play_card(Card(Card::RANK_NINE,Card::SUIT_HEARTS), Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  delete bob;
}

TEST(test_simple_player_leadall) { //only discard the first or the last
    // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  Card card_played = bob->lead_card(Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
  card_played = bob->lead_card(Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  card_played = bob->lead_card(Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  card_played = bob->lead_card(Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  card_played = bob->lead_card(Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_SPADES));

  delete bob;

  Player * charlie = Player_factory("charlie", "Simple");
  charlie->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  charlie->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  charlie->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  charlie->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  charlie->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  card_played = charlie->lead_card(Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
  card_played = charlie->lead_card(Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  card_played = charlie->lead_card(Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  card_played = charlie->lead_card(Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  card_played = charlie->lead_card(Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));

  delete charlie;
}

TEST(test_simple_player_leadall2) { //only discard the first or the last
    // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

  Card card_played = bob->lead_card(Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  card_played = bob->lead_card(Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  card_played = bob->lead_card(Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  card_played = bob->lead_card(Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  card_played = bob->lead_card(Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));

  delete bob;

}

TEST_MAIN()