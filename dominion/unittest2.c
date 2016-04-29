#include "dominion.h"
#include "stdio.h"

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
	int startingPlayer = g.whoseTurn;

	char* failMessage1 = "endTurn failed to end the turn for the current player";
	char* failMessage2 = "endTurn set the next player's turn incorrectly";

	myassert((endTurn(&g) > -1), failMessage1);
	myassert(whoseTurn(&g) == (startingPlayer + 1), failMessage2);


  checkasserts();
}
