#ifndef DE1SOCFPGA_H
#define DE1SOCFPGA_H
using namespace std;

// Physical base address of FPGA Devices
static const unsigned int LW_BRIDGE_BASE  = 0xFF200000;  // Base offset
// Length of memory-mapped IO window
static const unsigned int LW_BRIDGE_SPAN  = 0x00DEC700;  // Address map size
// Cyclone V FPGA device addresses
static const unsigned int SW_BASE         = 0x00000040;  // Switches offset
static const unsigned int HEX3_HEX0_BASE = 0x00000020; // HEX Reg1 offset
static const unsigned int HEX5_HEX4_BASE = 0x00000030;// HEX Reg2 offset
//0xFFFEC600 -0xFF200000 = 0xDEC600


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
DE1SoCfpga();

/**
  * Close general-purpose I/O.
*/
~DE1SoCfpga();
  /**
  * Write a 4-byte value at the specified general-purpose I/O location.
  * @parem offset  Offset where device is mapped.
  * @param value   Value to be written.
  */
  void RegisterWrite(unsigned int reg_offset, int value);


  /**
  * Read a 4-byte value from the specified general-purpose I/O location.
  * @param offset  Offset where device is mapped.
  * @return        Value read.
  */
  int RegisterRead(unsigned int reg_offset);
};

#endif
