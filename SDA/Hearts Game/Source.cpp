#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Cards {
private:
    string rank;        //for rank of single card
    char suit;          //for suit of single card

public:
    static const vector<string> ranks; //array for storing ranks {2, 3, 4, 5, 6.... J, Q, K, A}
    static const vector<char> suits;   //array for storing suits {H, S, C, D}

    Cards(string r, char s) {
        rank = r;
        suit = s;
    }

    string getRank() const {   //getter for ranks
        return rank;
    }

    char getSuit() const {   //getter function for suits
        return suit;
    }

    string toString() const {    //function for returning card as string: (2S --> 2 of Spades);
        return rank + string(1, suit);
    }
};

// Initializing the ranks and suits
const vector<string> Cards::ranks = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };
const vector<char> Cards::suits = { 'H','S','C','D' };


class Player {
private:
    string name;
    int score;

public:
    vector<Cards> hand;

    Player(string Pname) {
        name = Pname;
        score = 0;
    }

    void addCard(Cards card) {
        hand.push_back(card);
    }

    void addScore(int points) {
        score += points;
    }

    void showHand() {
        cout << name << "'s Hand: ";
        cout << endl << "Indexes: \n";
        for (int i = 0; i < hand.size(); i++) {
            cout << i + 1 << "  ";
        }
        cout << endl;
        for (int i = 0; i < hand.size(); i++) {
            cout << hand[i].toString() << " ";
        }
        cout << endl;
    }

    Cards playCard(int cardIndex) {
        if (cardIndex >= 1 && cardIndex <= hand.size()) {
            Cards playedCard = hand[cardIndex - 1];
            hand.erase(hand.begin() + cardIndex - 1);
            return playedCard;
        }
        else {
            cout << "Invalid Card Index, Try Again\n";
            return Cards("Invalid", 'X'); // Use "Invalid" for rank to identify invalid cards
        }
    }

    void passCards(Player& player, const vector<int>& Index) {
        for (int i = 0; i < Index.size(); i++) {
            player.addCard(hand[Index[i]]);
        }
        for (int i = Index.size() - 1; i >= 0; i--) {
            hand.erase(hand.begin() + Index[i]);
        }
    }

    string getName() {
        return name;
    }

    int getScore() {
        return score;
    }

    bool CardsExists()const {
        return !hand.empty();
    }
};


class Deck {
private:
    vector<Cards> deck;

public:
    Deck() {//constructor to build a deck
        for (char suit : Cards::suits) {
            for (string rank : Cards::ranks) {
                deck.push_back(Cards(rank, suit));//creating a card and adding to the deck
            }
        }
    }

    void shuffleDeck() {    //function for shuffling the deck
        random_shuffle(deck.begin(), deck.end());
    }

    void printDeck() {
        for (const auto& card : deck) {
            cout << card.toString() << " ";        //converting cards into string using rank+suit
        }
        cout << endl;
    }

    void dealCards(Player players[]) {
        int cardIndex = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                players[i].addCard(deck[cardIndex]);
                cardIndex++;
            }
        }
    }

};


// AI makes a move
Cards AIPlayCard(Player& player, char lead) {
    for (int i = 0; i < player.hand.size(); i++) {
        if (player.hand[i].getSuit() == lead) {
            return player.playCard(i + 1);
        }
    }
    return player.playCard(1);    //if no card of the lead suit then play the first holding card
}

// Function to compare cards based on suit and rank
int compareCards(const Cards& card1, const Cards& card2, char leadSuit) {
    string rankOrder = "23456789TJQKA"; // T represents 10
    int rank1 = -1, rank2 = -1;
    for (int i = 0; i < rankOrder.size(); i++) {
        if (card1.getRank()[0] == rankOrder[i]) {
            rank1 = i;
        }
        if (card2.getRank()[0] == rankOrder[i]) {
            rank2 = i;
        }
    }

    if (card1.getSuit() == leadSuit && card2.getSuit() == leadSuit) {
        if (rank1 > rank2) {
            return 1;  // card1 wins
        }
        else if (rank1 < rank2) {
            return 2;  // card2 wins
        }
        else {
            return 0;  // draw
        }
    }
    else if (card1.getSuit() == leadSuit) {
        return 1;  // card1 wins
    }
    else if (card2.getSuit() == leadSuit) {
        return 2;  // card2 wins
    }
    else {
        if (rank1 > rank2) {
            return 1;  // card1 wins
        }
        else if (rank1 < rank2) {
            return 2;  // card2 wins
        }
        else {
            return 0;  // draw
        }
    }
}

