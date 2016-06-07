CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)


dominion.o: dominion.h dominion.c rngs.o 
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -rf *.o playdom.exe playdom testdominion test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestadventurer player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM

unittests: dominion.o unittest1.c unittest2.c unittest3.c unittest4.c
	gcc -o unittest1 unittest1.c -g dominion.o   rngs.o $(CFLAGS)
	gcc -o unittest2 unittest2.c -g dominion.o   rngs.o $(CFLAGS)
	gcc -o unittest3 unittest3.c -g dominion.o   rngs.o $(CFLAGS)
	gcc -o unittest4 unittest4.c -g dominion.o   rngs.o $(CFLAGS)

cardtests: dominion.o cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	gcc -o cardtest1 cardtest1.c -g dominion.o   rngs.o $(CFLAGS)
	gcc -o cardtest2 cardtest2.c -g dominion.o   rngs.o $(CFLAGS)
	gcc -o cardtest3 cardtest3.c -g dominion.o   rngs.o $(CFLAGS)
	gcc -o cardtest4 cardtest4.c -g dominion.o   rngs.o $(CFLAGS)

randomtestcards: dominion.o randomtestcard1.c randomtestcard2.c randomtestadventurer.c
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o   rngs.o $(CFLAGS)
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o   rngs.o $(CFLAGS)
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o   rngs.o $(CFLAGS)

myTest:
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest1.c rngs.c   -o unittest1 -lm -g
	./unittest1 1 > unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest2.c rngs.c   -o unittest2 -lm -g
	./unittest2 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest3.c rngs.c   -o unittest3 -lm -g
	./unittest3 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest4.c rngs.c   -o unittest4 -lm -g
	./unittest4 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest1.c rngs.c   -o cardtest1 -lm -g
	./cardtest1 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest2.c rngs.c   -o cardtest2 -lm -g
	./cardtest2 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest3.c rngs.c   -o cardtest3 -lm -g
	./cardtest3 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest4.c rngs.c   -o cardtest4 -lm -g
	./cardtest4 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

myTestRandom:
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard1.c rngs.c   -o randomtestcard1 -lm -g
	./randomtestcard1 42 > randomtestcard1.out
	gcov -f   >> randomtestcard1.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard2.c rngs.c   -o randomtestcard2 -lm -g
	./randomtestcard2 42 > randomtestcard2.out
	gcov -f   >> randomtestcard2.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestadventurer.c rngs.c   -o randomtestadventurer -lm -g
	./randomtestadventurer 42 > randomtestadventurer.out
	gcov -f   >> randomtestadventurer.out

myTestRandom1:
	rm -f  .gcov cardEffects.gcda cardEffects.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard1.c rngs.c   -o randomtestcard1 -lm -g
	./randomtestcard1 42 > randomtestcard1.out
	gcov -f   >> randomtestcard1.out

myTestRandom2:
	rm -f  .gcov cardEffects.gcda cardEffects.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard2.c rngs.c   -o randomtestcard2 -lm -g
	./randomtestcard2 42 > randomtestcard2.out
	gcov -f   >> randomtestcard2.out

myTestRandomAdv:
	rm -f  .gcov cardEffects.gcda cardEffects.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestadventurer.c rngs.c   -o randomtestadventurer -lm -g
	./randomtestadventurer 42 > randomtestadventurer.out
	gcov -f   >> randomtestadventurer.out

testdominion: dominion.o interface.o testdominion.c
	gcc -o testdominion testdominion.c -g dominion.o   rngs.o interface.o $(CFLAGS)
