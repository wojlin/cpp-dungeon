set(Test testLevelGenerator)

#set(Sources ${Test}.cpp)
#add_executable(${Test} ${Sources})


#target_link_libraries(${Test} PUBLIC gtest_main dungeon_object)
#add_test(NAME ${Test} COMMAND ${Test})
#set_tests_properties(${Test} PROPERTIES CTEST_OPTIONS "--output-on-failure")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

set(TestCase 
testRandomNumber 
testCalculateMinimumNodeSize
testCalculateLevelSize 
testCalculateDesiredNodeSize 
testCalculateRecursionsAmount
testSplitBSP_normal
testSplitBSP_edge
testSplitBSP_fail
testCreateBSP
testVisalization
testCreateVisalizationRoom
testCreateVisalizationNode
testTraverseBSP
testCreateRoom
testCreateLevel)


set(Sources ${Test}.cpp)
add_executable(${Test} ${Sources})

foreach(tc ${TestCase})
    target_link_libraries(${Test} PUBLIC gtest_main dungeon_object)
    add_test(NAME ${tc} COMMAND ${Test} --gtest_filter=levelGeneratorSuite.${tc})
    set_tests_properties(${tc} PROPERTIES CTEST_OPTIONS "--output-on-failure" LABELS "LevelGeneration")
endforeach()



add_custom_target(run_tests DEPENDS ${Tests})
