#include <stdio.h>
#include <cstring>
#include "test_framework.h"

extern "C" {
#include "number_operations.h"
#include "utils.h"
#include "str_ops.h"
}


TEST(ReverseStr_ShouldReverseOdd) {
    char original[] = "abcde";
    ReverseStr(original);

    ASSERT_TRUE(strcmp(original, "edcba") == 0)
}

TEST(ReverseStr_ShouldReverseEven) {
    char original[] = "abcd";
    ReverseStr(original);

    ASSERT_TRUE(strcmp(original, "dcba") == 0)
}

TEST(ReverseStr_ShouldWorkWithEmptyString) {
    char original[] = "";
    ReverseStr(original);

    ASSERT_TRUE(strcmp(original, "") == 0)
}
