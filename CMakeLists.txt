cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  "cap"
  VERSION
    1.0.0
    DESCRIPTION
    "A header only utility for parsing command line arguments"
    LANGUAGES CXX
    HOMEPAGE_URL
    "https://github.com/something")


add_library(${PROJECT_NAME} INTERFACE)

# add alias so the project can be uses with add_subdirectory
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})



include(GNUInstallDirs)


target_include_directories(
  cap
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(cap INTERFACE cxx_std_17)


# Installation directives

install(TARGETS ${PROJECT_NAME}
		EXPORT ${PROJECT_NAME}_Targets
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)


message(STATUS "config: ${CMAKE_INSTALL_DATAROOTDIR}  ${CMAKE_INSTALL_LIBDIR}")

set(CAP_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/cap)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION
  ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)


install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)


install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

message(STATUS "HIMANSHU: ${PROJECT_SOURCE_DIR}")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
