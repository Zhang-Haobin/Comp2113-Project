CXX = g++
CXXFLAGS = -O2 -std=c++11 -Iinclude
TARGET = SpireLite
OBJS = main.o battle.o enemy.o player.o Card.o Deck.o save.o Cardfactory.o map.o game_state.o event_screen.o difficulty.o Potion.o
DEPS = $(wildcard include/*.h)

main: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS)

%.o: src/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: main clean
clean:
	rm -f *.o $(TARGET)
