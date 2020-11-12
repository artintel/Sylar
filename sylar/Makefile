cmake_minimum_required(VERSION 2.8) #定义需要的最低版本
project(sylar) #项目名称

set(CMAKE_VERBOSE_MAKEFILE ON) #在make过程中现实详细的make编译命令
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} rdynamic -03 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function") #自定义了一些我们自己要的编译参数

# 将我们编写的源码设到LIB_SRC之下
set(LIB_SRC
    sylar/log.cc
   )

add_library(sylar SHARED ${LIB_SRC}) # 增加了 SHARED库，生成ISO文件
#add_library(sylar_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (sylar_static PROPERTIES OUTPUT_NAME "sylar")

add_executable(test tests/test.cc) # 生成测试的文件
add_dependencies(test sylar)
target_link_libraries(test sylar)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
