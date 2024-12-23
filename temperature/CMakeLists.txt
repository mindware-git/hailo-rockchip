# CMakeLists.txt
# 최소 CMake 버전 설정
cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름 설정
project(Temp)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 14)

# 실행 파일 생성
add_executable(get_temp main.cpp)
target_link_libraries(get_temp hailort)
