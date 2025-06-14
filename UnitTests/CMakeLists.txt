add_executable(unit_tests Main.cpp)

target_link_libraries(unit_tests PRIVATE Catch2Main Catch2)
target_include_directories(unit_tests PRIVATE ${PROJECT_SOURCE_DIR})