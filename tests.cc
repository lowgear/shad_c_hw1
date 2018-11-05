#include <stdio.h>
#include <cstring>

extern "C" {
#include "number_operations.h"
#include "utils.h"
#include "str_ops.h"
}


//#define TEST(fixture, test) \
//void fixture##_##test##_check(); \
//void fixture##_##test() { \
//    printf("%s_%s testing: ", #fixture, #test); \
//    try { \
//        fixture##_##test##_check(); \
//    } \
//    catch (...) { \
//        printf("FAIL\n"); \
//        return; \
//    } \
//    printf("OK\n"); \
//} \
//void fixture##_##test##_check()
//
//#define RUN_TEST(fixture, test) fixture##_##test();

#define ASSERT_TRUE(v) \
if (!(v)) throw 1;

#define ASSERT_FALSE(v) \
if ((v)) throw 1;

#define ASSERT_EQUAL(a, b) \
if ((a) != (b)) throw 1;

#define ASSERT_NOT_EQUAL(a, b) \
if ((a) == (b)) throw 1;

void Dummy() {}

void (*TestsEntryPoint)() = Dummy;

#define TEST(name) \
void name##_test(); \
\
struct name##_class { \
    static void (*next)(); \
\
    static void Run() { \
        name##_test(); \
        next(); \
    } \
\
    name##_class() { \
        next = TestsEntryPoint; \
        TestsEntryPoint = name##_class::Run; \
    } \
}; \
\
void (*name##_class::next)() = nullptr; \
name##_class static_instance_##name; \
\
void name##_check(); \
void name##_test() { \
    printf("%s testing: ", #name); \
    try { \
        name##_check(); \
    } \
    catch (...) { \
        printf("FAIL\n"); \
        return; \
    } \
    printf("OK\n"); \
} \
void name##_check()

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

int main() {
    TestsEntryPoint();
    return 0;
}