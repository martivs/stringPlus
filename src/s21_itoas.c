#include "s21_string.h"

void s21_itoa(long long number, char *p_value_int, struct mod *p_token) {
  long sign = number;
  if (number < 0) number = -number;

  unsigned long twe = 0;
  if (number == LONG_MIN) twe = -number;

  int i = 0;

  if (number == 0) {
    if (!p_token->dot) {
      p_value_int[i++] = '0';
      p_value_int[i] = '\0';
    }
  }

  for (; number > 0; i++) {
    p_value_int[i] = number % 10 + '0';
    number /= 10;

    if (number == 0) p_value_int[i + 1] = '\0';
  }

  for (; twe > 0; i++) {
    p_value_int[i] = twe % 10 + '0';
    twe /= 10;

    if (twe == 0) p_value_int[i + 1] = '\0';
  }

  if (p_token->accuracy) {
    for (; i < p_token->accuracy; i++) {
      p_value_int[i] = '0';
      p_value_int[i + 1] = '\0';
    }
  }

  if (p_token->flag == '+' || p_token->plus) {
    p_value_int[i] = '+';
    p_value_int[i + 1] = '\0';
  }

  if (sign < 0) {
    p_value_int[i++] = '-';
    p_value_int[i] = '\0';
  }

  for (int i = 0, j = s21_strlen(p_value_int) - 1; i < j; i++, j--) {
    int var = p_value_int[j];
    p_value_int[j] = p_value_int[i];
    p_value_int[i] = var;
  }
  p_value_int[++i] = '\0';
}

void s21_itoa_u(unsigned long long number, char *p_value_uint,
                struct mod *p_token) {
  int i = 0;

  if (number == 0) {
    if (!p_token->dot) {
      p_value_uint[i++] = '0';
      p_value_uint[i] = '\0';
    }
  }

  for (; number > 0; i++) {
    p_value_uint[i] = number % 10 + '0';
    number /= 10;

    if (number == 0) p_value_uint[i + 1] = '\0';
  }

  if (p_token->accuracy) {
    for (; i < p_token->accuracy; i++) {
      p_value_uint[i] = '0';
      p_value_uint[i + 1] = '\0';
    }
  }

  for (int i = 0, j = s21_strlen(p_value_uint) - 1; i < j; i++, j--) {
    int var = p_value_uint[j];
    p_value_uint[j] = p_value_uint[i];
    p_value_uint[i] = var;
  }
  p_value_uint[++i] = '\0';
}

void s21_itoa_f(long long number, char *p_value_int, struct mod *p_token) {
  long sign = number;
  if (number < 0) number = -number;

  unsigned long twe = 0;
  if (number == LONG_MIN) twe = -number;

  int i = 0;

  if (number == 0) {
    if (!p_token->dot) {
      p_value_int[i++] = '0';
      p_value_int[i] = '\0';
    }
  }

  for (; number > 0; i++) {
    p_value_int[i] = number % 10 + '0';
    number /= 10;

    if (number == 0) p_value_int[i + 1] = '\0';
  }

  for (; twe > 0; i++) {
    p_value_int[i] = twe % 10 + '0';
    twe /= 10;

    if (twe == 0) p_value_int[i + 1] = '\0';
  }

  if (p_token->flag == '+' || p_token->plus) {
    p_value_int[i] = '+';
    p_value_int[i + 1] = '\0';
  }

  if (sign < 0) {
    p_value_int[i++] = '-';
    p_value_int[i] = '\0';
  }

  for (int i = 0, j = s21_strlen(p_value_int) - 1; i < j; i++, j--) {
    int var = p_value_int[j];
    p_value_int[j] = p_value_int[i];
    p_value_int[i] = var;
  }
  p_value_int[++i] = '\0';
}