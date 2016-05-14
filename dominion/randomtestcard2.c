#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TESTS 130000

int my_assert(int test, char* msg)
{
	if (!test) {
		printf ("ASSERT HAS FAILED: %s\n", msg);
		exit(-1);
	}
	return 0;
}
//This randomly tests great hall

int main() {

	  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};

	  int i, players, player, numActions, handCount, deckCount, seed, return_val, address;
	  //struct gameState state;
	  struct gameState state;


	  printf("Running Random Card Test for Great Hall\n");

	

	  for (i = 0; i < MAX_TESTS; i++) {


		 players = rand() % 4;
		 seed = rand();		//pick random seed

		 initializeGame(players, k, seed, &state);	//initialize Gamestate

		 //Set the initial state values
		 player = state.whoseTurn;
		state.deckCount[player] = (rand() % (MAX_DECK - 1) ) + 1;
		state.discardCount[player] = rand() % MAX_DECK;
		state.handCount[player] = (rand() % (MAX_HAND - 1) ) + 1;

		//Save the state of the game variables that should be checked
		numActions = state.numActions; //this should increase by 1
		deckCount = state.deckCount[player]; //this should decrease by 1
		handCount = state.handCount [player]; //this should not change


		//play the great hall card
		return_val = cardEffect(great_hall, 1, 1, 1, &state, handCount-1, &address);

		my_assert( return_val == 0, "Return value was non-zero");
		my_assert( state.numActions == numActions + 1, "numActions was not incremented");
		my_assert( state.deckCount[player] == deckCount - 1, "deckCount was not decremented" );
		my_assert( state.handCount[player] == handCount, "handCount value should not have been changed");

	  }

	  printf("Tests Complete\n");

	  return 0;
}
