add_executable( collection.list.test collection/list.c test-util.c )
target_link_libraries( collection.list.test ncl-list )
add_test( list-interface collection.list.test )

add_executable( collection.map.test collection/map.c test-util.c )
target_link_libraries( collection.map.test ncl-map )
add_test( map-interface collection.map.test )
