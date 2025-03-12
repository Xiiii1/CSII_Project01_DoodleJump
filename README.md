# CSII_Project01_DoodleJump

## Overview
This project is an implementation of the classic Doodle Jump game using C++. The game is developed as part of a Computer Science II course project.

## Features

- Simple and intuitive gameplay
- Basic graphics and animations
- Score tracking
- Randomly generated platforms
- Different platform types with unique behaviors
- Various monsters with different effects
- Collectible items that enhance gameplay
- Game over conditions and scoring system

## How to Control?

1. Click the play button on the initial screen using the left mouse button.
2. Use the left and right arrow keys on your keyboard to move the doodler horizontally.
3. The doodler jumps automatically upon landing on a platform.
4. Click the left mouse button to shoot bullets and eliminate monsters.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++, clang++)
- Make sure to have a C++17 compatible compiler

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/Xiiii1/CSII_Project01_DoodleJump.git
    cd CSII_Project01_DoodleJump
    ```

2. Compile the project:
    ```sh
    g++ -std=c++17 -o DoodleJump main.cpp
    ```

3. Run the executable:
    ```sh
    ./DoodleJump
    ```

## How to Compile (For Qt5 Version)

1. Open Cygwin (with Qt5 installed).
2. Enter the following commands step by step:
    ```sh
    cd /path/to/project  # Adjust the path accordingly
    qmake-qt5 -project
    qmake-qt5 "QT+=widgets" "QT+=core gui" "QT+=widgets multimedia"
    ```
3. Open a second Cygwin terminal and enter:
    ```sh
    startxwin
    ```
4. Return to the first terminal and run:
    ```sh
    make
    export DISPLAY=:0.0
    ./DoodleJump
    ```

If you want to play again, repeat steps 4-6 in terminal 1.

## Gameplay Mechanics

### Doodle Movement
- Jumps automatically with a height of 320 pixels.
- Gravity effect is applied to the jump.
- Moves left or right using arrow keys.
- Bullets fired using the left mouse button can kill monsters.
- The camera follows Doodle when it reaches half the screen height (480 pixels).
- Doodle wraps around the screen when moving off one side.

### Platforms
- **Normal platforms**: Move downward as Doodle jumps.
- **Broken platforms**: Break when stepped on, causing Doodle to fall.
- **Moving platforms**: Move left/right or up/down.
- **Disappearing platforms**: Vanish after being stepped on once.
- **Countdown platforms**: Disappear 4 seconds after appearing.
- **Thorn platforms**: Cause Doodle to lose 1 HP upon landing.

### Monsters
- 4 types of monsters.
- Doodle loses 1 HP upon touching a monster (except on its head).
- Jumping on a monster's head kills it and allows Doodle to jump again.

### Items
- **Spring**: Increases jump height to 960 pixels.
- **Trampoline**: Increases jump height to 1920 pixels.
- **Propeller hat**: Allows Doodle to fly 3840 pixels.
- **Jet pack**: Allows Doodle to fly 7680 pixels.
- **Shield**: Provides one-time damage immunity.

### Game Mechanics
- Doodle starts with 3 HP.
- The score is based on the highest pixel height reached.
- A black hole will instantly end the game if Doodle touches it.

## Acknowledgements
- [Doodle Jump](https://en.wikipedia.org/wiki/Doodle_Jump) - The original game
