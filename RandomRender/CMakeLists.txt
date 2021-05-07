

cmake_minimum_required(VERSION 3.10)

project(RandomRender)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/include ./include)

set(HEADERS
	utils/global.h
	utils/math.h
	scene/object.h
	scene/texture.h
	render/render.h
        render/light.h
        render/camera.h
        render/shader.h
        render/transform.h
        render/rasterizer.h
        )

set(SOURCES
	utils/math.cpp
        scene/object.cpp
	render/shader.cpp
	render/render.cpp
        render/transform.cpp
        render/rasterizer.cpp
	main.cpp
        )

add_executable(RandomRender  ${HEADERS} ${SOURCES})
target_link_libraries(RandomRender ${OpenCV_LIBRARIES})
#target_compile_options(RandomRender PUBLIC -Wall -Wextra -pedantic)

