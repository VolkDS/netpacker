### CppUTest ###
find_package(CppUTest REQUIRED)

add_executable(test_get test_get_main.cpp test_get_init.cpp)
target_include_directories(test_get PRIVATE ${CPPUTEST_INCLUDE_DIR})
target_link_libraries(test_get netpacker ${CPPUTEST_LIBRARY})
add_test(NAME get_test COMMAND test_get)
