# 1. Versión mínima de CMake
cmake_minimum_required(VERSION 3.10)

# 2. Nombre oficial del proyecto
project(TRABAJO_ARCHON)

# 3. Configuración del estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- NUEVA SECCIÓN: ESCANEO AUTOMÁTICO ---
# Buscamos todos los archivos .cpp y .h de la carpeta src
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

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

# 6. Crear el ejecutable ARCHON
<<<<<<< HEAD
# Ahora usamos la variable ${SOURCES} que contiene todo lo que hay en src
add_executable(ARCHON ${SOURCES} ${HEADERS})

=======
add_executable(ARCHON 
    src/main.cpp
    src/Menu.cpp
    src/Eleccion_1jugador.cpp
    src/Eleccion_2jugadores.cpp
    src/Eleccion2_1jugador.cpp
    src/ranking.cpp
    src/Pantalla_carga.cpp
    src/Tablero.cpp
    src/Tablero_vista.cpp
)
>>>>>>> fc82cfd4e66c4880259b58c56dc8bbbe98ff23c2
# 7. Directorio de trabajo del depurador
set_target_properties(ARCHON PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:ARCHON>"
)

# 8. Vincular las librerías al ejecutable ARCHON
target_link_libraries(ARCHON 
    freeglut 
    opengl32 
    glu32 
    ETSIDI
)

# 9. Copiar las DLLs automáticamente al compilar
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

# 10. Copiar assets automáticamente al compilar
# He corregido la ruta para que copie TODA la carpeta assets, no solo menu_imagenes
add_custom_command(TARGET ARCHON POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:ARCHON>/assets"
<<<<<<< HEAD
    COMMENT "Sincronizando carpeta de assets..."
)
=======
    COMMENT "Copiando assets...")
>>>>>>> fc82cfd4e66c4880259b58c56dc8bbbe98ff23c2
