#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include "SevenSegment.h"
#include "DE1SoCfpga.h"
using namespace std;

int bit_values[16] = {63, 6, 91, 79,102, 109, 125, 7, 127, 111, 119, 124, 57, 94, 121, 113};
int bit_alpha_values[18] = {119, 124, 57, 94, 121, 113, 118, 6, 14, 56, 84, 63, 115, 80, 109, 62, 102, 91};
char alpha_values[18] = {   'a', 'b', 'c','d','e', 'f', 'h','i','j','l','n','o', 'p','r', 's', 'u', 'y', 'z'};
string menuString = "Main menu:\n1. Erase all elements\n2. Clear specific element\n3. Write a specific element to a specific index\n4. Write a number to the display\n5. Exit \nSelect an option: _";
// create an array of 6 elements representing the value to write to each separate display
int curValue[6] = {0, 0, 0, 0, 0, 0};

void SevenSegment::Hex_ClearAll()
{
  RegisterWrite(HEX3_HEX0_BASE, 0);
  RegisterWrite(HEX5_HEX4_BASE, 0);
}

SevenSegment::SevenSegment()
{
  reg0_hexValue = RegisterRead(HEX3_HEX0_BASE);
  reg1_hexValue = RegisterRead(HEX5_HEX4_BASE);
}

SevenSegment::~SevenSegment()
{
  Hex_ClearAll();
}

void SevenSegment::Hex_ClearSpecific(int index)
{
  int curValue = RegisterRead(HEX5_HEX4_BASE);
  if(index > 3) {
    int bitVal = curValue;
    if(index == 4) {
      bitVal = bitVal << 8;
      bitVal = bitVal >> 8;
    } else {
      bitVal = bitVal >> 8;
      bitVal = bitVal << 8;
    }
    bitVal = ~bitVal;

    int clearedState4_5 = curValue & bitVal;
    RegisterWrite(HEX5_HEX4_BASE, clearedState4_5);
  } else {
    int bitVal = curValue;
    for(int i = 0; i < index; i++)
    {
      bitVal = bitVal << 8;
    }
    int curValue = RegisterRead(HEX3_HEX0_BASE);
    curValue = curValue << 4;
    bitVal = bitVal | curValue;
    int clearedState3_0 = bitVal >> 4;
    RegisterWrite(HEX3_HEX0_BASE, clearedState3_0);
  }

  reg0_hexValue = RegisterRead(HEX3_HEX0_BASE);
  reg1_hexValue = RegisterRead(HEX5_HEX4_BASE);
}

void SevenSegment::Hex_WriteSpecific(int index, unsigned int value)
{
  Hex_ClearSpecific(index);
  if(index > 3) {
    int curValue = RegisterRead(HEX5_HEX4_BASE);
    int bitVal = bit_alpha_values[value];
    for(int i = 4; i < index; i++)
    {
      bitVal = bitVal << 8;
    }

    curValue = curValue | bitVal;
    RegisterWrite(HEX5_HEX4_BASE, curValue);
  } else {
    int curValue = RegisterRead(HEX3_HEX0_BASE);
    int bitVal = bit_alpha_values[value];
    for(int i = 0; i < index; i++)
    {
      bitVal = bitVal << 8;
    }
    curValue = curValue | bitVal;
    RegisterWrite(HEX3_HEX0_BASE, curValue);
  }

}

