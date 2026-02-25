#include "unity.h"

#include <common.h>

extern u32int test_last_alloc_size;

void test_strcmp_returns_zero_for_equal_strings(void) {
  char left[] = "kernel";
  char right[] = "kernel";

  TEST_ASSERT_EQUAL_INT(0, strcmp(left, right));
}

void test_strcmp_returns_nonzero_for_different_strings(void) {
  char left[] = "kernel";
  char right[] = "kernal";

  TEST_ASSERT_NOT_EQUAL(0, strcmp(left, right));
}

void test_strcpy_copies_source_into_destination(void) {
  char dest[16] = {0};
  char src[] = "xo";

  char *returned = strcpy(dest, src);

  TEST_ASSERT_EQUAL_PTR(dest, returned);
  TEST_ASSERT_EQUAL_STRING("xo", dest);
}

void test_strcat_appends_source_to_destination(void) {
  char dest[16] = "tic";
  char src[] = "-tac";

  char *returned = strcat(dest, src);

  TEST_ASSERT_EQUAL_PTR(dest, returned);
  TEST_ASSERT_EQUAL_STRING("tic-tac", dest);
}

void test_malloc_forwards_size_to_allocate(void) {
  test_last_alloc_size = 0;

  void *ptr = malloc(37);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL_UINT32(37, test_last_alloc_size);
}
