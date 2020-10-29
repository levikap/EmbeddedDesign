#include <iostream>
#include "DE1SoCfpga.h"
#ifndef SNAKESANDLADDERS_H
#define SNAKESANDLADDERS_H

class SnakesAndLadders : public DE1SoCfpga
{
private:



public:
  /*
   * Constructor
   */
  SnakesAndLadders();

  /*
   * Destructor.
   */
  ~SnakesAndLadders();

  /*
   * Runs a game of snakes and ladders for two players.
   */
  void runSnakesAndLadders();

  /*
   * Prints the current snakes and ladders board.
   */
  void printBoard();

  /*
   * Allows a player to take a turn.
   * @Param playerStartLocation: Int -- the starting location of the player who's turn it is
   */
  void takeTurn(int playerStartLocation);

  /*
   * Gets the string value for the given space.
   * If there is a snake or ladder value there, returns "S" or "L" respectively, otherwise
   * returns the int associated with that value.
   * @param space: the integer value of the space in question
   * @Return string representing that space value.
   */
  void printSpaceValue(int space);

  /*
   * Calculates the new position of the player, taking into account the locations of shoots and ladders.
   * @Param locationWithoutSL: Int -- the location the player would be at if there were not shoots and
   *                                  ladders to alter the player's location.
   * @Returns int representing the new location after the player may have hit a snake or ladder
   */
  int calculateNewPosition(int locationWithoutSL);

  /*
   * Gives an addition challenge to the player that they have to solve before they can move.
   * @Param roll: Int -- what number the player rolled
   * @Param playerStartLocation -- where the player started
   */
  void additionChallenge(int roll, int playerStartLocation);
  /*
   * Ends the game by printing a winner and resetting values.
   */
  void endGame();

  /*
   * Resets game values so another game can be played.
   */
  void resetGame();
};

#endif
