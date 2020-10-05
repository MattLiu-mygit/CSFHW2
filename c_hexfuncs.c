/*
 * C implementation of hexdump functions
 * CSF Assignment 2
 * Matthew Liu
 * mliu78@jhu.edu
 */

#include <unistd.h> // this is the only system header file you may include!
#include "hexfuncs.h"

/*
 * Read up to 16 bytes from standard input into data_buf.
 * Returns the number of characters read.
 *
 * Parameters:
 *   data_buf - The array to which we put the 16 bytes read from stdin.
 *
 * Returns:
 *   count - a long that is the amount of bytes read in.
 */
long hex_read(char data_buf[])
{
  int count = 0;
  int n = read(STDIN_FILENO, &data_buf[count], 1);
  count += n;
  while (n != 0 && count < 16)
  {
    n = read(STDIN_FILENO, &data_buf[count], 1);
    if (n != 0)
    {
      count++;
    };
  }
  data_buf[count] = '\0';
  return count;
}

/*
 * Write given nul-terminated string to standard output.
 *
 * Parameters:
 *   s - The array to which we ouput characters from.
 */
void hex_write_string(const char s[])
{
  int count = 0;
  while (s[count] != '\0')
  {
    count++;
  }
  int i = write(STDOUT_FILENO, s, count);
  if (i < 0)
  {
    i++;
  }
}

/*
 * Format a long value as an offset string consisting of exactly 8
 * hex digits.  The formatted offset is stored in sbuf, which must
 * have enough room for a string of length 8.
 *
 * Parameters:
 *   offset - The long from which we convert to the offset hex.
 *   sbuf - The array to which we put the offset hex.
 */
void hex_format_offset(long offset, char sbuf[])
{
  for (int i = 7; i >= 0; i--)
  {
    int toConvert = offset % 16;
    if (toConvert >= 0 && toConvert < 10)
    {
      sbuf[i] = 48 + toConvert;
    }
    else
    {
      sbuf[i] = 87 + toConvert;
    }
    offset = offset / 16;
  }
  sbuf[8] = '\0';
}

/*
 * A helper function that checks and makes an inputed inputed value positive.
 *
 * Parameters:
 *   in - the value we want to check and make positive.
 */
int make_positive(int in)
{
  if (in < 0)
  {
    in += 16;
  }
  return in;
}

/*
 * A helper function that converts an inputed value to its corresponding ascii character
 *
 * Parameters:
 *   val - the value we want to convert.
 */
char convert_to_ascii(int val)
{
  if (val >= 10)
  {
    val = val + 87;
  }
  else
  {
    val = val + 48;
  }
  return val;
}

/*
 * Format a byte value (in the range 0-255) as string consisting
 * of two hex digits.  The string is stored in sbuf.
 *
 * Parameters:
 *   byteval - The long from which we convert to hex.
 *   sbuf - The array to which we put the offset hex.
 */
void hex_format_byte_as_hex(long byteval, char sbuf[])
{
  int ones = byteval & 15;
  int tens = byteval >> 4;
  ones = make_positive(ones);
  tens = make_positive(tens);
  char first = '0';
  char second = '0';
  first = convert_to_ascii(tens);
  second = convert_to_ascii(ones);
  sbuf[0] = first;
  sbuf[1] = second;
  sbuf[2] = '\0';
}

/*
 * Convert a byte value (in the range 0-255) to a printable character
 * value.  If byteval is already a printable character, it is returned
 * unmodified.  If byteval is not a printable character, then the
 * ASCII code for '.' should be returned.
 *
 * Parameters:
 *   byteval - The byte value.
 *
 * Returns:
 *   returns 46 or byteval depending on ascii representation of the value.
 */
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
