Arduino-fram
============

An adaption of https://github.com/ennui2342/arduino-sram for the Fujitsu MB85RS1MT FRAM IC.

Implements Stream for convenience so you get readBytes() etc. But be aware this is not the fastest way to do it because of that (setting the address for every byte transfered)

## Installation

Clone as FRAM and put in your Arduino/libraries folder

## Notes

* Due to the library implementing single byte access, writing is slower because writing must be enabled per byte.

## Usage

Use seek() to set the address before reading and writing

Example (full example located under examples/ folder):
  
    FRAM fram(FRAM_CS_PIN);
    fram.begin();
    char test [] = "hello, world";
    fram.seek(1);
    fram.write((byte *) test, sizeof test);
    char buf[100];
    fram.seek(1);
    fram.readBytes((char *) buf, sizeof buf);
    Serial.println(buf);
