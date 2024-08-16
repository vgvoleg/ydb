# Generated by devtools/yamaker.

LIBRARY()

VERSION(14.0.6)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/include
    contrib/libs/llvm14/lib/Analysis
    contrib/libs/llvm14/lib/IR
    contrib/libs/llvm14/lib/Support
    contrib/libs/llvm14/lib/Transforms/IPO
    contrib/libs/llvm14/lib/Transforms/Scalar
    contrib/libs/llvm14/lib/Transforms/Utils
)

ADDINCL(
    contrib/libs/llvm14/lib/Transforms/Coroutines
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    CoroCleanup.cpp
    CoroEarly.cpp
    CoroElide.cpp
    CoroFrame.cpp
    CoroSplit.cpp
    Coroutines.cpp
)

END()
