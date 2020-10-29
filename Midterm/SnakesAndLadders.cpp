#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <string>
#include "SnakesAndLadders.h"
#include "DE1SoCfpga.h"
using namespace std;

bool player1Turn = true;
int numberOfSnakes = 5;
int numberOfLadders = 5;
int player1Space = 1;
int player2Space = 1;

int board_spaces[5][10] = {
                          {41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
                          {40, 39, 38, 37, 36, 35, 34, 33, 32, 31},
                          {21, 22, 23, 24, 25, 26,27, 28, 29, 30},
                          {20, 19, 18, 17, 16, 15, 14, 13, 12, 11},
                          {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
                          };

int ladder_start[5] = {3, 8, 20, 15, 35};
int ladder_end[5] = {10, 40, 35, 33, 49};
int snake_start[5] = {12, 45, 32, 17, 40};
int snake_end[5] = {5, 25, 22, 10, 30};

string rowDivider = "+-----------------------------------------------------+\n";

SnakesAndLadders::SnakesAndLadders()
{
  runSnakesAndLadders();
}


SnakesAndLadders::~SnakesAndLadders()
{

}

void SnakesAndLadders::runSnakesAndLadders()
{
  printBoard();
  if(player1Turn) {
    cout << "It's player #'s turn! Press any key to roll the die!" << endl;
    takeTurn(player1Space);
    player1Turn = false;
  } else {
    cout << "It's player @'s turn! Press any key to roll the die!" << endl;
    takeTurn(player2Space);
    player1Turn = true;
  }
  if(player1Space < 50 && player2Space < 50) {
    runSnakesAndLadders();
  } else {
    endGame();
  }
}


void SnakesAndLadders::printBoard()
{
  cout << rowDivider;
  for(int i = 0; i < 5; i++) {
    cout << "|";
    for(int j = 0; j < 10; j++) {
      int space = board_spaces[i][j];
      if(space == player2Space) {
        space = -1;
      } else if(space == player1Space) {
        space = -2;
      }
      printSpaceValue(space);
    }
    cout << endl << rowDivider;
  }
}

void SnakesAndLadders::printSpaceValue(int space)
{
  if(space == -1) {
    cout << " @ |";
  } else if(space == -2) {
    cout << " # |";
  } else {
    bool printed = false;
    // print the Ladder spaces in the right spots
    for(int i = 0; i < numberOfLadders; i++)
    {
      if(ladder_start[i] == space || ladder_end[i] == space)
      {
        cout << " L |";
        printed = true;
      }
    }

    // print the Snake spaces in the right spots
    for(int j = 0; j < numberOfSnakes; j++)
    {
      if(snake_start[j] == space || snake_end[j] == space)
      {
        cout << " S |";
        printed = true;
      }
    }
    if(printed == false) {
      cout << " " << space << " |";
    }
  }
}

int SnakesAndLadders::calculateNewPosition(int locationWithoutSL)
{
  // determine if the player moved to a start of a ladder, and move the player up the ladder if so.
  for(int i = 0; i < numberOfLadders; i++)
  {
    if(ladder_start[i] == locationWithoutSL)
    {
      cout << "Yay! You found a ladder! You move up to " << ladder_end[i] << endl;
      return ladder_end[i];
    }
  }

  // determine if the player moved to a start of a snake, and move the player down the snake if so.
  for(int j = 0; j < numberOfSnakes; j++)
  {
    if(snake_start[j] == locationWithoutSL)
    {
      cout << "Oh no! You found a scary snake! You get gobbled up and move down to " << snake_end[j] << endl;
      return snake_end[j];
    }
  }
  return locationWithoutSL;
}

void SnakesAndLadders::takeTurn(int playerStartLocation)
{
  // TODO: Add addition/subtraciton challenge?
  // generate a random number between 1 and 6
  string playerInput;
  cin >> playerInput;
  int roll = rand() % 6 + 1;
  int newPosition = playerStartLocation + roll;
  cout << endl << "You rolled a " << roll << endl;
  additionChallenge(roll, playerStartLocation);
  if(player1Turn)
  {
    player1Space = calculateNewPosition(newPosition);
    cout << "Player # moved to " << player1Space << endl;
  } else {
    player2Space = calculateNewPosition(newPosition);
    cout << "Player @ moved to " << player2Space << endl;
  }
}

void SnakesAndLadders::additionChallenge(int roll, int playerStartLocation)
{
  int newPosition = roll + playerStartLocation;
  cout << "What's " << roll << " plus " << playerStartLocation << "?" << endl;
  int addition;
  cin >> addition;
  if(addition == newPosition) {
    cout << "great job! You can move now!" << endl;
  } else {
    cout << "Not quite! Let's try again!" << endl;
    additionChallenge(roll, playerStartLocation);
  }
}

void SnakesAndLadders::endGame()
{
  // player 1 won! Print this and then reset
  if(player1Space > 50) {
    cout << "Player # Wins!" << endl;
    resetGame();
  // player 2 won! Print this and then reset
  } else  {
    cout << "Player @ Wins!" << endl;
    resetGame();
  }
}

void SnakesAndLadders::resetGame() {
  string playerInput;
  cout << endl << "Press any key to play again!" << endl;
  cin >> playerInput;
  player1Turn = true;
  player1Space = 1;
  player2Space = 1;
}
