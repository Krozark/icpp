add_executable(${CMAKE_PROJECT_NAME}-test test.cpp test.hpp)
target_link_libraries(${CMAKE_PROJECT_NAME}-test ${LIBS})

add_executable(icpp-interpretor icpp-interpretor.cpp)
target_link_libraries(icpp-interpretor ${LIBS} ${CMAKE_PROJECT_NAME})


