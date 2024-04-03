cmake_minimum_required(VERSION 3.27)
project(leetcode)

set(CMAKE_CXX_STANDARD 17)

add_executable(longest_substring
        strings/longest_substring.cc)

add_executable(atoi
        strings/atoi.cc)

add_executable(romans
        strings/romans.cc)

add_executable(3sum
        arrays/3sum.cc)

add_executable(lru_cache
        misc/lru_cache.cc
        misc/lru_cache.cc)

add_executable(decoder
        dp/decoder.cc)       