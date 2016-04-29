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
//num hand cards test
int main() {
	struct gameState g;

	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
		   outpost,baron,tribute};

	int r = initializeGame(2, k, 5, &g);
	int i = numHandCards(&g);
	myassert(i == 5, "hand has proper amount");
	g.handCount[0] += 1;
	i = numHandCards(&g);
	myassert(i == 6, "No new cards");

	checkasserts();
}
