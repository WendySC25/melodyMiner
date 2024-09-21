#include "unity.h"

void setUp(void) {
    // Se llama antes de cada prueba
}

void tearDown(void) {
    // Se llama después de cada prueba
}

void test_print_hello(void){
    TEST_ASSERT_EQUAL_STRING("Hello World, DnaFoxdy!", "Hello World, DnaFoxdy!");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_print_hello);
    return UNITY_END();
}

