#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
    srand(time(NULL));
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char suit[4] = {'S','H','C','D'};
	string rank[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
	vector<string> player0, player1, player2, player3;
	string pile, pile1;
	char playerChoice, choiceSuit;
	bool eight, match;
	int num;
	
	int S = 0;
	int H = 0;
	int C = 0;
	int D = 0;
	int turn = 0;
	
	vector<string> deck; deck.reserve(52);   // Creating the deck of cards.
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {
			deck.push_back(suit[i] + rank[j]);
		}
	}
    random_shuffle(deck.begin(), deck.end());
	
	for (int i = 0; i < 6; ++i) {   // Giving each player 6 card.
		player0.push_back (deck[deck.size()-1]);
		deck.pop_back();
		
		player1.push_back (deck[deck.size()-1]);
		deck.pop_back();
		
		player2.push_back (deck[deck.size()-1]);
		deck.pop_back();
		
		player3.push_back (deck[deck.size()-1]);
		deck.pop_back();
	}
	
	pile = deck[deck.size()-1];   // Assigns the first card.
	deck.pop_back();
	
	while (true) {
		if (turn == 999) {break;}
		
		if (turn == 0) {   // Player 0's turn. 
			cout << "Pile has " << pile << " <--- your turn" << endl << endl;
			for (int i = 0; i < player0.size(); ++i) {
				cout << "\t(" << alphabet[i] << ") " << player0[i];
			}
			cout << "\t(" << alphabet[player0.size()] << ") " << "draw" << endl << endl;
			cout << "Which one to play? ";
			cin >> playerChoice;
			cout << endl;
			
			if (deck.size() == 0 || player0.size() == 25 || player0.size() == 0) {
                turn = 999;   // Ends game if deck is empty or if player has too much or too little.
                break;
            }
			
			if (playerChoice == '?') {   // (?) option
				cout << "Player 1";
				for (int i = 0; i < player1.size(); i++) {
					cout << "\t(" << alphabet[i] << ") " << player1[i];
				}
				cout << endl << "Player 2";
				for (int i = 0; i < player2.size(); i++) {
					cout << "\t(" << alphabet[i] << ") " << player2[i];
				}
				cout << endl << "Player 3";
				for (int i = 0; i < player3.size(); i++) {
					cout << "\t(" << alphabet[i] << ") " << player3[i];
				}
				cout << endl;
			}
			    		
            if (playerChoice == alphabet[player0.size()]) {   // Draw option
                player0.push_back (deck[deck.size()-1]);
                deck.pop_back();
                continue;
            }
            
            for (int i = 0; i < 26; ++i) {
                if (alphabet[i] == playerChoice) {
                    pile1 = player0[i];
                    
                    if (pile1 == "S8" || pile1 == "H8" || pile1 == "C8" || pile1 == "D8") {   // Crazy eights option
                        eight = true;
                    }
                    else {
                        eight = false;
                    }
                    
                    if (eight) {
                        cout << "Which suit you want? (S/H/C/D) ";
						cin >> choiceSuit;
						
						if (choiceSuit == 'S' || choiceSuit == 's') {
							cout << "\tPlayer 0 declared suite S" << endl;
							pile1 = "S*";
							player0.erase (player0.begin() + i);
							turn = 1;
						}
						if (choiceSuit == 'H' || choiceSuit == 'h') {
							cout << "\tPlayer 0 declared suite H" << endl;
							pile1 = "H*";
							player0.erase (player0.begin() + i);
							turn = 1;
						}
						if (choiceSuit == 'C' || choiceSuit == 'c') {
							cout << "\tPlayer 0 declared suite C" << endl;
							pile1 = "C*";
							player0.erase (player0.begin() + i);
							turn = 1;
						}
						if (choiceSuit == 'D' || choiceSuit == 'd') {
							cout << "\tPlayer 0 declared suite D" << endl;
							pile1 = "D*";
							player0.erase (player0.begin() + i);
							turn = 1;
						}
						else {
							cout << "Not a suit." << endl;
							continue;
						}
                    }
					if (pile.at(0) == pile1.at(0)) {   // Testing if the suits match.
						player0.erase (player0.begin() + i);
						turn = 1;
					}
					else if (pile.at(1) == pile1.at(1)) {   // Testing if the ranks match.
						player0.erase (player0.begin() + i);
						turn = 1;
					}
					else {
						cout << "That card cannot place. " << endl << endl;
					}
				}
			}
		}
		
		if (deck.size() == 0 || player0.size() == 25 || player0.size() == 0) {
			turn = 999;
			break;
		}
		
		S = 0; H = 0; C = 0; D = 0;
		
		if (turn == 1) {   // Computer's turn. The code mostly repeat for the other computer players. 
            cout << "Pile has " << pile1 << endl;
            
            while (turn == 1) {
				for (int i = 0; i < player1.size(); ++i) { 
					match = false;
					pile = player1[i];
					
					if (pile == "S8" || pile == "H8" || pile == "C8" || pile == "D8") {
						eight = true;
					}
					else {
						eight = false;
					}
					
					if (pile.at(0) == 'S') {   // This tallies up which suit appears most in computer hand.
						S = S + 1;    
					}
					if (pile.at(0) == 'H') {
						H = H + 1;    
					}
					if (pile.at(0) == 'C') {
						C = C + 1;    
					}
					if (pile.at(0) == 'D') {
						D = D + 1;    
					}
					
					if (pile.at(0) == pile1.at(0) && eight == false) {   // Testing if the suits match.
						cout << "\tPlayer 1 chose " << pile << endl;
						player1.erase (player1.begin() + i);
						match = true;
						turn = 2; 
						break;
					}
					else if (pile.at(1) == pile1.at(1) && eight == false) {   // Testing if the ranks match.
						cout << "\tPlayer 1 chose " << pile << endl;
						player1.erase (player1.begin() + i);
						match = true;
						turn = 2; 
						break;
					}
					else if (eight) {
						num = i;
					}
				}
				if (eight) {   // Testing if there is a crazy eight.
					if (S >= H && S >= C && S >= D) {
						pile = "S*";
						cout << "\tPlayer 1 chose " << player1[num] << endl;
						cout << "\tPlayer 1 declared suite S" << endl;
						player1.erase (player1.begin() + num);
						match = true;
						turn = 2; 
						break;
					}
					else if (H >= S && H >= C && H >= D) {
						cout << "\tPlayer 1 chose " << player1[num] << endl;
						cout << "\tPlayer 1 declared suite H" << endl;
						pile = "H*";
						player1.erase (player1.begin() + num);
						match = true;
						turn = 2; 
						break;
					}
					else if (C >= H && C >= S && C >= D) {
						cout << "\tPlayer 1 chose " << player1[num] << endl;
						cout << "\tPlayer 1 declared suite C" << endl;
						pile = "C*";
						player1.erase (player1.begin() + num);
						match = true;
						turn = 2;
						break;
					}
					else if (D >= H && D >= C && D >= S) {
						cout << "\tPlayer 1 chose " << player1[num] << endl;
						cout << "\tPlayer 1 declared suite D" << endl;
						pile = "D*";
						player1.erase (player1.begin() + num);
						match = true;
						turn = 2; 
						break;
					}
				}
				if (match == false) {   // Draw code.
					cout << "\tPlayer 1 drawing..." << endl;
					player1.push_back (deck[deck.size()-1]);
					deck.pop_back();
				}
				if (deck.size() == 0 || player1.size() == 25 || player1.size() == 0) {
					turn = 999;
					break;
				}
			}
		}
		
		S = 0; H = 0; C = 0; D = 0;
		
		if (turn == 2) {
			cout << "Pile has " << pile << endl;
            
            while (turn == 2) {
				for (int i = 0; i < player2.size(); ++i) { 
					match = false;
					pile1 = player2[i];
					
					if (pile1 == "S8" || pile1 == "H8" || pile1 == "C8" || pile1 == "D8") {
						eight = true;
					}
					else {
						eight = false;
					}
					
					if (pile1.at(0) == 'S') {
						S = S + 1;    
					}
					if (pile1.at(0) == 'H') {
						H = H + 1;    
					}
					if (pile1.at(0) == 'C') {
						C = C + 1;    
					}
					if (pile1.at(0) == 'D') {
						D = D + 1;    
					}
					
					if (pile.at(0) == pile1.at(0) && eight == false) {
						cout << "\tPlayer 2 chose " << pile1 << endl;
						player2.erase (player2.begin() + i);
						match = true;
						turn = 3; 
						break;
					}
					else if (pile.at(1) == pile1.at(1) && eight == false) {
						cout << "\tPlayer 2 chose " << pile1 << endl;
						player2.erase (player2.begin() + i);
						match = true;
						turn = 3; 
						break;
					}
					else if (eight) {
						num = i;
					}
				}
				if (eight) {
					if (S >= H && S >= C && S >= D) {
						pile1 = "S*";
						cout << "\tPlayer 2 chose " << player2[num] << endl;
						cout << "\tPlayer 2 declared suite S" << endl;
						player2.erase (player2.begin() + num);
						match = true;
						turn = 3; 
						break;
					}
					else if (H >= S && H >= C && H >= D) {
						cout << "\tPlayer 2 chose " << player2[num] << endl;
						cout << "\tPlayer 2 declared suite H" << endl;
						pile1 = "H*";
						player2.erase (player2.begin() + num);
						match = true;
						turn = 3; 
						break;
					}
					else if (C >= H && C >= S && C >= D) {
						cout << "\tPlayer 2 chose " << player2[num] << endl;
						cout << "\tPlayer 2 declared suite C" << endl;
						pile1 = "C*";
						player2.erase (player2.begin() + num);
						match = true;
						turn = 3;
						break;
					}
					else if (D >= H && D >= C && D >= S) {
						cout << "\tPlayer 2 chose " << player2[num] << endl;
						cout << "\tPlayer 2 declared suite D" << endl;
						pile1 = "D*";
						player2.erase (player2.begin() + num);
						match = true;
						turn = 3; 
						break;
					}
				}
				if (match == false) {
					cout << "\tPlayer 2 drawing..." << endl;
					player2.push_back (deck[deck.size()-1]);
					deck.pop_back();
				}
				if (deck.size() == 0 || player2.size() == 25 || player2.size() == 0) {
					turn = 999;
					break;
				}
			}
		}
		
		S = 0; H = 0; C = 0; D = 0;
		
		if (turn == 3) {
			cout << "Pile has " << pile1 << endl;
            
            while (turn == 3) {
				for (int i = 0; i < player3.size(); ++i) { 
					match = false;
					pile = player3[i];
					
					if (pile == "S8" || pile == "H8" || pile == "C8" || pile == "D8") {
						eight = true;
					}
					else {
						eight = false;
					}
					
					if (pile.at(0) == 'S') {
						S = S + 1;    
					}
					if (pile.at(0) == 'H') {
						H = H + 1;    
					}
					if (pile.at(0) == 'C') {
						C = C + 1;    
					}
					if (pile.at(0) == 'D') {
						D = D + 1;    
					}
					
					if (pile.at(0) == pile1.at(0) && eight == false) {
						cout << "\tPlayer 3 chose " << pile << endl;
						player3.erase (player3.begin() + i);
						match = true;
						turn = 0; 
						break;
					}
					else if (pile.at(1) == pile1.at(1) && eight == false) {
						cout << "\tPlayer 3 chose " << pile << endl;
						player3.erase (player3.begin() + i);
						match = true;
						turn = 0; 
						break;
					}
					else if (eight) {
						num = i;
					}
				}
				if (eight) {
					if (S >= H && S >= C && S >= D) {
						pile = "S*";
						cout << "\tPlayer 3 chose " << player3[num] << endl;
						cout << "\tPlayer 3 declared suite S" << endl;
						player3.erase (player3.begin() + num);
						match = true;
						turn = 0; 
						break;
					}
					else if (H >= S && H >= C && H >= D) {
						cout << "\tPlayer 3 chose " << player3[num] << endl;
						cout << "\tPlayer 3 declared suite H" << endl;
						pile = "H*";
						player3.erase (player3.begin() + num);
						match = true;
						turn = 0; 
						break;
					}
					else if (C >= H && C >= S && C >= D) {
						cout << "\tPlayer 3 chose " << player3[num] << endl;
						cout << "\tPlayer 3 declared suite C" << endl;
						pile = "C*";
						player3.erase (player3.begin() + num);
						match = true;
						turn = 0;
						break;
					}
					else if (D >= H && D >= C && D >= S) {
						cout << "\tPlayer 3 chose " << player3[num] << endl;
						cout << "\tPlayer 3 declared suite D" << endl;
						pile = "D*";
						player3.erase (player3.begin() + num);
						match = true;
						turn = 0; 
						break;
					}
				}
				if (match == false) {
					cout << "\tPlayer 3 drawing..." << endl;
					player3.push_back (deck[deck.size()-1]);
					deck.pop_back();
				}
				if (deck.size() == 0 || player3.size() == 25 || player3.size() == 0) {
					turn = 999;
					break;
				}
			}
		}
	}
	
	cout << endl;
	
	if (player0.size() < player1.size() && player0.size() < player2.size() && player0.size() < player3.size()) {   // Decide who wins.
		cout << "You won!" << endl << endl;
	}
	else if (player1.size() < player0.size() && player1.size() < player2.size() && player1.size() < player3.size()) {
		cout << "Player 1 won!" << endl << endl;
	}
	else if (player2.size() < player1.size() && player2.size() < player0.size() && player2.size() < player3.size()) {
		cout << "Player 2 won!" << endl << endl;
	}
	else if (player3.size() < player1.size() && player3.size() < player2.size() && player3.size() < player0.size()) {
		cout << "Player 3 won!" << endl << endl;
	}
	else {
		cout << "Match ended in a draw." << endl << endl;
	}
	
	cout << "[ Final card distributions ]" << endl;   // Final score display.
	
	cout << "Player 0";
	for (int i = 0; i < player0.size(); i++) {
		cout << "\t(" << alphabet[i] << ") " << player0[i];
	}
	cout << endl << "Player 1";
	for (int i = 0; i < player1.size(); i++) {
		cout << "\t(" << alphabet[i] << ") " << player1[i];
	}
	cout << endl << "Player 2";
	for (int i = 0; i < player2.size(); i++) {
		cout << "\t(" << alphabet[i] << ") " << player2[i];
	}
	cout << endl << "Player 3";
	for (int i = 0; i < player3.size(); i++) {
		cout << "\t(" << alphabet[i] << ") " << player3[i];
	}
	cout << endl;
	
    return 0;
}
