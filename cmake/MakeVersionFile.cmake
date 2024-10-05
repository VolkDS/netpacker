function(create_version_file SRC_FILE DST_FILE)
    ## Find out build date #########################################################
    execute_process(
        COMMAND date "+%Y-%m-%d %T %z"
        OUTPUT_VARIABLE BUILD_DATE
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    ## Find compiler version #######################################################
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} "--version"
        OUTPUT_VARIABLE BUILD_COMPILER
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    # Only output first string
    string(REGEX REPLACE "\n.*" "" BUILD_COMPILER ${BUILD_COMPILER})

    ## Preprocessing Templates #####################################################
    configure_file(${SRC_FILE} ${DST_FILE})
endfunction()
