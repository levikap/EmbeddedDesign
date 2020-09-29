#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
using namespace std;
// Physical base address of FPGA Devices
const unsigned int LW_BRIDGE_BASE  = 0xFF200000;  // Base offset
// Length of memory-mapped IO window
const unsigned int LW_BRIDGE_SPAN  = 0x00DEC700;  // Address map size
// Cyclone V FPGA device addresses
const unsigned int LEDR_BASE       = 0x00000000;  // Leds offset
const unsigned int SW_BASE         = 0x00000040;  // Switches offset
const unsigned int KEY_BASE        = 0x00000050;  // Push buttons offset
int buttonValues = 0;

class DE1SoCfpga {
  public:
    char *pBase;
    // File descriptor passed by reference, where the result of function 'open' will be stored.
    int fd;


    /**
     * Initialize general-purpose I/O
     *  - Opens access to physical memory /dev/mem
     *  - Maps memory into virtual address space
     */
  DE1SoCfpga()
  {
    // Open /dev/mem to give access to physical addresses
    fd = open( "/dev/mem", (O_RDWR | O_SYNC));
    if (fd == -1)   //  check for errors in openning /dev/mem
     {
       cout << "ERROR: could not open /dev/mem..." << endl;
       exit(1);
     }
     // Get a mapping from physical addresses to virtual addresses
     char *virtual_base = (char *)mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ
       | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
          if (virtual_base == MAP_FAILED)       // check for errors
          {
           cout << "ERROR: mmap() failed..." << endl;
           close (fd);            // close memory before exiting
           exit(1);        // Returns 1 to the operating system;
           }
    pBase = virtual_base;
  }

  /**
    * Close general-purpose I/O.
  */
  ~DE1SoCfpga()
  {
    if (munmap (pBase, LW_BRIDGE_SPAN) != 0)
    {
     cout << "ERROR: munmap() failed..." << endl;
     exit(1);
     }
   close (fd);    // close memory
  }

  /**
  * Write a 4-byte value at the specified general-purpose I/O location.
  * @parem offset  Offset where device is mapped.
  * @param value   Value to be written.
  */
  void RegisterWrite(unsigned int reg_offset, int value)
  {
    * (volatile unsigned int *)(pBase + reg_offset) = value;
  }


  /**
  * Read a 4-byte value from the specified general-purpose I/O location.
  * @param offset  Offset where device is mapped.
  * @return        Value read.
  */
  int RegisterRead(unsigned int reg_offset)
  {
     return * (volatile unsigned int *)(pBase + reg_offset);
  }


};


class LedControl : public DE1SoCfpga
{
public:
  LedControl() {}

  ~LedControl() {}

  void WriteAllLeds(int value)
  {
     RegisterWrite(LEDR_BASE, value);
  }

  /*
   * Calculates the value of the base rased to the power of the exponent.
   * @Param base - the base to calculate the power for
   * @Param exp - the exponent the base should be raised to
   * Returns value representing the value of the operation
   */
  int CalculatePower(int base, int exp) {
    int value = 1;
    for(int i = 0; i < exp; i++) {
      value = value * base;
    }
    return value;
  }

  /*
   * Changes the state of an LED (ON or OFF)
   *  @param pBase          Base address returned by 'mmap'
   *  @param ledNum         LED Number (0 to 9)
   *  @param state          State to change to (ON or OFF)
   */
  void Write1Led(int ledNum, int state)
  {

      // calculate the base 2 representation of ledNum
      int value = CalculatePower(2, ledNum);

      // read the current value of the led
      int curState = RegisterRead(LEDR_BASE);
      // // if the LED is on and it should be off, set the value to 0
      // if(curState == value && state == 0) {
      //   value = 0;
      // }
      if(state == 1) {
        curState = curState | value;
      } else {
        curState = (curState | value) ^ value;
      }
      // write the value to the board
      WriteAllLeds(curState);
  }



  /*
   * Reads all the switches and returns their value in a single integer
   * @return         A value that represents the value of the switches
   */
  int ReadAllSwitches()
  {
    return RegisterRead(SW_BASE);
  }

  /*
   * Reads all the buttons and returns their value in a single integer
   * @return         A value that represents the value of the buttons
   */
  int ReadAllButtons()
  {
    return RegisterRead(KEY_BASE);
  }


