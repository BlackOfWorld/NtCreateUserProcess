#include <cstdio>
#include <Windows.h>
#include "imports.h"
int main()
{
	// Path to the image file from which the process will be created
	UNICODE_STRING NtImagePath, Params, ImagePath;
	RtlInitUnicodeString(&ImagePath, (PWSTR)L"C:\\Windows\\System32\\cmd.exe");

	RtlInitUnicodeString(&NtImagePath, (PWSTR)L"\\??\\C:\\Windows\\System32\\cmd.exe");
	RtlInitUnicodeString(&Params, (PWSTR)L"\"C:\\WINDOWS\\SYSTEM32\\cmd.exe\" /k echo Hello world!");
	// Create the process parameters
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = NULL;
	RtlCreateProcessParametersEx(&ProcessParameters, &ImagePath, NULL, NULL, &Params, NULL, NULL, NULL, NULL, NULL, RTL_USER_PROCESS_PARAMETERS_NORMALIZED);

	// Initialize the PS_CREATE_INFO structure
	PS_CREATE_INFO CreateInfo = { 0 };
	CreateInfo.Size = sizeof(CreateInfo);
	CreateInfo.State = PsCreateInitialState;

	//Skip Image File Execution Options debugger
	CreateInfo.InitState.u1.InitFlags = PsSkipIFEODebugger;

	OBJECT_ATTRIBUTES objAttr = { sizeof(OBJECT_ATTRIBUTES)};
	PPS_STD_HANDLE_INFO stdHandleInfo = (PPS_STD_HANDLE_INFO)RtlAllocateHeap(RtlProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PS_STD_HANDLE_INFO));
	PCLIENT_ID clientId = (PCLIENT_ID)RtlAllocateHeap(RtlProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PS_ATTRIBUTE));
	PSECTION_IMAGE_INFORMATION SecImgInfo = (PSECTION_IMAGE_INFORMATION)RtlAllocateHeap(RtlProcessHeap(), HEAP_ZERO_MEMORY, sizeof(SECTION_IMAGE_INFORMATION));
	PPS_ATTRIBUTE_LIST AttributeList = (PS_ATTRIBUTE_LIST*)RtlAllocateHeap(RtlProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PS_ATTRIBUTE_LIST));

	// Create necessary attributes
	AttributeList->TotalLength = sizeof(PS_ATTRIBUTE_LIST);
	AttributeList->Attributes[0].Attribute = PS_ATTRIBUTE_CLIENT_ID;
	AttributeList->Attributes[0].Size = sizeof(CLIENT_ID);
	AttributeList->Attributes[0].ValuePtr = clientId;

	AttributeList->Attributes[1].Attribute = PS_ATTRIBUTE_IMAGE_INFO;
	AttributeList->Attributes[1].Size = sizeof(SECTION_IMAGE_INFORMATION);
	AttributeList->Attributes[1].ValuePtr = SecImgInfo;

	AttributeList->Attributes[2].Attribute = PS_ATTRIBUTE_IMAGE_NAME;
	AttributeList->Attributes[2].Size = NtImagePath.Length;
	AttributeList->Attributes[2].ValuePtr = NtImagePath.Buffer;

	AttributeList->Attributes[3].Attribute = PS_ATTRIBUTE_STD_HANDLE_INFO;
	AttributeList->Attributes[3].Size = sizeof(PS_STD_HANDLE_INFO);
	AttributeList->Attributes[3].ValuePtr = stdHandleInfo;

	DWORD64 policy = PROCESS_CREATION_MITIGATION_POLICY_BLOCK_NON_MICROSOFT_BINARIES_ALWAYS_ON;

	// Add process mitigation attribute
	AttributeList->Attributes[4].Attribute = PS_ATTRIBUTE_MITIGATION_OPTIONS;
	AttributeList->Attributes[4].Size = sizeof(DWORD64);
	AttributeList->Attributes[4].ValuePtr = &policy;

	// Spoof Parent Process Id as explorer.exe
	DWORD trayPID;
	HWND trayWnd = FindWindowW(L"Shell_TrayWnd", NULL);
	GetWindowThreadProcessId(trayWnd, &trayPID);
	HANDLE hParent = OpenProcess(PROCESS_ALL_ACCESS, false, trayPID);
	if (hParent)
	{
		AttributeList->Attributes[5].Attribute = PS_ATTRIBUTE_PARENT_PROCESS;
		AttributeList->Attributes[5].Size = sizeof(HANDLE);
		AttributeList->Attributes[5].ValuePtr = hParent;
	}
	else
	{
		AttributeList->TotalLength -= sizeof(PS_ATTRIBUTE);
	}
	// Create the process
	HANDLE hProcess = NULL, hThread = NULL;
	NtCreateUserProcess(&hProcess, &hThread, MAXIMUM_ALLOWED, MAXIMUM_ALLOWED, &objAttr, &objAttr, 0, 0, ProcessParameters, &CreateInfo, AttributeList);

	// Clean up
	if(hParent) CloseHandle(hParent);
	RtlFreeHeap(RtlProcessHeap(), 0, AttributeList);
	RtlFreeHeap(RtlProcessHeap(), 0, stdHandleInfo);
	RtlFreeHeap(RtlProcessHeap(), 0, clientId);
	RtlFreeHeap(RtlProcessHeap(), 0, SecImgInfo);
 	RtlDestroyProcessParameters(ProcessParameters);
}