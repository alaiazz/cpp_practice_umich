// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here
// get_sui(), get_rank(),get_suit(trump),init1,init2
TEST(test_card_suit_and_rank) {
    // init1
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(two_spades.get_suit(), Card::SUIT_SPADES);

    //init2, number 
    Card four_diamonds = Card(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(four_diamonds.get_rank(), Card::RANK_FOUR);
    ASSERT_EQUAL(four_diamonds.get_suit(), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(four_diamonds.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS);

    //init2, number 
    Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(nine_clubs.get_rank(), Card::RANK_NINE);
    ASSERT_EQUAL(nine_clubs.get_suit(), Card::SUIT_CLUBS);
    ASSERT_EQUAL(nine_clubs.get_suit(Card::SUIT_CLUBS), Card::SUIT_CLUBS);

    //init2, face 
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(ace_hearts.get_rank(), Card::RANK_ACE);
    ASSERT_EQUAL(ace_hearts.get_suit(), Card::SUIT_HEARTS);
    ASSERT_EQUAL(ace_hearts.get_suit(Card::SUIT_HEARTS), Card::SUIT_HEARTS);

    //init2, face
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(jack_hearts.get_rank(), Card::RANK_JACK);
    ASSERT_EQUAL(jack_hearts.get_suit(), Card::SUIT_HEARTS);
    ASSERT_EQUAL(jack_hearts.get_suit(Card::SUIT_HEARTS), Card::SUIT_HEARTS);

    // left bower 
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(jack_diamonds.get_rank(), Card::RANK_JACK);
    ASSERT_EQUAL(jack_diamonds.get_suit(), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(jack_diamonds.get_suit(Card::SUIT_HEARTS), Card::SUIT_HEARTS);

}

// trump, faceorace, right,left 
TEST(test_card_type) {
    // false case 
    Card four_hearts = Card(Card::RANK_FOUR, Card::SUIT_HEARTS);
    ASSERT_FALSE(four_hearts.is_face_or_ace());
    ASSERT_FALSE(four_hearts.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(four_hearts.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(four_hearts.is_trump(Card::SUIT_CLUBS));

    //ace case  
    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_TRUE(ace_clubs.is_face_or_ace());
    ASSERT_FALSE(ace_clubs.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(ace_clubs.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(ace_clubs.is_trump(Card::SUIT_CLUBS));

    //jack case
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(jack_hearts.is_face_or_ace());
    ASSERT_TRUE(jack_hearts.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(jack_hearts.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_TRUE(jack_hearts.is_trump(Card::SUIT_HEARTS));
    ASSERT_TRUE(jack_hearts.is_left_bower(Card::SUIT_DIAMONDS));
}

// operators
TEST(test_card_self_comparison) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card three_diamonds = Card(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card four_spades = Card(Card::RANK_FOUR, Card::SUIT_SPADES);

    ASSERT_TRUE(three_spades < four_spades);
    ASSERT_TRUE(three_spades < three_diamonds);
    ASSERT_TRUE(three_spades <= four_spades);
    ASSERT_TRUE(three_spades <= three_spades);

    ASSERT_TRUE(four_spades > three_diamonds);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(four_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_TRUE(three_spades != four_spades);
}

// suit next 
TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
}

// test card less 
TEST(test_Card_less_self) {
    // trump suit  
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card four_spades = Card(Card::RANK_FOUR, Card::SUIT_SPADES);
    // right bower 
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    // left bower 
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    // normal
    Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card three_clubs = Card(Card::RANK_THREE, Card::SUIT_CLUBS);
    //led suit diamonds or clubs 
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card two_diamonds = Card(Card::RANK_TWO, Card::SUIT_DIAMONDS);

    ASSERT_FALSE(Card_less(three_spades, three_spades, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(three_spades, three_spades, Card::SUIT_SPADES));

    ASSERT_TRUE(Card_less(three_spades, four_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(three_spades, jack_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(three_spades, jack_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(three_clubs, nine_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(three_clubs, jack_clubs, Card::SUIT_SPADES));

    ASSERT_TRUE(Card_less(three_clubs, three_spades, three_spades,
                           Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(three_clubs, three_spades, nine_diamonds,
                           Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(three_clubs, nine_diamonds, nine_diamonds,
                           Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(two_diamonds, nine_diamonds, nine_diamonds,
                           Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(nine_diamonds, three_spades, nine_diamonds,
                           Card::SUIT_SPADES));
}

// test insertion 
TEST(test_card_insertion) {
    Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ostringstream oss;
    oss << queen_clubs;
    ASSERT_EQUAL(oss.str(), "Queen of Clubs");
}

TEST_MAIN()
