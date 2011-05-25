#===========================================================================
#
#  Program:   Visualization Toolkit
#  Module:    $RCSfile: FindWindowsMangledMethods.cmake,v $
#
#  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
#  All rights reserved.
#  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.
#
#     This software is distributed WITHOUT ANY WARRANTY; without even
#     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#     PURPOSE.  See the above copyright notice for more information.
#
#===========================================================================

# See README.WindowsMangling.txt for the purpose of this script.

#-----------------------------------------------------------------------------
# Instructions to use this script:
#
# CMake version 2.0.x is required, but 2.0.5 or better is preferred.
#
# Set the current working directory to the top of a source tree and
# run this script with this command:
#
#  cmake -P /path/to/FindWindowsMangledMethods.cmake
#
# A list of potentially mangled methods will be displayed as output.
# Each line will consist of a file name and a partial method
# signature.  Note that Set/Get macros are capable of producing
# methods that might be mangled.  These are also listed.

IF("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.0)
  MESSAGE(FATAL_ERROR "CMake 2.0 or higher is required for this script.")
ENDIF("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.0)

# List of symbols that might be mangled.
SET(SYMBOLS
AbnormalTermination
AbortSystemShutdown
AccessCheckAndAuditAlarm
AddAtom
AddFontResource
AddForm
AddJob
AddMonitor
AddPort
AddPrintProcessor
AddPrintProvidor
AddPrinter
AddPrinterConnection
AddPrinterDriver
AddPrinterDriverEx
AdvancedDocumentProperties
AnsiLower
AnsiLowerBuff
AnsiNext
AnsiPrev
AnsiToOem
AnsiToOemBuff
AnsiUpper
AnsiUpperBuff
AppendMenu
BackupEventLog
BeginUpdateResource
BuildCommDCB
BuildCommDCBAndTimeouts
CallMsgFilter
CallNamedPipe
CallWindowProc
CdChangerClassGuid
CdRomClassGuid
CertAddEncodedCertificateToSystemStore
CertGetNameString
CertNameToStr
CertOpenSystemStore
CertRDNValueToStr
CertStrToName
ChangeDisplaySettings
ChangeDisplaySettingsEx
ChangeMenu
ChangeServiceConfig
ChangeServiceConfig2
CharLower
CharLowerBuff
CharNext
CharPrev
CharToOem
CharToOemBuff
CharUpper
CharUpperBuff
ChooseColor
ChooseFont
ClearEventLog
CommConfigDialog
CommDlg_OpenSave_GetFilePath
CommDlg_OpenSave_GetFilePathA
CommDlg_OpenSave_GetFilePathW
CommDlg_OpenSave_GetFolderIDList
CommDlg_OpenSave_GetFolderPath
CommDlg_OpenSave_GetFolderPathA
CommDlg_OpenSave_GetFolderPathW
CommDlg_OpenSave_GetSpec
CommDlg_OpenSave_GetSpecA
CommDlg_OpenSave_GetSpecW
CommDlg_OpenSave_HideControl
CommDlg_OpenSave_SetControlText
CommDlg_OpenSave_SetDefExt
CompareString
ConfigurePort
CopyAcceleratorTable
CopyCursor
CopyEnhMetaFile
CopyFile
CopyMemory
CopyMetaFile
CreateAcceleratorTable
CreateColorSpace
CreateDC
CreateDesktop
CreateDialog
CreateDialogA
CreateDialogIndirect
CreateDialogIndirectA
CreateDialogIndirectParam
CreateDialogIndirectW
CreateDialogParam
CreateDialogW
CreateDirectory
CreateDirectoryEx
CreateEnhMetaFile
CreateEvent
CreateFile
CreateFileMapping
CreateFont
CreateFontIndirect
CreateIC
CreateMDIWindow
CreateMailslot
CreateMetaFile
CreateMutex
CreateNamedPipe
CreateProcess
CreateProcessAsUser
CreatePropertySheetPage
CreateScalableFontResource
CreateSemaphore
CreateService
CreateWindow
CreateWindowA
CreateWindowEx
CreateWindowStation
CreateWindowW
CryptAcquireContext
CryptBinaryToString
CryptEnumProviderTypes
CryptEnumProviders
CryptGetDefaultProvider
CryptRetrieveObjectByUrl
CryptSetProvider
CryptSetProviderEx
CryptSignHash
CryptStringToBinary
CryptVerifySignature
DceErrorInqText
DdeCreateStringHandle
DdeInitialize
DdeQueryString
DecryptFile
DefDlgProc
DefFrameProc
DefHookProc
DefMDIChildProc
DefWindowProc
DefineDosDevice
DefineHandleTable
DeleteFile
DeleteForm
DeleteMonitor
DeletePort
DeletePrintProcessor
DeletePrintProvidor
DeletePrinterConnection
DeletePrinterData
DeletePrinterDataEx
DeletePrinterDriver
DeletePrinterDriverEx
DeletePrinterKey
DeviceCapabilities
DialogBox
DialogBoxA
DialogBoxIndirect
DialogBoxIndirectA
DialogBoxIndirectParam
DialogBoxIndirectW
DialogBoxParam
DialogBoxW
DiskClassGuid
DispatchMessage
DlgDirList
DlgDirListComboBox
DlgDirSelectComboBoxEx
DlgDirSelectEx
DoEnvironmentSubst
DocumentProperties
DragQueryFile
DrawState
DrawText
DrawTextEx
EncryptFile
EndUpdateResource
EnumCalendarInfo
EnumCalendarInfoEx
EnumDateFormats
EnumDateFormatsEx
EnumDependentServices
EnumDesktops
EnumDisplayDevices
EnumDisplaySettings
EnumDisplaySettingsEx
EnumFontFamilies
EnumFontFamiliesEx
EnumFonts
EnumForms
EnumICMProfiles
EnumJobs
EnumLanguageGroupLocales
EnumMonitors
EnumPorts
EnumPrintProcessorDatatypes
EnumPrintProcessors
EnumPrinterData
EnumPrinterDataEx
EnumPrinterDrivers
EnumPrinterKey
EnumPrinters
EnumProps
EnumPropsEx
EnumResourceLanguages
EnumResourceNames
EnumResourceTypes
EnumServicesStatus
EnumServicesStatusEx
EnumSystemCodePages
EnumSystemLanguageGroups
EnumSystemLocales
EnumTaskWindows
EnumTimeFormats
EnumUILanguages
EnumWindowStations
ExitWindows
ExpandEnvironmentStrings
ExtTextOut
ExtractAssociatedIcon
ExtractAssociatedIconEx
ExtractIcon
ExtractIconEx
FatalAppExit
FileEncryptionStatus
FillConsoleOutputCharacter
FillMemory
FindAtom
FindExecutable
FindFirstChangeNotification
FindFirstFile
FindNextFile
FindResource
FindResourceEx
FindText
FindWindow
FindWindowEx
FloppyClassGuid
FoldString
FormatMessage
FreeEnvironmentStrings
FreeModule
FreeProcInstance
GetAltTabInfo
GetAtomName
GetBValue
GetBinaryType
GetCPInfoEx
GetCValue
GetCalendarInfo
GetCharABCWidths
GetCharABCWidthsFloat
GetCharWidth
GetCharWidth32
GetCharWidthFloat
GetCharacterPlacement
GetClassInfo
GetClassInfoEx
GetClassLong
GetClassLongPtr
GetClassLongPtrA
GetClassLongPtrW
GetClassName
GetClipboardFormatName
GetCommandLine
GetCompressedFileSize
GetComputerName
GetConsoleTitle
GetCurrencyFormat
GetCurrentDirectory
GetCurrentTime
GetDateFormat
GetDefaultCommConfig
GetDefaultPrinter
GetDiskFreeSpace
GetDiskFreeSpaceEx
GetDlgItemText
GetDriveType
GetEnhMetaFile
GetEnhMetaFileDescription
GetEnvironmentStringsA
GetEnvironmentVariable
GetExceptionCode
GetExceptionInformation
GetExpandedName
GetFileAttributes
GetFileAttributesEx
GetFileSecurity
GetFileTitle
GetFileVersionInfo
GetFileVersionInfoSize
GetFirmwareEnvironmentVariable
GetForm
GetFreeSpace
GetFullPathName
GetGValue
GetGeoInfo
GetGlyphOutline
GetICMProfile
GetJob
GetKValue
GetKerningPairs
GetKeyNameText
GetKeyboardLayoutName
GetLocaleInfo
GetLogColorSpace
GetLogicalDriveStrings
GetLongPathName
GetMValue
GetMenuItemInfo
GetMenuString
GetMessage
GetMetaFile
GetModuleFileName
GetModuleHandle
GetMonitorInfo
GetNamedPipeHandleState
GetNextWindow
GetNumberFormat
GetObject
GetOpenCardName
GetOpenFileName
GetOutlineTextMetrics
GetPrintProcessorDirectory
GetPrinter
GetPrinterData
GetPrinterDataEx
GetPrinterDriver
GetPrinterDriverDirectory
GetPrivateProfileInt
GetPrivateProfileSection
GetPrivateProfileSectionNames
GetPrivateProfileString
GetPrivateProfileStruct
GetProfileInt
GetProfileSection
GetProfileString
GetProp
GetRValue
GetSaveFileName
GetScode
GetServiceDisplayName
GetServiceKeyName
GetShortPathName
GetStartupInfo
GetStringTypeEx
GetSysModalWindow
GetSystemDirectory
GetSystemWindowsDirectory
GetTabbedTextExtent
GetTempFileName
GetTempPath
GetTextExtentExPoint
GetTextExtentPoint
GetTextExtentPoint32
GetTextFace
GetTextMetrics
GetTimeFormat
GetUrlPolicyPermissions
GetUserName
GetUserObjectInformation
GetVersionEx
GetVolumeInformation
GetWindowLong
GetWindowLongPtr
GetWindowLongPtrA
GetWindowLongPtrW
GetWindowModuleFileName
GetWindowTask
GetWindowText
GetWindowTextLength
GetWindowsDirectory
GetYValue
GlobalAddAtom
GlobalDiscard
GlobalFindAtom
GlobalGetAtomName
GlobalLRUNewest
GlobalLRUOldest
GrayString
HandleToLong
HandleToULong
HandleToUlong
HasOverlappedIoCompleted
ImmConfigureIME
ImmEnumRegisterWord
ImmEscape
ImmGetCandidateList
ImmGetCandidateListCount
ImmGetCompositionFont
ImmGetCompositionString
ImmGetConversionList
ImmGetDescription
ImmGetGuideLine
ImmGetIMEFileName
ImmGetImeMenuItems
ImmGetRegisterWordStyle
ImmInstallIME
ImmIsUIMessage
ImmRegisterWord
ImmSetCompositionFont
ImmSetCompositionString
ImmUnregisterWord
InitiateSystemShutdown
InitiateSystemShutdownEx
InsertMenu
InsertMenuItem
Int32x32To64
IntToPtr
InterlockedCompareExchangePointer
InterlockedExchangePointer
IsBadStringPtr
IsCharAlpha
IsCharAlphaNumeric
IsCharLower
IsCharUpper
IsContainerPartition
IsDialogMessage
IsEqualCLSID
IsEqualFMTID
IsEqualIID
IsFTPartition
IsHashValCompatible
IsLFNDrive
IsLoggingEnabled
IsRecognizedPartition
IsReparseTagMicrosoft
IsReparseTagNameSurrogate
IsValidDevmode
LimitEmsPages
LoadAccelerators
LoadBitmap
LoadCursor
LoadCursorFromFile
LoadIcon
LoadImage
LoadKeyboardLayout
LoadLibrary
LoadLibraryEx
LoadMenu
LoadMenuIndirect
LoadString
LocalDiscard
LockSegment
LogonUser
LogonUserEx
LongToHandle
LongToPtr
LookupAccountName
LookupAccountSid
LookupPrivilegeDisplayName
LookupPrivilegeName
LookupPrivilegeValue
MakeProcInstance
MapVirtualKey
MapVirtualKeyEx
MaxNumberOfEEInfoParams
MediumChangerClassGuid
MessageBox
MessageBoxEx
MessageBoxIndirect
ModifyMenu
MoveFile
MoveFileEx
MoveMemory
MultinetGetConnectionPerformance
NdrFcLong
NdrFcShort
NdrFieldOffset
NdrFieldPad
NdrMarshCCtxtHdl
NdrMarshConfStringHdr
NdrMarshSCtxtHdl
NdrUnMarshCCtxtHdl
NdrUnMarshConfStringHdr
NdrUnMarshSCtxtHdl
ObjectCloseAuditAlarm
ObjectDeleteAuditAlarm
ObjectOpenAuditAlarm
ObjectPrivilegeAuditAlarm
OemToAnsi
OemToAnsiBuff
OemToChar
OemToCharBuff
OpenBackupEventLog
OpenDesktop
OpenEncryptedFileRaw
OpenEvent
OpenEventLog
OpenFileMapping
OpenMutex
OpenPrinter
OpenSCManager
OpenSemaphore
OpenService
OpenWindowStation
OutputDebugStr
OutputDebugString
PageSetupDlg
PartitionClassGuid
PeekConsoleInput
PeekMessage
PlaySound
PolyTextOut
PostAppMessage
PostAppMessageA
PostAppMessageW
PostMessage
PostThreadMessage
PrintDlg
PrintDlgEx
PrinterMessageBox
PrivateExtractIcons
PrivilegedServiceAuditAlarm
PropSheet_AddPage
PropSheet_Apply
PropSheet_CancelToClose
PropSheet_Changed
PropSheet_GetCurrentPageHwnd
PropSheet_GetResult
PropSheet_GetTabControl
PropSheet_HwndToIndex
PropSheet_IdToIndex
PropSheet_IndexToHwnd
PropSheet_IndexToId
PropSheet_IndexToPage
PropSheet_InsertPage
PropSheet_IsDialogMessage
PropSheet_PageToIndex
PropSheet_PressButton
PropSheet_QuerySiblings
PropSheet_RebootSystem
PropSheet_RecalcPageSizes
PropSheet_RemovePage
PropSheet_RestartWindows
PropSheet_SetCurSel
PropSheet_SetCurSelByID
PropSheet_SetFinishText
PropSheet_SetHeaderSubTitle
PropSheet_SetHeaderTitle
PropSheet_SetTitle
PropSheet_SetWizButtons
PropSheet_UnChanged
PropagateResult
PropertySheet
PtrToInt
PtrToLong
PtrToShort
PtrToUint
PtrToUlong
PtrToUshort
QueryDosDevice
QueryServiceConfig
QueryServiceConfig2
QueryServiceLockStatus
ReadConsole
ReadConsoleInput
ReadConsoleOutput
ReadConsoleOutputCharacter
ReadEventLog
RealGetWindowClass
RegConnectRegistry
RegCreateKey
RegCreateKeyEx
RegDeleteKey
RegDeleteValue
RegEnumKey
RegEnumKeyEx
RegEnumValue
RegLoadKey
RegOpenKey
RegOpenKeyEx
RegQueryInfoKey
RegQueryMultipleValues
RegQueryValue
RegQueryValueEx
RegReplaceKey
RegRestoreKey
RegSaveKey
RegSaveKeyEx
RegSetValue
RegSetValueEx
RegUnLoadKey
RegisterClass
RegisterClassEx
RegisterClipboardFormat
RegisterDeviceNotification
RegisterEventSource
RegisterServiceCtrlHandler
RegisterServiceCtrlHandlerEx
RegisterWindowMessage
RemoveDirectory
RemoveFontResource
RemoveProp
ReplaceText
ReportEvent
ResetDC
ResetPrinter
ResultFromScode
RpcAbnormalTermination
RpcAsyncGetCallHandle
RpcBindingFromStringBinding
RpcBindingInqAuthClient
RpcBindingInqAuthClientEx
RpcBindingInqAuthInfo
RpcBindingInqAuthInfoEx
RpcBindingSetAuthInfo
RpcBindingSetAuthInfoEx
RpcBindingToStringBinding
RpcEndExcept
RpcEndFinally
RpcEpRegister
RpcEpRegisterNoReplace
RpcExcept
RpcExceptionCode
RpcFinally
RpcMgmtEpEltInqNext
RpcMgmtInqServerPrincName
RpcNetworkInqProtseqs
RpcNetworkIsProtseqValid
RpcNsBindingExport
RpcNsBindingExportPnP
RpcNsBindingImportBegin
RpcNsBindingInqEntryName
RpcNsBindingLookupBegin
RpcNsBindingUnexport
RpcNsBindingUnexportPnP
RpcNsEntryExpandName
RpcNsEntryObjectInqBegin
RpcNsGroupDelete
RpcNsGroupMbrAdd
RpcNsGroupMbrInqBegin
RpcNsGroupMbrInqNext
RpcNsGroupMbrRemove
RpcNsMgmtBindingUnexport
RpcNsMgmtEntryCreate
RpcNsMgmtEntryDelete
RpcNsMgmtEntryInqIfIds
RpcNsProfileDelete
RpcNsProfileEltAdd
RpcNsProfileEltInqBegin
RpcNsProfileEltInqNext
RpcNsProfileEltRemove
RpcProtseqVectorFree
RpcServerInqCallAttributes
RpcServerInqDefaultPrincName
RpcServerRegisterAuthInfo
RpcServerUseProtseq
RpcServerUseProtseqEp
RpcServerUseProtseqEpEx
RpcServerUseProtseqEx
RpcServerUseProtseqIf
RpcServerUseProtseqIfEx
RpcStringBindingCompose
RpcStringBindingParse
RpcStringFree
RpcTryExcept
RpcTryFinally
RtlCopyMemory
RtlEqualMemory
RtlFillMemory
RtlMoveMemory
RtlZeroMemory
ScrollConsoleScreenBuffer
SearchPath
SecureZeroMemory
SendDlgItemMessage
SendMessage
SendMessageCallback
SendMessageTimeout
SendNotifyMessage
SetCalendarInfo
SetClassLong
SetClassLongPtr
SetClassLongPtrA
SetClassLongPtrW
SetComputerName
SetConsoleTitle
SetCurrentDirectory
SetDefaultCommConfig
SetDefaultPrinter
SetDlgItemText
SetEnvironmentStrings
SetEnvironmentVariable
SetFileAttributes
SetFileSecurity
SetFileShortName
SetFirmwareEnvironmentVariable
SetForm
SetICMProfile
SetJob
SetLocaleInfo
SetMenuItemInfo
SetPort
SetPrinter
SetPrinterData
SetPrinterDataEx
SetProp
SetSwapAreaSize
SetSysModalWindow
SetUrlPolicyPermissions
SetUserObjectInformation
SetVolumeLabel
SetWindowLong
SetWindowLongPtr
SetWindowLongPtrA
SetWindowLongPtrW
SetWindowText
SetWindowsHook
SetWindowsHookEx
ShellAbout
ShellExecute
ShellExecuteEx
ShellMessageBox
Shell_NotifyIcon
StartDoc
StartDocPrinter
StartService
StartServiceCtrlDispatcher
StoragePortClassGuid
SystemParametersInfo
TabbedTextOut
TapeClassGuid
TextOut
TranslateAccelerator
UintToPtr
UlongToHandle
UlongToPtr
UnlockResource
UnlockSegment
UnregisterClass
UpdateICMRegKey
UpdateResource
UuidFromString
UuidToString
VarBoolFromInt
VarBoolFromUint
VarBstrFromInt
VarBstrFromUint
VarCyFromInt
VarCyFromUint
VarDateFromInt
VarDateFromUint
VarDecFromInt
VarDecFromUint
VarI1FromInt
VarI1FromUint
VarI2FromInt
VarI2FromUint
VarI4FromI4
VarI4FromInt
VarI4FromUint
VarI8FromI8
VarI8FromInt
VarI8FromUint
VarIntFromBool
VarIntFromCy
VarIntFromDate
VarIntFromDec
VarIntFromDisp
VarIntFromI1
VarIntFromI2
VarIntFromI4
VarIntFromI8
VarIntFromR4
VarIntFromR8
VarIntFromStr
VarIntFromUI1
VarIntFromUI2
VarIntFromUI4
VarIntFromUI8
VarIntFromUint
VarR4FromInt
VarR4FromUint
VarR8FromInt
VarR8FromUint
VarUI1FromInt
VarUI1FromUint
VarUI2FromInt
VarUI2FromUint
VarUI4FromInt
VarUI4FromUI4
VarUI4FromUint
VarUI8FromUI8
VarUintFromBool
VarUintFromCy
VarUintFromDate
VarUintFromDec
VarUintFromDisp
VarUintFromI1
VarUintFromI2
VarUintFromI4
VarUintFromI8
VarUintFromInt
VarUintFromR4
VarUintFromR8
VarUintFromStr
VarUintFromUI1
VarUintFromUI2
VarUintFromUI4
VarUintFromUI8
VerFindFile
VerInstallFile
VerLanguageName
VerQueryValue
VerifyVersionInfo
VkKeyScan
VkKeyScanEx
VolumeClassGuid
WaitNamedPipe
WinExecError
WinHelp
WriteConsole
WriteConsoleInput
WriteConsoleOutput
WriteConsoleOutputCharacter
WriteOnceDiskClassGuid
WritePrivateProfileSection
WritePrivateProfileString
WritePrivateProfileStruct
WriteProfileSection
WriteProfileString
XcvDataZeroMemory
)

# Construct regular expressions to look for methods or Set/Get macros
# that define names that might be mangled.
SET(DIRECT_REGEX "[^>A-Za-z0-9](")
SET(MACRO_REGEX "vtk[A-Za-z0-9]*Macro *\\((")
SET(SEP1 "")
SET(SEP2 "")
FOREACH(s ${SYMBOLS})
  SET(DIRECT_REGEX "${DIRECT_REGEX}${SEP1}${s}")
  SET(SEP1 "|")
  IF("${s}" MATCHES "^(Get|Set)")
    STRING(REGEX REPLACE "^(Set|Get)(.+)$" "\\2" IVAR "${s}")
    IF(IVAR)
      SET(MACRO_REGEX "${MACRO_REGEX}${SEP2}${IVAR}")
      SET(SEP2 "|")
    ENDIF(IVAR)
  ENDIF("${s}" MATCHES "^(Get|Set)")
ENDFOREACH(s)
SET(DIRECT_REGEX "${DIRECT_REGEX})\\([^)]*\\)")
SET(MACRO_REGEX "${MACRO_REGEX})[^A-Za-z0-9_][^)]*\\)")

# Find all VTK class header files in the current directory and below.
FILE(GLOB_RECURSE VTK_CLASS_HEADERS "vtk*.h")

# Look for potentially mangled names.
FOREACH(h ${VTK_CLASS_HEADERS})
  # Read this class header.
  FILE(READ "${h}" CONTENTS)

  # Look for Set/Get macros defining methods with potentially mangled names.
  STRING(REGEX MATCH "${MACRO_REGEX}" OUTPUT "${CONTENTS}")
  IF(OUTPUT)
    MESSAGE("${h}: ${OUTPUT}")
  ENDIF(OUTPUT)

  # Look for methods with potentially mangled names.
  STRING(REGEX MATCH "${DIRECT_REGEX}" OUTPUT "${CONTENTS}")
  IF(OUTPUT)
    MESSAGE("${h}: ${OUTPUT}")
  ENDIF(OUTPUT)
ENDFOREACH(h)