  /*
   * A helper to determine whether the passed in switch (represented by value) is on or off.
   * @param switchNum representing the number switch the user wishes to see the state of
   * @param curSwitchValues - the decimal form of the base 2 representation of the switch State
   * Returns boolean representing whether the value is present in the curSwitchValues, meaning the switch is on
   */
  bool ReadSwitchHelper(int switchNum, int curSwitchValues) {
     // set alias of curSwitchValues to subtract from
     int curBase2 = curSwitchValues;
     // set default value of returnBool to false
     bool returnBool = false;

     // set up an empty array to store switch values
     int switches[10];

     // for each switch
     for(int i = 9; i >= 0; i--) {
       // calculate the power of 2 to the power of i
       int power = CalculatePower(2, i);
       // if the current base 2 value is greater than power, the switch is on
       if(curBase2 >= power) {
         // set the switch array value to 1
         switches[i] = 1;
         // subtract the power so the next switch can be read
         curBase2 = curBase2 - power;
       } else {
         // the current switch isn't on because the power is greater than the current base
         switches[i] = 0;
       }
     }
     // return the switch state of the desired switch, which is 1 or 0 which translates to true or false
     return switches[switchNum];
   }

  /*
   *Reads the value of a switch
   * -Uses base address of I/O
   * @param switchNumSwitch number(0 to 9)
   * @returnSwitch value read
   */
   int Read1Switch(int switchNum) {
     // calculate the binary value of the switchNum by calculating 2 ^ switchNum
     int value = CalculatePower(2, switchNum);
     // read the value of the current switches
     int curSwitchValues = ReadAllSwitches();
     // if the value equals the value of the current switches, the passed-in switch is on
     if(ReadSwitchHelper(switchNum, curSwitchValues)) {
       return 1;
     // otherwise, the passed-in switch is off
     } else {
       return 0;
     }
   }

  /*
   * Gets the value of all the push buttons that have been pressed.
   */
  int PushButtonGet() {
    return ReadAllButtons();
  }

  /*
   * Increments the value of the LEDs by one, and displays the updated LEDs.
   */
  void IncrementLeds() {
    cout << "Incrementing..." << endl;
    int currentValue = RegisterRead(LEDR_BASE);
    currentValue = currentValue + 1;
    cout << currentValue << endl;
    WriteAllLeds(currentValue);
  }

  /*
   * Decrements the value of the LEDs by one, and displays the updated LEDs.
   */
  void DecrementLeds() {
    cout << "Decrementing..." << endl;
    int currentValue = RegisterRead(LEDR_BASE);
    currentValue = currentValue - 1;
    cout << currentValue << endl;
    WriteAllLeds(currentValue);
  }

  /*
   * Shifts the value of the LEDs by one to the right, inserting a 0 bit on the far left of the binary.
   */
  void ShiftRight() {
    cout << "Shifting right..." << endl;
    int currentValue = RegisterRead(LEDR_BASE);
    currentValue = currentValue >> 1;
    cout << currentValue << endl;
    WriteAllLeds(currentValue);
  }

  /*
   * Shifts the value of the LEDs by one to the left, inserting a 0 bit on the far right of the binary.
   */
  void ShiftLeft() {
    cout << "Shifting left..." << endl;
    int currentValue = RegisterRead(LEDR_BASE);
    currentValue = currentValue << 1;
    cout << currentValue << endl;
    WriteAllLeds(currentValue);
  }

  /*
   * Handles the different cases for the values when the push buttons are pressed
   * @param buttonValue - the value of the button that has been pressed
   */
  void HandlePushButtons(int buttonValue) {
    // if the button's value is 0, don't do anything
    if (buttonValue != 0) {
      // if the value is 1, run the IncrementLeds function
      if(buttonValue == 1) {
        IncrementLeds();
      // if the value is 2, run the DecrementLeds function
      } else if (buttonValue == 2) {
        DecrementLeds();
      // if the value is 4, run the ShiftRight function
      } else if (buttonValue == 4) {
        ShiftRight();
      // if the value is 8, run the ShiftLeft function
      } else if (buttonValue == 8) {
        ShiftLeft();
      // otherwise, output an error but keep going
      } else {
        cout << "error" << endl;
      }
    }
  }

  /*
   * Detects whether a push button has been changed - either a new button has been pressed,
   * or a button has been let go of.
   */
  void DetectPushButtonChange() {
    // get the current button values
    int newButtonValues = PushButtonGet();
    // if there's been a change, set the new value of the buttons
    if(newButtonValues != buttonValues) {
      buttonValues = newButtonValues;
      // handle the button press properly
      HandlePushButtons(newButtonValues);
    }
  }
};

int main()
{
  DE1SoCfpga board;
  LedControl control;
  // detect push button changes
  while(true) {
    control.DetectPushButtonChange();
  }
  return 0;
}
