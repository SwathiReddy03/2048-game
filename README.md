# 2048 Game

This repository contains a C++ implementation of the popular 2048 puzzle game. The game is designed using object-oriented programming principles and includes features like undo, score tracking, and a simple menu system.

## How to Play

1. Clone the repository to your local machine.
2. Compile the code using a C++ compiler.
3. Run the executable.

## Game Controls

- **W/A/S/D**: Move tiles Up/Left/Down/Right
- **U**: Undo the last move
- **R**: Restart the game
- **Q**: Quit the game
- **H**: Display the help screen

## Features

- Interactive menu system for starting, quitting, and getting help.
- Grid display for a clear view of the game board.
- Undo functionality to revert the last move.
- Score tracking and display.
- Option to view and reset high scores.

## Game Rules

- The game starts with 1 or 2 randomly placed numbers in a 4x4 grid.
- Use the W/A/S/D keys to move the tiles Up/Left/Down/Right.
- Tiles with the same value will merge and add up.
- New tiles (2 or 4) appear randomly after each move.
- The objective is to achieve the 2048 tile to win the game.

## Score and Records

- The maximum possible tile is 65,536, and the maximum possible score is 3,932,156.
- The game records your name and score in a file (`record_round.txt`) after each turn.
- You can view and reset scores in the game menu.

## File Structure

- `2048.cpp`: The main C++ code for the 2048 game.
- `record_round.txt`: File to store player names and scores after each turn.


