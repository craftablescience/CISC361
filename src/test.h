#pragma once

#define test_begin()                       \
    int main() {                           \
        int zxcvb_helper_failed_tests = 0; \
        int zxcvb_helper_total_tests = 0;

#define test_end()                                                \
        printf(                                                   \
            "Passed %d / %d tests.",                              \
            zxcvb_helper_total_tests - zxcvb_helper_failed_tests, \
            zxcvb_helper_total_tests                              \
        );                                                        \
    }

#define test_group(name) // Empty, use this to group test blocks

#define expect_true(expr)                                            \
    do {                                                             \
        ++zxcvb_helper_total_tests;                                  \
        if (!(expr)) {                                               \
            ++zxcvb_helper_failed_tests;                             \
            printf("Expected \"%s\" to be true, was false!", #expr); \
        }                                                            \
    } while (0)

#define expect_false(expr)                                           \
    do {                                                             \
        ++zxcvb_helper_total_tests;                                  \
        if (expr) {                                                  \
            ++zxcvb_helper_failed_tests;                             \
            printf("Expected \"%s\" to be false, was true!", #expr); \
        }                                                            \
    } while (0)
