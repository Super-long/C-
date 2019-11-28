cmake_minimum_required(VERSION 3.4.1)
project(Web_Server) #引入两个变量

set(CMAKE_CXX_STANDARD 14)
link_libraries(pthread)
#add_definitions("-03")#下去搞清楚这个句子的含义

aux_source_directory(/src/base WS_BASE)
aux_source_directory(/src/core WS_CORE)
aux_source_directory(/src/http WS_HTTP)
aux_source_directory(/src/net  WS_NET)
aux_source_directory(/src/tool WS_TOOL)
#搜索目录下所有的cpp文件

add_executable(Web_Server
        src/Web_Server.cc
        ${WS_BASE}
        ${WS_CORE}
        ${WS_NET}
        ${WS_HTTP}
        ${WS_TOOL}
        )
