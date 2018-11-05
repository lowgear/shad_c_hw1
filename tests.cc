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

TEST(TryCharToDigit_ShouldGiveCorrectDigits) {
    int32_t digit;
    TryCharToDigit('0', 36, &digit);
    ASSERT_EQUAL(digit, 0)
    TryCharToDigit('4', 36, &digit);
    ASSERT_EQUAL(digit, 4)
    TryCharToDigit('9', 36, &digit);
    ASSERT_EQUAL(digit, 9)
    TryCharToDigit('A', 36, &digit);
    ASSERT_EQUAL(digit, 10)
    TryCharToDigit('a', 36, &digit);
    ASSERT_EQUAL(digit, 10)
    TryCharToDigit('Z', 36, &digit);
    ASSERT_EQUAL(digit, 35)
}

TEST(TryCharToDigit_ShouldReturnTrueOnCorrectDigits) {
    ASSERT_TRUE(TryCharToDigit('0', 36, nullptr));
    ASSERT_TRUE(TryCharToDigit('4', 36, nullptr));
    ASSERT_TRUE(TryCharToDigit('9', 36, nullptr));
    ASSERT_TRUE(TryCharToDigit('A', 36, nullptr));
    ASSERT_TRUE(TryCharToDigit('a', 36, nullptr));
    ASSERT_TRUE(TryCharToDigit('Z', 36, nullptr));
}

TEST(TryCharToDigit_ShouldReturnFalseOnIncorrectDigits) {
    ASSERT_FALSE(TryCharToDigit('7', 7, nullptr));
}

TEST(TryCharToDigit_ShouldWorkWithNullPtrAsDigit) {
    TryCharToDigit('6', 7, nullptr);
}

TEST(CharToDigit_ShouldGiveCorrectDigits) {
    ASSERT_EQUAL(CharToDigit('0'), 0);
    ASSERT_EQUAL(CharToDigit('4'), 4);
    ASSERT_EQUAL(CharToDigit('9'), 9);
    ASSERT_EQUAL(CharToDigit('A'), 10);
    ASSERT_EQUAL(CharToDigit('a'), 10);
    ASSERT_EQUAL(CharToDigit('Z'), 35);
}

TEST(DigitToChar_ShouldGiveCorrectChars) {
    ASSERT_EQUAL(DigitToChar(0), '0');
    ASSERT_EQUAL(DigitToChar(4), '4');
    ASSERT_EQUAL(DigitToChar(9), '9');
    ASSERT_EQUAL(DigitToChar(10), 'A');
    ASSERT_EQUAL(DigitToChar(35), 'Z');
}

TEST(TryParseInt_ShouldReturnFalseOnTrash) {
    ASSERT_FALSE(TryParseInt("kek", 10, nullptr))
}

TEST(TryParseInt_ShouldReturnTrueOnCorrectInts) {
    ASSERT_TRUE(TryParseInt("12345", 10, nullptr))
}

TEST(TryParseInt_ShouldGiveCorrectInts) {
    int32_t number;
    TryParseInt("12345", 10, &number);
    ASSERT_EQUAL(number, 12345)
}
