# Spire Lite
**A tiny text-based deckbuilding climb.**

## Team Members
- Team member 1: Zhang Haobin
- Team member 2: Peng Yik Sz
- Team member 3: Yeung Long
- Team member 4: Zhang Hanyun

## Application Description
Spire Lite is a playable terminal-based card battle game inspired by Slay the Spire. The player starts a new run, chooses a difficulty level, climbs through a randomly generated map, enters enemy encounters and events, improves their deck through rewards, and tries to defeat the final boss.

The game is designed as a simple but complete deckbuilding loop. Each battle uses a hand, draw pile, discard pile, energy system, player block, enemy armor, and card effects. Between battles, the player can gain cards, recover HP, resolve random events, and continue climbing until the run ends in victory or defeat.

Spire Lite also keeps save data and records, so the player can continue an unfinished run and view the best score, highest stage, wins, and losses.

## Features
- Text-based menu system with welcome, lobby, map, battle, record, help, and end screens.
- Three difficulty levels: Easy, Normal, and Hard.
- Randomly generated map with normal enemy rooms, event rooms, and a final boss room.
- Turn-based card combat with energy, block, enemy armor, draw pile, discard pile, and hand size limits.
- Single-enemy and double-enemy encounters. Attack cards auto-target when only one enemy is alive, and ask for a target when multiple enemies are alive.
- Starter deck and reward cards generated through a card factory.
- Multiple card effects, including attack, AOE damage, block, healing, energy recovery, block doubling, self-damage for energy, and scaling damage.
- Potion system with healing, energy, fire damage, and block potions. The player starts with a potion and can find more during the run.
- Multiple enemy types that change as the player reaches higher stages.
- Random events such as healing, traps, card removal, card gain, and mystery outcomes.
- Card Library screen that lists all card templates in the game.
- Colored battle text, clearer action logs, and short delays so terminal output is easier to read.
- File input/output for current run saves and long-term game records.
- Modular source code split across multiple header and source files.
- Dynamic data structures such as vectors, maps, and saved map layers.
- Dynamic memory management in card reward generation, where temporary reward choices are created with a dynamic array and released after use.

## Difficulty Levels
Difficulty changes player HP, map length, enemy HP, enemy damage, and score gain.

| Difficulty | Player HP | Floors | Enemy HP | Enemy Damage | Score |
| --- | ---: | ---: | ---: | ---: | ---: |
| Easy | 70 | 8 | x0.8 | x0.8 | x0.8 |
| Normal | 60 | 12 | x1.0 | x1.0 | x1.0 |
| Hard | 50 | 16 | x1.4 | x1.3 | x1.5 |

Normal and Hard can also generate double-enemy encounters later in the run. Easy keeps battles simpler.

## Gameplay Notes
- Enter the number shown beside a menu option to choose it.
- In battle, cards cost energy. Unused energy does not carry over to the next turn.
- Most single-target attack cards automatically hit the enemy when only one enemy is alive.
- If multiple enemies are alive, single-target attack cards ask which enemy to attack.
- AOE cards such as `Cleave` hit all alive enemies.
- Potions appear as battle options and are consumed after use.
- At the end of each turn, enemies attack and the next player turn begins.

## Coding Requirements Coverage
The project requirements ask the game to include several coding elements. Spire Lite uses them as follows:

| Requirement | How it is used in Spire Lite |
| --- | --- |
| Generation of random events | The map contains random event rooms, and `event_screen.cpp` randomly chooses event outcomes such as healing, traps, card removal, card gain, and mystery outcomes. Enemy encounters, card rewards, potion drops, double-enemy encounters, and map layouts also use random generation. |
| Data structures for storing data | The game uses `vector` for decks, hands, draw piles, discard piles, enemies, potions, reward cards, map layers, and map nodes. It uses `unordered_map` in battle to map player input options to actions. |
| Dynamic memory management | `Cardfactory::create_reward_card()` creates temporary reward choices using a dynamic array with `new[]`, copies them into a `vector`, and releases the memory with `delete[]`. |
| File input/output | `game_state.cpp` saves and loads unfinished runs through `game_save.txt`, including player data, deck, potions, score, difficulty, and map state. `save.cpp` stores long-term records such as best score, highest stage, wins, losses, and win rate in `save.txt`. |
| Program codes in multiple files | The project is split into separate `.h` and `.cpp` files for battle, cards, card factory, potions, map generation, events, save/load, difficulty, player, enemy, and the main game loop. |
| Multiple difficulty levels | `difficulty.cpp` defines Easy, Normal, and Hard. Difficulty changes player HP, map length, enemy HP multiplier, enemy damage multiplier, score multiplier, and double-enemy encounter frequency. |

## Non-standard Libraries
This project does not use any non-standard libraries.

## How to run the game?
1. On File Explorer / Finder, open the Spire Lite folder.
    * On File Explorer / Finder, you should see the "SpireLite" file, like this:

    ![Your folder containing SpireLite](./folder_demo.png)

2. Open **Terminal** on the Spire Lite folder:
    * On **Windows**, follow [these steps](https://johnwargo.com/posts/2024/launch-windows-terminal/).
    * On **Mac**, follow [these steps](https://www.youtube.com/watch?v=6rzT130xpM4).
    * On **Linux**, open Terminal and run ```cd``` on the Spire Lite folder.

3. Run the game!
    * On **Windows**, enter this command: ```SpireLite```
    * On **Linux / Mac**, enter this command: ```./SpireLite```

4. Spire Lite should now appear. Enjoy!

## Compilation (using make)
1. Open Terminal.

2. Make sure you are on the right folder before you proceed.

3. Run ```make clean && make main```

## Save Files
The game uses local text files for save data:

- `game_save.txt` stores the current unfinished run.
- `save.txt` stores long-term game records such as best score, highest stage, wins, and losses.

The game saves at key checkpoints, such as after creating a new run, after winning a normal battle, and after resolving an event. It does not save every single action inside a battle. When a run ends in victory or defeat, the long-term record is updated.

Save files are created relative to the folder where the program is run. For best results, run the executable from the project folder.

## Code Structure
- `src/main.cpp` controls the main game loop, screen flow, map transitions, and global run state.
- `src/battle.cpp` handles combat, turn flow, card use, enemy attacks, potion use, rewards, and battle victory/defeat.
- `src/Card.cpp` and `src/Cardfactory.cpp` define card templates and card reward generation.
- `src/Potion.cpp` defines potion templates and random potion generation.
- `src/map.cpp` generates and displays the room map.
- `src/event_screen.cpp` handles random event rooms.
- `src/game_state.cpp` saves and loads the current run, including player data, deck, potions, score, and map state.
- `src/save.cpp` stores long-term records such as best score, wins, losses, and win rate.
- `src/difficulty.cpp` defines and applies difficulty settings.

## Warnings
ANSI escape sequences may not work in some older terminals, especially old Windows cmd. If colors or clear-screen behavior looks strange, use a modern terminal such as Windows Terminal, macOS Terminal, or a Linux terminal.
