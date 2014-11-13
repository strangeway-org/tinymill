cmake_minimum_required(VERSION 2.8.4)
project(tinymill)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${PROJECT_SOURCE_DIR}/srcgen/Lexer.c)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
        OUTPUT  ${FlexOutput} ${PROJECT_SOURCE_DIR}/srcgen/Lexer.h
        COMMAND ${FLEX_EXECUTABLE} --outfile=/media/data/projects/tinymill/srcgen/Lexer.c --header-file=/media/data/projects/tinymill/srcgen/Lexer.h ${PROJECT_SOURCE_DIR}/src/Lexer.l
        COMMENT "Generating Lexer.c"
    )
ENDIF()

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput ${PROJECT_SOURCE_DIR}/srcgen/Parser.c)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
        OUTPUT  ${BisonOutput} ${PROJECT_SOURCE_DIR}/srcgen/Parser.h
        COMMAND ${BISON_EXECUTABLE} --output=/media/data/projects/tinymill/srcgen/Parser.c --defines=/media/data/projects/tinymill/srcgen/Parser.h ${PROJECT_SOURCE_DIR}/src/Parser.y
        COMMENT "Generating Parser.c"
    )
ENDIF()

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/srcgen")

set(SOURCE_FILES src/main.c src/Expression.c)
add_executable(tinymill ${SOURCE_FILES} ${BisonOutput} ${FlexOutput})