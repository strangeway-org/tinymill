cmake_minimum_required(VERSION 2.8.4)
project(tinymill)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput Lexer.c)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${FlexOutput}
      COMMAND ${FLEX_EXECUTABLE}
              --outfile=${FlexOutput}
              ${PROJECT_SOURCE_DIR}/Lexer.l
      COMMENT "Generating Lexer.c"
    )
ENDIF()

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput Parser.c)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${BisonOutput}
      COMMAND ${BISON_EXECUTABLE}
              --output=${BisonOutput}
              ${PROJECT_SOURCE_DIR}/Parser.y
      COMMENT "Generating Parser.c"
    )
ENDIF()

include_directories("${PROJECT_SOURCE_DIR}")

set(SOURCE_FILES main.c Expression.c)
add_executable(tinymill ${SOURCE_FILES} ${BisonOutput} ${FlexOutput})