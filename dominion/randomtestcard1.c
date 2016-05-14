#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#define MAX_TESTS 1300

/*
Updater's note. I'm pretty much just axing everything. This code is so bad. Mine may not be better.
*/

void myAssert(int result, char* failMessage){
  (result > 0) ? : (printf("%s\n", failMessage), exit(0));
}

int main(int argc, char* argv[]) {
	srand(time(NULL)); //seed the random number generator
	int maxRunTimes = MAX_TESTS;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, steward};

	int i, j, n, players, player, handCount, deckCount, seed, address, choice1, choice2, choice3, result;

	struct gameState* testState;
	struct gameState* backupState;

	int runCount = 0;
	printf("Running Random Card Test for Steward\n");
	for(runCount = 0; runCount < maxRunTimes; runCount++){
		printf("Iteration number: %d\n", runCount);
		if (!(testState = malloc(sizeof(struct gameState)))){
			fprintf(stderr, "Failed to malloc.\n");
			exit(1);
		}
		if (!(backupState = malloc(sizeof(struct gameState)))){
			fprintf(stderr, "Failed to malloc.\n");
			exit(1);
		}
		players = rand() % MAX_PLAYERS;
		seed = rand() % 999;
		if(initializeGame(players, k, seed, testState) != -1){
			player = whoseTurn(testState);


			testState->deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
			testState->discardCount[player] = rand() % MAX_DECK;
			testState->handCount[player] = rand() % MAX_HAND;

			testState->hand[0][0] = steward; //force the first card to be a steward
			testState->coins = rand() % 10;

			printf("hand count start: %d\n", testState->handCount[player]);
			printf("deck count start: %d\n", testState->deckCount[player]);
			printf("coin count start: %d\n", testState->coins);

			if(!(memcpy(backupState, testState, sizeof(struct gameState)))){
				printf("memcpy error\n");
				exit(1);
			}
			choice1 = rand() % 3; //0, 1 or 2. If 0 the else statement will be triggered.
			choice2 = (testState->handCount[player] - 1);
			choice3 = choice2 - 1;
			result = playCard(0, choice1, choice2, choice3, testState);
			printf("Choice: %d\n", choice1);
			printf("hand count end: %d\n", testState->handCount[player]);
			printf("deck count end: %d\n", testState->deckCount[player]);
			printf("coin count end: %d\n", testState->coins);
			printf("backup hand count: %d\n", backupState->handCount[player]);
			printf("backup deck count end: %d\n", backupState->deckCount[player]);
			printf("backup coin count: %d\n", backupState->coins);

			//oracle section
			//does each choice generate the correct game state?
			//hand count should go up by 1 if the player draws 2 cards
			//hand count should go down by 3 if the player trashes 2 cards
			//coins should go up by 2 if the player chooses to gain coins

			if(choice1 == 0){
				if(testState->handCount[player] < 0){
					myAssert(-1, "ERROR: Player should not be able to trash more cards than they have.\n");
				}
				else{
					myAssert((testState->handCount[player] == backupState->handCount[player] - 3), "ERROR: Player should have 3 fewer cards in hand.\n");
				}
			}
			if(choice1 == 1){
				myAssert((testState->handCount[player] == (backupState->handCount[player] + 1)), "ERROR: Player should have drawn two cards."); //+2 for draw -1 for play
			}
			if(choice1 == 2){
				myAssert(((backupState->coins + 2) == testState->coins), "ERROR: Player should have +2 coins.\n");
			}
		}
		free(testState);
		free(backupState);
	}

	return 0;
}
