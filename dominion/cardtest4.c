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

  char* errorMessage = "unable to play embargo";
  char* errorMessage2 = "embargo should add an embargo token to a supply pile";
  char* errorMessage3 = "embargo should cause the player to have 2 coins";



  g.hand[0][0] = embargo;
  int coins = g.coins + 2;
  myassert((playCard(0, 1, -1, -1, &g) > -1), errorMessage);
  myassert((g.coins == coins), errorMessage3);
  myassert((g.embargoTokens[1] == 1), errorMessage2);

  checkasserts();
}
