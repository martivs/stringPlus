#include <string.h>

#include "s21_string.h"
void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *temp_str = (char *)str;
  char find_sym = (char)c;
  char *result_pointer = s21_NULL;
  for (s21_size_t p = 0; p < n; p++) {
    if (temp_str[p] == find_sym) {
      result_pointer = (char *)temp_str + p;
      break;
    }
  }
  return result_pointer;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  unsigned char *f_string = (unsigned char *)str1;
  unsigned char *s_string = (unsigned char *)str2;

  for (s21_size_t i = 0; i < n; i++)
    if (f_string[i] != s_string[i]) {
      result = f_string[i] - s_string[i];
      break;
    }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *ds = (unsigned char *)dest;
  unsigned char *sr = (unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    ds[i] = sr[i];
  }
  return ds;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  void *ret = dest;
  if (dest <= src || (char *)dest >= ((char *)src + n)) {
    while (n--) {
      *(char *)dest = *(char *)src;
      dest = (char *)dest + 1;
      src = (char *)src + 1;
    }
  } else {
    dest = (char *)dest + n - 1;
    src = (char *)src + n - 1;
    while (n--) {
      *(char *)dest = *(char *)src;
      dest = (char *)dest - 1;
      src = (char *)src - 1;
    }
  }
  return (ret);
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *str_in = str;
  while (n--) *str_in++ = c;
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0, j;
  while (dest[i]) i++;
  for (j = 0; src[j] != '\0' && j < n; j++) dest[i + j] = src[j];
  dest[i + j] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *res = s21_NULL;
  while (*str != c && *str) str++;
  if (*str == c) res = (char *)str;
  return res;
}

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return (*str1 - *str2) > 0    ? (*str1 - *str2) / (*str1 - *str2)
         : (*str1 - *str2) == 0 ? 0
                                : (-1) * (*str1 - *str2) / (*str1 - *str2);
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t i = 0;
  while (*str1 && (*str1 == *str2) && i < n - 1) {
    str1++;
    str2++;
    i++;
  }
  return (*str1 - *str2) > 0    ? (*str1 - *str2) / (*str1 - *str2)
         : (*str1 - *str2) == 0 ? 0
                                : (-1) * (*str1 - *str2) / (*str1 - *str2);
}