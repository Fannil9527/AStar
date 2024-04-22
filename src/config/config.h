#pragma once
#ifndef _CONFIG_H_
#define _CONFIG_H_

constexpr auto WIDTH = 1200;    // Windows width
constexpr auto HEIGHT = 1000;   // Windows heigth, in C will use #define HEIGTH 1000

constexpr auto LEN = 20;    // Grand length
constexpr auto XLEN = 28;   // Grand diagnal length

constexpr auto ROWS = 40;   // Map rows
constexpr auto COLS = 50;   // Map columns

constexpr auto ORIX = 100;  // distance between map and windows in x direction
constexpr auto ORIY = 100;  // distance between map and windows in y direction

constexpr auto DELAYTIME_SEARCH = 3;    // Search distance
constexpr auto DELAYTIME_RESULT = 20;   // Result path draw distance

#endif