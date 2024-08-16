# Generated by devtools/yamaker.

LIBRARY()

VERSION(14.0.6)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/include
    contrib/libs/llvm14/lib/BinaryFormat
    contrib/libs/llvm14/lib/MC
    contrib/libs/llvm14/lib/Support
    contrib/libs/llvm14/lib/Target/PowerPC/TargetInfo
)

ADDINCL(
    ${ARCADIA_BUILD_ROOT}/contrib/libs/llvm14/lib/Target/PowerPC
    contrib/libs/llvm14/lib/Target/PowerPC
    contrib/libs/llvm14/lib/Target/PowerPC/MCTargetDesc
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    PPCAsmBackend.cpp
    PPCELFObjectWriter.cpp
    PPCELFStreamer.cpp
    PPCInstPrinter.cpp
    PPCMCAsmInfo.cpp
    PPCMCCodeEmitter.cpp
    PPCMCExpr.cpp
    PPCMCTargetDesc.cpp
    PPCPredicates.cpp
    PPCXCOFFObjectWriter.cpp
    PPCXCOFFStreamer.cpp
)

END()
