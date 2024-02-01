#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int flag = 0;
  int mem_error = 0;
  char *result = s21_NULL;
  s21_size_t len_src = 0;
  s21_size_t len_str = 0;
  s21_size_t length = 0;

  if ((src == s21_NULL) || (str == s21_NULL) || ((int)start_index < 0) ||
      (start_index > s21_strlen(src))) {
    flag++;
  }

  if (!flag) {
    len_src = s21_strlen(src);
    len_str = s21_strlen(str);
    length = len_src + len_str;
  }

  if (!flag) {
    result = malloc((length + 1) * sizeof(char *));
    if (result == s21_NULL) {
      mem_error = 1;
    }
  }

  // src == ""
  if (!len_src && !flag && !mem_error) {
    for (s21_size_t i = 0; i < len_str; i++) {
      result[i] = str[i];
    }
    result[len_str] = '\0';
    flag++;
  }

  // str == ""
  if (!len_str && !flag && !mem_error) {
    for (s21_size_t i = 0; i < len_src; i++) {
      result[i] = src[i];
    }
    result[len_src] = '\0';
    flag++;
  }

  // str & src are not blank
  if (!flag && !mem_error) {
    s21_size_t count = 0;
    for (; count < start_index; count++) {
      result[count] = src[count];
    }
    for (s21_size_t i = 0; i < len_str; i++, count++) {
      result[count] = str[i];
    }
    for (; count < length; count++) {
      result[count] = src[count - len_str];
    }
    result[count] = '\0';
  }

  return result;
}
