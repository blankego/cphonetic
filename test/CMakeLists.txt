set(syllist all_syllables.txt)

add_executable(test mandarin_test.cxx)
add_custom_target( copyfiles COMMENT "copying ${syllist}")
add_custom_command(TARGET copyfiles
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${syllist} ${CMAKE_CURRENT_BINARY_DIR}/${syllist}
    
    )
add_dependencies(test copyfiles)
target_link_libraries(test mandarin boost_unit_test_framework)
