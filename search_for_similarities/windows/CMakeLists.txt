cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME SearchForSimilarities)
project(${PROJECT_NAME}) 

set(CMAKE_CXX_STANDARD 17)

set(ALIGN ./src/Alignment.cpp ./include/Alignment.h)
set(NW ./src/NeedlemanWunsch.cpp ./include/NeedlemanWunsch.h)
set(SW ./src/SlidingWindow.cpp ./include/SlidingWindow.h)

add_executable(${PROJECT_NAME} 
        Application.cpp ./include/SlidingWindow.h
	${ALIGN} ${NW} ${SW})