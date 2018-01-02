file(GLOB SRCS *.cpp)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_executable(testBinTree ${SRCS})

target_link_libraries(testBinTree
        bintree
        gtest
        gmock
)

include_directories("..")

install(TARGETS testBinTree DESTINATION bin)
