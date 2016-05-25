import subprocess
import os
import sys

nullf = open(os.devnull,'w')

dominion1dir = sys.argv[1]
dominion2dir = sys.argv[2]

dominions = [(dominion1dir, "one"), (dominion2dir, "two")]

subprocess.call(["make clean; make all"], shell=True)

testexes = []

for (d, n) in dominions:
    c1 = "cd " + d + "; make clean; make all"
    subprocess.call ([c1], shell=True, stderr = nullf, stdout = nullf)
    c2 = "gcc -o " + n + "test fulldomtest.c " + d + "/dominion.o rngs.o interface.o --coverage"
    subprocess.call ([c2], shell=True, stderr = nullf, stdout = nullf)
    testexes.append (n + "test")

numTests = 100


for t in xrange(1,numTests+1):
    print "TEST/SEED #", t
    outfiles = []
    for e in testexes:
        eout = open(e+".out",'w')
        subprocess.call(["./" + e + ".exe", str(t)], stdout=eout, stderr = nullf)
        eout.close()
        outfiles.append(e+".out")

    r = subprocess.call(["diff " + outfiles[0] + " " + outfiles[1]], shell=True, stderr = nullf, stdout = nullf)
    if (r != 0):
        print "DIFFERENCE DETECTED, ABORTING"
        break
