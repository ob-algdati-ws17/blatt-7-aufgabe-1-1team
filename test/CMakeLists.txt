file(GLOB SRCS *.cpp)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_executable(testAvlTree ${SRCS} ../avlTree/avlTree.h ../avlTree/avlTree.cpp)

target_link_libraries(testAvlTree
        gtest
        gmock
)

include_directories("..")

install(TARGETS testAvlTree DESTINATION bin)
