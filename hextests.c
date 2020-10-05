/*
 * Unit tests for hex functions for both C and Assembly implementations.
 * CSF Assignment 2
 * Matthew Liu
 * mliu78@jhu.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "tctest.h"
#include "hexfuncs.h"

// test fixture object
typedef struct
{
  char test_data_1[16];
  char test_data_empty[1];
  char test_data_16_chars[17];
  char test_data_zoom[100];
} TestObjs;

// setup function (to create the test fixture)
TestObjs *setup(void)
{
  TestObjs *objs = malloc(sizeof(TestObjs));
  strcpy(objs->test_data_1, "Hello, world!\n");
  strcpy(objs->test_data_empty, "");
  strcpy(objs->test_data_16_chars, "Greetings my bo");
  strcpy(objs->test_data_zoom, "https://JHUBlueJays.zoom.us/j/92836602907?pwd=S1pzTGU1QUFZZEtHb1hjdFdSTXV1QT09");
  return objs;
}

// cleanup function (to destroy the test fixture)
void cleanup(TestObjs *objs)
{
  free(objs);
}

// Prototypes for test functions
void testFormatOffset(TestObjs *objs);
void testFormatByteAsHex(TestObjs *objs);
void testHexToPrintable(TestObjs *objs);

int main(int argc, char **argv)
{
  if (argc > 1)
  {
    tctest_testname_to_execute = argv[1];
  }

  TEST_INIT();

  TEST(testFormatOffset);
  TEST(testFormatByteAsHex);
  TEST(testHexToPrintable);

  TEST_FINI();

  return 0;
}

void testFormatOffset(TestObjs *objs)
{
  (void)objs; // suppress warning about unused parameter
  char buf[16];
  hex_format_offset(0L, buf);
  ASSERT(0 == strcmp(buf, "00000000"));
  hex_format_offset(1L, buf);
  ASSERT(0 == strcmp(buf, "00000001"));
  hex_format_offset(2L, buf);
  ASSERT(0 == strcmp(buf, "00000002"));
  hex_format_offset(17L, buf);
  //printf("\nbuf is %s\n", buf);
  ASSERT(0 == strcmp(buf, "00000011"));
  hex_format_offset(4294967295L, buf);
  ASSERT(0 == strcmp(buf, "ffffffff"));
}

void testFormatByteAsHex(TestObjs *objs)
{
  char buf[16];
  hex_format_byte_as_hex(objs->test_data_1[0], buf);
  ASSERT(0 == strcmp(buf, "48"));
  memset(buf, 0, sizeof(buf));
  hex_format_byte_as_hex(objs->test_data_1[5], buf);
  printf("\nbuf is %s\n", buf);
  ASSERT(0 == strcmp(buf, "2c"));
  memset(buf, 0, sizeof(buf));
  hex_format_byte_as_hex(objs->test_data_1[6], buf);
  ASSERT(0 == strcmp(buf, "20"));
  memset(buf, 0, sizeof(buf));
  hex_format_byte_as_hex(objs->test_data_1[7], buf);
  ASSERT(0 == strcmp(buf, "77"));
  hex_format_byte_as_hex(objs->test_data_1[12], buf);
  ASSERT(0 == strcmp(buf, "21"));
  memset(buf, 0, sizeof(buf));
  hex_format_byte_as_hex(objs->test_data_1[13], buf);
  ASSERT(0 == strcmp(buf, "0a"));
  memset(buf, 0, sizeof(buf));
  hex_format_byte_as_hex(objs->test_data_1[14], buf);
  ASSERT(0 == strcmp(buf, "00"));
  memset(buf, 0, sizeof(buf));
  hex_format_byte_as_hex(objs->test_data_empty[0], buf);
  ASSERT(0 == strcmp(buf, "00"));
  memset(buf, 0, sizeof(buf));
  hex_format_byte_as_hex(255, buf);
  ASSERT(0 == strcmp(buf, "ff"));
  memset(buf, 0, sizeof(buf));
}

void testHexToPrintable(TestObjs *objs)
{
  ASSERT('H' == hex_to_printable(objs->test_data_1[0]));
  ASSERT('e' == hex_to_printable(objs->test_data_1[1]));
  ASSERT('.' == hex_to_printable(objs->test_data_1[13]));
  ASSERT('!' == hex_to_printable(objs->test_data_1[12]));
  ASSERT('.' == hex_to_printable(objs->test_data_empty[0]));
  ASSERT('.' == hex_to_printable(objs->test_data_16_chars[15]));
  ASSERT('J' == hex_to_printable(objs->test_data_zoom[15]));
  ASSERT('a' == hex_to_printable(objs->test_data_zoom[16]));
  ASSERT('9' == hex_to_printable(objs->test_data_zoom[77]));
  ASSERT('.' == hex_to_printable('\n'));
  ASSERT('.' == hex_to_printable('\0'));
  ASSERT(' ' == hex_to_printable(' '));
}
