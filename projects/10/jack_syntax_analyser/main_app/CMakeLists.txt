project(JackSyntaxAnalyser)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER main_app)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ../)

target_link_libraries(${PROJECT_NAME} jack_tokeniser)
# target_link_libraries(${PROJECT_NAME} jack_grammar_engine)

## #################################################################
## Installation
## #################################################################
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin)
