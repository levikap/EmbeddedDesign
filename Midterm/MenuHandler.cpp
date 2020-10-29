#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <string>
#include "MenuHandler.h"
#include "SnakesAndLadders.h"
#include "TonePlayer.h"
using namespace std;

string menuString = "Welcome to Snakes and Ladders and Tones! If you'd like to start a new\nSnakes and Ladders game, please enter 1. If you'd prefer to play a tone, press 2.\n_";

MenuHandler::MenuHandler()
{

}

MenuHandler::~MenuHandler()
{

}

int MenuHandler::RunMenu()
{
  char selection;
  cout << menuString;
  cin >> selection;
  return DisplayMenu(selection);
}

int MenuHandler::DisplayMenu(char selection)
{
  switch (selection) {
    // Start a new Snakes an dLadders game
    case '1':
      cout << "Starting a new Snakes and Ladders game..." << endl;
      // Start new Snakes and ladders game
      SnakesAndLadders();
      RunMenu();
      break;
    // Play a Tone
    case '2':
      // Play a Tone
      TonePlayer();
      RunMenu();
      break;
    // exits the program
    case '5':
      // TODO: clear data
      return 0;
      break;
    // if invalid, display an error and run the menu again
    default:
      cout << "Error: please enter a valid option" << endl;
      RunMenu();
      break;
  }
}
