cmake_minimum_required(VERSION 3.20)
project(arithmetic)

set(CMAKE_CXX_STANDARD 14)

# 遍历项目根目录下所有的 .c 文件
#file (GLOB files *.c)
#foreach (file ${files})
#    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
#    add_executable (${exe} ${file})
#    message (\ \ \ \ --\ src/${exe}.c\ will\ be\ compiled\ to\ bin/${exe})
#endforeach ()

include_directories(include)
add_executable(${PROJECT_NAME} arith_main.c pre_input.c big_integer.c arith_utils.c)