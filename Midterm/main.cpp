#include <iostream>
#include <string>
#include "MenuHandler.h"
using namespace std;

/*
 * Main is in charge of opening a user interface that allows the user to choose to play a tone
 * or start a new Snakes and Ladders game and handle the interactions in either case.
 */
int main(void)
{
  MenuHandler *menu = new MenuHandler;
  return menu->RunMenu();
}