// Function to validate cards played
bool validateCard(const Cards& playedCard, const vector<Cards>& roundCards, bool heart, const vector<Cards>& playerHand) {
    // If no cards have been played yet
    if (roundCards.empty()) {
        // If hearts are not broken, check if the player is trying to lead with hearts
        if (playedCard.getSuit() == 'H' && !heart) {
            return false; // Cannot lead with hearts if hearts not broken
        }
        return true; // Else, it's valid to lead with any card
    }

    // If the player has no other suits to play, hearts can be played if they are the only remaining cards
    bool hasNonHeartsCard = false;
    for (const Cards& card : playerHand) {
        if (card.getSuit() != 'H') {
            hasNonHeartsCard = true;
            break;
        }
    }

    // If player has only hearts remaining, allow playing hearts
    if (!hasNonHeartsCard && playedCard.getSuit() == 'H') {
        return true;
    }

    // If there's a previous card played, check if the player is following suit or rank
    const Cards& lastCard = roundCards.back();
    return playedCard.getRank() == lastCard.getRank() || playedCard.getSuit() == lastCard.getSuit();
}


// Function to display the leaderboard
void displayLeaderBoard(Player players[], int num) {
    cout << "\n\033[32m===== Round Leaderboard =====\033[0m\n";
    cout << "Name " << "   Score " << endl;
    cout << "---------------------------------------\n";
    for (int i = 0; i < num; i++) {
        cout << players[i].getName() << "\t" << players[i].getScore() << endl;
    }
    cout << "---------------------------------------\n";
}

int main() {
    srand(time(0));
    int choice;
    bool gameRunning = true;
    bool heartsBroken = false;

    Deck deck;
    deck.shuffleDeck();

    Player players[4] = { Player("User "),Player("AI-1"),Player("AI-2"),Player("AI-3") };

    deck.dealCards(players);
    vector<Cards> roundCards; // To track the cards played in a round

    // Card passing mechanism at the start of the game
    for (int i = 0; i < 4; i++) {
        vector<int> Indices = { 0, 1, 2 }; // Pass the first 3 cards to the next player
        players[i].passCards(players[(i + 1) % 4], Indices);
    }

    while (gameRunning) {
        cout << "\n\033[33m = >=> = >=> = >=> = >=>\033[0m";
        cout << "\n\t\033[33m MAIN MENU\033[0m \n";
        cout << "\033[33m = >=> = >=> = >=> = >=>\033[0m\n";
        cout << "1. View Hand: \n";
        cout << "2. Play Round: \n";
        cout << "3. Show Scores: \n";
        cout << "4. End Game: \n";
        cout << "Press Key (1-3): \033[";
        cin >> choice;

        if (choice == 1) {
            players[0].showHand();
        }

        else if (choice == 2) {

            if (!players[0].CardsExists()) {
                cout << " You have no Cards Left!!!\n";
                gameRunning = false;
                break;
            }

            int cardIndex;
            players[0].showHand();
            cout << "Enter the index of the Card you want to play: ";
            cin >> cardIndex;

            Cards playedCard = players[0].playCard(cardIndex);
            if (playedCard.getRank() != "Invalid") {
                cout << " You Played: " << playedCard.toString() << endl;
            }

            if (!validateCard(playedCard, roundCards, heartsBroken, players[0].hand)) { // Fix validation check
                cout << "Invalid Card Played!!! Penalty Applied!!!\n";
                players[0].addScore(-1);
                players[0].addCard(playedCard); // Return the invalid card back
                continue;
            }

            roundCards.push_back(playedCard); // Store the played card for validation

            if (playedCard.getSuit() == 'H') heartsBroken = true; // Hearts are broken

            // AI Players' turns
            for (int i = 1; i < 4; i++) {
                Cards aiCard = AIPlayCard(players[i], playedCard.getSuit());
                roundCards.push_back(aiCard);
                cout << "AI-" << i << " Played: " << aiCard.toString() << endl;
            }

            // Determine the winner of the round based on the played cards
            char lead = roundCards[0].getSuit();  // The first card played sets the lead suit
            int roundWinner = 1;  // Assume the first player wins
            for (int i = 1; i < roundCards.size(); i++) {
                int comparison = compareCards(roundCards[i], roundCards[roundWinner - 1], lead);
                if (comparison == 1) {
                    roundWinner = i + 1;
                }
            }

            // Check if the Queen of Spades was played and add 13 points
            for (const Cards& card : roundCards) {
                if (card.getRank() == "Q" && card.getSuit() == 'S') {
                    players[roundWinner - 1].addScore(13);
                    break;
                }
            }

            // Add the winner's score
            players[roundWinner - 1].addScore(1); // For winning the round
            cout << players[roundWinner - 1].getName() << " won the round!" << endl;
            displayLeaderBoard(players, 4);

            // Reset the round
            roundCards.clear();
        }

        else if (choice == 3) {
            displayLeaderBoard(players, 4);
        }

        else if (choice == 4) {
            cout << "Game Over! Final Leaderboard: \n";
            displayLeaderBoard(players, 4);
            gameRunning = false;
        }

    }

    return 0;
}
