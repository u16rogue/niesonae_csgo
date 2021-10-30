#include <sdk/types.hpp>

// https://www.geoffchappell.com/studies/windows/win32/ntdll/structs/

namespace sdk::env::structs
{
	using ExportFnAddress = unsigned long*;
	using ExportFnNames   = unsigned long*;
	using ExportFnOrdinal = unsigned short*;

	typedef struct _UNICODE_STRING {
		sdk::uint16_t Length;
		sdk::uint16_t MaximumLength;
		wchar_t *Buffer;
	} UNICODE_STRING;

	typedef struct _LIST_ENTRY {
		sdk::ptr_t Flink;
		sdk::ptr_t Blink;
	} LIST_ENTRY, *PLIST_ENTRY;

	typedef struct _LDR_DATA_TABLE_ENTRY {
		LIST_ENTRY     InLoadOrderLinks;
		LIST_ENTRY     InMemoryOrderLinks;
		LIST_ENTRY     InInitializationOrderLinks;
		sdk::ptr_t     DllBase;
		sdk::ptr_t     EntryPoint;
		sdk::size32_t  SizeOfImage;
		UNICODE_STRING FullDllName;
		UNICODE_STRING BaseDllName;
	} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

	typedef struct _PEB_LDR_DATA {
		sdk::uint32_t  Length;
		sdk::uint32_t  Initialized;
		sdk::ptr_t     SsHandle;
		LIST_ENTRY     InLoadOrderModuleList;
		LIST_ENTRY     InMemoryOrderModuleList;
	} PEB_LDR_DATA, *PPEB_LDR_DATA;

	typedef struct _PEB {
		bool  InheritedAddressSpace;
		bool  ReadImageFileExecOptions;
		bool  BeingDebugged;
		bool  SpareBool;
		sdk::ptr_t Mutant;
		sdk::ptr_t ImageBaseAddress;
		PPEB_LDR_DATA Ldr;
	} PEB, *PPEB;

	typedef struct _NT_TIB
	{
		sdk::ptr_t ExceptionList;
		sdk::ptr_t StackBase;
		sdk::ptr_t StackLimit;
		sdk::ptr_t SubSystemTib;
		union
		{
			sdk::ptr_t FiberData;
			sdk::ptr_t Version;
		};
		sdk::ptr_t ArbitraryUserPointer;
		sdk::ptr_t Self;
	} NT_TIB, *PNT_TIB;

	typedef struct _TEB
	{
		NT_TIB NtTib;
		sdk::ptr_t EnvironmentPointer;
		sdk::ptr_t ClientId[2];
		sdk::ptr_t ActiveRpcHandle;
		sdk::ptr_t ThreadLocalStoragePointer;
		PPEB  ProcessEnvironmentBlock;
	} TEB, *PTEB;

	// DOS .EXE header
	typedef struct _IMAGE_DOS_HEADER 
	{     
		sdk::uint16_t e_magic;    // Magic number
		sdk::uint16_t e_cblp;     // Bytes on last page of file
		sdk::uint16_t e_cp;       // Pages in file
		sdk::uint16_t e_crlc;     // Relocations
		sdk::uint16_t e_cparhdr;  // Size of header in paragraphs
		sdk::uint16_t e_minalloc; // Minimum extra paragraphs needed
		sdk::uint16_t e_maxalloc; // Maximum extra paragraphs needed
		sdk::uint16_t e_ss;       // Initial (relative) SS value
		sdk::uint16_t e_sp;       // Initial SP value
		sdk::uint16_t e_csum;     // Checksum
		sdk::uint16_t e_ip;       // Initial IP value
		sdk::uint16_t e_cs;       // Initial (relative) CS value
		sdk::uint16_t e_lfarlc;   // File address of relocation table
		sdk::uint16_t e_ovno;     // Overlay number
		sdk::uint16_t e_res[4];   // Reserved words
		sdk::uint16_t e_oemid;    // OEM identifier (for e_oeminfo)
		sdk::uint16_t e_oeminfo;  // OEM information; e_oemid specific
		sdk::uint16_t e_res2[10]; // Reserved words
		sdk::uint16_t e_lfanew;   // File address of new exe header
	} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

	typedef struct _IMAGE_DATA_DIRECTORY
	{
		sdk::uint32_t   VirtualAddress;
		sdk::uint32_t   Size;
	} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

	typedef struct _IMAGE_OPTIONAL_HEADER
	{
		//
		// Standard fields.
		//
		sdk::int16_t   Magic;
		sdk::byte_t    MajorLinkerVersion;
		sdk::byte_t    MinorLinkerVersion;
		sdk::uint32_t  SizeOfCode;
		sdk::uint32_t  SizeOfInitializedData;
		sdk::uint32_t  SizeOfUninitializedData;
		sdk::uint32_t  AddressOfEntryPoint;
		sdk::uint32_t  BaseOfCode;
		sdk::uint32_t  BaseOfData;
		//
		// NT additional fields.
		//
		sdk::uint32_t   ImageBase;
		sdk::uint32_t   SectionAlignment;
		sdk::uint32_t   FileAlignment;
		sdk::uint16_t   MajorOperatingSystemVersion;
		sdk::uint16_t   MinorOperatingSystemVersion;
		sdk::uint16_t   MajorImageVersion;
		sdk::uint16_t   MinorImageVersion;
		sdk::uint16_t   MajorSubsystemVersion;
		sdk::uint16_t   MinorSubsystemVersion;
		sdk::uint32_t   Win32VersionValue;
		sdk::uint32_t   SizeOfImage;
		sdk::uint32_t   SizeOfHeaders;
		sdk::uint32_t   CheckSum;
		sdk::uint16_t   Subsystem;
		sdk::uint16_t   DllCharacteristics;
		sdk::uint32_t   SizeOfStackReserve;
		sdk::uint32_t   SizeOfStackCommit;
		sdk::uint32_t   SizeOfHeapReserve;
		sdk::uint32_t   SizeOfHeapCommit;
		sdk::uint32_t   LoaderFlags;
		sdk::uint32_t   NumberOfRvaAndSizes;
		IMAGE_DATA_DIRECTORY DataDirectory[16];
	} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;


