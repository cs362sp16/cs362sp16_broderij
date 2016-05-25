#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(){
  printf("Initializing game\n");
  srand(time(NULL));
  struct gameState G;
  struct gameState *gamePointer = &G;
  int choice1 = -1;
  int choice2 = -1;
  int choice3 = -1;
  int i = 0;
  int j = 0;
  int temp;
  //all of the possible cards in the deck
  char* cards[27] = {"curse",
   "estate",
   "duchy",
   "province",

   "copper",
   "silver",
   "gold",

   "adventurer",
   /* If no/only 1 treasure found, stop when full deck seen */
   "council_room",
   "feast", /* choice1 is supply # of card gained) */
   "gardens",
   "mine", /* choice1 is hand# of money to trash, choice2 is supply# of
	    money to put in hand */
   "remodel", /* choice1 is hand# of card to remodel, choice2 is supply# */
   "smithy",
   "village",

   "baron", /* choice1: boolean for discard of estate */
   /* Discard is always of first (lowest index) estate */
   "great_hall",
   "minion", /* choice1:  1 = +2 coin, 2 = redraw */
   "steward", /* choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3) */
   "tribute",

   //"ambassador", /* choice1 = hand#, choice2 = number to return to supply */
   "cutpurse",
   "embargo", /* choice1 = supply# */
   "outpost",
   "salvager", /* choice1 = hand# to trash */
   "sea_hag",
   "treasure_map"
  };



  int shuffledCards[20] = {
  adventurer,
  /* If no/only 1 treasure found, stop when full deck seen */
  council_room,
  feast, /* choice1 is supply # of card gained) */
  gardens,
  mine, /* choice1 is hand# of money to trash, choice2 is supply# of
     money to put in hand */
  remodel, /* choice1 is hand# of card to remodel, choice2 is supply# */
  smithy,
  village,

  baron, /* choice1: boolean for discard of estate */
  /* Discard is always of first (lowest index) estate */
  great_hall,
  minion, /* choice1:  1 = +2 coin, 2 = redraw */
  steward, /* choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3) */
  tribute,

  ambassador, /* choice1 = hand#, choice2 = number to return to supply */
  cutpurse,
  embargo, /* choice1 = supply# */
  outpost,
  salvager, /* choice1 = hand# to trash */
  sea_hag,
  treasure_map};

  //shuffle them
  for(i = 0; i < 20; i++){
    j = i + rand() / (RAND_MAX / (20 - i) + 1);
    if (i != j) {
            temp = shuffledCards[i];
            shuffledCards[i] = shuffledCards[j];
            shuffledCards[j] = temp;
        }
  }
  //20 possible cards, grab the first 10 out of the suffled array of all cards
  int k[10];
  for(i = 0; i<10;i++){
    k[i] = shuffledCards[i];
  }
  int numPlayers = rand()%3 + 2; //random number of players between 1 and 4.
  int seed = rand()%10000;

  printf("Starting game.\n");
  printf("Number of players: %d\n", numPlayers);
  printf("Seed is: %d\n", seed);
  printf("Cards are: \n");
  for(i = 0; i < 10; i++){
    printf("%s\n", cards[i]);
  }

  if(initializeGame(numPlayers, k, seed, gamePointer) == -1){
    printf("Failed to initialize game. Exiting.\n");
    exit(1);
  }

  int retValue = 0;
  //6 cost
  int advInDeck = 0;
  //5 cost
  int council_roomInDeck = 0;
  int tributeInDeck = 0;
  int minionInDeck = 0;
  int mineInDeck = 0;
  int outpostInDeck = 0;
  //4 cost
  int feastInDeck = 0;
  int gardensInDeck = 0;
  int remodelInDeck = 0;
  int smithyInDeck = 0;
  int baronInDeck = 0;
  int cutpurseInDeck = 0;
  int treasure_mapInDeck = 0;
  //3 cost
  int villageInDeck = 0;
  int great_hallInDeck = 0;
  int stewardInDeck = 0;
  int ambassadorInDeck = 0;
  //2 cost
  int embargoInDeck = 0;
  for(i = 0; i < 10; i++){
    //6 cost
    if(k[i] == adventurer){
      advInDeck = 1;
    }
  //5 cost
    if(k[i] == council_room){
      council_roomInDeck = 1;
    }
    else if(k[i] == tribute){
      tributeInDeck = 1;
    }
    else if(k[i] == minion){
      minionInDeck = 1;
    }
    else if(k[i] == mine){
      mineInDeck = 1;
    }
    else if(k[i] == outpost){
      outpostInDeck = 1;
    }
    //4 cost
    else if(k[i] == feast){
      feastInDeck = 1;
    }
    else if(k[i] == gardens){
      gardensInDeck = 1;
    }
    else if(k[i] == remodel){
      remodelInDeck = 1;
    }
    else if(k[i] == smithy){
      smithyInDeck = 1;
    }
    else if(k[i] == baron){
      baronInDeck = 1;
    }
    else if(k[i] == cutpurse){
      cutpurseInDeck = 1;
    }
    else if(k[i] == treasure_map){
      treasure_mapInDeck = 1;
    }
    //3 cost
    else if(k[i] == village){
      villageInDeck = 1;
    }
    else if(k[i] == great_hall){
      great_hallInDeck = 1;
    }
    else if(k[i] == steward){
      stewardInDeck = 1;
    }
    else if(k[i] == ambassador){
      ambassadorInDeck = 1;
    }
    //2 cost
    else if(k[i] == embargo){
      embargoInDeck = 1;
    }
  }
  printf("Playing game\n");
  while (!isGameOver(gamePointer)) {
    //play some cards
    int unableToAct = 0;
    while(gamePointer->numActions > 0){
      printf("player %d is taking an action. They have %d actions.\n", whoseTurn(gamePointer), gamePointer->numActions);
      for (i = 0; i < numHandCards(gamePointer); i++) {
        //6 cost
        if(gamePointer->hand[whoseTurn(gamePointer)][i] == adventurer){
          retValue = playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play adventurer\n", whoseTurn(gamePointer));
            break;
          }
          else{
            printf("player %d played adventurer\n", whoseTurn(gamePointer));
          }
        }
      //5 cost
        if(gamePointer->hand[whoseTurn(gamePointer)][i] == council_room){
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play council_room\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played council_room\n", whoseTurn(gamePointer));
            break;
          }
        }
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == minion){
          choice1 = 1;
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play minion\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played minion\n", whoseTurn(gamePointer));
            break;
          }
        }
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == outpost){
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play outpost\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played outpost\n", whoseTurn(gamePointer));
            break;
          }
        }
        //4 cost
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == feast){
          choice1 = silver;
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play feast\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played feast\n", whoseTurn(gamePointer));
            break;
          }
        }
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == remodel){
          choice1 = 0;
          choice2 = duchy;
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play remodel\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played remodel\n", whoseTurn(gamePointer));
            break;
          }
        }
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == smithy){
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play smithy\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played smithy\n", whoseTurn(gamePointer));
            break;
          }
        }
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == baron){
          choice1 = 0;
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play baron\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played baron\n", whoseTurn(gamePointer));
            break;
          }
        }
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == cutpurse){
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play cutpurse\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played cutpurse\n", whoseTurn(gamePointer));
            break;
          }
        }
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == treasure_map){
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play treasure_map\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played treasure_map\n", whoseTurn(gamePointer));
            break;
          }
        }
        //3 cost
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == village){
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play village\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played village\n", whoseTurn(gamePointer));
            break;
          }
        }
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == great_hall){
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play great_hall\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played great_hall\n", whoseTurn(gamePointer));
            break;
          }
        }
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == steward){
          choice1 = 2;
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play steward\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played steward\n", whoseTurn(gamePointer));
            break;
          }
        }
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == ambassador){
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play ambassador\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played ambassador\n", whoseTurn(gamePointer));
            break;
          }
        }
        //2 cost
        else if(gamePointer->hand[whoseTurn(gamePointer)][i] == embargo){
          choice1 = copper;
          playCard(i, choice1, choice2, choice3, gamePointer);
          if (retValue == -1) {
            printf("player %d failed to play embargo\n", whoseTurn(gamePointer));
          }
          else{
            printf("player %d played embargo\n", whoseTurn(gamePointer));
            break;
          }
        }
        else if(numHandCards(gamePointer) == (i+1)){
          unableToAct = 1;
        }
      }
      if(unableToAct == 1){
        break; //unable to take any actions
      }
    }

    //figure out how much money we have
    gamePointer->coins = 0;
    for (i = 0; i < numHandCards(gamePointer); i++) {
      if (handCard(i, gamePointer) == copper)
        gamePointer->coins++;
      else if (handCard(i, gamePointer) == silver)
        gamePointer->coins += 2;
      else if (handCard(i, gamePointer) == gold)
        gamePointer->coins += 3;
    }
    //buy stuff!
    while(gamePointer->numBuys > 0){
      if(gamePointer->coins >= 8){
        retValue = buyCard(province, gamePointer);
        if(retValue > -1){
          printf("Player %d bought Province.\n", whoseTurn(gamePointer));
        }
        else{
          printf("Player %d failed to buy Province.\n", whoseTurn(gamePointer));
          break;
        }
      }
      else if(gamePointer->coins >= 6){
        if(advInDeck){
          retValue = buyCard(adventurer, gamePointer);
          if(retValue > -1){
            printf("Player %d bought Adventurer.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy Adventurer.\n", whoseTurn(gamePointer));
            break;
          }
        }
        else{
          retValue = buyCard(gold, gamePointer);
          if(retValue > -1){
            printf("Player %d bought Gold.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy Gold.\n", whoseTurn(gamePointer));
            break;
          }
        }
      }
      else if(gamePointer->coins == 5){
        if(council_roomInDeck){
          retValue = buyCard(duchy, gamePointer);
          if(retValue > -1){
            printf("Player %d bought council room.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy council room.\n", whoseTurn(gamePointer));
            //try to buy a duchy
            retValue = buyCard(duchy, gamePointer);
            if(retValue > -1){
              printf("Player %d bought Duchy.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy Duchy.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else if(tributeInDeck){
          retValue = buyCard(tribute, gamePointer);
          if(retValue > -1){
            printf("Player %d bought tribute.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy tribute.\n", whoseTurn(gamePointer));
            //try to buy a duchy
            retValue = buyCard(duchy, gamePointer);
            if(retValue > -1){
              printf("Player %d bought Duchy.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy Duchy.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else if(minionInDeck){
          retValue = buyCard(minion, gamePointer);
          if(retValue > -1){
            printf("Player %d bought minion.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy minion.\n", whoseTurn(gamePointer));
            //try to buy a duchy
            retValue = buyCard(duchy, gamePointer);
            if(retValue > -1){
              printf("Player %d bought Duchy.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy Duchy.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else if(mineInDeck){
          retValue = buyCard(mine, gamePointer);
          if(retValue > -1){
            printf("Player %d bought mine.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy mine.\n", whoseTurn(gamePointer));
            //try to buy a duchy
            retValue = buyCard(duchy, gamePointer);
            if(retValue > -1){
              printf("Player %d bought Duchy.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy Duchy.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else if(outpostInDeck){
          retValue = buyCard(outpost, gamePointer);
          if(retValue > -1){
            printf("Player %d bought outpost.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy outpost.\n", whoseTurn(gamePointer));
            //try to buy a duchy
            retValue = buyCard(duchy, gamePointer);
            if(retValue > -1){
              printf("Player %d bought Duchy.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy Duchy.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else{
          retValue = buyCard(duchy, gamePointer);
          if(retValue > -1){
            printf("Player %d bought Duchy.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy Duchy.\n", whoseTurn(gamePointer));
            break;
          }
        }
      }
      //4 coins
      else if(gamePointer->coins == 4){
        if(feastInDeck){
          retValue = buyCard(feast, gamePointer);
          if(retValue > -1){
            printf("Player %d bought feast.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy feast.\n", whoseTurn(gamePointer));
            //try to buy a copper
            retValue = buyCard(silver, gamePointer);
            if(retValue > -1){
              printf("Player %d bought silver.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy silver.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else if(gardensInDeck){
          retValue = buyCard(gardens, gamePointer);
          if(retValue > -1){
            printf("Player %d bought gardens.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy gardens.\n", whoseTurn(gamePointer));
            //try to buy a copper
            retValue = buyCard(silver, gamePointer);
            if(retValue > -1){
              printf("Player %d bought silver.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy silver.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else if(smithyInDeck){
          retValue = buyCard(smithy, gamePointer);
          if(retValue > -1){
            printf("Player %d bought smithy.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy smithy.\n", whoseTurn(gamePointer));
            //try to buy a copper
            retValue = buyCard(silver, gamePointer);
            if(retValue > -1){
              printf("Player %d bought silver.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy silver.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else if(baronInDeck){
          retValue = buyCard(baron, gamePointer);
          if(retValue > -1){
            printf("Player %d bought baron.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy baron.\n", whoseTurn(gamePointer));
            //try to buy a copper
            retValue = buyCard(silver, gamePointer);
            if(retValue > -1){
              printf("Player %d bought silver.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy silver.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else if(treasure_mapInDeck){
          retValue = buyCard(treasure_map, gamePointer);
          if(retValue > -1){
            printf("Player %d bought treasure_map.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy treasure_map.\n", whoseTurn(gamePointer));
            //try to buy a copper
            retValue = buyCard(silver, gamePointer);
            if(retValue > -1){
              printf("Player %d bought silver.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy silver.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }

        else{
          retValue = buyCard(silver, gamePointer);
          if(retValue > -1){
            printf("Player %d bought silver.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy silver.\n", whoseTurn(gamePointer));
            break;
          }
        }

      }
      else if(gamePointer->coins == 3){
        if(villageInDeck){
          retValue = buyCard(village, gamePointer);
          if(retValue > -1){
            printf("Player %d bought village.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy village.\n", whoseTurn(gamePointer));
            //try to buy a copper
            retValue = buyCard(silver, gamePointer);
            if(retValue > -1){
              printf("Player %d bought silver.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy silver.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else if(great_hallInDeck){
          retValue = buyCard(great_hall, gamePointer);
          if(retValue > -1){
            printf("Player %d bought great_hall.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy great_hall.\n", whoseTurn(gamePointer));
            //try to buy a copper
            retValue = buyCard(silver, gamePointer);
            if(retValue > -1){
              printf("Player %d bought silver.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy silver.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else if(stewardInDeck){
          retValue = buyCard(steward, gamePointer);
          if(retValue > -1){
            printf("Player %d bought steward.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy steward.\n", whoseTurn(gamePointer));
            //try to buy a copper
            retValue = buyCard(silver, gamePointer);
            if(retValue > -1){
              printf("Player %d bought silver.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy silver.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else if(ambassadorInDeck){
          retValue = buyCard(ambassador, gamePointer);
          if(retValue > -1){
            printf("Player %d bought ambassador.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy ambassador.\n", whoseTurn(gamePointer));
            //try to buy a copper
            retValue = buyCard(silver, gamePointer);
            if(retValue > -1){
              printf("Player %d bought silver.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy silver.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else{
          retValue = buyCard(silver, gamePointer);
          if(retValue > -1){
            printf("Player %d bought silver.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy silver.\n", whoseTurn(gamePointer));
            break;
          }
        }
      }
      else if(gamePointer->coins == 2){
        if(embargoInDeck){
          retValue = buyCard(embargo, gamePointer);
          if(retValue > -1){
            printf("Player %d bought embargo.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy embargo.\n", whoseTurn(gamePointer));
            //try to buy a duchy
            retValue = buyCard(copper, gamePointer);
            if(retValue > -1){
              printf("Player %d bought copper.\n", whoseTurn(gamePointer));
            }
            else{
              printf("Player %d failed to buy copper.\n", whoseTurn(gamePointer));
              break;
            }
          }
        }
        else{
          retValue = buyCard(copper, gamePointer);
          if(retValue > -1){
            printf("Player %d bought copper.\n", whoseTurn(gamePointer));
          }
          else{
            printf("Player %d failed to buy copper.\n", whoseTurn(gamePointer));
            break;
          }
        }
      }
      //1 or 0 coins
      else{
        retValue = buyCard(copper, gamePointer);
        if(retValue > -1){
          printf("Player %d bought copper.\n", whoseTurn(gamePointer));
        }
        else{
          printf("Player %d failed to buy copper.\n", whoseTurn(gamePointer));
          break;
        }
      }
    }
    printf("Ending turn for player %d\n", whoseTurn(gamePointer));
    endTurn(gamePointer);
  }

  printf("Finished playing Dominion.\n Scores are: \n");
  for(i = 0; i< numPlayers; i++){
    printf("Player %d: %d\n", i, scoreFor(i, gamePointer));
  }
  return 0;
}
