cmake_minimum_required(VERSION 3.3)
project(GameOfLife)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/TreeNode.cpp src/TreeNode.h src/TreeUniverse.cpp src/TreeUniverse.h src/TreeHashMap.cpp src/TreeHashMap.h src/CanonicalTreeNode.cpp src/CanonicalTreeNode.h src/HashLifeTreeNode.cpp src/HashLifeTreeNode.h)
add_executable(GameOfLife ${SOURCE_FILES})