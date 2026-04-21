# 1. Versión mínima de CMake
cmake_minimum_required(VERSION 3.10)
# 2. Nombre oficial del proyecto
project(TRABAJO_ARCHON)
# 3. Configuración del estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 4. Escaneo automático de fuentes
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")
# 5. Rutas de cabeceras (.h)
include_directories(
    src
    lib/freeglut/include
    lib/ETSIDI_2019
)
# 6. Rutas de librerías (.lib)
link_directories(
    lib/freeglut/lib/x64
    lib/ETSIDI_2019
)
# 7. Crear el ejecutable ARCHON
add_executable(ARCHON ${SOURCES} ${HEADERS})
# 8. Directorio de trabajo del depurador
set_target_properties(ARCHON PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:ARCHON>"
)
# 9. Vincular las librerías al ejecutable ARCHON
target_link_libraries(ARCHON
    freeglut
    opengl32
    glu32
    ETSIDI
)
# 10. Copiar las DLLs automáticamente al compilar
set(DLLS
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/freeglut/bin/x64/freeglut.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/ETSIDI_2019/ETSIDI.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/ETSIDI_2019/fmodL.dll"
)
foreach(DLL ${DLLS})
    add_custom_command(TARGET ARCHON POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${DLL}"
        $<TARGET_FILE_DIR:ARCHON>
        COMMENT "Copiando DLL: ${DLL}..."
    )
endforeach()
# 11. Copiar assets automáticamente al compilar
add_custom_command(TARGET ARCHON POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:ARCHON>/assets"
    COMMENT "Sincronizando carpeta de assets..."
)