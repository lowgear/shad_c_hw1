#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>


char const *const INVALID_ARGUMENT_NUMBER_MESSAGE =
        "There should be 3 arguments, but %d found\n";

char const *const INVALID_INTEGER_ARGUMENT_MESSAGE =
        "Argument <%d> should be decimal number but was \"%s\"\n";


bool TryCharToDigit(const char c, int32_t base, int32_t *digit) {
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

    *digit = res;
    return true;
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


int main(int32_t argc, char *argv[]) {
    if (argc < 4) {
        printf(INVALID_ARGUMENT_NUMBER_MESSAGE, argc - 1);
        return 1;
    }

    int32_t fromBase;
    int32_t toBase;

#define try_parse_int_arg(id, target) if (!TryParseInt(argv[(id)], 10, &(target))) { \
        printf(INVALID_INTEGER_ARGUMENT_MESSAGE, (id), argv[(id)]); \
        return 1; \
    }

    try_parse_int_arg(1, fromBase);
    try_parse_int_arg(2, toBase);

#undef try_parse_int_arg


}