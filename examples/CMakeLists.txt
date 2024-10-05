set(EXAMPLES
    run.cpp
    run2.cpp
)

### Boost ###
#set(Boost_COMPONENTS system)
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost COMPONENTS ${Boost_COMPONENTS} REQUIRED)

### Threads ###
#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
#find_package(Threads REQUIRED)

#message(${Boost_INCLUDE_DIR})

foreach(EXAMPLE ${EXAMPLES})
    get_filename_component(EXECUTABLE ${EXAMPLE} NAME_WE)
    add_executable(${EXECUTABLE} ${EXAMPLE})
#    target_include_directories(${EXECUTABLE} PRIVATE
        #${Boost_INCLUDE_DIR}
#    )
    #target_link_libraries(${EXECUTABLE} ${Boost_LIBRARIES})
    target_link_libraries(${EXECUTABLE} netpacker)
endforeach()
