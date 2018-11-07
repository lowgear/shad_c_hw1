#pragma once

#include <inttypes.h>
#include <stdbool.h>


bool TryCharToDigit(char c, int32_t base, int32_t *digit);

int32_t CharToDigit(char c);

char DigitToChar(int32_t d);

bool TryParseInt(char const *str, int32_t base, int32_t *result);

bool IsCorrectNumberOfBase(char const *number, int32_t base, bool* isFraction);

bool IsZero(char const *number);

void Divide(char *number, int32_t divider, int32_t base, int32_t *remainder);

void Multiply(char *number, int32_t multiplier, int32_t base, int32_t *overflow);

char *ConvertIntegerPart(char *number, int32_t fromBase, int32_t toBase);

char *ConvertFractionalPart(char *fractional, int32_t fromBase, int32_t toBase, int32_t digitsAfterPoint);

char *ConvertBaseFractional(char *number, int32_t fromBase, int32_t toBase, int32_t digitsAfterPoint);
