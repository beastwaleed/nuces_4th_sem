//#include<iostream>
//#include<string>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//class Cards {
//private:
//	string rank;		//for rank of single card
//	char suit;			//for suit of single card
//
//public:
//	static const vector<string> ranks; //array for storing ranks {1,2,3,4,5....J,Q,K,A}
//	static const vector<char>suits;///array for stroing suits {H, S, C, D}
//
//	Cards(string r, char s) {
//		rank = r;
//		suit = s;
//
//	}
//
//	string getRank() const {	///getter for ranks
//		return rank;
//	}
//
//	char getSuit() const {	///getter function for suits
//		return suit;
//	}
//
//	string toString() const {	//function for return card as string: (2S --> 2 of spades); 
//		return rank + string(1, suit);
//	}
//
//};
//
////initiallizing the ranks and suits
//const vector<string> Cards::ranks = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };
//const vector<char>Cards::suits = { 'H','S','C','D' };
//
//
//
//class Player {
//private:
//	string name;
//	int score;
//
//public:
//	vector<Cards> hand;
//
//	Player(string Pname) {
//		name = Pname;
//		score = 0;
//	}
//
//
//	void addCard(Cards card) {
//		hand.push_back(card);
//	}
//
//	void addScore(int points) {
//		score += points;
//	}
//
//	void showHand() {
//		cout << name << "'s Hand: ";
//
//		cout << endl << "Indexes: \n";
//
//		for (int i = 0;i < hand.size();i++) {
//			cout << i + 1 << "  ";
//		}
//
//		cout << endl;
//
//		for (int i = 0;i < hand.size();i++) {
//			cout << hand[i].toString() << " ";
//		}
//		cout << endl;
//	}
//
//	Cards playCard(int cardIndex) {
//		if (cardIndex >= 1 && cardIndex <= hand.size()) {
//			Cards playedCard = hand[cardIndex - 1];
//			hand.erase(hand.begin() + cardIndex - 1);
//			return playedCard;
//		}
//		else {
//			cout << "Invalid Card Index, Try Again\n";
//			return Cards("Invalid", 'X'); // Use "Invalid" for rank to identify invalid cards
//		}
//	}
//
//	void passCards(Player& player, const vector<int>& Index) {
//		for (int i = 0;i < Index.size();i++) {
//			player.addCard(hand[Index[i]]);
//		}
//		for (int i = Index.size() - 1; i >= 0;i--) {
//			hand.erase(hand.begin() + Index[i]);
//		}
//	}
//
//
//	string getName() {
//		return name;
//	}
//
//	int getScore() {
//		return score;
//	}
//
//	bool CardsExists()const {
//		return !hand.empty();
//	}
//
//};
//
//
//
//class Deck {
//private:
//	vector<Cards> deck;
//
//public:
//	Deck() {//constructor to build a deck
//		for (char suit : Cards::suits) {
//			for (string rank : Cards::ranks) {
//				deck.push_back(Cards(rank, suit));//creating a card and adding to the deck
//			}
//		}
//	}
//
//	void shuffleDeck() {	//function for shuffling the deck
//		random_shuffle(deck.begin(), deck.end());
//	}
//
//	void printDeck() {
//		for (const auto& card : deck) {
//			cout << card.toString() << " ";		//converting cards into string using rank+suit
//		}
//		cout << endl;
//	}
//
//	void dealCards(Player players[]) {
//		int cardIndex = 0;
//		for (int i = 0;i < 4;i++) {
//			for (int j = 0;j < 13;j++) {
//				players[i].addCard(deck[cardIndex]);
//				cardIndex++;
//			}
//		}
//	}
//
//};
//
//
//Cards AIPlayCard(Player& player, char lead) {
//
//	for (int i = 0;i < player.hand.size();i++) {
//		if (player.hand[i].getSuit() == lead) {
//			return player.playCard(i + 1);
//		}
//	}
//	return player.playCard(1);	//if no card of the lead suit then play the first holding card
//}
//
//int compareCards(const Cards& card1, const Cards& card2, char leadSuit, bool& heartsBroken) {
//	string rankOrder = "23456789TJQKA"; // T represents 10
//
//	int rank1 = -1, rank2 = -1;
//	for (int i = 0; i < rankOrder.size(); i++) {
//		if (card1.getRank()[0] == rankOrder[i]) {
//			rank1 = i;
//		}
//		if (card2.getRank()[0] == rankOrder[i]) {
//			rank2 = i;
//		}
//	}
//
//	// Add point scoring for Hearts and Queen of Spades
//	if (card1.getSuit() == 'H') {
//		card1.addScore(1); // Add 1 point for Hearts
//	}
//	if (card2.getSuit() == 'H') {
//		card2.addScore(1); // Add 1 point for Hearts
//	}
//	if (card1.getSuit() == 'S' && card1.getRank() == "Q") {
//		card1.addScore(13); // Add 13 points for Queen of Spades
//	}
//	if (card2.getSuit() == 'S' && card2.getRank() == "Q") {
//		card2.addScore(13); // Add 13 points for Queen of Spades
//	}
//
//	if (card1.getSuit() == leadSuit && card2.getSuit() == leadSuit) {
//		if (rank1 > rank2) {
//			return 1;
//		}
//		else if (rank1 < rank2) {
//			return 2;
//		}
//		else {
//			return 0;
//		}
//	}
//	else if (card1.getSuit() == leadSuit) {
//		return 1;
//	}
//	else if (card2.getSuit() == leadSuit) {
//		return 2;
//	}
//	else {
//		if (rank1 > rank2) {
//			return 1;
//		}
//		else if (rank1 < rank2) {
//			return 2;
//		}
//		else {
//			return 0;
//		}
//	}
//}
//
//
//	//function for validating card
//bool validateCard(const Cards& playedCard, const vector<Cards>& roundCards, bool heart) {
//	if (roundCards.empty()) {
//
//		if (playedCard.getSuit() == 'H' && !heart) {
//			return false; // Cannot lead with hearts if hearts not broken
//		}
//
//		return true;
//	}
//	const Cards& lastCard = roundCards.back();
//	
//	//match the rank or suit with the lastly played card
//	return playedCard.getRank() == lastCard.getRank() || playedCard.getSuit() == lastCard.getSuit();
//}
//
//
//void displayLeaderBoard(Player players[], int num) {
//	cout << "\n\033[32m===== Round Leaderboard =====\033[0m\n";
//	cout << "Name " << "   Score " << endl;
//	cout << "---------------------------------------\n";
//	for (int i = 0;i < num;i++) {
//		cout << players[i].getName() << "\t" << players[i].getScore() << endl;
//	}
//	cout << "---------------------------------------\n";
//}
//
//int main() {
//	srand(time(0));
//	int choice;
//	bool gameRunning = true;
//	bool heartsBroken = false;
//
//	Deck deck;
//	deck.shuffleDeck();
//
//	Player players[4] = { Player("User "),Player("AI-1"),Player("AI-2"),Player("AI-3") };
//
//	deck.dealCards(players);
//	vector<Cards> roundCards; // To track the cards played in a round
//
//	for (int i = 0;i < 4;i++) {
//		vector<int> Indices = { 0,1,2 };
//		players[i].passCards(players[(i + 1) % 4], Indices);
//	}
//
//
//	while (gameRunning) {
//		cout <<	"\n\033[33m = >=> = >=> = >=> = >=>\033[0m";
//		cout << "\n\t\033[33m MAIN MENU\033[0m \n";
//		cout << "\033[33m = >=> = >=> = >=> = >=>\033[0m\n";
//		cout << "1. View Hand: \n";
//		cout << "2. Play Round: \n";
//		cout << "3. Show Scores: \n";
//		cout << "4. End Game: \n";
//		cout << "Press Key (1-3): \033[";
//		cin >> choice;
//
//		if (choice == 1) {
//			players[0].showHand();
//		}
//
//		else if (choice == 2) {
//
//			if (!players[0].CardsExists()) {
//				cout << " You have no Cards Left!!!\n";
//				gameRunning = false;
//				break;
//			}
//
//			int cardIndex;
//			players[0].showHand();
//			cout << "Enter the index of the Card you want to play: ";
//			cin >> cardIndex;
//
//			Cards playedCard = players[0].playCard(cardIndex);
//			if (playedCard.getRank() != "Invalid") {
//				cout << " You Played: " << playedCard.toString() << endl;
//			}
//
//			if (!validateCard(playedCard, roundCards, heartsBroken)) { // Fix validation check
//				cout << "Invalid Card Played!!! Penalty Applied!!!\n";
//				players[0].addScore(-1);
//				players[0].addCard(playedCard); // Return the invalid card back to the player's hand
//				continue;
//			}
//
//
//			roundCards.push_back(playedCard);
//			cout << "You Played: " << playedCard.toString() << endl;
//
//			if (playedCard.getSuit() == 'H') {
//				heartsBroken = true; // Hearts are now broken
//			}
//
//			char leadSuit = playedCard.getSuit();
//
//
//			//Remaining 3 automated players turns;
//			//vector<Cards> roundCards = { playedCard };
//			for (int i = 1;i < 4;i++) {
//
//				if (!players[i].CardsExists()) {
//					continue;
//				}
//
//				Cards AiPlay = AIPlayCard(players[i],leadSuit);
//				if (!validateCard(AiPlay, roundCards, heartsBroken)) {
//					cout << players[i].getName() << " Played an Invalid card and loses 1 point!!\n";
//					players[i].addScore(-1);
//					continue;
//				}
//
//				roundCards.push_back(AiPlay);
//				cout << players[i].getName() << "played: " << AiPlay.toString() << endl;
//			}
//
//			//finding winner
//			int winIdx = 0;
//			for (int i = 1; i < roundCards.size(); i++) {
//				if (compareCards(roundCards[winIdx], roundCards[i],leadSuit) == 2) {
//					winIdx = i;
//				}
//			}
//			cout << players[winIdx].getName() << " wins this round!!\n";
//			players[winIdx].addScore(1);
//
//
//			displayLeaderBoard(players, 4);
//			roundCards.clear();		//clear the vector for next round
//
//		}
//		else if (choice == 3) {
//			cout << "SCORES: \n";
//			cout << "| Name |   | Scores | \n";
//			for (int i = 0;i < 4;i++) {
//				cout << "  " << players[i].getName() << ": \t" << players[i].getScore() << endl;
//			}
//
//		}
//
//		else if (choice == 4) {
//			cout << "Final Scores: \n";
//			cout << "| Name | \t|  Scores | \n";
//			for (int i = 0;i < 4;i++) {
//				cout << players[i].getName() << ": \t" << players[i].getScore() << endl;
//			}
//			cout << "Game Over! " << endl;
//
//			//finding final winner
//			int winner = 0;
//			for (int i = 1;i < 4;i++) {
//				if (players[i].getScore() > players[winner].getScore()) {
//					winner = i;
//				}
//			}
//			cout << "Winner is: " << players[winner].getName() << " With the Score: " << players[winner].getScore() << endl;
//
//			gameRunning = false;
//
//		}
//
//		else {
//			cout << "Don't You Know How to Use Keyboard , Huh ??\n";
//		}
//	}
//
//	system("pause");
//	return 0;
//}