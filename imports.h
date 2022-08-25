#pragma once
#pragma comment( lib, "ntdll" )
#include <Windows.h>
#ifdef __cplusplus
extern "C"
{
#endif
	typedef enum _PS_ATTRIBUTE_NUM
	{
		PsAttributeParentProcess, // in HANDLE
		PsAttributeDebugObject, // in HANDLE
		PsAttributeToken, // in HANDLE
		PsAttributeClientId, // out PCLIENT_ID
		PsAttributeTebAddress, // out PTEB *
		PsAttributeImageName, // in PWSTR
		PsAttributeImageInfo, // out PSECTION_IMAGE_INFORMATION
		PsAttributeMemoryReserve, // in PPS_MEMORY_RESERVE
		PsAttributePriorityClass, // in UCHAR
		PsAttributeErrorMode, // in ULONG
		PsAttributeStdHandleInfo, // 10, in PPS_STD_HANDLE_INFO
		PsAttributeHandleList, // in HANDLE[]
		PsAttributeGroupAffinity, // in PGROUP_AFFINITY
		PsAttributePreferredNode, // in PUSHORT
		PsAttributeIdealProcessor, // in PPROCESSOR_NUMBER
		PsAttributeUmsThread, // ? in PUMS_CREATE_THREAD_ATTRIBUTES
		PsAttributeMitigationOptions, // in PPS_MITIGATION_OPTIONS_MAP (PROCESS_CREATION_MITIGATION_POLICY_*) // since WIN8
		PsAttributeProtectionLevel, // in PS_PROTECTION // since WINBLUE
		PsAttributeSecureProcess, // in PPS_TRUSTLET_CREATE_ATTRIBUTES, since THRESHOLD
		PsAttributeJobList, // in HANDLE[]
		PsAttributeChildProcessPolicy, // 20, in PULONG (PROCESS_CREATION_CHILD_PROCESS_*) // since THRESHOLD2
		PsAttributeAllApplicationPackagesPolicy, // in PULONG (PROCESS_CREATION_ALL_APPLICATION_PACKAGES_*) // since REDSTONE
		PsAttributeWin32kFilter, // in PWIN32K_SYSCALL_FILTER
		PsAttributeSafeOpenPromptOriginClaim, // in
		PsAttributeBnoIsolation, // in PPS_BNO_ISOLATION_PARAMETERS // since REDSTONE2
		PsAttributeDesktopAppPolicy, // in PULONG (PROCESS_CREATION_DESKTOP_APP_*)
		PsAttributeChpe, // in BOOLEAN // since REDSTONE3
		PsAttributeMitigationAuditOptions, // in PPS_MITIGATION_AUDIT_OPTIONS_MAP (PROCESS_CREATION_MITIGATION_AUDIT_POLICY_*) // since 21H1
		PsAttributeMachineType, // in WORD // since 21H2
		PsAttributeComponentFilter,
		PsAttributeEnableOptionalXStateFeatures, // since WIN11
		PsAttributeMax
	} PS_ATTRIBUTE_NUM;

#define RTL_USER_PROCESS_PARAMETERS_NORMALIZED              0x01
#define PS_ATTRIBUTE_NUMBER_MASK    0x0000ffff
#define PS_ATTRIBUTE_THREAD         0x00010000 // Attribute may be used with thread creation
#define PS_ATTRIBUTE_INPUT          0x00020000 // Attribute is input only
#define PS_ATTRIBUTE_ADDITIVE       0x00040000 // Attribute may be "accumulated", e.g. bitmasks, counters, etc.

#define PsAttributeValue(Number, Thread, Input, Additive) \
    (((Number) & PS_ATTRIBUTE_NUMBER_MASK) | \
    ((Thread) ? PS_ATTRIBUTE_THREAD : 0) | \
    ((Input) ? PS_ATTRIBUTE_INPUT : 0) | \
    ((Additive) ? PS_ATTRIBUTE_ADDITIVE : 0))

#define PS_ATTRIBUTE_PARENT_PROCESS \
    PsAttributeValue(PsAttributeParentProcess, FALSE, TRUE, TRUE) // 0x60000
#define PS_ATTRIBUTE_DEBUG_OBJECT \
    PsAttributeValue(PsAttributeDebugObject, FALSE, TRUE, TRUE) // 0x60001
#define PS_ATTRIBUTE_TOKEN \
    PsAttributeValue(PsAttributeToken, FALSE, TRUE, TRUE) // 0x60002
#define PS_ATTRIBUTE_CLIENT_ID \
    PsAttributeValue(PsAttributeClientId, TRUE, FALSE, FALSE) // 0x10003
#define PS_ATTRIBUTE_TEB_ADDRESS \
    PsAttributeValue(PsAttributeTebAddress, TRUE, FALSE, FALSE) // 0x10004
#define PS_ATTRIBUTE_IMAGE_NAME \
    PsAttributeValue(PsAttributeImageName, FALSE, TRUE, FALSE) // 0x20005
#define PS_ATTRIBUTE_IMAGE_INFO \
    PsAttributeValue(PsAttributeImageInfo, FALSE, FALSE, FALSE) // 0x6
#define PS_ATTRIBUTE_MEMORY_RESERVE \
    PsAttributeValue(PsAttributeMemoryReserve, FALSE, TRUE, FALSE) // 0x20007
#define PS_ATTRIBUTE_PRIORITY_CLASS \
    PsAttributeValue(PsAttributePriorityClass, FALSE, TRUE, FALSE) // 0x20008
#define PS_ATTRIBUTE_ERROR_MODE \
    PsAttributeValue(PsAttributeErrorMode, FALSE, TRUE, FALSE) // 0x20009
#define PS_ATTRIBUTE_STD_HANDLE_INFO \
    PsAttributeValue(PsAttributeStdHandleInfo, FALSE, TRUE, FALSE) // 0x2000A
#define PS_ATTRIBUTE_HANDLE_LIST \
    PsAttributeValue(PsAttributeHandleList, FALSE, TRUE, FALSE) // 0x2000B
#define PS_ATTRIBUTE_GROUP_AFFINITY \
    PsAttributeValue(PsAttributeGroupAffinity, TRUE, TRUE, FALSE) // 0x2000C
#define PS_ATTRIBUTE_PREFERRED_NODE \
    PsAttributeValue(PsAttributePreferredNode, FALSE, TRUE, FALSE) // 0x2000D
#define PS_ATTRIBUTE_IDEAL_PROCESSOR \
    PsAttributeValue(PsAttributeIdealProcessor, TRUE, TRUE, FALSE) // 0x2000E
#define PS_ATTRIBUTE_MITIGATION_OPTIONS \
    PsAttributeValue(PsAttributeMitigationOptions, FALSE, TRUE, FALSE) // 0x60010
#define PS_ATTRIBUTE_PROTECTION_LEVEL \
    PsAttributeValue(PsAttributeProtectionLevel, FALSE, TRUE, FALSE) // 0x20011
#define PS_ATTRIBUTE_SECURE_PROCESS \
    PsAttributeValue(PsAttributeSecureProcess, FALSE, TRUE, FALSE) // 0x20012
#define PS_ATTRIBUTE_JOB_LIST \
    PsAttributeValue(PsAttributeJobList, FALSE, TRUE, FALSE) // 0x20013
#define PS_ATTRIBUTE_CHILD_PROCESS_POLICY \
    PsAttributeValue(PsAttributeChildProcessPolicy, FALSE, TRUE, FALSE) // 0x20014
#define PS_ATTRIBUTE_ALL_APPLICATION_PACKAGES_POLICY \
    PsAttributeValue(PsAttributeAllApplicationPackagesPolicy, FALSE, TRUE, FALSE) // 0x20015
#define PS_ATTRIBUTE_WIN32K_FILTER \
    PsAttributeValue(PsAttributeWin32kFilter, FALSE, TRUE, FALSE) // 0x20016
#define PS_ATTRIBUTE_SAFE_OPEN_PROMPT_ORIGIN_CLAIM \
    PsAttributeValue(PsAttributeSafeOpenPromptOriginClaim, FALSE, TRUE, FALSE) // 0x20017
#define PS_ATTRIBUTE_BNO_ISOLATION \
    PsAttributeValue(PsAttributeBnoIsolation, FALSE, TRUE, FALSE) // 0x20018
#define PS_ATTRIBUTE_DESKTOP_APP_POLICY \
    PsAttributeValue(PsAttributeDesktopAppPolicy, FALSE, TRUE, FALSE) // 0x20019
#define PS_ATTRIBUTE_CHPE \
    PsAttributeValue(PsAttributeChpe, FALSE, TRUE, TRUE) // 0x6001A
#define PS_ATTRIBUTE_MITIGATION_AUDIT_OPTIONS \
    PsAttributeValue(PsAttributeMitigationAuditOptions, FALSE, TRUE, FALSE) // 0x2001B
#define PS_ATTRIBUTE_MACHINE_TYPE \
    PsAttributeValue(PsAttributeMachineType, FALSE, TRUE, TRUE) // 0x6001C
#define PS_ATTRIBUTE_COMPONENT_FILTER \
    PsAttributeValue(PsAttributeComponentFilter, FALSE, TRUE, FALSE) // 0x2001D
#define PS_ATTRIBUTE_ENABLE_OPTIONAL_XSTATE_FEATURES \
    PsAttributeValue(PsAttributeEnableOptionalXStateFeatures, TRUE, TRUE, FALSE) // 0x3001E

	typedef struct _PS_ATTRIBUTE
	{
		ULONG_PTR Attribute;                // PROC_THREAD_ATTRIBUTE_XXX | PROC_THREAD_ATTRIBUTE_XXX modifiers, see ProcThreadAttributeValue macro and Windows Internals 6 (372)
		SIZE_T Size;                        // Size of Value or *ValuePtr
		union
		{
			ULONG_PTR Value;                // Reserve 8 bytes for data (such as a Handle or a data pointer)
			PVOID ValuePtr;                 // data pointer
		};
		PSIZE_T ReturnLength;               // Either 0 or specifies size of data returned to caller via "ValuePtr"
	} PS_ATTRIBUTE, * PPS_ATTRIBUTE;

	typedef enum _PS_IFEO_KEY_STATE
	{
		PsReadIFEOAllValues,
		PsSkipIFEODebugger,
		PsSkipAllIFEO,
		PsMaxIFEOKeyStates
	} PS_IFEO_KEY_STATE, * PPS_IFEO_KEY_STATE;

	typedef enum _PS_CREATE_STATE
	{
		PsCreateInitialState,
		PsCreateFailOnFileOpen,
		PsCreateFailOnSectionCreate,
		PsCreateFailExeFormat,
		PsCreateFailMachineMismatch,
		PsCreateFailExeName, // Debugger specified
		PsCreateSuccess,
		PsCreateMaximumStates
	} PS_CREATE_STATE;

	typedef struct _PS_CREATE_INFO
	{
		SIZE_T Size;
		PS_CREATE_STATE State;
		union
		{
			// PsCreateInitialState
			struct
			{
				union
				{
					ULONG InitFlags;
					struct
					{
						UCHAR WriteOutputOnExit : 1;
						UCHAR DetectManifest : 1;
						UCHAR IFEOSkipDebugger : 1;
						UCHAR IFEODoNotPropagateKeyState : 1;
						UCHAR SpareBits1 : 4;
						UCHAR SpareBits2 : 8;
						USHORT ProhibitedImageCharacteristics : 16;
					} s1;
				} u1;
				ACCESS_MASK AdditionalFileAccess;
			} InitState;

			// PsCreateFailOnSectionCreate
			struct
			{
				HANDLE FileHandle;
			} FailSection;

			// PsCreateFailExeFormat
			struct
			{
				USHORT DllCharacteristics;
			} ExeFormat;

			// PsCreateFailExeName
			struct
			{
				HANDLE IFEOKey;
			} ExeName;

			// PsCreateSuccess
			struct
			{
				union
				{
					ULONG OutputFlags;
					struct
					{
						UCHAR ProtectedProcess : 1;
						UCHAR AddressSpaceOverride : 1;
						UCHAR DevOverrideEnabled : 1; // From Image File Execution Options
						UCHAR ManifestDetected : 1;
						UCHAR ProtectedProcessLight : 1;
						UCHAR SpareBits1 : 3;
						UCHAR SpareBits2 : 8;
						USHORT SpareBits3 : 16;
					} s2;
				} u2;
				HANDLE FileHandle;
				HANDLE SectionHandle;
				ULONGLONG UserProcessParametersNative;
				ULONG UserProcessParametersWow64;
				ULONG CurrentParameterFlags;
				ULONGLONG PebAddressNative;
				ULONG PebAddressWow64;
				ULONGLONG ManifestAddress;
				ULONG ManifestSize;
			} SuccessState;
		};
	} PS_CREATE_INFO, * PPS_CREATE_INFO;
	typedef struct _UNICODE_STRING
	{
		USHORT Length;
		USHORT MaximumLength;
		PWSTR Buffer;
	} UNICODE_STRING, * PUNICODE_STRING;
	typedef const UNICODE_STRING* PCUNICODE_STRING;
	typedef struct _PS_ATTRIBUTE_LIST
	{
		SIZE_T TotalLength;                 // sizeof(PS_ATTRIBUTE_LIST)
		PS_ATTRIBUTE Attributes[6];         // Depends on how many attribute entries should be supplied to NtCreateUserProcess
	} PS_ATTRIBUTE_LIST, * PPS_ATTRIBUTE_LIST;
	typedef struct _CURDIR
	{
		UNICODE_STRING DosPath;
		HANDLE Handle;
	} CURDIR, * PCURDIR;
	typedef struct _RTL_DRIVE_LETTER_CURDIR
	{
		USHORT Flags;
		USHORT Length;
		ULONG TimeStamp;
		UNICODE_STRING DosPath;
	} RTL_DRIVE_LETTER_CURDIR, * PRTL_DRIVE_LETTER_CURDIR;

#define RTL_MAX_DRIVE_LETTERS 32
	typedef struct _RTL_USER_PROCESS_PARAMETERS
	{
		ULONG MaximumLength;
		ULONG Length;

		ULONG Flags;
		ULONG DebugFlags;

		HANDLE ConsoleHandle;
		ULONG ConsoleFlags;
		HANDLE StandardInput;
		HANDLE StandardOutput;
		HANDLE StandardError;

		CURDIR CurrentDirectory;
		UNICODE_STRING DllPath;
		UNICODE_STRING ImagePathName;
		UNICODE_STRING CommandLine;
		PWCHAR Environment;

		ULONG StartingX;
		ULONG StartingY;
		ULONG CountX;
		ULONG CountY;
		ULONG CountCharsX;
		ULONG CountCharsY;
		ULONG FillAttribute;

		ULONG WindowFlags;
		ULONG ShowWindowFlags;
		UNICODE_STRING WindowTitle;
		UNICODE_STRING DesktopInfo;
		UNICODE_STRING ShellInfo;
		UNICODE_STRING RuntimeData;
		RTL_DRIVE_LETTER_CURDIR CurrentDirectories[RTL_MAX_DRIVE_LETTERS];

		ULONG_PTR EnvironmentSize;
		ULONG_PTR EnvironmentVersion;
		PVOID PackageDependencyData;
		ULONG ProcessGroupId;
		ULONG LoaderThreads;
	} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;
	typedef struct _OBJECT_ATTRIBUTES
	{
		ULONG Length;
		HANDLE RootDirectory;
		PUNICODE_STRING ObjectName;
		ULONG Attributes;
		PVOID SecurityDescriptor;
		PVOID SecurityQualityOfService;
	} OBJECT_ATTRIBUTES, * POBJECT_ATTRIBUTES;
	NTSYSAPI
		NTSTATUS
		NTAPI
		RtlDestroyProcessParameters(PRTL_USER_PROCESS_PARAMETERS ProcessParameters);

	NTSYSAPI
		BOOLEAN
		NTAPI
		RtlFreeHeap(PVOID HeapHandle, ULONG Flags, PVOID BaseAddress);

	NTSYSAPI
		VOID
		NTAPI
		RtlInitUnicodeString(PUNICODE_STRING DestinationString, PWSTR SourceString);
	NTSYSAPI
		NTSTATUS
		NTAPI
		RtlCreateProcessParametersEx(
			PRTL_USER_PROCESS_PARAMETERS* pProcessParameters,
			PUNICODE_STRING ImagePathName,
			PUNICODE_STRING DllPath,
			PUNICODE_STRING CurrentDirectory,
			PUNICODE_STRING CommandLine,
			PVOID Environment,
			PUNICODE_STRING WindowTitle,
			PUNICODE_STRING DesktopInfo,
			PUNICODE_STRING ShellInfo,
			PUNICODE_STRING RuntimeData,
			ULONG Flags
		);
	NTSYSCALLAPI
		NTSTATUS
		NTAPI
		NtCreateUserProcess(
			_Out_ PHANDLE ProcessHandle,
			_Out_ PHANDLE ThreadHandle,
			_In_ ACCESS_MASK ProcessDesiredAccess,
			_In_ ACCESS_MASK ThreadDesiredAccess,
			_In_opt_ POBJECT_ATTRIBUTES ProcessObjectAttributes,
			_In_opt_ POBJECT_ATTRIBUTES ThreadObjectAttributes,
			_In_ ULONG ProcessFlags,
			_In_ ULONG ThreadFlags,
			_In_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters,
			_Inout_ PPS_CREATE_INFO CreateInfo,
			_In_ PPS_ATTRIBUTE_LIST AttributeList
		);

	NTSYSAPI
		PVOID
		NTAPI
		RtlAllocateHeap(
			_In_ PVOID HeapHandle,
			_In_opt_ ULONG Flags,
			_In_ SIZE_T Size
		);

	typedef struct _PS_STD_HANDLE_INFO
	{
		union
		{
			ULONG Flags;
			struct
			{
				ULONG StdHandleState : 2; // PS_STD_HANDLE_STATE
				ULONG PseudoHandleMask : 3; // PS_STD_*
			} s;
		};
		ULONG StdHandleSubsystemType;
	} PS_STD_HANDLE_INFO, * PPS_STD_HANDLE_INFO;
	typedef struct _CLIENT_ID
	{
		HANDLE UniqueProcess;
		HANDLE UniqueThread;
	} CLIENT_ID, * PCLIENT_ID;

	typedef struct _SECTION_IMAGE_INFORMATION
	{
		PVOID TransferAddress; // Entry point
		ULONG ZeroBits;
		SIZE_T MaximumStackSize;
		SIZE_T CommittedStackSize;
		ULONG SubSystemType;
		union
		{
			struct
			{
				USHORT SubSystemMinorVersion;
				USHORT SubSystemMajorVersion;
			} s1;
			ULONG SubSystemVersion;
		} u1;
		union
		{
			struct
			{
				USHORT MajorOperatingSystemVersion;
				USHORT MinorOperatingSystemVersion;
			} s2;
			ULONG OperatingSystemVersion;
		} u2;
		USHORT ImageCharacteristics;
		USHORT DllCharacteristics;
		USHORT Machine;
		BOOLEAN ImageContainsCode;
		union
		{
			UCHAR ImageFlags;
			struct
			{
				UCHAR ComPlusNativeReady : 1;
				UCHAR ComPlusILOnly : 1;
				UCHAR ImageDynamicallyRelocated : 1;
				UCHAR ImageMappedFlat : 1;
				UCHAR BaseBelow4gb : 1;
				UCHAR ComPlusPrefer32bit : 1;
				UCHAR Reserved : 2;
			} s3;
		} u3;
		ULONG LoaderFlags;
		ULONG ImageFileSize;
		ULONG CheckSum;
	} SECTION_IMAGE_INFORMATION, * PSECTION_IMAGE_INFORMATION;
	typedef struct _PEB_LDR_DATA
	{
		ULONG Length;
		BOOLEAN Initialized;
		HANDLE SsHandle;
		LIST_ENTRY InLoadOrderModuleList;
		LIST_ENTRY InMemoryOrderModuleList;
		LIST_ENTRY InInitializationOrderModuleList;
		PVOID EntryInProgress;
		BOOLEAN ShutdownInProgress;
		HANDLE ShutdownThreadId;
	} PEB_LDR_DATA, * PPEB_LDR_DATA;
	typedef struct _PEB
	{
		BOOLEAN InheritedAddressSpace;
		BOOLEAN ReadImageFileExecOptions;
		BOOLEAN BeingDebugged;
		union
		{
			BOOLEAN BitField;
			struct
			{
				BOOLEAN ImageUsesLargePages : 1;
				BOOLEAN IsProtectedProcess : 1;
				BOOLEAN IsImageDynamicallyRelocated : 1;
				BOOLEAN SkipPatchingUser32Forwarders : 1;
				BOOLEAN IsPackagedProcess : 1;
				BOOLEAN IsAppContainer : 1;
				BOOLEAN IsProtectedProcessLight : 1;
				BOOLEAN IsLongPathAwareProcess : 1;
			} s1;
		} u1;

		HANDLE Mutant;

		PVOID ImageBaseAddress;
		PPEB_LDR_DATA Ldr;
		PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
		PVOID SubSystemData;
		PVOID ProcessHeap;
	} PEB, * PPEB;

	typedef struct _TEB
	{
		NT_TIB NtTib;

		PVOID EnvironmentPointer;
		CLIENT_ID ClientId;
		PVOID ActiveRpcHandle;
		PVOID ThreadLocalStoragePointer;
		PPEB ProcessEnvironmentBlock;
	} TEB, * PTEB;

#define NtCurrentPeb()            (NtCurrentTeb()->ProcessEnvironmentBlock)
#define RtlProcessHeap()          (NtCurrentPeb()->ProcessHeap)
#ifdef __cplusplus
}
#endif