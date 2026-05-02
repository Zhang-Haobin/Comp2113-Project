main: main.o battle.o enemy.o player.o Card.o Deck.o save.o Cardfactory.o map.o game_state.o event_screen.o difficulty.o
	g++ main.o battle.o enemy.o player.o Card.o Deck.o save.o Cardfactory.o map.o game_state.o event_screen.o difficulty.o -o SpireLite -O2 -std=c++11

main.o: src/main.cpp include/main.h include/event_screen.h include/difficulty.h player.o save.o battle.o map.o Cardfactory.o enemy.o Card.o Deck.o game_state.o event_screen.o difficulty.o
	g++ -c src/main.cpp -O2 -std=c++11

battle.o: src/battle.cpp include/battle.h include/main.h save.o Cardfactory.o
	g++ -c src/battle.cpp -O2 -std=c++11

enemy.o: src/enemy.cpp include/enemy.h
	g++ -c src/enemy.cpp -O2 -std=c++11

player.o: src/player.cpp include/player.h
	g++ -c src/player.cpp -O2 -std=c++11

Card.o: src/Card.cpp include/Card.h
	g++ -c src/Card.cpp -O2 -std=c++11

Deck.o: src/Deck.cpp include/Deck.h Card.o
	g++ -c src/Deck.cpp -O2 -std=c++11

save.o: src/save.cpp include/save.h include/main.h
	g++ -c src/save.cpp -O2 -std=c++11

Cardfactory.o: src/Cardfactory.cpp include/Cardfactory.h Card.o
	g++ -c src/Cardfactory.cpp -O2 -std=c++11

map.o: src/map.cpp include/map.h include/main.h
	g++ -c src/map.cpp -O2 -std=c++11

game_state.o: src/game_state.cpp include/game_state.h player.o map.o Cardfactory.o
	g++ -c src/game_state.cpp -O2 -std=c++11

event_screen.o: src/event_screen.cpp include/event_screen.h include/main.h Cardfactory.o player.o Card.o
	g++ -c src/event_screen.cpp -O2 -std=c++11

difficulty.o: src/difficulty.cpp include/difficulty.h include/player.h include/main.h
	g++ -c src/difficulty.cpp -O2 -std=c++11

clean:
	rm -f *.o SpireLite
