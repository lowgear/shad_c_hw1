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


int main(int32_t argc, char *argv[]) {
    if (argc < 4) {
        printf(INVALID_ARGUMENT_NUMBER_MESSAGE, argc - 1);
        return 1;
    }

    int32_t fromBase;
    int32_t toBase;

#define try_parse_int_arg(id, target) { \
    if (!TryParseInt(argv[(id)], 10, &(target))) { \
        printf(INVALID_INTEGER_ARGUMENT_MESSAGE, (id), argv[(id)]); \
        return 1; \
    } \
}

    try_parse_int_arg(1, fromBase);
    try_parse_int_arg(2, toBase);

#undef try_parse_int_arg
    char *const number = argv[3];

    if (!IsCorrectNumberOfBase(number, fromBase)) {
        printf(NAN_OR_WRONG_BASE_MESSAGE, number, fromBase);
        return 1;
    }

    char * inNewBase = ConvertBase(number, fromBase, toBase);

    printf("%s\n", inNewBase);

    free(inNewBase);
}
