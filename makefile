SEED=1
alfa=0
LENLIST=0.3
MAXITS = 30
ARCHIVO = 'peligro-mezcla4-min-riesgo-zona1-2k-AE.2.hazmat'
TYPE=NL

INPUT=$(TYPE)$(alfa)
VARIABLES=$(SEED) $(alfa) $(LENLIST) $(MAXITS) $(ARCHIVO)
RUN=./main $(SEED) $(alfa) $(LENLIST) $(MAXITS) $(ARCHIVO)

all: compile
	$(RUN)

compile:
	g++ -std=c++11 -o main main.cpp

clean:
