/*
  TinyCircuits Flash Memory TinyShield Example Sketch
  
  This is an example of how to write to and read data from the Winbond W25Q80DV
  Flash Memory chip using the SPIFlash library. Whole page write functions are
  not used. This example will specifically be using the writeByte/readByte
  functions. Documentation on functions for other data types can be found on
  the library's Github page.

  SPIFlash is authored by Marzogh: https://github.com/Marzogh/SPIFlash

  Written 19 January 2017
  By Lilith Freed
  Modified 07 January 2019
  By Hunter Hykes

  https://TinyCircuits.com
*/

#include <SPIFlash.h>

// Decide what Serial port to use!
#ifdef ARDUINO_ARCH_SAMD
  #define SerialMonitor SerialUSB // Our TinyScreen+ is an SAMD board.
#else
  #define SerialMonitor Serial
#endif

const int flashCS = 5; // The chip/slave select pin is pin 5.

SPIFlash flash(flashCS); // The SPIFlash object for the chip. Passed the chip select pin in the constructor.
uint16_t page; // The page to be written to. (Page value MUST be type uint16_t)
uint8_t offset; // The specific location on the page. (Offset value MUST be type uint8_t)
uint32_t address; // The specific address in memory to be written to. (Address value MUST be type uint32_t)
const bool errorCheck = true; // A boolean parameter used to check for writing errors. Turned on by default.
const bool fastRead = false; // A boolean parameter used to implement a fast read function. Defaults to false.

void setup() {
  SerialMonitor.begin(115200);
  while(!SerialMonitor); // This will ensure the serial monitor is OPEN before writing to it on TinyScreen+.
  
  SerialMonitor.println("Initializing Flash Memory...");
  SerialMonitor.println();
  pinMode(flashCS, OUTPUT); // Ensure chip select pin is an output. This line is currently REQUIRED for proper operation.
  flash.begin(); // Boots the flash memory
  SerialMonitor.println(); 

  page = random(0, 4095); // The W25Q80DV has 4,096 writeable pages, referenced as 0-4095 in this library.
  offset = random(0, 255); // There are 256 individually addressable bytes per page, referenced 0-255.
  address = ((page+1) * 255) - (255 - offset); // Calculates the proper address given the page and offset.
  /* Writing/Reading a byte */
  SerialMonitor.println("Using writeByte...");
  uint8_t testByte = 8; // Byte data to be written to flash memory
  flash.eraseSector(address); // Must erase memory before writing per datasheet.
  // writeByte(address, testByte, errorCheck) - returns true if successful
  // address: int 0-(4095*255)
  // testByte: uint8_t or byte type data
  // errorCheck: bool
  if(flash.writeByte(address, testByte, errorCheck)) { 
    SerialMonitor.println("Write successful!");
  }
  else {
    SerialMonitor.println("Write failed!");
  }
  SerialMonitor.println("Using readByte...");
  char printBuffer[50]; // for formatting the random values, using sprintf
  sprintf(printBuffer, "The byte on page %d at position %d is: ", page, offset);
  SerialMonitor.print(printBuffer);
  // readByte(address, fastRead)
  SerialMonitor.println(flash.readByte(address, fastRead)); // This should read 8 on the serial monitor.

}

void loop() {
  // Code that runs repeatedly goes here.
}

