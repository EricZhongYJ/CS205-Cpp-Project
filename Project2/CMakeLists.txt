# Project Name: Project2
project(Project2)

# Construct
aux_source_directory(./src SRCS)
include_directories(./inc)
add_executable(Project2.out ${SRCS})