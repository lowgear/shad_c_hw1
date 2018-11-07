#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

#include "number_operations.h"
#include "utils.h"
#include "str_ops.h"


bool TryCharToDigit(char c, int32_t base, int32_t *digit) {
    int32_t res;
    if ('0' <= c && c <= '9')
        res = c - '0';
    else if ('a' <= c && c <= 'z')
        res = c - 'a' + 10;
    else if ('A' <= c && c <= 'Z')
        res = c - 'A' + 10;
    else
        return false;

    if (res >= base)
        return false;

    if (digit != NULL)
        *digit = res;
    return true;
}

int32_t CharToDigit(char c) {
    int32_t res;
    TryCharToDigit(c, 100, &res);
    return res;
}

char DigitToChar(int32_t d) {
    if (d < 10)
        return (char) ('0' + d);
    return (char) ('A' + (d - 10));
}

bool TryParseInt(char const *str, int32_t base, int32_t *result) {
    int32_t res = 0;
    bool isNegative = *str == '-';
    bool isSigned = isNegative || *str == '+';
    if (isSigned)
        ++str;
    for (char const *cPtr = str; *cPtr; ++cPtr) {
        int32_t digit;
        if (!TryCharToDigit(*cPtr, base, &digit))
            return false;
        res = res * base + digit;
    }

    if (result != NULL)
        *result = res * (isNegative ? -1 : 1);
    return true;
}

bool IsCorrectNumberOfBase(char const *number, int32_t base, bool *isFraction) {
    if (number[0] == '-' || number[0] == '+')
        ++number;
    bool isFrac = false;
    char const *c = number;
    for (; *c; ++c) {
        if (*c == '.') {
            isFrac = true;
            ++c;
        }
        if (!TryCharToDigit(*c, base, NULL)) {
            return false;
        }
    }
    if (isFrac)
        for (; *c; ++c) {
            if (!TryCharToDigit(*c, base, NULL)) {
                return false;
            }
        }

    if (isFraction != NULL)
        *isFraction = isFrac;
    return true;
}

bool IsZero(char const *number) {
    for (char const *c = (*number == '+' || *number == '-'
                          ? number + 1
                          : number);
         *c; ++c) {
        if (*c != '0')
            return false;
    }
    return true;
}

void Divide(char *number, int32_t divider, int32_t base, int32_t *remaining) {
    int32_t r = 0;
    bool isNegative = *number == '-';
    bool isSigned = isNegative || *number == '+';
    if (isSigned)
        ++number;
    for (char *c = number; *c; ++c) {
        int32_t d = CharToDigit(*c);
        r = r * base + d;
        *c = DigitToChar(r / divider);
        r %= divider;
    }

    if (remaining != NULL)
        *remaining = r * (isNegative ? -1 : 1);
}

void Multiply(char *number, int32_t multiplier, int32_t base, int32_t *overflow) {
    const size_t len = strlen(number);

    int32_t over = 0;
    for (int32_t i = len - 1; i >= 0; --i) {
        int32_t d = CharToDigit(number[i]);
        over = over + d * multiplier;
        number[i] = DigitToChar(over % base);
        over /= base;
    }

    if (overflow != NULL)
        *overflow = over;
}

char *ConvertIntegerPart(char *number, int32_t fromBase, int32_t toBase) {
    const int32_t MAX_NUM_SIZE = 600;
    char *res = malloc(MAX_NUM_SIZE * sizeof(char));
    res[MAX_NUM_SIZE - 1] = '\0';

    if (IsZero(number)) {
        res[0] = 0;
        res[1] = '\0';
        return res;
    }

    bool isNegative = *number == '-';
    bool isSigned = isNegative || *number == '+';
    if (isSigned) {
        res[0] = number[0];
        ++number;
    }

    size_t i;
    for (i = 0; !IsZero(number); ++i) {
        int32_t remaining;
        Divide(number, toBase, fromBase, &remaining);
        res[i] = DigitToChar(remaining);
    }
    if (isSigned) {
        res[i++] = number[-1];
    }
    res[i] = '\0';

    ReverseStr(res);
    return res;
}

char *GetPointPtr(char *number) {
    while (*number && *number != '.')
        ++number;
    return number;
}

char *ConvertFractionalPart(char *fractional, int32_t fromBase, int32_t toBase, int32_t digitsAfterPoint) {
    char *result = malloc(sizeof(char) * (digitsAfterPoint + 1));

    result[digitsAfterPoint] = '\0';
    for (size_t i = 0; i < digitsAfterPoint; ++i) {
        int32_t overflow;
        Multiply(fractional, toBase, fromBase, &overflow);
        result[i] = DigitToChar(overflow);
    }

    return result;
}

char *ConvertBaseFractional(char *number, int32_t fromBase, int32_t toBase, int32_t digitsAfterPoint) {
    char *pointPtr = GetPointPtr(number);

    *pointPtr = '\0';

    char *integerPartConverted = ConvertIntegerPart(number, fromBase, toBase);

    char *fractionalPartConverted = ConvertFractionalPart(pointPtr + 1, fromBase, toBase, digitsAfterPoint);

    const size_t integerLen = strlen(integerPartConverted);
    const size_t fractionalLen = strlen(fractionalPartConverted);
    char *result = malloc(
            sizeof(char) *
            (integerLen
             + fractionalLen)
            + 2);

    strcpy(result, integerPartConverted);
    result[integerLen] = '.';
    strcpy(result + integerLen + 1, fractionalPartConverted);

    free(integerPartConverted);
    free(fractionalPartConverted);

    return result;
}
