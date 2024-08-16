# Generated by devtools/yamaker.

PROGRAM(lli-child-target)

VERSION(14.0.6)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/lib/Demangle
    contrib/libs/llvm14/lib/ExecutionEngine/Orc
    contrib/libs/llvm14/lib/ExecutionEngine/Orc/Shared
    contrib/libs/llvm14/lib/ExecutionEngine/Orc/TargetProcess
    contrib/libs/llvm14/lib/Support
)

ADDINCL(
    contrib/libs/llvm14/tools/lli/ChildTarget
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    ChildTarget.cpp
)

END()
