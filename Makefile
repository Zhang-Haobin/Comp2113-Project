main: main.o battle.o enemy.o player.o
	g++ main.o battle.o enemy.o player.o -o main -O2 -std=c++11

battle.o: battle.cpp battle.h
	g++ -c battle.cpp -O2 -std=c++11

enemy.o: enemy.cpp enemy.h
	g++ -c enemy.cpp -O2 -std=c++11

player.o: player.cpp player.h
	g++ -c player.cpp -O2 -std=c++11
