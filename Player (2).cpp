//Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <string>
#include "Player.h"
#include <algorithm>
#include <cassert>
using namespace std;

//SimplePlayer Implementation
class SimplePlayer : public Player {
  private:
    string name;
    vector<Card> hand;
  public:
    SimplePlayer(const string & name_in) : name(name_in){};
    const std::string & get_name() const{
        return SimplePlayer::name;
    }
    void add_card(const Card &c){
        assert(hand.size()<=MAX_HAND_SIZE);
        hand.push_back(c);
    };

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const{
        assert(round== 1 || round == 2);
        string upcardsuit;
        int count=0;
        if (round == 1){
            upcardsuit = upcard.get_suit();
            for (size_t i = 0; i < hand.size(); i++){
                if (hand[i].get_suit(upcardsuit) == upcardsuit 
                    && hand[i].is_face_or_ace() == true){
                    count++;
                }
            }
            if (count >=2){
                order_up_suit=upcardsuit;
                return true;
            }
            else{
                return false;
            }
        }
        else if (round==2){
            if (is_dealer==true){
                upcardsuit = Suit_next(upcard.get_suit());
                order_up_suit=upcardsuit;
                return true;
            }
            upcardsuit = Suit_next(upcard.get_suit());
            for (size_t i = 0; i < hand.size(); i++){
                if (hand[i].get_suit(upcardsuit)==upcardsuit
                    &&hand[i].is_face_or_ace()==true){
                    count++;
                }
            }
            if (count >=1){
                order_up_suit=upcardsuit;
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    };

    void add_and_discard(const Card &upcard){
        assert(hand.size()>=1);
        hand.push_back(upcard);
        int discardposition = 0;
        string trumpsuit = upcard.get_suit();
        for (size_t i = 0; i < hand.size(); i++){
            if (Card_less(hand[i] , hand[discardposition] , trumpsuit) == true){
                discardposition = i;
            }
        }
        hand.erase(hand.begin()+discardposition);
    };

    Card lead_card(const std::string &trump){
        //dont know how to check if trump is a valid suit
        assert(hand.size()>=1);
        int leadposition = -1;
        for (size_t i = 0; i < hand.size(); i++){
            if (hand[i].get_suit(trump)!=trump && leadposition==-1){
                leadposition=i;
            }
            else if(hand[i].get_suit(trump)!=trump && leadposition!=-1){
                if (Card_less(hand[i] , hand[leadposition] , trump) == false){
                    leadposition = i;
                }
            }
        }
        if (leadposition ==-1){
            leadposition = 0;
            for (size_t i = 0; i < hand.size(); i++){
                if (Card_less(hand[i] , hand[leadposition] , trump) == false){
                    leadposition = i;
                }
            }
            Card lead = hand[leadposition];
            hand.erase(hand.begin()+leadposition);
            return lead;            
        }
        else{
            Card lead = hand[leadposition];
            hand.erase(hand.begin()+leadposition);
            return lead;
        }
    };

    Card play_card(const Card &led_card, const std::string &trump){
        assert(hand.size()>=1);
        int playposition = -1;
        string followsuit = led_card.get_suit(trump);
        for (size_t i = 0; i < hand.size(); i++){
            if (hand[i].get_suit(trump)==followsuit && playposition==-1){
                playposition=i;
            }  
            else if(hand[i].get_suit(trump)==followsuit && playposition!=-1){
                if (Card_less(hand[i] , hand[playposition] , trump) == false){
                    playposition = i;
                }
            }
        }    
        if (playposition ==-1){
            playposition = 0;
            for (size_t i = 0; i < hand.size(); i++){
                if (Card_less(hand[i] , hand[playposition] , trump) == true){
                    playposition = i;
                }
            }
            Card play = hand[playposition];
            hand.erase(hand.begin()+playposition);
            return play; 
        }
        else{
            Card play = hand[playposition];
            hand.erase(hand.begin()+playposition);
            return play;
        }
    };
};




//HumanPlayer Implementation
class HumanPlayer : public Player {
  private:
    string name;
    vector<Card> hand;
    void print_hand() const {
        for (size_t i=0; i < hand.size(); ++i)
        cout << "Human player " << name << "'s hand: "
             << "[" << i << "] " << hand[i] << "\n";
    }
  public:
    HumanPlayer(const string & name_in) : name(name_in){};
    const std::string & get_name() const{
        return HumanPlayer::name;
    };

    void add_card(const Card &c){
        assert(hand.size()<=MAX_HAND_SIZE);
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    };

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const{
        assert(round== 1 || round == 2);
        string humaninput;
        print_hand();
        cout << "Human player " << name << ", please enter a suit, or \"pass\":\n"; 
        cin >> humaninput;
        if (humaninput=="pass"){
            return false;
        }
        else{
            order_up_suit=humaninput;
            return true;
        }
    };

    void add_and_discard(const Card &upcard){
        assert(hand.size()>=1);
        int humaninput;
        std::sort(hand.begin(), hand.end());
        print_hand();
        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << ", please select a card to discard:\n";
        cin >> humaninput;
        if (humaninput!=-1){
            hand.erase(hand.begin()+humaninput);
            hand.push_back(upcard);
        }
    };

    Card lead_card(const std::string &trump){
        assert(hand.size()>=1);
        int humaninput;
        std::sort(hand.begin(), hand.end());
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        cin >> humaninput;
        Card lead = hand[humaninput];
        hand.erase(hand.begin()+humaninput);
        return lead;
    };

    Card play_card(const Card &led_card, const std::string &trump){
        assert(hand.size()>=1);
        int humaninput;
        std::sort(hand.begin(), hand.end());
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        cin >> humaninput;
        Card play = hand[humaninput];
        hand.erase(hand.begin()+humaninput);
        return play;
    };
};



Player * Player_factory(const std::string &name, const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  else if (strategy == "Human") {
    return new HumanPlayer(name);
  }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}