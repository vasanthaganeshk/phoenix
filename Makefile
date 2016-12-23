LIBS = -lseccomp
WARNINGS = -Wall

engine: ./src/engine.c
	$(CC) $(LIBS) $(WARNINGS) -o engine ./src/engine.c

.PHONY: run clean

run:
	./engine bot1 bot2

clean:
	\rm engine *~ ./src/*~ ./bots/*~
