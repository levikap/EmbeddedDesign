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


/**
* Write a 4-byte value at the specified general-purpose I/O location.
*
* @param pBase   Base address returned by 'mmap'.
* @parem offset  Offset where device is mapped.
* @param value   Value to be written.
*/
void RegisterWrite(char *pBase, unsigned int reg_offset, int value)
{
  * (volatile unsigned int *)(pBase + reg_offset) = value;
}


/**
* Read a 4-byte value from the specified general-purpose I/O location.
*
* @param pBase   Base address returned by 'mmap'.
* @param offset  Offset where device is mapped.
* @return        Value read.
*/
int RegisterRead(char *pBase, unsigned int reg_offset)
{
   return * (volatile unsigned int *)(pBase + reg_offset);
}

void WriteAllLeds(char *pBase, int value)
{
   RegisterWrite(pBase, LEDR_BASE, value);
}


/**
 * Initialize general-purpose I/O
 *  - Opens access to physical memory /dev/mem
 *  - Maps memory into virtual address space
 *
 * @param fd      File descriptor passed by reference, where the result
 *                of function 'open' will be stored.
 * @return  Address to virtual memory which is mapped to physical, or MAP_FAILED on error.
 */
char *Initialize(int *fd)
{
 // Open /dev/mem to give access to physical addresses
 *fd = open( "/dev/mem", (O_RDWR | O_SYNC));
 if (*fd == -1)   //  check for errors in openning /dev/mem
  {
    cout << "ERROR: could not open /dev/mem..." << endl;
    exit(1);
  }
  // Get a mapping from physical addresses to virtual addresses
  char *virtual_base = (char *)mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ
    | PROT_WRITE), MAP_SHARED, *fd, LW_BRIDGE_BASE);
       if (virtual_base == MAP_FAILED)       // check for errors
       {
        cout << "ERROR: mmap() failed..." << endl;
        close (*fd);            // close memory before exiting
        exit(1);        // Returns 1 to the operating system;
        }
       return virtual_base;
}


/**
  * Close general-purpose I/O.
  *
  * @param pBase   Virtual address where I/O was mapped.
  * @param fd      File descriptor previously returned by 'open'.
*/
void Finalize(char *pBase, int fd)
{
   if (munmap (pBase, LW_BRIDGE_SPAN) != 0)
   {
    cout << "ERROR: munmap() failed..." << endl;
    exit(1);
    }
  close (fd);    // close memory
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
void Write1Led(char *pBase,int ledNum, int state)
{

    // calculate the base 2 representation of ledNum
    int value = CalculatePower(2, ledNum);

    // read the current value of the led
    int curState = RegisterRead(pBase, LEDR_BASE);
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
    WriteAllLeds(pBase, curState);
}



/*
 * Reads all the switches and returns their value in a single integer
 * @param pBase    Base address for general-purpose I/O
 * @return         A value that represents the value of the switches
 */
int ReadAllSwitches(char *pBase)
{
  return RegisterRead(pBase, SW_BASE);
}

int main()
{
  // Initialize
  int fd;
  char *pBase = Initialize(&fd);

  int value = 0;
  int ledNum = 0;
  // get user input
  cout << "Enter an LED number (0 to 9):_" << endl;
  cin >> ledNum;
  cout << "Led Number chosen: " << ledNum << endl;
  cout << "Enter a state for this LED (0 or 1):_" << endl;
  cin >> value;
  cout << "State chosen: " << value << endl;
  if(ledNum > 9 || ledNum < 0 || (value != 1 && value != 0)) {
    cout << "Please enter valid values" << endl;
  } else {
    // write the passed-in LED to the board
    Write1Led(pBase, ledNum, value);
  }
  // Done
  Finalize(pBase, fd);
}
