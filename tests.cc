#include <stdio.h>
#include <cstring>
#include <cstdlib>
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

TEST(TryParseInt_ShouldReturnTrueOnCorrectNegativeInts) {
    ASSERT_TRUE(TryParseInt("-12345", 10, nullptr))
}

TEST(TryParseInt_ShouldGiveCorrectInts) {
    int32_t number;
    TryParseInt("12345", 10, &number);
    ASSERT_EQUAL(number, 12345)

    TryParseInt("aB", 12, &number);
    ASSERT_EQUAL(number, 131)
}

TEST(IsCorrectNumberOfBase_ShouldGiveTrueForCorrect) {
    ASSERT_TRUE(IsCorrectNumberOfBase("1234", 5))
    ASSERT_TRUE(IsCorrectNumberOfBase("1234ABcd", 14))
}

TEST(IsCorrectNumberOfBase_ShouldGiveTrueForCorrectSigned) {
    ASSERT_TRUE(IsCorrectNumberOfBase("-1234", 5))
    ASSERT_TRUE(IsCorrectNumberOfBase("+1234ABcd", 14))
}

TEST(IsCorrectNumberOfBase_ShouldGiveFalseForIncorrect) {
    ASSERT_FALSE(IsCorrectNumberOfBase("1234", 3))
    ASSERT_FALSE(IsCorrectNumberOfBase("1234ABcd", 7))
}

TEST(IsZero_ShouldReturnTrueForZero) {
    ASSERT_TRUE(IsZero("0000000"));
    ASSERT_TRUE(IsZero(""));
}

TEST(IsZero_ShouldReturnTrueForSignedZero) {
    ASSERT_TRUE(IsZero("+0000000"));
    ASSERT_TRUE(IsZero("-"));
}

TEST(IsZero_ShouldReturnFalseForNonZero) {
    ASSERT_FALSE(IsZero("0000001"));
    ASSERT_FALSE(IsZero("42"));
    ASSERT_FALSE(IsZero("A"));
}

TEST(Divide_ShouldDivideCorrectly) {
    char number[] = "123";
    int32_t remainder;
    Divide(number, 6, 10, &remainder);

    int32_t parsed;
    TryParseInt(number, 10, &parsed);
    ASSERT_EQUAL(parsed, 20)
    ASSERT_EQUAL(remainder, 3)
}

TEST(Divide_ShouldDivideNegativeCorrectly) {
    char number[] = "-123";
    int32_t remainder;

    Divide(number, 6, 10, &remainder);

    int32_t parsed;
    TryParseInt(number, 10, &parsed);
    ASSERT_EQUAL(parsed, -20)
    ASSERT_EQUAL(remainder, -3)
}

#define TEST_CASE_CONVERT_BASE(num, from, to) \
TEST(ConvertBase_ShouldConvertCorrectly_##num##_##from##_##to) { \
    char number[] = #num; \
    int32_t expected; \
    TryParseInt(number, (from), &expected); \
\
    char* converted = ConvertBase(number, (from), (to)); \
\
    int32_t actual; \
    TryParseInt(converted, (to), &actual); \
    ASSERT_EQUAL(expected, actual) \
\
    free(converted); \
}

#define TEST_CASE_CONVERT_BASE_NEGATIVE(num, from, to) \
TEST(ConvertBase_ShouldConvertNegativeCorrectly_##num##_##from##_##to) { \
    char number[] = "-" #num; \
    int32_t expected; \
    TryParseInt(number, (from), &expected); \
\
    char* converted = ConvertBase(number, (from), (to)); \
\
    int32_t actual; \
    TryParseInt(converted, (to), &actual); \
    ASSERT_EQUAL(expected, actual) \
\
    free(converted); \
}

TEST_CASE_CONVERT_BASE(123, 10, 2)
TEST_CASE_CONVERT_BASE(123, 7, 26)
TEST_CASE_CONVERT_BASE_NEGATIVE(123, 7, 26)
TEST_CASE_CONVERT_BASE_NEGATIVE(12aBc, 15, 2)

TEST(SWAP_ShouldSwap) {
    int orig_a = 13;
    int orig_b = 42;

    int a = orig_a;
    int b = orig_b;

    SWAP(int, a, b)

    ASSERT_EQUAL(orig_a, b)
    ASSERT_EQUAL(orig_b, a)
}

TEST(SWAP_ShouldNotChangeSingleVariable) {
    int orig_a = 13;

    int a = orig_a;

    SWAP(int, a, a)

    ASSERT_EQUAL(orig_a, a)
}
