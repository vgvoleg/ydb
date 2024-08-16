# Generated by devtools/yamaker.

LIBRARY()

VERSION(14.0.6)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/lib/Object
    contrib/libs/llvm14/lib/Support
)

ADDINCL(
    contrib/libs/llvm14/lib/XRay
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    BlockIndexer.cpp
    BlockPrinter.cpp
    BlockVerifier.cpp
    FDRRecordProducer.cpp
    FDRRecords.cpp
    FDRTraceExpander.cpp
    FDRTraceWriter.cpp
    FileHeaderReader.cpp
    InstrumentationMap.cpp
    LogBuilderConsumer.cpp
    Profile.cpp
    RecordInitializer.cpp
    RecordPrinter.cpp
    Trace.cpp
)

END()
