cmake_minimum_required(VERSION 3.14)
project(StudentuAnalyze CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimizavimas release konfigūracijai
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Bendras šaltinio failas (matematika + pagalbinės funkcijos)
set(SHARED_SRC funkcijos.cpp)

# ---- Pagrindinė programa (v0.4 su vector meniu) ----
add_executable(programa
    Uzd1.cpp
    vektorius.cpp
    testavimas.cpp
    ${SHARED_SRC}
)

# ---- Tyrimo programos (v1.0) ----
add_executable(studentai_vector
    studentai_vector.cpp
    ${SHARED_SRC}
)

add_executable(studentai_list
    studentai_list.cpp
    ${SHARED_SRC}
)

add_executable(studentai_deque
    studentai_deque.cpp
    ${SHARED_SRC}
)

# Windows konsolės UTF-8 palaikymas
if(WIN32)
    target_compile_definitions(programa         PRIVATE _WIN32)
    target_compile_definitions(studentai_vector PRIVATE _WIN32)
    target_compile_definitions(studentai_list   PRIVATE _WIN32)
    target_compile_definitions(studentai_deque  PRIVATE _WIN32)
endif()

# g++ 8 reikalauja -lstdc++fs; g++ 9+ įtraukia automatiškai.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0")
    foreach(target programa studentai_vector studentai_list studentai_deque)
        target_link_libraries(${target} stdc++fs)
    endforeach()
endif()
