main: main.o battle.o enemy.o player.o Card.o Deck.o save.o Cardfactory.o map.o
	g++ main.o battle.o enemy.o player.o Card.o Deck.o save.o Cardfactory.o map.o -o main -O2 -std=c++11

battle.o: battle.cpp battle.h
	g++ -c battle.cpp -O2 -std=c++11

enemy.o: enemy.cpp enemy.h
	g++ -c enemy.cpp -O2 -std=c++11

player.o: player.cpp player.h
	g++ -c player.cpp -O2 -std=c++11

Card.o: Card.cpp Card.h
	g++ -c Card.cpp -O2 -std=c++11

Deck.o: Deck.cpp Deck.h Card.h
	g++ -c Deck.cpp -O2 -std=c++11

save.o: save.cpp save.h
	g++ -c save.cpp -O2 -std=c++11

Cardfactory.o: Cardfactory.cpp Cardfactory.h Card.h
	g++ -c Cardfactory.cpp -O2 -std=c++11

map.o: map.cpp map.h main.h
	g++ -c map.cpp -O2 -std=c++11

clean:
	rm -f main *.o
