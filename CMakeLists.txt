cmake_minimum_required(VERSION 3.11)

project (DetectFaces )
find_package(OpenCV REQUIRED)
find_package(Boost 1.55.0 COMPONENTS filesystem system)

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
endif()

#We need fetchcontent for gtests
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
    )
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# Face detection library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(detector_lib SHARED detector.cc detector.h)
target_include_directories( detector_lib PRIVATE ${Boost_INCLUDE_DIRS})
include_directories(${googletest_SOURCE_DIR}/googletest/include)
target_link_libraries( detector_lib ${OpenCV_LIBS} )
# ?? install(FILE haarcascade_frontalface_alt.xml DESTINATION )

#example executable
add_executable(simple_detect simple_detect.cc)
target_include_directories( simple_detect PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries( simple_detect detector_lib)
target_link_libraries( simple_detect ${Boost_LIBRARIES} )

#tests
enable_testing()
add_executable(func_tests test.cc)
add_test(NAME basic_tests COMMAND func_tests)
target_link_libraries(func_tests gtest_main detector_lib) 
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/haarcascade_frontalface_alt.xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_images/multiple_faces.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test_images/)
