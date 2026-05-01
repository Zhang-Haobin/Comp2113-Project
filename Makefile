main: main.o battle.o enemy.o player.o Card.o Deck.o save.o Cardfactory.o map.o
	g++ main.o battle.o enemy.o player.o Card.o Deck.o save.o Cardfactory.o map.o -o SpireLite -O2 -std=c++11

main.o: src/main.cpp include/main.h src/player.cpp include/player.h src/save.cpp include/save.h src/battle.cpp include/battle.h src/map.cpp include/map.h
	g++ -c src/main.cpp -O2 -std=c++11

battle.o: src/battle.cpp include/battle.h
	g++ -c src/battle.cpp -O2 -std=c++11

enemy.o: src/enemy.cpp include/enemy.h
	g++ -c src/enemy.cpp -O2 -std=c++11

player.o: src/player.cpp include/player.h
	g++ -c src/player.cpp -O2 -std=c++11

Card.o: src/Card.cpp include/Card.h
	g++ -c src/Card.cpp -O2 -std=c++11

Deck.o: src/Deck.cpp include/Deck.h src/Card.cpp include/Card.h
	g++ -c src/Deck.cpp -O2 -std=c++11

save.o: src/save.cpp include/save.h src/main.cpp include/main.h
	g++ -c src/save.cpp -O2 -std=c++11

Cardfactory.o: src/Cardfactory.cpp include/Cardfactory.h src/Card.cpp include/Card.h
	g++ -c src/Cardfactory.cpp -O2 -std=c++11

map.o: src/map.cpp include/map.h src/main.cpp include/main.h
	g++ -c src/map.cpp -O2 -std=c++11

clean:
	rm -f *.o SpireLite
