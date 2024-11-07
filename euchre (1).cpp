//Project UID 1d9f47bfc76643019cfbf037641defe1
# include <iostream>
# include <string>
# include <cassert>
# include <vector>
# include <fstream>
# include <sstream>
# include <cstdlib>
# include <algorithm>

# include "Pack.h"
# include "Player.h"
# include "Card.h"

using namespace std;

class Game {
 public:
  Game(     istream &pack_input, string shufflearg,     
            int pointstowin, vector<Player*> playerinput)
        : players(playerinput), points_to_win(pointstowin), shuffleornot(shufflearg){
    Pack pack0(pack_input);
    pack=pack0;
  };

  void play(){
    int handnumber=1;
    int partner02score=0;
    int partner13score=0;
    while (partner02score<points_to_win && partner13score< points_to_win){
        shuffle(shuffleornot);
        deal(handnumber);
        play_hand(partner02score, partner13score, handnumber);
        handnumber++;
    }
    if(partner02score>=points_to_win && partner13score<points_to_win){
        cout<<*players[0]<< " and "<< *players[2]<< " win!"<<endl;
    }
    else if(partner13score>=points_to_win && partner02score<points_to_win){
        cout<<*players[1]<< " and "<< *players[3]<< " win!"<<endl;
    }
  };

 private:
  vector<Player*> players;
  Pack pack;
  int points_to_win;
  string shuffleornot;

  void shuffle(string shuffle) {
    if (shuffle == "shuffle") {
        pack.shuffle();
    }
    else if (shuffle == "noshuffle") {   
        pack.reset();  
    }
  }

  void deal(int handnumber){
    int dealposition=handnumber;
    for(int i=1; i<=8; i++){
        if (i==1||i==3||i==6||i==8){
            for(int times=1; times<=3; times++){
                players[dealposition%4]->add_card(pack.deal_one());
            }
            dealposition++;
        }
        else{
            for(int times=1; times<=2; times++){
                players[dealposition%4]->add_card(pack.deal_one());
            }
            dealposition++;
        }
    }
  };

//takes in the trick number and the upcard;
// modifies whomadetrump and trumpsuit.
  void make_trump(Card& upcard, int& whomadetrump, int handnumber, string& trumpsuit){
    int makeposition=handnumber;
    int i=1;
    bool orderup=false;
    while(i<=4&&orderup==false){
        orderup=players[makeposition%4]->make_trump(upcard,
                                    makeposition%4==(handnumber-1)%4,1,trumpsuit);
        if(orderup==true){
            cout << *players[makeposition%4] <<" orders up "<< trumpsuit <<endl;
            whomadetrump=makeposition%4;

            //the dealer take the upcard
            players[(handnumber-1)%4]->add_and_discard(upcard);
            cout<<endl;
        }
        else if(orderup==false){
            cout << *players[makeposition%4] <<" passes"<< endl;
        }
        i++;
        makeposition++;
    }
    while( i>4 && i<=8 && orderup==false){
        orderup=players[makeposition%4]->make_trump(upcard,
                                    makeposition%4==(handnumber-1)%4,2,trumpsuit);
        if(orderup==true){
            cout << *players[makeposition%4] <<" orders up "<< trumpsuit <<endl <<endl;
            whomadetrump=makeposition%4;
        }
        else if(orderup==false){
            cout << *players[makeposition%4] <<" passes" << endl;
        }
        i++;
        makeposition++;
    }
  };

  void play_hand(int& partner02score, int& partner13score, int handnumber){
    int leadposition=handnumber%4;
    string trumpsuit;
    int whomadetrump;
    Card upcard=pack.deal_one();
    int trick02=0;
    int trick13=0;
//print
//Hand x
//xxx deals
//xxx turned up
    cout<< "Hand "<< handnumber-1<<endl << *players[(handnumber-1)%4]<< " deals"<<endl 
        << upcard<< " turned up"<<endl;
    make_trump(upcard, whomadetrump, handnumber, trumpsuit);
//play 5 tricks
    for (int i=1; i<=5; i++){
        play_tricks(trick02, trick13, leadposition, trumpsuit);
    }
//decide the winning partnership and add score
    if (trick02>trick13){
        cout<< *players[0]<< " and "<< *players[2]<< " win the hand"<<endl;
        if(whomadetrump==0||whomadetrump==2){
            if(trick02==5){
                partner02score= partner02score+2;
                cout<< "march!"<< endl 
                    <<*players[0]<< " and "<< *players[2]<< " have "<< partner02score
                    <<" points"<< endl <<*players[1]<< " and "
                    << *players[3]<< " have "<< partner13score
                    <<" points"<< endl<< endl;
            }
            else{
                partner02score= partner02score+1;
                cout<<*players[0]<< " and "<< *players[2]<< " have "<< partner02score
                    <<" points"<< endl <<*players[1]<< " and "
                    << *players[3]<< " have "<< partner13score
                    <<" points"<< endl<< endl;
            }
        }
        else if(whomadetrump!=0&&whomadetrump!=2){
            partner02score= partner02score+2;
            cout<<"euchred!"<< endl
                <<*players[0]<< " and "<< *players[2]<< " have "<< partner02score
                <<" points"<< endl <<*players[1]<< " and "
                << *players[3]<< " have "<< partner13score
                <<" points"<< endl<< endl;
        }
    }
    if (trick02<trick13){
        cout<< *players[1]<< " and "<< *players[3]<< " win the hand"<<endl;
        if(whomadetrump==1||whomadetrump==3){
            if(trick13==5){

                partner13score= partner13score+2;
                cout<<"march!"<< endl
                    <<*players[0]<< " and "<< *players[2]<< " have "<< partner02score
                    <<" points"<< endl <<*players[1]<< " and "
                    << *players[3]<< " have "<< partner13score
                    <<" points"<< endl<< endl;
            }
            else{
                partner13score= partner13score+1;
                cout<<*players[0]<< " and "<< *players[2]<< " have "<< partner02score
                    <<" points"<< endl <<*players[1]<< " and "
                    << *players[3]<< " have "<< partner13score
                    <<" points"<< endl<< endl;
            }
        }
        else if(whomadetrump!=1&&whomadetrump!=3){
            partner13score= partner13score+2;
            cout<<"euchred!"<< endl
                << *players[0]<< " and "<< *players[2]<< " have "<< partner02score
                <<" points"<< endl <<*players[1]<< " and "
                << *players[3]<< " have "<< partner13score
                <<" points"<< endl<< endl;
        }
    }
  };

