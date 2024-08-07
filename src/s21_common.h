

// s21_common.h

#ifndef S21_COMMON_H_
#define S21_COMMON_H_

#include <iostream>
#include <algorithm>  // для std::copy, std::move, std::swap
#include <utility>    // для std::exchange
#include <functional> // printMap
#include <initializer_list>


// Цветовые макросы для печати
#define VALUE_COLOR "\033[01;38;05;232;48;05;214m"
#define RED_ALERT_COLOR "\033[0;91m"
#define FAKENODE_COLOR "\033[03;38;05;238m"
#define NORMAL_COLOR "\x1B[0m"

#define RED_ALERT \
  RED_ALERT_COLOR       \
  "\n >> Error: " NORMAL_COLOR
// вывод на экран красной надписи ERROR для
// вспомогательной функции определения
// входных данных на валидность


// Макрос для упрощения печати функции print
#define PRINT(var) print(var, #var)

#ifdef __APPLE__
using std::exchange;
#endif

#ifdef __linux__
#define exchange __exchange
using std::__exchange;
#endif

// Используемые стандартные функции
using std::cout, std::endl, std::copy, std::move, std::swap;

#endif  // S21_COMMON_H_