#include "dominion.h"
#include "dominion_helpers.h"

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

         char* errorMessage1 = "buy didn't reduce card supply count";
          char* errorMessage2 = "buy didn't reduce buy count";
          char* errorMessage3 = "bought a card when player had no buys";
          char* errorMessage4 = "bought a card when player had insufficent coins";
          char* errorMessage5 = "reduced card supply when player failed to buy card";

          initializeGame(2, k, 4, &g);
          int startCount = supplyCount(mine, &g);
          g.coins = 50;
          //test a valid buy
          buyCard(mine, &g);
          myassert((supplyCount(mine, &g) == startCount - 1), errorMessage1); //reduced supply count
          myassert((g.numBuys == 0), errorMessage2); //reduced buy count
          g.numBuys = 0;
          myassert((buyCard(mine, &g) == -1), errorMessage3); //test buying with no buys
          myassert((supplyCount(mine, &g) == startCount - 1), errorMessage5); //test if card supply is reduced when player fails to buy a card with no buys
          g.coins = 0;
          myassert((buyCard(mine, &g) == -1), errorMessage4); //test if player is able to buy a card with no coins
          myassert((supplyCount(mine, &g) == startCount - 1), errorMessage5); //test if card supply is reduced when player fails to buy a card with no money

          return 0;

  checkasserts();
}
