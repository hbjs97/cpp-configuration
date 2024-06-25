cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름과 버전
project(MyConfigProject VERSION 1.0)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 소스 파일 설정
set(SOURCES src/bootstrap/application.cpp)

# yaml-cpp 라이브러리 경로 설정
find_package(yaml-cpp REQUIRED)
include_directories(/opt/homebrew/opt/yaml-cpp/include) # 설치 경로에 따라 변경
link_directories(/opt/homebrew/opt/yaml-cpp/lib)       # 설치 경로에 따라 변경

# 실행 파일 생성
add_executable(MyConfigProject ${SOURCES})

# yaml-cpp 라이브러리 링크
target_link_libraries(MyConfigProject yaml-cpp)

# 산출물 경로 설정
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
