cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include_directories(inc)
aux_source_directory(src SRC_LIST)
add_library(cliedit SHARED ${SRC_LIST})








		


