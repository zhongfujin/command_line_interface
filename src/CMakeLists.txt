cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include_directories(../cli/inc)
aux_source_directory(. SRC_LIST)
add_library(telnetdbg SHARED ${SRC_LIST})








		


