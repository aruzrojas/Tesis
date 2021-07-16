SEED = 1
alfa = 10
LENLIST = 0.3
MAXITS = 30
ALG_GREEDY = 3
ARCHIVO = 'peligro-mezcla4-min-riesgo-zona7-2k-AE.2.hazmat'
TYPE = NL

INPUT=$(TYPE)$(alfa)
VARIABLES=$(SEED) $(alfa) $(LENLIST) $(MAXITS) $(ALG_GREEDY) $(ARCHIVO)
RUN=./main $(SEED) $(alfa) $(LENLIST) $(MAXITS) $(ALG_GREEDY) $(ARCHIVO)

all: compile
	$(RUN)

compile:
	g++ -std=c++11 -o main main.cpp

clean:
