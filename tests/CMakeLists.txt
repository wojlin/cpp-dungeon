set(Test testLevelGenerator)

set(TestCase testRandomNumber testAnother)


set(Sources ${Test}.cpp)
add_executable(${Test} ${Sources})

foreach(tc ${TestCase})
    target_link_libraries(${Test} PUBLIC gtest_main dungeon_object)
    add_test(NAME ${tc} COMMAND ${Test} --gtest_filter=levelGeneratorSuite.${tc})
    set_tests_properties(${tc} PROPERTIES CTEST_OPTIONS "--output-on-failure")
endforeach()

add_custom_target(run_tests DEPENDS ${Tests})
