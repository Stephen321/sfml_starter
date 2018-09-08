# TODO: PUBLIC vs INTERFACE vs PRIVATE
# See: https://github.com/stephen321/sdl_starter


cmake_minimum_required(VERSION 3.7.2-1)
project("sfml_starter")

set(PROJECT_LIB "${PROJECT_NAME}_lib")
set(INCLUDE_DIR "include")

# local dependencies
set(DEPENDENCIES_DIR "dependencies")

# Good practice to list this instead of GLOBing. 
# https://stackoverflow.com/questions/1027247/is-it-better-to-specify-source-files-with-glob-or-each-file-individually-in-cmak
file(GLOB INCLUDE_FILES "${INCLUDE_DIR}/*.h")
file(GLOB SOURCE_FILES "src/*.cpp")

#split off main as it doesnt need to be in lib, only exe
set(SOURCE_MAIN "src/main.cpp")
# list(REMOVE_ITEM SOURCE_FILES SOURCE_MAIN)
# the above doesnt seem to work so using regex
# https://stackoverflow.com/questions/15550777/how-do-i-exclude-a-single-file-from-a-cmake-fileglob-pattern
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*${SOURCE_MAIN}$")

set(JSON_INCLUDE_DIR "${DEPENDENCIES_DIR}/json")

# since sfml 2.5 this method will no longer work https://en.sfml-dev.org/forums/index.php?topic=24070.0
# set(SFML_ROOT "${DEPENDENCIES_DIR}/sfml")
# https://github.com/tcbrindle/sdl2-cmake-scripts
# Added these find cmake scripts and update module path to include cmake directory which contains them.
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${${PROJECT_NAME}_SOURCE_DIR}/cmake")
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2.5 REQUIRED COMPONENTS network audio graphics window system)

# create static library from SpriterEngine
# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
set(SPRITER_LIBRARY "SpriterEngine")
set(SPRITER_INCLUDE_DIR "${DEPENDENCIES_DIR}/spriter/spriterengine")
file(GLOB_RECURSE SPRITER_HEADERS  "${DEPENDENCIES_DIR}/spriter/*.h")
file(GLOB_RECURSE SPRITER_SOURCES  "${DEPENDENCIES_DIR}/spriter/*.cpp")

add_library(${SPRITER_LIBRARY} ${SPRITER_HEADERS} ${SPRITER_SOURCES})
target_include_directories(${SPRITER_LIBRARY} PUBLIC ${SPRITER_INCLUDE_DIR})
target_include_directories(${SPRITER_LIBRARY} PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(${SPRITER_LIBRARY} PUBLIC sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
# set_target_properties(${SPRITER_LIBRARY} PROPERTIES PUBLIC_HEADER "${INCLUDE_DIR}/Spriter.h")

# create static library from project files
add_library(${PROJECT_LIB} ${INCLUDE_FILES} ${SOURCE_FILES})
target_include_directories(${PROJECT_LIB} PUBLIC ${INCLUDE_DIR})
target_include_directories(${PROJECT_LIB} PUBLIC ${JSON_INCLUDE_DIR})
# target_include_directories(${PROJECT_LIB} PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_LIB} PUBLIC ${SPRITER_LIBRARY})
# target_link_libraries(${PROJECT_LIB} PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(${PROJECT_LIB} PUBLIC Catch)

# link executable with project library
add_executable(${PROJECT_NAME} ${SOURCE_MAIN})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_LIB})

#------------------------------------------------------------------------------
#Catch2 library:
# https://github.com/catchorg/Catch2/blob/master/docs/build-systems.md
set(TESTS_TARGET_NAME "tests")

set(CATCH_INCLUDE_DIR "${DEPENDENCIES_DIR}/catch")
file(GLOB TEST_SOURCES "tests/*.cpp")

# make Catch library
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Make test target
add_executable(${TESTS_TARGET_NAME} ${TEST_SOURCES})
target_link_libraries(${TESTS_TARGET_NAME} ${PROJECT_LIB})
target_link_libraries(${TESTS_TARGET_NAME} Catch)

if (CMAKE_COMPILER_IS_GNUCC)
    # gcc on raspbian is 6.3 and got warnings about changes in gcc 7.1, disable these warnings 
    target_compile_options(${TESTS_TARGET_NAME} PRIVATE "-Wno-psabi")
    target_compile_options(${SPRITER_LIBRARY} PRIVATE "-Wno-psabi")

    # https://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
    set (CMAKE_CXX_STANDARD 11)
endif()
#------------------------------------------------------------------------------

#copy assets
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/assets/"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

if (WIN32)
    #set VS working directory
    # https://stackoverflow.com/questions/47244633/set-visual-studio-debugger-working-directory-to-executable-output-directory-in-c
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}")

    #windows visual studio also needs to copy the dll as well:
    # https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        
        COMMAND ${CMAKE_COMMAND} -E copy_directory  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/${DEPENDENCIES_DIR}/sfml/bin" # <--this is in-file
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )                 # <--this is out-file path
endif ()
