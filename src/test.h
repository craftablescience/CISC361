#pragma once

#include <stdarg.h>
#include <stdbool.h>

#define test(name) static bool name(bool zxcvb_helper_failed_expected)

#define assert_true(expr)                                                             \
    do {                                                                              \
        if (!(expr)) {                                                                \
            printf("Line %d: asserted %s to be true, was false!\n", __LINE__, #expr); \
            return false;                                                             \
        }                                                                             \
    } while (0)

#define assert_false(expr)                                                            \
    do {                                                                              \
        if (expr) {                                                                   \
            printf("Line %d: asserted %s to be false, was true!\n", __LINE__, #expr); \
            return false;                                                             \
        }                                                                             \
    } while (0)

#define assert_eq(lhs, rhs)                                                      \
    do {                                                                         \
        if ((lhs) != (rhs)) {                                                    \
            printf("Line %d: asserted %s to equal %s!\n", __LINE__, #lhs, #rhs); \
            return false;                                                        \
        }                                                                        \
    } while (0)

#define assert_neq(lhs, rhs)                                                         \
    do {                                                                             \
        if ((lhs) == (rhs)) {                                                        \
            printf("Line %d: asserted %s to NOT equal %s!\n", __LINE__, #lhs, #rhs); \
            return false;                                                            \
        }                                                                            \
    } while (0)

#define expect_true(expr)                                                             \
    do {                                                                              \
        if (!(expr)) {                                                                \
            printf("Line %d: expected %s to be true, was false!\n", __LINE__, #expr); \
            zxcvb_helper_failed_expected = false;                                     \
        }                                                                             \
    } while (0)

#define expect_false(expr)                                                            \
    do {                                                                              \
        if (expr) {                                                                   \
            printf("Line %d: expected %s to be false, was true!\n", __LINE__, #expr); \
            zxcvb_helper_failed_expected = false;                                     \
        }                                                                             \
    } while (0)

#define expect_eq(lhs, rhs)                                                      \
    do {                                                                         \
        if ((lhs) != (rhs)) {                                                    \
            printf("Line %d: expected %s to equal %s!\n", __LINE__, #lhs, #rhs); \
            zxcvb_helper_failed_expected = false;                                \
        }                                                                        \
    } while (0)

#define expect_neq(lhs, rhs)                                                         \
    do {                                                                             \
        if ((lhs) == (rhs)) {                                                        \
            printf("Line %d: expected %s to NOT equal %s!\n", __LINE__, #lhs, #rhs); \
            zxcvb_helper_failed_expected = false;                                    \
        }                                                                            \
    } while (0)

#define test_end() return zxcvb_helper_failed_expected

#define test_run(...)                                       \
    static void test_run_internal(bool(*test)(bool), ...) { \
        int total = 0;                                      \
        int passed = 0;                                     \
        va_list args;                                       \
        va_start(args, test);                               \
        while (test) {                                      \
            ++total;                                        \
            if ((*test)(true)) {                            \
                ++passed;                                   \
            }                                               \
            test = va_arg(args, bool(*)(bool));             \
        }                                                   \
        va_end(args);                                       \
        printf("Passed %d/%d tests!\n", passed, total);     \
    }                                                       \
    int main() {                                            \
        test_run_internal(__VA_ARGS__, NULL);               \
    }