	typedef struct _IMAGE_OPTIONAL_HEADER64
	{
		sdk::uint16_t   Magic;
		sdk::byte_t     MajorLinkerVersion;
		sdk::byte_t     MinorLinkerVersion;
		sdk::uint32_t   SizeOfCode;
		sdk::uint32_t   SizeOfInitializedData;
		sdk::uint32_t   SizeOfUninitializedData;
		sdk::uint32_t   AddressOfEntryPoint;
		sdk::uint32_t   BaseOfCode;
		sdk::uint64_t   ImageBase;
		sdk::uint32_t   SectionAlignment;
		sdk::uint32_t   FileAlignment;
		sdk::uint16_t   MajorOperatingSystemVersion;
		sdk::uint16_t   MinorOperatingSystemVersion;
		sdk::uint16_t   MajorImageVersion;
		sdk::uint16_t   MinorImageVersion;
		sdk::uint16_t   MajorSubsystemVersion;
		sdk::uint16_t   MinorSubsystemVersion;
		sdk::uint32_t   Win32VersionValue;
		sdk::uint32_t   SizeOfImage;
		sdk::uint32_t   SizeOfHeaders;
		sdk::uint32_t   CheckSum;
		sdk::uint16_t   Subsystem;
		sdk::uint16_t   DllCharacteristics;
		sdk::uint64_t   SizeOfStackReserve;
		sdk::uint64_t   SizeOfStackCommit;
		sdk::uint64_t   SizeOfHeapReserve;
		sdk::uint64_t   SizeOfHeapCommit;
		sdk::uint32_t   LoaderFlags;
		sdk::uint32_t   NumberOfRvaAndSizes;
		IMAGE_DATA_DIRECTORY DataDirectory[16];
	} IMAGE_OPTIONAL_HEADER64, *PIMAGE_OPTIONAL_HEADER64;

	typedef struct _IMAGE_FILE_HEADER {
		sdk::uint16_t Machine;
		sdk::uint16_t NumberOfSections;
		sdk::uint32_t TimeDateStamp;
		sdk::uint32_t PointerToSymbolTable;
		sdk::uint32_t NumberOfSymbols;
		sdk::uint16_t SizeOfOptionalHeader;
		sdk::uint16_t Characteristics;
	} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

	typedef struct _IMAGE_NT_HEADERS64
	{
		sdk::uint32_t           Signature;
		IMAGE_FILE_HEADER       FileHeader;
		IMAGE_OPTIONAL_HEADER64 OptionalHeader;
	} IMAGE_NT_HEADERS64, *PIMAGE_NT_HEADERS64;

	typedef struct _IMAGE_NT_HEADERS
	{
		sdk::uint32_t           Signature;
		IMAGE_FILE_HEADER       FileHeader;
		IMAGE_OPTIONAL_HEADER32 OptionalHeader;
	} IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;
	
	typedef struct _IMAGE_EXPORT_DIRECTORY {
		sdk::uint32_t Characteristics;
		sdk::uint32_t TimeDateStamp;
		sdk::uint16_t MajorVersion;
		sdk::uint16_t MinorVersion;
		sdk::uint32_t Name;
		sdk::uint32_t Base;
		sdk::uint32_t NumberOfFunctions;
		sdk::uint32_t NumberOfNames;
		sdk::uint32_t AddressOfFunctions;    // RVA from base of image
		sdk::uint32_t AddressOfNames;        // RVA from base of image
		sdk::uint32_t AddressOfNameOrdinals; // RVA from base of image
	} IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;

	#ifdef _M_IX86
		using IMAGE_OPTIONAL_HEADER  = IMAGE_OPTIONAL_HEADER32;
		using PIMAGE_OPTIONAL_HEADER = PIMAGE_OPTIONAL_HEADER32;
		using IMAGE_NT_HEADERS       = IMAGE_NT_HEADERS32;
		using PIMAGE_NT_HEADERS      = PIMAGE_NT_HEADERS32;
	#elif _M_AMD64
		using IMAGE_OPTIONAL_HEADER  = IMAGE_OPTIONAL_HEADER64;
		using PIMAGE_OPTIONAL_HEADER = PIMAGE_OPTIONAL_HEADER64;
		using IMAGE_NT_HEADERS       = IMAGE_NT_HEADERS64;
		using PIMAGE_NT_HEADERS      = PIMAGE_NT_HEADERS64;
	#endif
}