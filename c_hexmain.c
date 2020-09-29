// C implementation of hexdump main function

#include "hexfuncs.h" // this is the only header file which may be included!
#include <stdio.h>

int main(void)
{
  char toInsert[17];
  long count = 0;
  while (hex_read(toInsert) > 0)
  {
    char location[16];
    hex_format_offset(count, location);
    char mid1[4] = ":  ";
    hex_write_string(location);
    hex_write_string(mid1);

    char hexInsert[3];
    for (int i = 0; i < sizeof(toInsert) - 1; i++)
    {
      hex_format_byte_as_hex(toInsert[i], hexInsert);
      hexInsert[2] = ' ';
      hexInsert[3] = '\0';
      hex_write_string(hexInsert);
    }
    hex_write_string(" ");
    hex_write_string(toInsert);
    hex_write_string("\n\0");
    count += 10;
  }

  return 0;
}
