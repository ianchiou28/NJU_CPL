#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_example() {
    CU_ASSERT(1 + 1 == 2);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Example Suite", NULL, NULL);
    CU_add_test(suite, "Example Test", test_example);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}