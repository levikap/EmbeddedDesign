#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <string>
#include "TonePlayer.h"
#include "DE1SoCfpga.h"
using namespace std;

static const unsigned  int  MPCORE_PRIV_TIMER_LOAD_OFFSET  =  0xDEC600;//  Points  to  LOAD Register
static const unsigned  int  MPCORE_PRIV_TIMER_COUNTER_OFFSET  =  0xDEC604;//  Points  to COUNTER Register
static const  unsigned  int  MPCORE_PRIV_TIMER_CONTROL_OFFSET  =  0xDEC608;//  Points  to CONTROL Register
static const  unsigned  int  MPCORE_PRIV_TIMER_INTERRUPT_OFFSET  =  0xDEC60C;//  Points  to INTERRUPT Register
unsigned int BASE_ADDR_JP1PORT = 0x60;           // Points to JP1 Port Register
unsigned int DIR_REGISTER_JP1PORT = 0x64;        // Points to JP1 Direction Register

TonePlayer::TonePlayer()
{
  playTone();
}

TonePlayer::~TonePlayer()
{

}

void TonePlayer::playTone()
{
  cout << "Program Starting...!" << endl;
  int counter= 227272;
  RegisterWrite(MPCORE_PRIV_TIMER_LOAD_OFFSET, counter);
  RegisterWrite(MPCORE_PRIV_TIMER_CONTROL_OFFSET, 3);
  cout << "set up timer!" << endl;
  //*DIR_REGISTER_JP1PORT = 0;
  //* (volatile unsigned int *)(DIR_REGISTER_JP1PORT) = 0;
  //RegisterWrite(DIR_REGISTER_JP1PORT, 0);
  RegisterWrite(DIR_REGISTER_JP1PORT, 0);
  cout << "BASE: " << RegisterRead(BASE_ADDR_JP1PORT) << endl;
  cout << "DIR: " << RegisterRead(DIR_REGISTER_JP1PORT) << endl;
  cout << "Possibly successfully registered pins" << endl;
  int writeValue=0;
  while(1)
  {
     if (RegisterRead(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET) != 0)
     {
       RegisterWrite(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET, 1);
        //*DIR_REGISTER_JP1PORT += 1;
       int currValue = RegisterRead(DIR_REGISTER_JP1PORT);
       cout << currValue << endl;
       RegisterWrite(DIR_REGISTER_JP1PORT, writeValue);
       writeValue+=1;
     }
     // else {
     //   RegisterWrite(BASE_ADDR_JP1PORT, 0);
     // }
  }
}
