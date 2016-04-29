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

  char* errorMessage = "unable to play village";
  char* errorMessage2 = "village should cause the player to draw a card";
  char* errorMessage3 = "village should cause the player to have 2 actions";

  g.hand[0][0] = village;
  int initCount = g.deckCount[0];
  myassert((playCard(0, -1, -1, -1, &g) > -1), errorMessage);
  myassert((g.numActions == 2), errorMessage3);
  myassert((g.deckCount[0] == initCount -1), errorMessage2);

  checkasserts();
}
