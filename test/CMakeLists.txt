file(GLOB SRCS *.cpp)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_executable(testAlvTree ${SRCS} ../test/testAlvTree.h)

target_link_libraries(testAlvTree
        gtest
        gmock
)

include_directories("..")

install(TARGETS testAlvTree DESTINATION bin)
