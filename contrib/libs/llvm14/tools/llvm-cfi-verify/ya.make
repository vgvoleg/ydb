# Generated by devtools/yamaker.

PROGRAM()

VERSION(14.0.6)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/lib/BinaryFormat
    contrib/libs/llvm14/lib/Bitcode/Reader
    contrib/libs/llvm14/lib/Bitstream/Reader
    contrib/libs/llvm14/lib/DebugInfo/CodeView
    contrib/libs/llvm14/lib/DebugInfo/DWARF
    contrib/libs/llvm14/lib/DebugInfo/MSF
    contrib/libs/llvm14/lib/DebugInfo/PDB
    contrib/libs/llvm14/lib/DebugInfo/Symbolize
    contrib/libs/llvm14/lib/Demangle
    contrib/libs/llvm14/lib/IR
    contrib/libs/llvm14/lib/MC
    contrib/libs/llvm14/lib/MC/MCDisassembler
    contrib/libs/llvm14/lib/MC/MCParser
    contrib/libs/llvm14/lib/Object
    contrib/libs/llvm14/lib/Remarks
    contrib/libs/llvm14/lib/Support
    contrib/libs/llvm14/lib/Target/AArch64/AsmParser
    contrib/libs/llvm14/lib/Target/AArch64/Disassembler
    contrib/libs/llvm14/lib/Target/AArch64/MCTargetDesc
    contrib/libs/llvm14/lib/Target/AArch64/TargetInfo
    contrib/libs/llvm14/lib/Target/AArch64/Utils
    contrib/libs/llvm14/lib/Target/ARM/AsmParser
    contrib/libs/llvm14/lib/Target/ARM/Disassembler
    contrib/libs/llvm14/lib/Target/ARM/MCTargetDesc
    contrib/libs/llvm14/lib/Target/ARM/TargetInfo
    contrib/libs/llvm14/lib/Target/ARM/Utils
    contrib/libs/llvm14/lib/Target/BPF/AsmParser
    contrib/libs/llvm14/lib/Target/BPF/Disassembler
    contrib/libs/llvm14/lib/Target/BPF/MCTargetDesc
    contrib/libs/llvm14/lib/Target/BPF/TargetInfo
    contrib/libs/llvm14/lib/Target/NVPTX/MCTargetDesc
    contrib/libs/llvm14/lib/Target/NVPTX/TargetInfo
    contrib/libs/llvm14/lib/Target/PowerPC/AsmParser
    contrib/libs/llvm14/lib/Target/PowerPC/Disassembler
    contrib/libs/llvm14/lib/Target/PowerPC/MCTargetDesc
    contrib/libs/llvm14/lib/Target/PowerPC/TargetInfo
    contrib/libs/llvm14/lib/Target/X86/AsmParser
    contrib/libs/llvm14/lib/Target/X86/Disassembler
    contrib/libs/llvm14/lib/Target/X86/MCTargetDesc
    contrib/libs/llvm14/lib/Target/X86/TargetInfo
    contrib/libs/llvm14/lib/TextAPI
    contrib/libs/llvm14/tools/llvm-cfi-verify/lib
)

ADDINCL(
    contrib/libs/llvm14/tools/llvm-cfi-verify
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    llvm-cfi-verify.cpp
)

END()
