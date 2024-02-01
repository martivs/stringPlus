#include "s21_string.h"

int s21_sprintf(char *str, char *format, ...) {
  va_list ap;
  va_start(ap, format);

  struct mod token = {'\0'};

  char *str_current_adress = str;  // указатель на текущий адрес str
  *str_current_adress = '\0';
  char *form_current_adress = format;  // указатель на текущий адрес format

  int char_flag = 0;  // проверка char на '\0'
  int last_zero = 0;  // проверка на последний '\0'
  int other = 0;      // проверка на спецификатор
  int flag_entry = 0;
  int space_count = 0;
  int percent = 0;
  // ниже буфферы для разных типов
  char p_value_int[50] = {'\0'};
  char *p_value_float = s21_NULL;
  char value_float[100] = {'\0'};
  int number = 0;
  char buff_char = '\0';
  char *p_string = s21_NULL;
  char *pp_string = s21_NULL;
  unsigned delow = 0;
  double whole = 0;
  // ниже переменные для short и long флагов
  short short_check = 0;
  unsigned short uns_short_check = 0;
  long long_check = 0;
  unsigned long uns_long_check = 0;

  while (*form_current_adress) {
    if (*form_current_adress == '%' || (other)) {
      if (*(form_current_adress - 1) == '%' && *form_current_adress == '%' &&
          !percent) {
        *str_current_adress++ = *form_current_adress++;
        *str_current_adress = '\0';
        percent = 1;
        continue;
      }
      if (!other) {
        form_current_adress++;
        percent = 0;
      }

      micropars(form_current_adress,
                &other);  // проверка на то, включен ли флаг

      if (other) {
        switch (*form_current_adress)  // после прохода спецификатора other
                                       // должен быть = 0
        {
          case 'c':
            buff_char = (char)va_arg(ap, int);
            str_current_adress =
                mod_char(&buff_char, &token, str_current_adress, &flag_entry);
            if (!flag_entry) {
              *str_current_adress++ = buff_char;
              *str_current_adress = '\0';
              flag_entry = 0;
            }
            if (buff_char == '\0' && *(form_current_adress + 1)) {
              char_flag++;
            }
            if (buff_char == '\0' && *(form_current_adress + 1) == '\0') {
              last_zero = 1;
            }
            form_current_adress++;
            other = 0;
            break;
          case 'd':
            if (token.length == 'h') {
              short_check = (short int)(va_arg(ap, int));
              s21_itoa(short_check, p_value_int,
                       &token);  // переворачиваем, записываем в массив
            } else if (token.length == 'l') {
              long_check = (va_arg(ap, long));
              s21_itoa(long_check, p_value_int,
                       &token);  // переворачиваем, записываем в массив
            } else {
              number = (va_arg(ap, int));
              s21_itoa(number, p_value_int,
                       &token);  // переворачиваем, записываем в массив
            }

            str_current_adress =
                mod_integer(number, p_value_int, &token, str_current_adress,
                            &flag_entry, &space_count);
            if (!flag_entry) {
              str_current_adress = &str[s21_strlen(s21_strcat(
                  str, p_value_int))];  // перенос указателя на текущий str
              flag_entry = 0;
              *str_current_adress = '\0';
            }
            form_current_adress++;
            other = 0;
            for (s21_size_t i = 0; p_value_int[i] != '\0'; i++) {
              p_value_int[i] = '\0';
            }
            break;
          case 'i':
            if (token.length == 'h') {
              short_check = (short int)(va_arg(ap, int));
              s21_itoa(short_check, p_value_int,
                       &token);  // переворачиваем, записываем в массив
            } else if (token.length == 'l') {
              long_check = (va_arg(ap, long));
              s21_itoa(long_check, p_value_int,
                       &token);  // переворачиваем, записываем в массив
            } else {
              number = (va_arg(ap, int));
              s21_itoa(number, p_value_int,
                       &token);  // переворачиваем, записываем в массив
            }

            str_current_adress =
                mod_integer(number, p_value_int, &token, str_current_adress,
                            &flag_entry, &space_count);
            if (!flag_entry) {
              str_current_adress = &str[s21_strlen(s21_strcat(
                  str, p_value_int))];  // перенос указателя на текущий str
              flag_entry = 0;
              *str_current_adress = '\0';
            }
            form_current_adress++;
            other = 0;
            for (s21_size_t i = 0; p_value_int[i] != '\0'; i++) {
              p_value_int[i] = '\0';
            }
            break;
          case 'f':
            whole = va_arg(ap, double);
            if (token.dot && !token.accuracy) {
              whole = round(whole);
              s21_itoa_f(whole, value_float, &token);
              str_current_adress =
                  mod_float(whole, value_float, &token, str_current_adress,
                            &flag_entry, &space_count);
              *str_current_adress = '\0';
              if (!flag_entry) {
                str_current_adress = &str[s21_strlen(s21_strcat(
                    str, value_float))];  // перенос указателя на текущий str
                flag_entry = 1;
                *str_current_adress = '\0';
              }
              for (s21_size_t i = 0; value_float[i] != '\0'; i++) {
                value_float[i] = '\0';
              }
            } else {
              s21_float(whole, &p_value_float, &token);
              str_current_adress =
                  mod_float(whole, p_value_float, &token, str_current_adress,
                            &flag_entry, &space_count);
              *str_current_adress = '\0';
              if (!flag_entry) {
                str_current_adress = &str[s21_strlen(s21_strcat(
                    str, p_value_float))];  // перенос указателя на текущий str
                *str_current_adress = '\0';
                flag_entry = 1;
              }
              free(p_value_float);
            }
            flag_entry = 0;
            form_current_adress++;
            other = 0;

            break;
          case 's':
            pp_string = va_arg(ap, char *);
            p_string = (char *)malloc(
                s21_strlen(pp_string) +
                1 * sizeof(char));  // для преобразования точности
            for (s21_size_t i = 0; i < s21_strlen(pp_string); i++) {
              p_string[i] = pp_string[i];
            }
            p_string[s21_strlen(pp_string)] = '\0';
            str_current_adress =
                mod_string(p_string, &token, str_current_adress, &flag_entry);
            if (!flag_entry) {
              for (s21_size_t i = 0; i < s21_strlen(pp_string); i++)
                *str_current_adress++ = pp_string[i];
            }
            *str_current_adress = '\0';
            form_current_adress++;
            other = 0;
            break;
          case 'u':
            if (token.length == 'h') {
              uns_short_check = (va_arg(ap, int));
              s21_itoa_u(uns_short_check, p_value_int,
                         &token);  // переворачиваем, записываем в массив
            } else if (token.length == 'l') {
              uns_long_check = (va_arg(ap, long));
              s21_itoa_u(uns_long_check, p_value_int,
                         &token);  // переворачиваем, записываем в массив
            } else {
              delow = va_arg(ap, int);
              s21_itoa_u(delow, p_value_int, &token);
            }
            str_current_adress =
                mod_uns_integer(p_value_int, &token, str_current_adress,
                                &flag_entry, &space_count);
            if (!flag_entry) {
              str_current_adress = &str[s21_strlen(s21_strcat(
                  str, p_value_int))];  // перенос указателя на текущий str
              flag_entry = 0;
              *str_current_adress = '\0';
            }
            form_current_adress++;
            other = 0;
            for (s21_size_t i = 0; p_value_int[i] != '\0'; i++) {
              p_value_int[i] = '\0';
            }
            break;
          default:
            printf("S21_sprintf: error");
        }
      } else {
        form_current_adress =
            modpars(form_current_adress, &token, &other, &space_count);
      }
    } else {
      *str_current_adress++ = *form_current_adress++;
      percent = 0;
      *str_current_adress = '\0';
    }
  }
  va_end(ap);

  int finish = s21_strlen(str);
  char *tmp_finish = s21_NULL;
  for (int i = 0; i < char_flag; i++) {
    tmp_finish = &str[finish + 1];
    finish += s21_strlen(tmp_finish) + 1;
  }

  if (last_zero) finish++;

  return finish;
}