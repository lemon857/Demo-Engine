cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

set(PROJECT_NAME Test_app)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
	src/main.cpp
	)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(external/CppEngine)

target_link_libraries(${PROJECT_NAME} EngineCore)

target_include_directories(${PROJECT_NAME} PRIVATE includes)
include_directories(external/CppEngine/includes)
include_directories(external/CppEngine/external/glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
					
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/systemres $<TARGET_FILE_DIR:${PROJECT_NAME}>/systemres)
