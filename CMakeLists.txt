cmake_minimum_required(VERSION 3.20)

project(ESP32_S3_N16R8_SKELETON LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

if(BUILD_TESTING)
	find_package(GTest CONFIG QUIET)

	if((NOT TARGET GTest::gtest) OR (NOT TARGET GTest::gmock_main))
		include(FetchContent)

		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

		FetchContent_Declare(
			googletest
			URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
			DOWNLOAD_EXTRACT_TIMESTAMP TRUE
		)

		FetchContent_MakeAvailable(googletest)

		if(TARGET gtest AND NOT TARGET GTest::gtest)
			add_library(GTest::gtest ALIAS gtest)
		endif()

		if(TARGET gtest_main AND NOT TARGET GTest::gtest_main)
			add_library(GTest::gtest_main ALIAS gtest_main)
		endif()

		if(TARGET gmock AND NOT TARGET GTest::gmock)
			add_library(GTest::gmock ALIAS gmock)
		endif()

		if(TARGET gmock_main AND NOT TARGET GTest::gmock_main)
			add_library(GTest::gmock_main ALIAS gmock_main)
		endif()
	endif()
endif()

add_subdirectory(common_utils)
add_subdirectory(common_os)
add_subdirectory(common_driver)
add_subdirectory(sample_project)
