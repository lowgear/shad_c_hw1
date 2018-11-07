#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>

#include "number_operations.h"


char const *const INVALID_ARGUMENT_NUMBER_MESSAGE =
        "There should be 3 arguments, but %d found\n";

char const *const INVALID_INTEGER_ARGUMENT_MESSAGE =
        "Argument <%d> should be decimal number but was \"%s\"\n";

char const *const NAN_OR_WRONG_BASE_MESSAGE =
        "<%s> is not a valid number of base %d\n";

char const *const MISSING_PLACE_AFTER_POINT_MESSAGE =
        "There should be fifth argument which specifies number"
        "of digit after float point, but it was not found";


#define ERROR(...) do { \
    printf(__VA_ARGS__); \
    return 0; \
} while(0);


#define try_parse_int_arg(id, target) do { \
    if (!TryParseInt(argv[(id)], 10, &(target))) { \
        ERROR(INVALID_INTEGER_ARGUMENT_MESSAGE, (id), argv[(id)]) \
    } \
} while (0);


int main(int32_t argc, char *argv[]) {
    if (argc < 4)
        ERROR(INVALID_ARGUMENT_NUMBER_MESSAGE, argc - 1)

    int32_t fromBase;
    int32_t toBase;

    try_parse_int_arg(1, fromBase);
    try_parse_int_arg(2, toBase);

    char *const number = argv[3];

    bool isFraction;
    if (!IsCorrectNumberOfBase(number, fromBase, &isFraction)) {
        printf(NAN_OR_WRONG_BASE_MESSAGE, number, fromBase);
        return 1;
    }

    char *inNewBase;

    if (isFraction) {
        if (argc < 5)
            ERROR(MISSING_PLACE_AFTER_POINT_MESSAGE);
        int32_t digitsAfterPoint;
        try_parse_int_arg(4, digitsAfterPoint);

        inNewBase = ConvertBaseFractional(number, fromBase, toBase, digitsAfterPoint);
    } else {
        inNewBase = ConvertIntegerPart(number, fromBase, toBase);
    }

    printf("%s\n", inNewBase);

    free(inNewBase);
}

#undef try_parse_int_arg
