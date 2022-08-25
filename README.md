# What is this?

This is a small PoC (Proof of concept) that invokes `NtCreateUserProcess` to spawn a Command prompt.
This also showcases PPID* (Parent Process ID) spoofing, where the parent is not the creator.

\* You must have a valid handle to the parent process.
## What is NtCreateUserProcess?
`NtCreateUserProcess` is lowest level API that spawns processes. Every WINAPI calls this.

Call chain from APIs to NtCreateUserProcess

* kernel32.dll!CreateProcess
* * CreateProcessInternalW
* *  * ntdll.dll!NtCreateUserProcess
<br>

* ntdll.dll!RtlCreateUserProcessEx
* * RtlpCreateUserProcess
* * * ntdll.dll!NtCreateUserProcess

## Requirements
```
Visual Studio
x86 or x64 machine (ARM or ARM64 is not tested)
```

### Remarks
This API function is very buggy on Windows 10, that's where most other PoCs fail. Especially when the executable is Win32 (x86).

#[License](https://github.com/BlackOfWorld/NtCreateUserProcess/LICENSE.md)
