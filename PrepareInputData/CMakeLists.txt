cmake_minimum_required(VERSION 3.10)
project(PrepareInputData)

set(CMAKE_CXX_STANDARD 11)

set(OPEN3D_ROOT "C:/Program Files (x86)/Open3D")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${Open3D_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Open3D_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${Open3D_EXE_LINKER_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

#link_directories(${OPEN3D_ROOT}/lib)
#add_executable(${PROJECT_NAME} PrepareInputData.cpp)
#target_link_libraries(${PROJECT_NAME} Open3D::Open3D)   # release
#target_include_directories(${PROJECT_NAME} PUBLIC ${OPEN3D_ROOT}/include)

find_package(Open3D HINTS ${OPEN3D_ROOT}/CMake)
# Set OS-specific things here
if(WIN32)
elseif(CYGWIN)
elseif(APPLE)
elseif(UNIX)
	add_definitions(-DUNIX)
	add_compile_options(-Wno-deprecated-declarations)
	add_compile_options(-Wno-unused-result)
    add_definitions(-O3)
endif(WIN32)

# Open3D
if (Open3D_FOUND)
    message(STATUS "Found Open3D ${Open3D_VERSION}")

    # link_directories must be before add_executable
    link_directories(${Open3D_LIBRARY_DIRS})

    add_executable(${PROJECT_NAME} PrepareInputData.cpp)

    target_link_libraries(${PROJECT_NAME} ${Open3D_LIBRARIES})

    target_include_directories(${PROJECT_NAME} PUBLIC ${Open3D_INCLUDE_DIRS})

    # Hot fix windows dll not found issue, assumming we're using the Release build
    option(BUILD_SHARED_LIBS "Whether Open3D was build as shared library" OFF)
    if(WIN32 AND BUILD_SHARED_LIBS)
        message("Will copy Open3D.dll to ${CMAKE_CURRENT_BINARY_DIR}/Release")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy
                                ${CMAKE_INSTALL_PREFIX}/bin/Open3D.dll
                                ${CMAKE_CURRENT_BINARY_DIR}/Release)
    endif()

else ()
    message(SEND_ERROR "Open3D not found")
endif ()


