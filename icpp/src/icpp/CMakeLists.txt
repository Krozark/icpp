set(INCROOT ${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})


SET(BisonOutputSrc ${SRCROOT}/parser/Parser.cpp)
set(BisonOutputInc ${SRCROOT}/parser/Parser.hpp)
set(BisonOutputExtra ${SRCROOT}/parser/stack.hh)
SET(FlexOutputSrc ${SRCROOT}/parser/Lexer.cpp)

FIND_PACKAGE(BISON REQUIRED)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${BisonOutputSrc} ${BisonOutputInc} ${BisonOutputExtra}
      COMMAND ${BISON_EXECUTABLE}
      --output=${BisonOutputSrc}
      --defines=${BisonOutputInc}
              ${SRCROOT}/parser/Parser.yy
      COMMENT "Generating Parser.cpp"
    )
    INSTALL( FILES ${BisonOutputExtra} ${BisonOutputInc} DESTINATION include/${CMAKE_PROJECT_NAME}/parser )
else()
    message( SEND_ERROR "Bison is required" )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${FlexOutputSrc}
      COMMAND ${FLEX_EXECUTABLE}
      --outfile=${FlexOutputSrc}
              ${SRCROOT}/parser/Lexer.lex
              COMMENT "Generating Lexer.cpp"
    )
else()
    message( SEND_ERROR "Flex is required" )
ENDIF()

#ROOT files
set(ROOT_SRC
    ${SRCROOT}/parser/Driver.cpp
    ${SRCROOT}/parser/Scanner.cpp
    ${BisonOutputSrc}
    ${FlexOutputSrc}

    ${SRCROOT}/Context.cpp
    ${SRCROOT}/Function.cpp
    ${SRCROOT}/Value.cpp

)
set(ROOT_HEADER
    ${INCROOT}/parser/Driver.hpp
    ${INCROOT}/parser/FlexLexer.hpp
    ${INCROOT}/parser/Scanner.hpp
    ${BisonOutputInc}
    ${BisonOutputExtra}

    ${INCROOT}/Context.hpp
    ${INCROOT}/Context.tpl
    ${INCROOT}/Function.hpp
    ${INCROOT}/Function.tpl
    ${INCROOT}/Value.hpp
    ${INCROOT}/Value.tpl
)
#FILES
set(FILES_HEADER
    ${ROOT_HEADER}
)
set(FILES_SRC
    ${ROOT_SRC}
)

#SHARED lib
add_library(${CMAKE_PROJECT_NAME} SHARED ${FILES_HEADER} ${FILES_SRC})
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME}
    PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})
INSTALL(TARGETS ${CMAKE_PROJECT_NAME}
    DESTINATION lib
)

#static lib
add_library(${CMAKE_PROJECT_NAME}-static STATIC ${FILES_HEADER} ${FILES_SRC})
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME}-static
    PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
target_link_libraries(${CMAKE_PROJECT_NAME}-static ${LIBS})
INSTALL(TARGETS ${CMAKE_PROJECT_NAME}-static
    DESTINATION lib
)


file(GLOB DEPLOY_FILES_AND_DIRS "${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/*")
foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
   IF( IS_DIRECTORY "${ITEM}" )
      LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   ELSE()
      LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
   ENDIF()
endforeach()
INSTALL( FILES ${FILES_TO_DEPLOY} ${BisonOutputInc} DESTINATION include/${CMAKE_PROJECT_NAME} )
INSTALL( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include/${CMAKE_PROJECT_NAME} )
