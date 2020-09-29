// C implementation of hexdump functions

#include <unistd.h> // this is the only system header file you may include!
#include "hexfuncs.h"
#include <stdio.h>

// Read up to 16 bytes from standard input into data_buf.
// Returns the number of characters read.
long hex_read(char data_buf[])
{
  int count = 0;
  int n = read(STDIN_FILENO, &data_buf[count], 1);
  count += n;
  while (n != 0 && count < 16)
  {
    n = read(STDIN_FILENO, &data_buf[count], 1);
    count++;
  }
  return count;
}

// Write given nul-terminated string to standard output.
void hex_write_string(const char s[])
{
  int count = 0;
  while (s[count] != '\0')
  {
    count++;
  }
  int i = write(STDOUT_FILENO, s, count); //find some other way to write to out
}

// Format a long value as an offset string consisting of exactly 8
// hex digits.  The formatted offset is stored in sbuf, which must
// have enough room for a string of length 8.
void hex_format_offset(long offset, char sbuf[])
{
  for (int i = 7; i >= 0; i--)
  {
    sbuf[i] = 48 + (offset % 10);
    offset = offset / 10;
  }
  sbuf[8] = '\0';
}

// Format a byte value (in the range 0-255) as string consisting
// of two hex digits.  The string is stored in sbuf.
void hex_format_byte_as_hex(long byteval, char sbuf[])
{
  byteval = byteval & 0X7FFFFFFF;
  int tens = byteval / 16;
  int ones = byteval % 16;
  char first = '0';
  char second = '0';
  if (tens >= 10)
  {
    first = tens + 87;
  }
  else
  {
    first = tens + 48;
  }
  if (ones >= 10)
  {
    second = ones + 87;
  }
  else
  {
    second = ones + 48;
  }
  sbuf[0] = first;
  sbuf[1] = second;
  sbuf[2] = '\0';
}

// Convert a byte value (in the range 0-255) to a printable character
// value.  If byteval is already a printable character, it is returned
// unmodified.  If byteval is not a printable character, then the
// ASCII code for '.' should be returned.
long hex_to_printable(long byteval)
{
  if (byteval >= 32 && byteval <= 126)
  {
    return byteval;
  }
  else
  {
    return 46;
  }
}
