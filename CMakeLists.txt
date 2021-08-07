cmake_minimum_required (VERSION 3.14)

project (Shesh-Besh_Game)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/permissive-)
endif ()

add_executable (Shesh-Besh_Game "")

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)

if( APPLE )
    #this is for macos=======================
    include_directories(/usr/local/Cellar)

    find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIRS})
        target_link_libraries(Shesh-Besh_Game sfml-window sfml-graphics sfml-audio sfml-network)
    endif()
    #=========================================
else()
    #this is for windows==============================
set (SFML_STATIC_LIBRARIES TRUE)
set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")

find_package (SFML 2.5 COMPONENTS graphics audio REQUIRED)

set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
configure_file ("C:/SFML/SFML-2.5.1/bin/openal32.dll" ${CMAKE_BINARY_DIR} COPYONLY)

target_link_libraries (Shesh-Besh_Game sfml-graphics sfml-audio sfml-main)
endif()