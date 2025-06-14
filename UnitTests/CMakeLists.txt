add_executable(unittests Main.cpp)

target_link_libraries(unittests PRIVATE Catch2Main Catch2)
target_include_directories(unittests PRIVATE ${PROJECT_SOURCE_DIR})