# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

# Réglage de la politique CMP0002 pour éviter les conflits de cibles
if(POLICY CMP0002)
    cmake_policy(SET CMP0002 NEW)
endif()

# Réglage de la politique CMP0079 pour autoriser la liaison de bibliothèques non construites dans le même répertoire
if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("TIPE")

# Include sub-projects.
add_subdirectory ("Motor")