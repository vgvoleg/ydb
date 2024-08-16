# Generated by devtools/yamaker.

LIBRARY()

VERSION(16.0.0)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm16
    contrib/libs/llvm16/include
    contrib/libs/llvm16/lib/IR
    contrib/libs/llvm16/lib/Support
)

ADDINCL(
    ${ARCADIA_BUILD_ROOT}/contrib/libs/llvm16/lib/Target/AArch64
    contrib/libs/llvm16/lib/Target/AArch64
    contrib/libs/llvm16/lib/Target/AArch64/Utils
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    AArch64BaseInfo.cpp
    AArch64SMEAttributes.cpp
)

END()
