#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#define MAX_TESTS 1000000

void myAssert(int result, char* failMessage){
  (result > 0) ? : (printf("%s\n", failMessage), exit(0));
}

//This randomly tests Adventurer

int main() {
	srand(time(NULL));
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};
		int cashMoney[3] = {copper, silver, gold};

		int i, j, n, players, player, handCount, deckCount, seed, address, treasureCount, counter, deckCoins, discardCoins, result, handTreasureCount, discardCount;
		//struct gameState state;
		struct gameState* testState;
		struct gameState* backupState;

		printf("Running Random Adventurer Test\n");

		for (i = 0; i < MAX_TESTS; i++) {
			if (!(testState = malloc(sizeof(struct gameState)))){
				fprintf(stderr, "Failed to malloc.\n");
				exit(1);
			}
			if (!(backupState = malloc(sizeof(struct gameState)))){
				fprintf(stderr, "Failed to malloc.\n");
				exit(1);
			}
			players = rand() % 4;

			seed = rand() % 999;		//pick random seed

			if(initializeGame(players, k, seed, testState) != -1){	//initialize Gamestate
				//Initiate valid state variables
				treasureCount = 0;
				deckCoins = 0;
				discardCoins = 0;
				deckCount = rand() % MAX_DECK;
				discardCount = rand() % (MAX_DECK - deckCount);
				testState->deckCount[player] = deckCount; //Pick random deck size out of MAX DECK size
				testState->discardCount[player] = discardCount;
				player = whoseTurn(testState);

				//put the adventurere card in our hand
				testState->hand[player][0] = adventurer;
				//build the deck seeding it with some number of cards and coins
				//1 in 5 chance that we will seed a coin
				for(counter = 0; counter < deckCount; counter++){
					testState->deck[player][counter] = (rand() % 5 == 0) ? deckCoins++, cashMoney[rand() % 3] : k[rand() % 10];
				}
				//build the discards seeding it with some number of cards and coins
				for(counter = 0; counter < discardCount; counter++){
					testState->discard[player][counter] = (rand() % 5 == 0) ? discardCoins++, cashMoney[rand() % 3] : k[rand() % 10];
				}
				treasureCount = deckCoins + discardCoins;
				//calculate coins in hand
				handTreasureCount = 0;
				for(counter = 0; counter < testState->handCount[player]; counter++){
					if((testState->hand[player][counter] == copper) || (testState->hand[player][counter] == silver) || (testState->hand[player][counter] == gold)){
						handTreasureCount += 1;
					}
				}

				result = playCard(0, 1, 1, 1, testState);		//Run adventurer card
				if(result == -1){
					printf("Adventurer returned an error. No point in checking state. Try again.\n");
				}
				else{
					//oracle time!
					//Adventurer should traw 2 treasure starting with the deck, then shuffling in the discards if needed.
					//If there are not 2 treasure to draw then as many as possible are drawn.
					printf("Validating state.\n");
					printf("Starting treasure in deck: %d\n", deckCoins);
					printf("Starting treasure in discards: %d\n", discardCoins);
					printf("Starting treasure in deck + discards: %d\n", treasureCount);
					printf("Starting treasure in hand: %d\n", handTreasureCount);
					int finalTreasureCount = 0;
					for(counter = 0; counter < testState->handCount[player]; counter++){
						if((testState->hand[player][counter] == copper) || (testState->hand[player][counter] == silver) || (testState->hand[player][counter] == gold)){
							finalTreasureCount += 1;
						}
					}
					printf("Final treasure in hand: %d\n", finalTreasureCount);
					//validate that we drew the correct number of treasure
					if(treasureCount == 0){
						myAssert(finalTreasureCount == (handTreasureCount + treasureCount), "ERROR: The player should have no more treasure than they started with in their hand.\n");
					}
					if(treasureCount == 1){
						myAssert(finalTreasureCount == (handTreasureCount + treasureCount), "ERROR: The player should have 1 more treasure than they started with in their hand.\n");
					}
					if(treasureCount >= 2){
						myAssert(finalTreasureCount == (handTreasureCount + 2), "ERROR: The player should end up with 2 more treasure in their hand than they started with assuming there is that much treasure to find.\n");
					}
					printf("State is valid.\n");
				}
			}
			free(testState);
			free(backupState);
		}

		return 0;
	}
