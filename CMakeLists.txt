cmake_minimum_required(VERSION 3.11)

project (DetectFaces )
find_package(OpenCV REQUIRED)
find_package(Boost 1.55.0 COMPONENTS filesystem system)

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
add_library(detector_lib SHARED detector.cc detector.h)
include_directories(${googletest_SOURCE_DIR}/googletest/include)
target_link_libraries( detector_lib ${OpenCV_LIBS} )
# ?? install(FILE haarcascade_frontalface_alt.xml DESTINATION )

#example executable
add_executable(simple_detect simple_detect.cc)
target_link_libraries( simple_detect detector_lib)
target_link_libraries( simple_detect ${Boost_LIBRARIES} )

#tests
enable_testing()
add_executable(func_tests test.cc)
add_test(NAME basic_tests COMMAND func_tests)
target_link_libraries(func_tests gtest_main detector_lib) 
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/haarcascade_frontalface_alt.xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_images/multiple_faces.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test_images/)
