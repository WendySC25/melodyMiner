#include "third_party/unity/src/unity.h"

void setUp(void) {
   
}

void tearDown(void) {
    
}

void testQueryTitle(void) {
    const char* input = "title[love]"; 
    const char* expected = "SELECT * FROM rolas r WHERE (r.title LIKE '%love%')";
    const char* resultado = processQuery(input);
    TEST_ASSERT_EQUAL_STRING(expected, resultado);

    input = "title[love|happy]";
    expected = "SELECT * FROM rolas r WHERE (r.title LIKE '%love%' OR r.title LIKE '%happy%')";
    const char* resultado = processQuery(input);
    TEST_ASSERT_EQUAL_STRING(expected, resultado);

    input = "title[love&happy]";
    expected = "SELECT * FROM rolas r WHERE (r.title LIKE '%love%' AND r.title LIKE '%happy%')";
    const char* resultado = processQuery(input);
    TEST_ASSERT_EQUAL_STRING(expected, resultado);

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testQueryTitle);
    return UNITY_END();
}
