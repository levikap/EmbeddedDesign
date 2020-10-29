#include <iostream>
#include <string>
#include "SevenSegment.h"
using namespace std;

// /*
//  * Main operates the DE1-SoC 7-Segment Displays
//  * This program writes an integer number on the 7-Segment Displays
//  */
// int main()
// {
//   // Create a pointer object of the SevenSegment class
//   SevenSegment *display = new SevenSegment;
//   cout << "Program Starting...!" << endl;
//    return display->RunMenu();   // display menu
// }


/*
*
* Main operates the DE1-SoC 7-Segment Displays
* This program writes an integer number on the 7-Segment Displays
*/
int main(void)
{
  SevenSegment *display = new SevenSegment;
  cout << "Program Starting...!" << endl;
  int counter= 200000000;// timeout = 1/(200 MHz) x 200x10^6 = 1 sec
  display->RegisterWrite(MPCORE_PRIV_TIMER_LOAD_OFFSET, counter);
  display->RegisterWrite(MPCORE_PRIV_TIMER_CONTROL_OFFSET, 3);
  int entervalue = 0;
  int enterindex = 0;
  int curValue;
  int reg0_hexValue;

  display->Hex_ClearAll();

  // list of indices of the letters should query from bit_alpha_values in order or display
  int letterVals[18] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
  int i = 0;
  //cin >> bitentervalue;
  while (1)
  {

    if (display->RegisterRead(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET) != 0)
    {
      display->RegisterWrite(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET, 1); // reset timer flag
      if(i < 18)
      {
        curValue = display->RegisterRead(HEX3_HEX0_BASE);
        // display ->Hex_WriteNumber(letterVals[i]);
          curValue = curValue << 8;
        for(int j = 1; j < 5; j++) {
          if(i - j > 0) {
            display ->Hex_WriteSpecific(j, letterVals[i-j]);
          }
        }
        display ->Hex_WriteSpecific(0, letterVals[i]);
        cout << letterVals[i] << endl;
        i = i + 1;
      } else {
        i = 0;
      }

    }
  }
  delete display;

  cout << "Terminating...!" << endl;
  return 0;
    }