// int SevenSegment::CalculateDisplay(int start, int end, int values[]) {
//   bool first = true;
//   int display = 0;
//   // for the first four displays, display the proper hex value
//   for(int j = start; j > end; j--) {
//     // get the decimal value that represents the display for the j'th hex digit
//     int value = bit_alpha_values[values[j]];
//     // if it's the first display, we don't want to shift over the bits,
//       // we just want toset the display as the bits
//     if(first == true) {
//       display = value;
//       first = false;
//     // otherwise, we want to shift over the bits by 8 and then add the bits to the display
//     } else {
//       display = display << 8 | value;
//     }
//   }
//   return display;
// }
//
// void SevenSegment::Hex_WriteNumber(unsigned int number)
// {
//
//   // // there are 6 possible display values
//   // for (int i = 0; i < 6; i++) {
//   //   // get the first hexadecimal number by using modulo to calculate the base-16 representation
//   //   digits[i] = number % 16;
//   //   // divide the number by 16 to shrink it down to the next power of 16
//   //   number = number / 16;
//   // }
//
//   for(int i = 0; i < 6; i++) {
//     if(curValue[i] != 0) {
//       curValue[i] = number;
//     }
//   }
//
//   // calculate the values to display on the two sets of displays
//   int display = CalculateDisplay(3, -1, curValue);
//   int display2 = CalculateDisplay(5, 3, curValue);
//
//   RegisterWrite(HEX3_HEX0_BASE, display);
//   RegisterWrite(HEX5_HEX4_BASE, display2);
//
//   reg1_hexValue = RegisterRead(HEX3_HEX0_BASE);
//   reg0_hexValue = RegisterRead(HEX5_HEX4_BASE);
// }


int SevenSegment::CalculateDisplay(int start, int end, int digits[]) {
  bool first = true;
  int display = 0;
  // for the first four displays, display the proper hex value
  for(int j = start; j > end; j--) {
    // get the decimal value that represents the display for the j'th hex digit
    int value = bit_values[digits[j]];
    // if it's the first display, we don't want to shift over the bits,
      // we just want toset the display as the bits
    if(first == true) {
      display = value;
      first = false;
    // otherwise, we want to shift over the bits by 8 and then add the bits to the display
    } else {
      display = display << 8 | value;
    }
  }
  return display;
}

void SevenSegment::Hex_WriteNumber(unsigned int number)
{
  // create an array of 6 elements representing the value to write to each separate display
  int digits[6];
  // there are 6 possible display values
  for (int i = 0; i < 6; i++) {
    // get the first hexadecimal number by using modulo to calculate the base-16 representation
    digits[i] = number % 16;
    // divide the number by 16 to shrink it down to the next power of 16
    number = number / 16;
  }

  // calculate the values to display on the two sets of displays
  int display = CalculateDisplay(3, -1, digits);
  int display2 = CalculateDisplay(5, 3, digits);
  // display = 0 | bit_values[digits[0]];
  // cout << "bits: " << bit_values[digits[0]] << endl;

  RegisterWrite(HEX3_HEX0_BASE, display);
  RegisterWrite(HEX5_HEX4_BASE, display2);

  reg1_hexValue = RegisterRead(HEX3_HEX0_BASE);
  reg0_hexValue = RegisterRead(HEX5_HEX4_BASE);
}
int SevenSegment::RunMenu()
{
  char selection;
  cout << menuString;
  cin >> selection;
  return DisplayMenu(selection);
}

int SevenSegment::DisplayMenu(char selection)
{
  int clearIndex = 0;
  int writeIndex = 0;
  int writeElement = 0;
  int number = 0;
  switch (selection) {
    // clear all elements
    case '1':
      cout << "Clear all elements" << endl;
      Hex_ClearAll();
      RunMenu();
      break;
    // clear specific element
    case '2':
      cout << "Clear specific element" << endl;
      cout << "Enter the index to clear: _";
      cin >> clearIndex;
      Hex_ClearSpecific(clearIndex);
      RunMenu();
      break;
    // write specific element
    case '3':
      cout << "Write a specific element to a specific index" << endl;
      cout << "Enter the index to write to: _";
      cin >> writeIndex;
      cout << endl;
      cout << "Enter the element to write: _";
      cin >> writeElement;
      Hex_WriteSpecific(writeIndex, writeElement);
      RunMenu();
      break;
    // write a number to the display
    case '4':
      cout << "Write a number to the display" << endl;
      cout << "Enter the number: _";
      cin >> number;
      Hex_WriteNumber(number);
      RunMenu();
      break;
    // exit the program
    case '5':
      Hex_ClearAll();
      return 0;
      break;
    // if invalid, display an error and run the menu again
    default:
      cout << "Error: please enter a valid option" << endl;
      RunMenu();
      break;
  }
}
