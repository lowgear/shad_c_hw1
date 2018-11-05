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
    printf("%-70s: ", #name); \
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

int main() {
    TestsEntryPoint();
}
