#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

#include "number_operations.h"
#include "utils.h"


void ReverseStr(char * str) {
    size_t len = strlen(str);
    size_t end = len / 2;
    for (int32_t i = 0; i < end; ++i) {
        size_t j = len - i - 1;
        SWAP(char, str[i], str[j])
    }
}

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
        return (char)('0' + d);
    return (char)('A' + (d - 10));
}

bool TryParseInt(char const *str, int32_t base, int32_t *result) {
    int32_t res = 0;
    for (char const *cPtr = str; *cPtr; ++cPtr) {
        int32_t digit;
        if (!TryCharToDigit(*cPtr, base, &digit))
            return false;
        res = res * base + digit;
    }

    *result = res;
    return true;
}

bool IsCorrectNumberOfBase(char const *number, int32_t base) {
    if (number[0] == '-' || number[0] == '+')
        ++number;
    for (char const *c = number; *c; ++c) {
        if (!TryCharToDigit(*c, base, NULL)) {
            return false;
        }
    }
    return true;
}

bool IsZero(char const * number) {
    for (char const* c = number; *c; ++c) {
        if (*c != '0')
            return false;
    }
    return true;
}

void Divide(char * number, int32_t divider, int32_t base, int32_t *remaining) {
    int32_t r = 0;
    for (char* c = number; *c; ++c) {
        int32_t d = CharToDigit(*c);
        r = r * base + d;
        *c = DigitToChar(r / divider);
        r %= divider;
    }
    *remaining = r;
}

char *ConvertBase(char * number, int32_t fromBase, int32_t toBase) {
    const int32_t MAX_NUM_SIZE = 600;
    char* res = malloc(MAX_NUM_SIZE * sizeof(char));
    res[MAX_NUM_SIZE - 1] = '\0';

    if (IsZero(number)) {
        res[0] = 0;
        res[1] = '\0';
        return res;
    }

    size_t i;
    for (i = 0; !IsZero(number); ++i) {
        int32_t remaining;
        Divide(number, toBase, fromBase, &remaining);
        res[i] = DigitToChar(remaining);
    }
    res[i] = '\0';

    ReverseStr(res);
    return res;
}