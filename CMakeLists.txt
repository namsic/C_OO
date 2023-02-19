cmake_minimum_required(VERSION 3.25)

project(NamsiClang)

include_directories(include)

add_custom_target(test
COMMENT "Run test"
DEPENDS collection-test.out
COMMAND ./collection-test.out
COMMAND rm ./collection-test.out
)

add_executable(collection-test.out EXCLUDE_FROM_ALL
test/collection-test.c
src/test_util.c
src/collection/list.c
)