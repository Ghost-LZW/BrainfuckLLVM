cmake_minimum_required(VERSION 3.14)

project(Brainfuck VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# don't work like expect
# llvm_map_components_to_libnames(llvm_libs support core irreader x86codegen x86asmparser asmparser asmprinter)
# set(llvm_libs "LLVM-13")

set(llvm_libs
  LLVMWindowsManifest
  LLVMWindowsDriver
  LLVMXRay
  LLVMLibDriver
  LLVMDlltoolDriver
  LLVMCoverage
  LLVMLineEditor
  LLVMXCoreDisassembler
  LLVMXCoreCodeGen
  LLVMXCoreDesc
  LLVMXCoreInfo
  LLVMX86TargetMCA
  LLVMX86Disassembler
  LLVMX86AsmParser
  LLVMX86CodeGen
  LLVMX86Desc
  LLVMX86Info
  LLVMWebAssemblyDisassembler
  LLVMWebAssemblyAsmParser
  LLVMWebAssemblyCodeGen
  LLVMWebAssemblyDesc
  LLVMWebAssemblyUtils
  LLVMWebAssemblyInfo
  LLVMVEDisassembler
  LLVMVEAsmParser
  LLVMVECodeGen
  LLVMVEDesc
  LLVMVEInfo
  LLVMSystemZDisassembler
  LLVMSystemZAsmParser
  LLVMSystemZCodeGen
  LLVMSystemZDesc
  LLVMSystemZInfo
  LLVMSparcDisassembler
  LLVMSparcAsmParser
  LLVMSparcCodeGen
  LLVMSparcDesc
  LLVMSparcInfo
  LLVMRISCVDisassembler
  LLVMRISCVAsmParser
  LLVMRISCVCodeGen
  LLVMRISCVDesc
  LLVMRISCVInfo
  LLVMPowerPCDisassembler
  LLVMPowerPCAsmParser
  LLVMPowerPCCodeGen
  LLVMPowerPCDesc
  LLVMPowerPCInfo
  LLVMNVPTXCodeGen
  LLVMNVPTXDesc
  LLVMNVPTXInfo
  LLVMMSP430Disassembler
  LLVMMSP430AsmParser
  LLVMMSP430CodeGen
  LLVMMSP430Desc
  LLVMMSP430Info
  LLVMMipsDisassembler
  LLVMMipsAsmParser
  LLVMMipsCodeGen
  LLVMMipsDesc
  LLVMMipsInfo
  LLVMLanaiDisassembler
  LLVMLanaiCodeGen
  LLVMLanaiAsmParser
  LLVMLanaiDesc
  LLVMLanaiInfo
  LLVMHexagonDisassembler
  LLVMHexagonCodeGen
  LLVMHexagonAsmParser
  LLVMHexagonDesc
  LLVMHexagonInfo
  LLVMBPFDisassembler
  LLVMBPFAsmParser
  LLVMBPFCodeGen
  LLVMBPFDesc
  LLVMBPFInfo
  LLVMAVRDisassembler
  LLVMAVRAsmParser
  LLVMAVRCodeGen
  LLVMAVRDesc
  LLVMAVRInfo
  LLVMARMDisassembler
  LLVMARMAsmParser
  LLVMARMCodeGen
  LLVMARMDesc
  LLVMARMUtils
  LLVMARMInfo
  LLVMAMDGPUTargetMCA
  LLVMAMDGPUDisassembler
  LLVMAMDGPUAsmParser
  LLVMAMDGPUCodeGen
  LLVMAMDGPUDesc
  LLVMAMDGPUUtils
  LLVMAMDGPUInfo
  LLVMAArch64Disassembler
  LLVMAArch64AsmParser
  LLVMAArch64CodeGen
  LLVMAArch64Desc
  LLVMAArch64Utils
  LLVMAArch64Info
  LLVMOrcJIT
  LLVMMCJIT
  LLVMJITLink
  LLVMInterpreter
  LLVMExecutionEngine
  LLVMRuntimeDyld
  LLVMOrcTargetProcess
  LLVMOrcShared
  LLVMDWP
  LLVMDebugInfoGSYM
  LLVMOption
  LLVMObjectYAML
  LLVMObjCopy
  LLVMMCA
  LLVMMCDisassembler
  LLVMLTO
  LLVMPasses
  LLVMCFGuard
  LLVMCoroutines
  LLVMObjCARCOpts
  LLVMipo
  LLVMVectorize
  LLVMLinker
  LLVMInstrumentation
  LLVMFrontendOpenMP
  LLVMFrontendOpenACC
  LLVMExtensions
  LLVMDWARFLinker
  LLVMGlobalISel
  LLVMMIRParser
  LLVMAsmPrinter
  LLVMSelectionDAG
  LLVMCodeGen
  LLVMIRReader
  LLVMAsmParser
  LLVMInterfaceStub
  LLVMFileCheck
  LLVMFuzzMutate
  LLVMTarget
  LLVMScalarOpts
  LLVMInstCombine
  LLVMAggressiveInstCombine
  LLVMTransformUtils
  LLVMBitWriter
  LLVMAnalysis
  LLVMProfileData
  LLVMSymbolize
  LLVMDebugInfoPDB
  LLVMDebugInfoMSF
  LLVMDebugInfoDWARF
  LLVMObject
  LLVMTextAPI
  LLVMMCParser
  LLVMMC
  LLVMDebugInfoCodeView
  LLVMBitReader
  LLVMCore
  LLVMRemarks
  LLVMBitstreamReader
  LLVMBinaryFormat
  LLVMTableGen
  LLVMSupport
  LLVMDemangle  
  )

message(STATUS "llvm " ${llvm_libs})

set(BrainfuckIncludePath ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BrainfuckLibraryPath ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(BrainfuckToolsPath ${CMAKE_CURRENT_SOURCE_DIR}/tools)

set(CMAKE_CXX_FLAGS "-g -Wall -Werror -fno-rtti")

configure_file(${BrainfuckIncludePath}/BrainfuckConfig.h.in ${BrainfuckIncludePath}/BrainfuckConfig.h)

include_directories(${BrainfuckIncludePath})

add_subdirectory(${BrainfuckLibraryPath})
add_subdirectory(${BrainfuckToolsPath})

install(TARGETS brainfuck
        DESTINATION bin
        )
