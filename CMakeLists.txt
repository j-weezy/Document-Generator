cmake_minimum_required(VERSION 3.13)

project(DocumentGenerator C CXX ASM)

file(GLOB SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

find_package(LibXml2 REQUIRED)

add_executable(DocumentGenerator
    ${SOURCES}
)

target_compile_features(DocumentGenerator PUBLIC cxx_std_17)

target_include_directories(DocumentGenerator PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(DocumentGenerator
    PRIVATE
        LibXml2::LibXml2
)