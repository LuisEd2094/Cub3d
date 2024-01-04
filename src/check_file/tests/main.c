#include <cub3d.h>
#include "unity.h"
#include "unity_internals.h"
#include "../parse_file.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_error_val()
{

    int exit_value = system("../../../cub3D ../../../valid.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../another_valid.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, WEXITSTATUS(exit_value));
   
    exit_value = system("../../../cub3D ../../../invalid_multiple_ids.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));
    
    exit_value = system("../../../cub3D ../../../invalid_order.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));
    
    exit_value = system("../../../cub3D ../../../invalid_spaces.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));
    
    exit_value = system("../../../cub3D ../../../invalid_tabs.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));
    
    exit_value = system("../../../cub3D ../../../touch invalid_extension.cu");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));

}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_error_val);
    UNITY_END();
    return (0);
}