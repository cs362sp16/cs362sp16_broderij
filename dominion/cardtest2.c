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


  g.hand[0][0] = outpost;
    char* errorMessage = "unable to play the outpost card from hand.";
    char* errorMessage2 = "outpost should not be playeable 2 turns in a row";
    char* errorMessage3 = "player should stay the same after outpost is played";

    int player = g.whoseTurn;

    myassert((playCard(0, -1, -1, -1, &g) > -1), errorMessage); //can we play the card
    myassert(endTurn(&g) > -1, "unable to end turn");
    myassert(g.whoseTurn == player, errorMessage3); //player should be the same after outpost and end turn
    g.hand[0][0] = outpost; //load another outpost into our hand
    myassert((playCard(0, -1, -1, -1, &g) < 0), errorMessage2); //should error out on 2 outposts in a row
  checkasserts();
}