  void win_trickpoint(int position, int& trick02, int& trick13){
    if (position==0 || position==2){
        trick02++;
    }
    else if (position==1 || position==3){
        trick13++;
    }
  }

  void play_tricks(int& trick02, int& trick13, int& leadposition, string trumpsuit){

    Card ledcard= players[leadposition]->lead_card(trumpsuit);
    cout<< ledcard<<" led by "<< *players[leadposition]<<endl;

    Card card1= players[(leadposition+1)%4]->play_card(ledcard, trumpsuit);
    cout<< card1<<" played by "<< *players[(leadposition+1)%4]<<endl;

    Card card2= players[(leadposition+2)%4]->play_card(ledcard, trumpsuit);
    cout<< card2<<" played by "<< *players[(leadposition+2)%4]<<endl;

    Card card3= players[(leadposition+3)%4]->play_card(ledcard, trumpsuit);
    cout<< card3<<" played by "<< *players[(leadposition+3)%4]<<endl;

    if (!Card_less(ledcard, card1, ledcard, trumpsuit) &&
        !Card_less(ledcard, card2, ledcard, trumpsuit) &&
        !Card_less(ledcard, card3, ledcard, trumpsuit)){
        win_trickpoint(leadposition, trick02, trick13);
        //print an extra newline at the end of each trick.
        cout<< *players[leadposition]<< " takes the trick"<<endl<<endl;
    }
    else if (!Card_less(card1, ledcard, ledcard, trumpsuit) &&
            !Card_less(card1, card2, ledcard, trumpsuit) &&
            !Card_less(card1, card3, ledcard, trumpsuit)){
        win_trickpoint((leadposition+1)%4, trick02, trick13);
        //print an extra newline at the end of each trick.
        cout<< *players[(leadposition+1)%4]<< " takes the trick"<<endl<<endl;
        leadposition=(leadposition+1)%4;
    }
    else if (!Card_less(card2, ledcard, ledcard, trumpsuit) &&
            !Card_less(card2, card1, ledcard, trumpsuit) &&
            !Card_less(card2, card3, ledcard, trumpsuit)){
        win_trickpoint((leadposition+2)%4, trick02, trick13);
        //print an extra newline at the end of each trick.
        cout<< *players[(leadposition+2)%4]<< " takes the trick"<<endl<<endl;
        leadposition=(leadposition+2)%4;
    }
    else if (!Card_less(card3, ledcard, ledcard, trumpsuit) &&
            !Card_less(card3, card1, ledcard, trumpsuit) &&
            !Card_less(card3, card2, ledcard, trumpsuit)){
        win_trickpoint((leadposition+3)%4, trick02, trick13);
        //print an extra newline at the end of each trick.
        cout<< *players[(leadposition+3)%4]<< " takes the trick"<<endl<<endl;
        leadposition=(leadposition+3)%4;
    }
  }
};






int main(int argc, char **argv) {
//Read command line args and check for errors
    string shuffle=argv[2];
    int points_to_win=atoi(argv[3]);
    string p0n=argv[4];
    string p0t=argv[5];
    string p1n=argv[6];
    string p1t=argv[7];
    string p2n=argv[8];
    string p2t=argv[9];
    string p3n=argv[10];
    string p3t=argv[11];
  if(argc== 12 && 1<=points_to_win && points_to_win<=100 
    && (shuffle=="shuffle"||shuffle=="noshuffle") 
    && (p0t=="Simple"||p0t=="Human") && (p1t=="Simple"||p1t=="Human")
    && (p2t=="Simple"||p2t=="Human") && (p3t=="Simple"||p3t=="Human")){

//print the executable and all arguments on the first line.
    for (int i=0; i<12; i++){
        if(i!=11){
            cout<<argv[i] <<" ";
        }
        else if(i==11){
            cout<<argv[i] <<" "<<endl;
        }
    }

    string pack_filename= argv[1];
    ifstream fin;
    fin.open(pack_filename);
    if (!fin.is_open()) {
    cout << "Error opening " << pack_filename << endl;
    return 1;
    }
    vector<Player*> players;
 /*   Player * p0 = Player_factory(p0n, p0t);
    Player * p1 = Player_factory(p1n, p1t);
    Player * p2 = Player_factory(p2n, p2t);
    Player * p3 = Player_factory(p3n, p3t); */
    players.push_back(Player_factory(p0n, p0t));
    players.push_back(Player_factory(p1n, p1t));
    players.push_back(Player_factory(p2n, p2t));
    players.push_back(Player_factory(p3n, p3t));

    Game game(fin, shuffle, points_to_win, players);
    game.play();
    for (size_t i = 0; i < players.size(); ++i) {
    delete players[i];
    }
    return 0;
  }

  else{
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    return 2;
  }
}