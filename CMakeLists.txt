# TODO: PUBLIC vs INTERFACE vs PRIVATE

cmake_minimum_required(VERSION 3.7.2-1)
project("sdl_starter")

set(PROJECT_LIB "${PROJECT_NAME}_lib")
set(INCLUDE_DIR "include")

# Good practice to list this instead of GLOBing. 
# https://stackoverflow.com/questions/1027247/is-it-better-to-specify-source-files-with-glob-or-each-file-individually-in-cmak
file(GLOB INCLUDE_FILES "${INCLUDE_DIR}/*.h")
file(GLOB SOURCE_FILES "src/*.cpp")
set(SOURCE_MAIN "src/main.cpp")
list(REMOVE_ITEM SOURCE_FILES SOURCE_MAIN)
set(JSON_INCLUDE_DIR "${INCLUDE_DIR}/json")

# This might not work as cmake has a FindSDL.cmake and doesn't find SDL2
# Though when I tested it, it worked on linux but not windows...
# find_package(SDL2 REQUIRED)

if (WIN32)
    #https://ccavusoglu.github.io/posts/Setting-up-SDL2-and-SDL_gpu-on-Windows-using-CMake/
    # on linux there libraies get installed to some default location, on windows you must let the 
    # find script know here to look
    # *todo: could the Find cmake files path not be set directly from enviroment variables?*
    set(SDL2_PATH "$ENV{SDL2_ROOT}/SDL2-2.0.8")
    set(SDL2_IMAGE_PATH "$ENV{SDL2_ROOT}/SDL2_image-2.0.2")
endif ()

# https://github.com/tcbrindle/sdl2-cmake-scripts
# Added these find cmake scripts and update module path to include cmake directory which contains them.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${${PROJECT_NAME}_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# create static library from project files
add_library(${PROJECT_LIB} ${INCLUDE_FILES} ${SOURCE_FILES})
target_include_directories(${PROJECT_LIB} PUBLIC ${INCLUDE_DIR})
target_include_directories(${PROJECT_LIB} PUBLIC ${JSON_INCLUDE_DIR})
target_include_directories(${PROJECT_LIB} PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${PROJECT_LIB} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_LIB} PUBLIC ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_LIB} PUBLIC ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${PROJECT_LIB} PUBLIC Catch)

# link executable with project library
# *todo: it seems like sdl_starter_lib and sdl_starter both compile the src files so its done twice. why? (possibly
# because of add_library and add_executable both incling source files??)*
add_executable(${PROJECT_NAME} ${INCLUDE_FILES} ${SOURCE_FILES} ${SOURCE_MAIN})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_LIB})

#------------------------------------------------------------------------------
#Catch2 library:
# https://github.com/catchorg/Catch2/blob/master/docs/build-systems.md
set(TESTS_TARGET_NAME "tests")

set(CATCH_INCLUDE_DIR "${INCLUDE_DIR}/catch")
file(GLOB TEST_SOURCES "tests/*.cpp")

# make Catch library
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Make test target
add_executable(${TESTS_TARGET_NAME} ${TEST_SOURCES})
target_link_libraries(${TESTS_TARGET_NAME} ${PROJECT_LIB})
target_link_libraries(${TESTS_TARGET_NAME} Catch)

# gcc on raspbian is 6.3 and got warnings about changes in gcc 7.1
# disable these warnings 
if (CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(${TESTS_TARGET_NAME} PRIVATE "-Wno-psabi")
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
	set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

    #windows visual studio also needs to copy the dll as well:
    # https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        
        COMMAND ${CMAKE_COMMAND} -E copy_directory  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/lib/"      # <--this is in-file
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )                 # <--this is out-file path
endif ()
