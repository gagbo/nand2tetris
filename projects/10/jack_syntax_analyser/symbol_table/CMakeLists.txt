project(jack_symbol_table)

file(GLOB ${PROJECT_NAME}_SRCS "*.cpp" )

file(GLOB ${PROJECT_NAME}_HEADERS "*.h" )

if(BUILD_SHARED_LIBS)
  set(LIBRARY_TYPE SHARED)
else(BUILD_SHARED_LIBS)
  set(LIBRARY_TYPE STATIC)
endif(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} ${LIBRARY_TYPE}
    ${${PROJECT_NAME}_SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ../)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER symbol_table)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
