/*
 * C implementation of hexdump main function
 * CSF Assignment 2
 * Matthew Liu
 * mliu78@jhu.edu
 */

#include "hexfuncs.h" // this is the only header file which may be included!
#include <stdio.h>

/*
 * A helper function that writes the first part of the output line.
 *
 * Parameters:
 *   count - how many lines in the program is at.
 */
void write_beginning(int count)
{
  char location[16];
  hex_format_offset(count, location); // Line memory number.
  hex_write_string(location);
}

/*
 * A helper function that writes the third part of the output line.
 *
 * Parameters:
 *   toInsert - the input read from hex_read
 */
void write_end(char *toInsert)
{
  hex_write_string(" ");
  hex_write_string(toInsert);
  hex_write_string("\n\0");
}

/*
 * A helper function that writes the second part of the output line.
 *
 * Parameters:
 *   toInsert - the input read from hex_read
 *   n - the amount of characters read from hex_read
 */
void write_mid(char *toInsert, int n)
{
  char hexInsert[3];
  for (int i = 0; i < 16; i++) // Writes out all char to hex bytes from the read string.
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
}

int main(void)
{
  char toInsert[17];
  long count = 0;
  int n = hex_read(toInsert);
  while (n > 0) // While there are characters to be read, continue.
  {
    write_beginning(count);
    char mid1[4] = ": ";
    hex_write_string(mid1);
    write_mid(toInsert, n);
    write_end(toInsert);
    count += 16; // Line memory number increases by 16 every time.
    n = hex_read(toInsert);
  }
  return 0;
}
