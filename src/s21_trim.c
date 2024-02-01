#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  int flag = 0;
  int sp_flag = 0;
  int mem_error = 0;

  char *ptr_first = s21_NULL;
  char *result = s21_NULL;

  if (src == s21_NULL) sp_flag = 1;

  if ((trim_chars == s21_NULL) && !sp_flag) {
    result = malloc((s21_strlen(src) + 1) * sizeof(char));
    if (result == s21_NULL) {
      mem_error = 1;
    } else {
      s21_strcpy(result, src);
    }
    sp_flag = 1;
  }

  if (!sp_flag) {
    result = malloc(sizeof(char));
    if (result == s21_NULL) {
      mem_error = 1;
    } else {
      result[0] = '\0';
    }
  }

  if (!mem_error && !sp_flag) {
    ptr_first = (char *)&src[s21_strspn(src, trim_chars)];
    if (ptr_first[0] == '\0') {
      flag = 1;
    }
  }

  int length = 0;
  char *tmp_first = ptr_first;

  while (!flag && !mem_error && !sp_flag) {
    tmp_first = &tmp_first[s21_strcspn(tmp_first, trim_chars)];
    length = tmp_first - ptr_first;
    if (*tmp_first == '\0') {
      flag = 1;
    } else {
      tmp_first = (char *)&tmp_first[s21_strspn(tmp_first, trim_chars)];
      if (*tmp_first == '\0') {
        flag = 1;
      }
    }
  }

  tmp_first = s21_NULL;
  if (!mem_error && !sp_flag) {
    tmp_first = realloc(result, (length + 1) * sizeof(char));
    if (tmp_first == s21_NULL) {
      mem_error = 1;
    } else {
      result = tmp_first;
    }
  }

  for (int i = 0; (i < length) && !mem_error && !sp_flag; i++) {
    result[i] = ptr_first[i];
  }

  if (!mem_error && !sp_flag) result[length] = '\0';

  return result;
}
