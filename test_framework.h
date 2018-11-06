int TotalTests = 0;
int PassedTests = 0;

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
    printf("%-74s: ", #name); \
    ++TotalTests; \
    try { \
        name##_check(); \
    } \
    catch (...) { \
        printf("%4s\n", "FAIL"); \
        return; \
    } \
    printf("%4s\n", "OK"); \
    ++PassedTests; \
} \
void name##_check()

int main() {
#define PRINT_HOR_LINE \
    for (size_t i = 0; i < 80; ++i)\
        printf("="); \
    printf("\n");

    PRINT_HOR_LINE
    TestsEntryPoint();
    PRINT_HOR_LINE

    printf("Passed %d/%d: ",
           PassedTests,
           TotalTests);
    if (PassedTests == TotalTests)
        printf("OK");
    else
        printf("FAIL");

    printf("\n");
}

#define ASSERT_TRUE(v) \
if (!(v)) throw 1;

#define ASSERT_FALSE(v) \
if ((v)) throw 1;

#define ASSERT_EQUAL(a, b) \
if ((a) != (b)) throw 1;

#define ASSERT_NOT_EQUAL(a, b) \
if ((a) == (b)) throw 1;
