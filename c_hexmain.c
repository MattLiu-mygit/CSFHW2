/*
 * C implementation of hexdump main function
 * CSF Assignment 2
 * Matthew Liu
 * mliu78@jhu.edu
 */

#include "hexfuncs.h" // this is the only header file which may be included!
#include <stdio.h>

int main(void)
{
  char toInsert[17];
  long count = 0;
  int n = hex_read(toInsert);
  while (n > 0) // While there are characters to be read, continue.
  {
    char location[16];
    hex_format_offset(count, location); // Line memory number.
    char mid1[4] = ": ";
    hex_write_string(location);
    hex_write_string(mid1);
    char hexInsert[3];
    for (int i = 0; i < sizeof(toInsert) - 1; i++) // Writes out all char to hex bytes from the read string.
    {
      if (i < n)
      {
        hex_format_byte_as_hex(toInsert[i], hexInsert);
        toInsert[i] = hex_to_printable(toInsert[i]);
        hexInsert[2] = ' ';
        hexInsert[3] = '\0';
        hex_write_string(hexInsert);
      }
      else
      {
        hex_write_string("   ");
      }
    }
    hex_write_string(" ");
    hex_write_string(toInsert);
    hex_write_string("\n\0");
    count += 16; // Line memory number increases by 16 every time.
    n = hex_read(toInsert);
  }

  return 0;
}
