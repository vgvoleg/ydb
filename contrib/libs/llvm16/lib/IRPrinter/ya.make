# Generated by devtools/yamaker.

LIBRARY()

VERSION(16.0.0)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm16
    contrib/libs/llvm16/include
    contrib/libs/llvm16/lib/Analysis
    contrib/libs/llvm16/lib/IR
    contrib/libs/llvm16/lib/Support
)

ADDINCL(
    contrib/libs/llvm16/lib/IRPrinter
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    IRPrintingPasses.cpp
)

END()
