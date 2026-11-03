
cmake_minimum_required(VERSION 3.16)

project(MyAnalysis VERSION 1.0 LANGUAGES CXX)

# Utilizziamo C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Troviamo ROOT
find_package(ROOT REQUIRED COMPONENTS Core RIO Tree Hist Graf Gpad)

# Cartella contenente gli header
include_directories(${PROJECT_SOURCE_DIR}/include)

# Creiamo l'eseguibile
add_executable(MyAnalysis
    src/main.cpp
    src/Reader.cpp
    src/Analysis.cpp
)

# Colleghiamo le librerie ROOT
target_link_libraries(MyAnalysis PRIVATE
    ROOT::Core
    ROOT::RIO
    ROOT::Tree
    ROOT::Hist
    ROOT::Graf
    ROOT::Gpad
)
