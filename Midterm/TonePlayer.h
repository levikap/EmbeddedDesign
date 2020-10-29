#include <iostream>
#include "DE1SoCfpga.h"
#ifndef TONEPLAYER_H
#define TONEPLAYER_H

class TonePlayer : public DE1SoCfpga
{
private:



public:

  /*
   * Constructor for TonePlayer.
   */
  TonePlayer();

  /*
   * Destructor for TonePlayer.
   */
  ~TonePlayer();

  /*
   * Plays a tone on the connected speaker.
   */
  void playTone();
};

#endif
