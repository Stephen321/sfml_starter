# See: https://github.com/stephen321/sfml_starter for origin of this file

cmake_minimum_required(VERSION 3.7.2-1)
project("sfml_starter")

set(PROJECT_LIB "${PROJECT_NAME}_lib")
set(INCLUDE_DIR "include")

# local dependencies
set(DEPENDENCIES_DIR "dependencies")

file(GLOB INCLUDE_FILES "${INCLUDE_DIR}/*.h")
file(GLOB SOURCE_FILES "src/*.cpp")

#split off main as it doesnt need to be in lib, only exe
set(SOURCE_MAIN "src/main.cpp")
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*${SOURCE_MAIN}$")

set(JSON_INCLUDE_DIR "${DEPENDENCIES_DIR}/json")
if (WIN32)
	set(SFML_ROOT "${DEPENDENCIES_DIR}/sfml")
endif ()

#Find any version 2.X of SFML
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${${PROJECT_NAME}_SOURCE_DIR}/cmake")
find_package(SFML 2 REQUIRED network audio graphics window system)

# find threads and setup
# https://stackoverflow.com/questions/1620918/cmake-and-libpthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


# create static library from project files
add_library(${PROJECT_LIB} ${INCLUDE_FILES} ${SOURCE_FILES})
target_include_directories(${PROJECT_LIB} PUBLIC ${SFML_INCLUDE_DIR})
target_include_directories(${PROJECT_LIB} PUBLIC ${INCLUDE_DIR})
target_include_directories(${PROJECT_LIB} PUBLIC ${JSON_INCLUDE_DIR})
target_link_libraries(${PROJECT_LIB} PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(${PROJECT_LIB} PUBLIC Catch)
target_link_libraries(${PROJECT_LIB} PUBLIC Threads::Threads)

# link executable with project library
add_executable(${PROJECT_NAME} ${SOURCE_MAIN})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_LIB})

#------------------------------------------------------------------------------
#Catch2 library:
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
    target_compile_options(${PROJECT_LIB} PRIVATE "-Wno-psabi")
    # set (CMAKE_CXX_STANDARD 11) #doesnt seem to work
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
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
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}")

    #copy sfml dlls
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/${DEPENDENCIES_DIR}/sfml/bin"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif ()