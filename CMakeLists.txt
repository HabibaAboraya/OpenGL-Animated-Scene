cmake_minimum_required(VERSION 3.10)
project(GLUTProject)
set(CMAKE_CXX_STANDARD 20)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS} ${GLUT_LIBRARY_DIRS})
add_executable(GLUTProject main.cpp)
target_link_libraries(GLUTProject ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
