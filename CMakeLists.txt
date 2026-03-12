# 1. Versión mínima de CMake
cmake_minimum_required(VERSION 3.10)

# 2. Nombre oficial del proyecto
project(TRABAJO_ARCHON)

# 3. Configuración del estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Rutas de cabeceras (.h)
include_directories(
    src 
    lib/freeglut/include
    lib/ETSIDI_2019
)

# 5. Rutas de librerías (.lib)
link_directories(
    lib/freeglut/lib/x64 
    lib/ETSIDI_2019
)

# 6. Crear el ejecutable ARCHON (SOLO UNA LÍNEA AQUÍ)
add_executable(ARCHON src/main.cpp)

# 7. Vincular las librerías al ejecutable ARCHON
target_link_libraries(ARCHON 
    freeglut 
    opengl32 
    glu32 
    ETSIDI
)

# 8. Copiar las DLLs automáticamente al compilar
add_custom_command(TARGET ARCHON POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/freeglut/bin/x64/freeglut.dll"
    $<TARGET_FILE_DIR:ARCHON>
    COMMENT "Copiando freeglut.dll...")

add_custom_command(TARGET ARCHON POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/ETSIDI_2019/ETSIDI.dll"
    $<TARGET_FILE_DIR:ARCHON>
    COMMENT "Copiando ETSIDI.dll...")