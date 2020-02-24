#include <SPI.h>

#define FRAM_WREN  0b110  // Set write enable latch
#define FRAM_WRDI  0b100  // Reset write enable latch
#define FRAM_RDSR  0b101  // Read status register
#define FRAM_WRSR  0b001  // Write status register
#define FRAM_READ  0b011  // Read data from memory array beginning at selected address
#define FRAM_WRITE 0b010  // Write data to memory array beginning at selected address
#define FRAM_RDID  0b10011111  // Read device ID
#define FRAM_FSTRD 0b00001011  // Fast Read Memory Code
#define FRAM_SLEEP 0b10111001  // Sleep mode

class FRAM : public Stream
{
private:
  uint8_t cs_pin;
  uint32_t address;
  
public:
  FRAM(uint8_t);
  void begin();  
  void seek(uint32_t);

  // Print::write
  size_t write(uint8_t);

  // Stream
  int read();
  int available() { return -1; }
  void flush() {}
  int peek() { return -1; }
  
  using Print::write;
};
