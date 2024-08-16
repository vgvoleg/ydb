# Generated by devtools/yamaker.

LIBRARY()

VERSION(14.0.6)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/lib/MC
    contrib/libs/llvm14/lib/Support
)

ADDINCL(
    contrib/libs/llvm14/lib/Target/PowerPC
    contrib/libs/llvm14/lib/Target/PowerPC/TargetInfo
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    PowerPCTargetInfo.cpp
)

END()
