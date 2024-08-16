# Generated by devtools/yamaker.

LIBRARY()

VERSION(16.0.0)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm16
    contrib/libs/llvm16/include
    contrib/libs/llvm16/lib/Bitstream/Reader
    contrib/libs/llvm16/lib/IR
    contrib/libs/llvm16/lib/Support
    contrib/libs/llvm16/lib/TargetParser
)

ADDINCL(
    contrib/libs/llvm16/lib/Bitcode/Reader
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    BitReader.cpp
    BitcodeAnalyzer.cpp
    BitcodeReader.cpp
    MetadataLoader.cpp
    ValueList.cpp
)

END()
