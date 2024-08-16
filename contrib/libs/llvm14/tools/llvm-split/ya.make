# Generated by devtools/yamaker.

PROGRAM()

VERSION(14.0.6)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/include
    contrib/libs/llvm14/lib/Analysis
    contrib/libs/llvm14/lib/AsmParser
    contrib/libs/llvm14/lib/BinaryFormat
    contrib/libs/llvm14/lib/Bitcode/Reader
    contrib/libs/llvm14/lib/Bitcode/Writer
    contrib/libs/llvm14/lib/Bitstream/Reader
    contrib/libs/llvm14/lib/DebugInfo/DWARF
    contrib/libs/llvm14/lib/Demangle
    contrib/libs/llvm14/lib/IR
    contrib/libs/llvm14/lib/IRReader
    contrib/libs/llvm14/lib/MC
    contrib/libs/llvm14/lib/MC/MCParser
    contrib/libs/llvm14/lib/Object
    contrib/libs/llvm14/lib/ProfileData
    contrib/libs/llvm14/lib/Remarks
    contrib/libs/llvm14/lib/Support
    contrib/libs/llvm14/lib/TextAPI
    contrib/libs/llvm14/lib/Transforms/Utils
)

ADDINCL(
    contrib/libs/llvm14/tools/llvm-split
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    llvm-split.cpp
)

END()
