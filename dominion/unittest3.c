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

	char* errorMessage = "supplyCount returns an incorrect count for cards";
	myassert((supplyCount(mine, &g) == 10), errorMessage);

	g.supplyCount[mine] -= 1;
	myassert((supplyCount(mine, &g) == 9), errorMessage);


  checkasserts();
}
