# Generated by devtools/yamaker.

PROGRAM()

VERSION(16.0.0)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm16
    contrib/libs/llvm16/include
    contrib/libs/llvm16/lib/Analysis
    contrib/libs/llvm16/lib/BinaryFormat
    contrib/libs/llvm16/lib/Bitstream/Reader
    contrib/libs/llvm16/lib/Demangle
    contrib/libs/llvm16/lib/IR
    contrib/libs/llvm16/lib/Remarks
    contrib/libs/llvm16/lib/Support
    contrib/libs/llvm16/lib/TargetParser
)

ADDINCL(
    contrib/libs/llvm16/tools/llvm-stress
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    llvm-stress.cpp
)

END()
