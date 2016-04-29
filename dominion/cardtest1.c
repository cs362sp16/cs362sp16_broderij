#include "dominion.h"

int failed = 0;

int myassert(int b,char* msg) {
  if (b == 0) {
    printf("FAILED ASSERTION: %s\n",msg);
    failed = 1;
  }
}

void checkasserts() {
  if (!failed) {
    printf ("TEST SUCCESSFULLY COMPLETED.\n");
  }
}

int main() {
  struct gameState g;

  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};

  int r = initializeGame(2, k, 5, &g);

  char* errorMessage = "unable to play council room";
    char* errorMessage2 = "council room should cause the player to draw 4 cards";
    char* errorMessage3 = "council room should cause the player to have 2 buys";
    char* errorMessage4 = "council room should increase opponents hand size by 1";


    int initCount = g.deckCount[0];
    int enemyCount = g.deckCount[1];
    g.hand[0][0] = council_room;
    myassert((playCard(0, -1, -1, -1, &g) > -1), errorMessage);
    myassert((g.numBuys == 2), errorMessage3);
    myassert((g.deckCount[0] == initCount -4), errorMessage2);
    myassert((g.deckCount[1] == enemyCount - 1), errorMessage4);
  checkasserts();
}
