# Generated by devtools/yamaker.

LIBRARY()

VERSION(16.0.0)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm16
    contrib/libs/llvm16/lib/BinaryFormat
    contrib/libs/llvm16/lib/DebugInfo/CodeView
    contrib/libs/llvm16/lib/DebugInfo/MSF
    contrib/libs/llvm16/lib/Object
    contrib/libs/llvm16/lib/Support
)

ADDINCL(
    contrib/libs/llvm16/lib/DebugInfo/PDB
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    GenericError.cpp
    IPDBSourceFile.cpp
    Native/DbiModuleDescriptor.cpp
    Native/DbiModuleDescriptorBuilder.cpp
    Native/DbiModuleList.cpp
    Native/DbiStream.cpp
    Native/DbiStreamBuilder.cpp
    Native/EnumTables.cpp
    Native/FormatUtil.cpp
    Native/GSIStreamBuilder.cpp
    Native/GlobalsStream.cpp
    Native/Hash.cpp
    Native/HashTable.cpp
    Native/InfoStream.cpp
    Native/InfoStreamBuilder.cpp
    Native/InjectedSourceStream.cpp
    Native/InputFile.cpp
    Native/LinePrinter.cpp
    Native/ModuleDebugStream.cpp
    Native/NamedStreamMap.cpp
    Native/NativeCompilandSymbol.cpp
    Native/NativeEnumGlobals.cpp
    Native/NativeEnumInjectedSources.cpp
    Native/NativeEnumLineNumbers.cpp
    Native/NativeEnumModules.cpp
    Native/NativeEnumSymbols.cpp
    Native/NativeEnumTypes.cpp
    Native/NativeExeSymbol.cpp
    Native/NativeFunctionSymbol.cpp
    Native/NativeInlineSiteSymbol.cpp
    Native/NativeLineNumber.cpp
    Native/NativePublicSymbol.cpp
    Native/NativeRawSymbol.cpp
    Native/NativeSession.cpp
    Native/NativeSourceFile.cpp
    Native/NativeSymbolEnumerator.cpp
    Native/NativeTypeArray.cpp
    Native/NativeTypeBuiltin.cpp
    Native/NativeTypeEnum.cpp
    Native/NativeTypeFunctionSig.cpp
    Native/NativeTypePointer.cpp
    Native/NativeTypeTypedef.cpp
    Native/NativeTypeUDT.cpp
    Native/NativeTypeVTShape.cpp
    Native/PDBFile.cpp
    Native/PDBFileBuilder.cpp
    Native/PDBStringTable.cpp
    Native/PDBStringTableBuilder.cpp
    Native/PublicsStream.cpp
    Native/RawError.cpp
    Native/SymbolCache.cpp
    Native/SymbolStream.cpp
    Native/TpiHashing.cpp
    Native/TpiStream.cpp
    Native/TpiStreamBuilder.cpp
    PDB.cpp
    PDBContext.cpp
    PDBExtras.cpp
    PDBInterfaceAnchors.cpp
    PDBSymDumper.cpp
    PDBSymbol.cpp
    PDBSymbolAnnotation.cpp
    PDBSymbolBlock.cpp
    PDBSymbolCompiland.cpp
    PDBSymbolCompilandDetails.cpp
    PDBSymbolCompilandEnv.cpp
    PDBSymbolCustom.cpp
    PDBSymbolData.cpp
    PDBSymbolExe.cpp
    PDBSymbolFunc.cpp
    PDBSymbolFuncDebugEnd.cpp
    PDBSymbolFuncDebugStart.cpp
    PDBSymbolLabel.cpp
    PDBSymbolPublicSymbol.cpp
    PDBSymbolThunk.cpp
    PDBSymbolTypeArray.cpp
    PDBSymbolTypeBaseClass.cpp
    PDBSymbolTypeBuiltin.cpp
    PDBSymbolTypeCustom.cpp
    PDBSymbolTypeDimension.cpp
    PDBSymbolTypeEnum.cpp
    PDBSymbolTypeFriend.cpp
    PDBSymbolTypeFunctionArg.cpp
    PDBSymbolTypeFunctionSig.cpp
    PDBSymbolTypeManaged.cpp
    PDBSymbolTypePointer.cpp
    PDBSymbolTypeTypedef.cpp
    PDBSymbolTypeUDT.cpp
    PDBSymbolTypeVTable.cpp
    PDBSymbolTypeVTableShape.cpp
    PDBSymbolUnknown.cpp
    PDBSymbolUsingNamespace.cpp
    UDTLayout.cpp
)

END()
