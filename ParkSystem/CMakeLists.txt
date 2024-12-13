# # 指定最低 CMake 版本要求
# cmake_minimum_required(VERSION 3.10)

# # 设置项目名称和版本
# project(Simple_Redis VERSION 1.0.0 LANGUAGES C)

# # 设置 C 标准
# set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED ON)

# # 设置输出目录
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# # 添加头文件目录
# #include_directories(${CMAKE_SOURCE_DIR}/include)
# include_directories(${PROJECT_SOURCE_DIR}/include)

# # 定义静态库或动态库
# #add_library(addlib STATIC
# #    src/add.c
# #)

# # 定义可执行文件
# add_executable(Simple_Redis
#     src/main.c
# )

# # 链接库
# #target_link_libraries(my_program PRIVATE addlib)

# # 添加系统库（如 pthread 或 m）
# #find_package(Threads REQUIRED)
# #target_link_libraries(my_program PRIVATE Threads::Threads)

# # 如果需要数学库
# #find_package(Math REQUIRED)
# #target_link_libraries(my_program PRIVATE m)

# # 添加调试信息（可选）
# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#     target_compile_options(Simple_Redis PRIVATE -g)
# endif()

# # 添加优化选项（可选）
# #if(CMAKE_BUILD_TYPE STREQUAL "Release")
# #    target_compile_options(my_program PRIVATE -O3)
# #endif()

# # 配置安装规则
# install(TARGETS Simple_Redis DESTINATION bin)
# install(DIRECTORY include/ DESTINATION include)
# install(FILES README.md LICENSE DESTINATION share/doc/${PROJECT_NAME})

# # 配置包信息（可选）
# include(CPack)

project(ParkSystem)
# set minimum version
cmake_minimum_required(VERSION 3.5)
# set c++ standard
set(CMAKE_CXX_STANDARD 11)
# include directories
include_directories(include)
# source files
set(SRC 
    src/main.c
    src/user.c)
#    src/dictEntry.c)
# add executable
add_executable(ParkSystem ${SRC})