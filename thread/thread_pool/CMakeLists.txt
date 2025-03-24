cmake_minimum_required(VERSION 3.10)
project(threadpool)
file(GLOB SOURCES "*.cc")

add_executable(threadpool ${SOURCES})
