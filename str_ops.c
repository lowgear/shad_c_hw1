#include <string.h>
#include <inttypes.h>

#include "str_ops.h"
#include "utils.h"


void ReverseStr(char * str) {
    size_t len = strlen(str);
    size_t end = len / 2;
    for (int32_t i = 0; i < end; ++i) {
        size_t j = len - i - 1;
        SWAP(char, str[i], str[j])
    }
}
