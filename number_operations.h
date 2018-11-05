#pragma once

#include <inttypes.h>
#include <stdbool.h>


bool TryCharToDigit(char c, int32_t base, int32_t *digit);

int32_t CharToDigit(char c);

char DigitToChar(int32_t d);

bool TryParseInt(char const *str, int32_t base, int32_t *result);

bool IsCorrectNumberOfBase(char const *number, int32_t base);

bool IsZero(char const *number);

void Divide(char *number, int32_t divider, int32_t base, int32_t *remainder);

char *ConvertBase(char * number, int32_t fromBase, int32_t toBase);
