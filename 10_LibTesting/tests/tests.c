#include <check.h>
#include "../src/buffer.h"

START_TEST(test_buffer_init) {
    Buffer buf;
    buffer_init(&buf);
    ck_assert_int_eq(buf.capacity, INITIAL_CAPACITY);
    ck_assert_int_eq(buf.size, 0);
    ck_assert_ptr_ne(buf.data, NULL);
    buffer_free(&buf);
}
END_TEST

START_TEST(test_buffer_append) {
    Buffer buf;
    buffer_init(&buf);
    const char *data = "hello";
    int ret = buffer_append(&buf, data, 5);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(buf.size, 5);
    ck_assert_str_eq(buf.data, "hello");
    buffer_free(&buf);
}
END_TEST

Suite *buffer_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Buffer");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_buffer_init);
    tcase_add_test(tc_core, test_buffer_append);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = buffer_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
