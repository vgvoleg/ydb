# Generated by devtools/yamaker.

LIBRARY() 
 
OWNER( 
    somov 
    g:cpp-contrib 
) 
 
LICENSE(BSD-3-Clause)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt) 
 
PEERDIR(
    contrib/libs/re2
)

ADDINCL(
    GLOBAL contrib/restricted/googletest/googletest/include
    contrib/restricted/googletest/googletest
)

NO_COMPILER_WARNINGS() 
 
NO_UTIL()

CFLAGS(
    GLOBAL -DGTEST_HAS_ABSL=0
    GLOBAL -DGTEST_OS_FUCHSIA=0
    GLOBAL -DGTEST_HAS_STD_WSTRING=1
)

SRCS( 
    src/gtest-all.cc
) 
 
END() 
