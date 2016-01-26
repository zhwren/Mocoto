#************************************************************
#* Author       : ZhuHaiWen                                 *
#* Email        : zhuhw@ihep.ac.cn/zhwren0211@whu.edu.cn    *
#* Last modified: 2015-10-27 16:41:1445935314               *
#* Filename     : CMakeLists.txt                            *
#* Phone Number : 18625272373                               *
#* Discription  :                                           *
#************************************************************
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
PROJECT(Reconstruct)
FIND_PACKAGE(Geant4 REQUIRED)
INCLUDE(${Geant4_USE_FILE})
FIND_PACKAGE(ROOT REQUIRED)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR}
		    ${ROOT_INCLUDE_DIR})
FILE(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
FILE(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
ADD_EXECUTABLE(Reconstruct main.cc ${sources} ${headers})
TARGET_LINK_LIBRARIES(Reconstruct ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow -std=c++11")
