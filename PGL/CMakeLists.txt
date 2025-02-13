cmake_minimum_required(VERSION 3.10)

# Définir le projet
project(PGL VERSION 1.0)

# Définir la version C++
set(CMAKE_CXX_STANDARD 20)

# Définir le répertoire de sortie des exécutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Définir les fichiers sources pour ImGui
set(ImGUI_SOURCES
    libs/ImGUI/imgui.cpp
    libs/ImGUI/imgui_demo.cpp
    libs/ImGUI/imgui_draw.cpp
    libs/ImGUI/imgui_impl_glfw.cpp
    libs/ImGUI/imgui_impl_opengl3.cpp
    libs/ImGUI/imgui_stdlib.cpp
    libs/ImGUI/imgui_tables.cpp
    libs/ImGUI/imgui_widgets.cpp
)

# Définir les fichiers sources pour gérer OpenGL
set(OPENGL_SOURCES
    src/openGL/IndexBuffer.cpp
    src/openGL/Renderer.cpp
    src/openGL/Shader.cpp
    src/openGL/VertexArray.cpp
    src/openGL/VertexBuffer.cpp
    src/openGL/VertexBufferLayout.cpp
)

# Définir les fichiers sources principaux
set(SOURCES
    src/PGL.cpp
    src/Logger.cpp
    ${ImGUI_SOURCES}
    ${OPENGL_SOURCES}
)

# Ajout des sous-répertoires pour GLFW et GLM
add_subdirectory(libs/glfw)
add_subdirectory(libs/glm)

# Création de la bibliothèque statique
add_library(PGL STATIC ${SOURCES})

# Ajouter les répertoires d'inclusion
target_include_directories(PGL PUBLIC
    "include/"
    "include/ImGui"
    "include/pgl/openGL"
    "include/pgl"
    ${GLFW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

# Lier les bibliothèques
target_link_libraries(PGL
    glfw
    glm
    OpenGL32  # OpenGL standard sur Windows
)

# Affichage des chemins pour vérification
message(STATUS "GLFW_INCLUDE_DIRS = ${GLFW_INCLUDE_DIRS}")
message(STATUS "GLM_INCLUDE_DIRS = ${GLM_INCLUDE_DIRS}")


install(TARGETS PGL
    CONFIGURATIONS Debug Release
    ARCHIVE DESTINATION lib/$<CONFIG>
    LIBRARY DESTINATION lib/$<CONFIG>
    RUNTIME DESTINATION bin/$<CONFIG>
)

install(DIRECTORY include/ DESTINATION include)