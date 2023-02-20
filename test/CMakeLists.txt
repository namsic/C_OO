add_executable( list.out list.c )
target_link_libraries( list.out ncl-list )

add_test( list-interface list.out )