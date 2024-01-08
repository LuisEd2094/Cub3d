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



void test_ids()
{
/// SUCCESS TESTS///
    int exit_value = system("../../../cub3D ../../../maps/valid.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/another_valid.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/valid_spaces.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/valid_f_c_spaces.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, WEXITSTATUS(exit_value));


/// ERROR TESTS///

    exit_value = system("../../../cub3D ../../../maps/invalid_multiple_ids.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));
    
    exit_value = system("../../../cub3D ../../../maps/invalid_order.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));
    
    exit_value = system("../../../cub3D ../../../maps/invalid_tabs.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));
    
    exit_value = system("../../../cub3D ../../../maps/invalid_extension.cu");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/invalid_spaces.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));
    
    exit_value = system("../../../cub3D ../../../maps/another_invalid_space.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));




    exit_value = system("../../../cub3D ../../../maps/another_invalid_extension_img.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));

    ///Commented test since I need to remove all permision////
   //exit_value = system("../../../cub3D ../../../maps/invalid_access_img.cub");
   //TEST_ASSERT_EQUAL_INT(EBADF, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/invalid_img_ext.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));


}

void test_maps(void)
{
    //Success test
    int exit_value = system("../../../cub3D ../../../maps/valid.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/another_valid.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/valid_pit_fall.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/valid_pit_fall_down.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, WEXITSTATUS(exit_value));

    //Error Test
    exit_value = system("../../../cub3D ../../../maps/invalid_long_open_down.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/invalid_long_open.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/invalid_multiple_players.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/invalid_no_map.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/invalid_no_player.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/invalid_open_complex.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/invalid_open_map.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/invalid_open_pitfall.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));

    exit_value = system("../../../cub3D ../../../maps/invalid_open_pitfall_down.cub");
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, WEXITSTATUS(exit_value));


}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_ids);
    RUN_TEST(test_maps);
    UNITY_END();
    return (0);
}