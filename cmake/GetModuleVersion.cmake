# Get module version from git tags
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS ${PROJECT_SOURCE_DIR}/.git)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --match "v[0-9]*" --abbrev=9 --tags HEAD
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_VARIABLE DESCRIBE_BUILD
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(NOT "${DESCRIBE_BUILD}" STREQUAL "")
        string(REPLACE "-" "." DESCRIBE_BUILD ${DESCRIBE_BUILD})
        string(REGEX REPLACE "^v" "" VERSION_FULL ${DESCRIBE_BUILD})
    else()
        set(VERSION_FULL "0.0.0")
    endif()
else()
    set(VERSION_FULL "0.0.0")
endif()

if("${VERSION_FULL}" MATCHES "^(([0-9]+)\\.([0-9]+)(\\.([0-9]+)?)?(\\.([0-9]+)?)?)(\\.([0-9a-z]*)?)?$")
    set(PROJECT_VERSION ${CMAKE_MATCH_1})
    set(PROJECT_VERSION_MAJOR ${CMAKE_MATCH_2})
    set(PROJECT_VERSION_MINOR ${CMAKE_MATCH_3})
    if ("${CMAKE_MATCH_5}" STREQUAL "")
        set(PROJECT_VERSION_PATCH 0)
    else()
        set(PROJECT_VERSION_PATCH ${CMAKE_MATCH_5})
    endif()

    if ("${CMAKE_MATCH_7}" STREQUAL "")
        set(PROJECT_VERSION_TWEAK 0)
    else()
        set(PROJECT_VERSION_TWEAK ${CMAKE_MATCH_7})
    endif() 
endif()

message("${PROJECT_NAME} version full  [${VERSION_FULL}]")
message("${PROJECT_NAME} version short [${PROJECT_VERSION}]")
message("${PROJECT_NAME} version major [${PROJECT_VERSION_MAJOR}]")
message("${PROJECT_NAME} version minor [${PROJECT_VERSION_MINOR}]")
message("${PROJECT_NAME} version patch [${PROJECT_VERSION_PATCH}]")
message("${PROJECT_NAME} version tweak [${PROJECT_VERSION_TWEAK}]")
