cmake_minimum_required(VERSION 3.30)
project(myFixedCapBiMap)

set(CMAKE_CXX_STANDARD 20)

add_executable(myFixedCapBiMap
        App.cpp
        ExtendedTest.cpp
        FixedCapBiMap.cpp
        FixedCapBiMapIterator.cpp
        ShortTest.cpp
)
