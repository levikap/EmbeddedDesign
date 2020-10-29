#include <iostream>
#ifndef MENUHANDLER_H
#define MENUHANDLER_H

class MenuHandler
{
public:
  MenuHandler();

  ~MenuHandler();
  /*
   * Runs the menu by calling DisplayMenu.
   @returns int when the menu is quit.
   */
  int RunMenu();

  /*
   * Displays the menu and allows the user to select what option they want to choose.
   */
  int DisplayMenu(char selection);


};

#endif
