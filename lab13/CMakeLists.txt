cmake_minimum_required(VERSION 3.16)
project(lab13 C)

set(CMAKE_C_STANDARD 11)

find_package (Threads)

add_executable(queue src/queue.c src/utils.c)
add_executable(queue_mutex src/queue_mutex.c src/utils.c)
add_executable(queue_cond src/queue_cond.c src/utils.c)
target_link_libraries (queue ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (queue_mutex ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (queue_cond ${CMAKE_THREAD_LIBS_INIT})
