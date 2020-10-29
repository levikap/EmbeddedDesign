#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include "DE1SoCfpga.h"
#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H


class SevenSegment : public DE1SoCfpga
{
private:
  unsigned int reg0_hexValue;
  unsigned int reg1_hexValue;
public:
  /*
   * Clears all the values on to the displays.
   */
  void Hex_ClearAll();

  /*
   * Constructor - assigns intitial values to reg0_hexValue and reg1_hexValue
   *               based on the intital state of the displays.
   */
  SevenSegment();

  /*
   * Destructor - Clears the current displays.
   */
  ~SevenSegment();

  /*
   * Clears a specific display as specified by the index.
   * @Param index (int) - the 0-indexed index of the display, from 0 to 5
   */
  void Hex_ClearSpecific(int index);

  /*
   * Writes a specific value to the board.
   * @Param index (int) - the index to write to
   * @Param value (unsigned int) - the value to be written
   */
  void Hex_WriteSpecific(int index, unsigned int value);

  /*
   * Calculates the display value to display on the board
   * @param start (int) - The index to start the indexing at
   * @param end (int) - The index to end the indexing at
   * @param digits[] (array) - The list of digits who's values will query bit_values
   * @Returns int representing the display value to write to the board
   */
  int CalculateDisplay(int start, int end, int digits[]);

  /*
   * Writes the passed-in number in hex to the board's display.
   * @param number (unsigned int) - The base-10 integer value to write to the display
   */
  void Hex_WriteNumber(unsigned int number);


  /*
   * Runs the menu, displaying menu options and getting user input.
   * @return : int if the program is exited, representing the user wanting to quit the program
   */
  int RunMenu();

  /*
   * Allows for functionality selection. Returns int when quit.
   * @param selection (char) - the character value for the selected option
   * @Returns int when program quit to pass back to main
   */
  int DisplayMenu(char selection);
};

#endif
