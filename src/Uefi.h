#pragma once

typedef unsigned long long UINT64;

typedef long long INT64;

typedef unsigned int UINT32;

typedef int INT32;

typedef unsigned short UINT16;

typedef unsigned short CHAR16;

typedef short INT16;

typedef unsigned char BOOLEAN;
#define FALSE 0
#define TRUE 1
#define NULL 0

typedef unsigned char UINT8;

typedef char CHAR8;

typedef signed char INT8;

typedef UINT64 UINTN;

typedef INT64 INTN;
typedef void VOID;

extern UINT8 _VerifySizeofBOOLEAN[(sizeof(BOOLEAN) == (1)) / (sizeof(BOOLEAN) == (1))];
extern UINT8 _VerifySizeofINT8[(sizeof(INT8) == (1)) / (sizeof(INT8) == (1))];
extern UINT8 _VerifySizeofUINT8[(sizeof(UINT8) == (1)) / (sizeof(UINT8) == (1))];
extern UINT8 _VerifySizeofINT16[(sizeof(INT16) == (2)) / (sizeof(INT16) == (2))];
extern UINT8 _VerifySizeofUINT16[(sizeof(UINT16) == (2)) / (sizeof(UINT16) == (2))];
extern UINT8 _VerifySizeofINT32[(sizeof(INT32) == (4)) / (sizeof(INT32) == (4))];
extern UINT8 _VerifySizeofUINT32[(sizeof(UINT32) == (4)) / (sizeof(UINT32) == (4))];
extern UINT8 _VerifySizeofINT64[(sizeof(INT64) == (8)) / (sizeof(INT64) == (8))];
extern UINT8 _VerifySizeofUINT64[(sizeof(UINT64) == (8)) / (sizeof(UINT64) == (8))];
extern UINT8 _VerifySizeofCHAR8[(sizeof(CHAR8) == (1)) / (sizeof(CHAR8) == (1))];
extern UINT8 _VerifySizeofCHAR16[(sizeof(CHAR16) == (2)) / (sizeof(CHAR16) == (2))];

typedef struct {
	UINT32 Data1;
	UINT16 Data2;
	UINT16 Data3;
	UINT8 Data4[8];
} GUID;

typedef UINT64 PHYSICAL_ADDRESS;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;

typedef struct _LIST_ENTRY LIST_ENTRY;

struct _LIST_ENTRY {
	LIST_ENTRY* ForwardLink;
	LIST_ENTRY* BackLink;
};

typedef GUID EFI_GUID;
typedef UINTN RETURN_STATUS;
typedef RETURN_STATUS EFI_STATUS;

#define IB_API static
#define EFI_SUCCESS		0
#define EFI_NOT_FOUND		14
#define EFI_BUFFER_TOO_SMALL	5

typedef void* EFI_HANDLE;
typedef UINTN EFI_TPL;
typedef void* EFI_EVENT;

typedef enum {

	EfiReservedMemoryType,

	EfiLoaderCode,

	EfiLoaderData,

	EfiBootServicesCode,

	EfiBootServicesData,

	EfiRuntimeServicesCode,

	EfiRuntimeServicesData,

	EfiConventionalMemory,

	EfiUnusableMemory,

	EfiACPIReclaimMemory,

	EfiACPIMemoryNVS,

	EfiMemoryMappedIO,

	EfiMemoryMappedIOPortSpace,

	EfiPalCode,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef struct {
	UINT16 ScanCode;
	CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL SIMPLE_INPUT_INTERFACE;



typedef
EFI_STATUS
(*EFI_INPUT_RESET)(
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL* This,
	BOOLEAN ExtendedVerification
	);
typedef
EFI_STATUS
(*EFI_INPUT_READ_KEY)(
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL* This,
	EFI_INPUT_KEY* Key
	);

typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;
typedef
EFI_STATUS
(*EFI_INPUT_RESET_EX)(
	EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	BOOLEAN ExtendedVerification
	);

struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	EFI_INPUT_RESET Reset;
	EFI_INPUT_READ_KEY ReadKeyStroke;

	EFI_EVENT WaitForKey;
};

typedef UINT8 EFI_KEY_TOGGLE_STATE;

typedef struct _EFI_KEY_STATE {

	UINT32 KeyShiftState;

	EFI_KEY_TOGGLE_STATE KeyToggleState;
} EFI_KEY_STATE;

typedef struct {

	EFI_INPUT_KEY Key;

	EFI_KEY_STATE KeyState;
} EFI_KEY_DATA;
typedef
EFI_STATUS
(*EFI_INPUT_READ_KEY_EX)(
	EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	EFI_KEY_DATA* KeyData
	);
typedef
EFI_STATUS
(*EFI_SET_STATE)(
	EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	EFI_KEY_TOGGLE_STATE* KeyToggleState
	);

typedef
EFI_STATUS
(*EFI_KEY_NOTIFY_FUNCTION)(
	EFI_KEY_DATA* KeyData
	);
typedef
EFI_STATUS
(*EFI_REGISTER_KEYSTROKE_NOTIFY)(
	EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	EFI_KEY_DATA* KeyData,
	EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
	EFI_HANDLE* NotifyHandle
	);
typedef
EFI_STATUS
(*EFI_UNREGISTER_KEYSTROKE_NOTIFY)(
	EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	EFI_HANDLE NotificationHandle
	);
struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
	EFI_INPUT_RESET_EX Reset;
	EFI_INPUT_READ_KEY_EX ReadKeyStrokeEx;

	EFI_EVENT WaitForKeyEx;
	EFI_SET_STATE SetState;
	EFI_REGISTER_KEYSTROKE_NOTIFY RegisterKeyNotify;
	EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
};

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL SIMPLE_TEXT_OUTPUT_INTERFACE;
typedef
EFI_STATUS
(*EFI_TEXT_RESET)(
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	BOOLEAN ExtendedVerification
	);
typedef
EFI_STATUS
(*EFI_TEXT_STRING)(
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	CHAR16* String
	);
typedef
EFI_STATUS
(*EFI_TEXT_TEST_STRING)(
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	CHAR16* String
	);
typedef
EFI_STATUS
(*EFI_TEXT_QUERY_MODE)(
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	UINTN ModeNumber,
	UINTN* Columns,
	UINTN* Rows
	);
typedef
EFI_STATUS
(*EFI_TEXT_SET_MODE)(
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	UINTN ModeNumber
	);
typedef
EFI_STATUS
(*EFI_TEXT_SET_ATTRIBUTE)(
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	UINTN Attribute
	);
typedef
EFI_STATUS
(*EFI_TEXT_CLEAR_SCREEN)(
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This
	);
typedef
EFI_STATUS
(*EFI_TEXT_SET_CURSOR_POSITION)(
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	UINTN Column,
	UINTN Row
	);
typedef
EFI_STATUS
(*EFI_TEXT_ENABLE_CURSOR)(
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	BOOLEAN Visible
	);

typedef struct {

	INT32 MaxMode;
	INT32 Mode;

	INT32 Attribute;

	INT32 CursorColumn;

	INT32 CursorRow;

	BOOLEAN CursorVisible;
} EFI_SIMPLE_TEXT_OUTPUT_MODE;

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	EFI_TEXT_RESET Reset;

	EFI_TEXT_STRING OutputString;
	EFI_TEXT_TEST_STRING TestString;

	EFI_TEXT_QUERY_MODE QueryMode;
	EFI_TEXT_SET_MODE SetMode;
	EFI_TEXT_SET_ATTRIBUTE SetAttribute;

	EFI_TEXT_CLEAR_SCREEN ClearScreen;
	EFI_TEXT_SET_CURSOR_POSITION SetCursorPosition;
	EFI_TEXT_ENABLE_CURSOR EnableCursor;

	EFI_SIMPLE_TEXT_OUTPUT_MODE* Mode;
};

typedef enum {

	AllocateAnyPages,

	AllocateMaxAddress,

	AllocateAddress,

	MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef struct {
	UINT8 Type;

	UINT8 SubType;

	UINT8 Length[2];

} EFI_DEVICE_PATH_PROTOCOL;

typedef EFI_DEVICE_PATH_PROTOCOL EFI_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT8 Function;

	UINT8 Device;
} PCI_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT8 FunctionNumber;
} PCCARD_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 MemoryType;

	EFI_PHYSICAL_ADDRESS StartingAddress;

	EFI_PHYSICAL_ADDRESS EndingAddress;
} MEMMAP_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	EFI_GUID Guid;

} VENDOR_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 ControllerNumber;
} CONTROLLER_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 HID;

	UINT32 UID;
} ACPI_HID_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 HID;

	UINT32 UID;

	UINT32 CID;

} ACPI_EXTENDED_HID_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 ADR;

} ACPI_ADR_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT8 PrimarySecondary;

	UINT8 SlaveMaster;

	UINT16 Lun;
} ATAPI_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT16 Pun;

	UINT16 Lun;
} SCSI_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 Reserved;

	UINT64 WWN;

	UINT64 Lun;
} FIBRECHANNEL_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 Reserved;

	UINT8 WWN[8];

	UINT8 Lun[8];
} FIBRECHANNELEX_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 Reserved;

	UINT64 Guid;
} F1394_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT8 ParentPortNumber;

	UINT8 InterfaceNumber;
} USB_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT16 VendorId;

	UINT16 ProductId;

	UINT8 DeviceClass;

	UINT8 DeviceSubClass;

	UINT8 DeviceProtocol;
} USB_CLASS_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT16 InterfaceNumber;

	UINT16 VendorId;

	UINT16 ProductId;

} USB_WWID_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT8 Lun;
} DEVICE_LOGICAL_UNIT_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT16 HBAPortNumber;

	UINT16 PortMultiplierPortNumber;

	UINT16 Lun;
} SATA_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 Tid;
} I2O_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;
	UINT32 ResourceFlags;

	UINT8 PortGid[16];

	UINT64 ServiceId;

	UINT64 TargetPortId;

	UINT64 DeviceId;
} INFINIBAND_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 Reserved;

	UINT64 BaudRate;

	UINT8 DataBits;
	UINT8 Parity;

	UINT8 StopBits;
} UART_DEVICE_PATH;

typedef VENDOR_DEVICE_PATH VENDOR_DEFINED_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	EFI_GUID Guid;

	UINT32 FlowControlMap;
} UART_FLOW_CONTROL_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	EFI_GUID Guid;

	UINT32 Reserved;

	UINT64 SasAddress;

	UINT64 Lun;

	UINT16 DeviceTopology;

	UINT16 RelativeTargetPort;
} SAS_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT8 SasAddress[8];

	UINT8 Lun[8];

	UINT16 DeviceTopology;

	UINT16 RelativeTargetPort;
} SASEX_DEVICE_PATH;

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT16 NetworkProtocol;

	UINT16 LoginOption;

	UINT64 Lun;

	UINT16 TargetPortalGroupTag;

} ISCSI_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT16 VlanId;
} VLAN_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 PartitionNumber;

	UINT64 PartitionStart;

	UINT64 PartitionSize;

	UINT8 Signature[16];

	UINT8 MBRType;

	UINT8 SignatureType;
} HARDDRIVE_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT32 BootEntry;

	UINT64 PartitionStart;

	UINT64 PartitionSize;
} CDROM_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	CHAR16 PathName[1];
} FILEPATH_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	EFI_GUID Protocol;
} MEDIA_PROTOCOL_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	EFI_GUID FvFileName;
} MEDIA_FW_VOL_FILEPATH_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	EFI_GUID FvName;
} MEDIA_FW_VOL_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;
	UINT32 Reserved;
	UINT64 StartingOffset;
	UINT64 EndingOffset;
} MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH;
typedef struct {
	EFI_DEVICE_PATH_PROTOCOL Header;

	UINT16 DeviceType;

	UINT16 StatusFlag;

	CHAR8 String[1];
} BBS_BBS_DEVICE_PATH;
typedef union {
	EFI_DEVICE_PATH_PROTOCOL DevPath;
	PCI_DEVICE_PATH Pci;
	PCCARD_DEVICE_PATH PcCard;
	MEMMAP_DEVICE_PATH MemMap;
	VENDOR_DEVICE_PATH Vendor;

	CONTROLLER_DEVICE_PATH Controller;
	ACPI_HID_DEVICE_PATH Acpi;
	ACPI_EXTENDED_HID_DEVICE_PATH ExtendedAcpi;
	ACPI_ADR_DEVICE_PATH AcpiAdr;

	ATAPI_DEVICE_PATH Atapi;
	SCSI_DEVICE_PATH Scsi;
	ISCSI_DEVICE_PATH Iscsi;
	FIBRECHANNEL_DEVICE_PATH FibreChannel;
	FIBRECHANNELEX_DEVICE_PATH FibreChannelEx;

	F1394_DEVICE_PATH F1394;
	USB_DEVICE_PATH Usb;
	SATA_DEVICE_PATH Sata;
	USB_CLASS_DEVICE_PATH UsbClass;
	USB_WWID_DEVICE_PATH UsbWwid;
	DEVICE_LOGICAL_UNIT_DEVICE_PATH LogicUnit;
	I2O_DEVICE_PATH I2O;
	VLAN_DEVICE_PATH Vlan;
	INFINIBAND_DEVICE_PATH InfiniBand;
	UART_DEVICE_PATH Uart;
	UART_FLOW_CONTROL_DEVICE_PATH UartFlowControl;
	SAS_DEVICE_PATH Sas;
	SASEX_DEVICE_PATH SasEx;
	HARDDRIVE_DEVICE_PATH HardDrive;
	CDROM_DEVICE_PATH CD;

	FILEPATH_DEVICE_PATH FilePath;
	MEDIA_PROTOCOL_DEVICE_PATH MediaProtocol;

	MEDIA_FW_VOL_DEVICE_PATH FirmwareVolume;
	MEDIA_FW_VOL_FILEPATH_DEVICE_PATH FirmwareFile;
	MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH Offset;

	BBS_BBS_DEVICE_PATH Bbs;
} EFI_DEV_PATH;

typedef union {
	EFI_DEVICE_PATH_PROTOCOL* DevPath;
	PCI_DEVICE_PATH* Pci;
	PCCARD_DEVICE_PATH* PcCard;
	MEMMAP_DEVICE_PATH* MemMap;
	VENDOR_DEVICE_PATH* Vendor;

	CONTROLLER_DEVICE_PATH* Controller;
	ACPI_HID_DEVICE_PATH* Acpi;
	ACPI_EXTENDED_HID_DEVICE_PATH* ExtendedAcpi;
	ACPI_ADR_DEVICE_PATH* AcpiAdr;

	ATAPI_DEVICE_PATH* Atapi;
	SCSI_DEVICE_PATH* Scsi;
	ISCSI_DEVICE_PATH* Iscsi;
	FIBRECHANNEL_DEVICE_PATH* FibreChannel;
	FIBRECHANNELEX_DEVICE_PATH* FibreChannelEx;

	F1394_DEVICE_PATH* F1394;
	USB_DEVICE_PATH* Usb;
	SATA_DEVICE_PATH* Sata;
	USB_CLASS_DEVICE_PATH* UsbClass;
	USB_WWID_DEVICE_PATH* UsbWwid;
	DEVICE_LOGICAL_UNIT_DEVICE_PATH* LogicUnit;
	I2O_DEVICE_PATH* I2O;
	VLAN_DEVICE_PATH* Vlan;
	INFINIBAND_DEVICE_PATH* InfiniBand;
	UART_DEVICE_PATH* Uart;
	UART_FLOW_CONTROL_DEVICE_PATH* UartFlowControl;
	SAS_DEVICE_PATH* Sas;
	SASEX_DEVICE_PATH* SasEx;
	HARDDRIVE_DEVICE_PATH* HardDrive;
	CDROM_DEVICE_PATH* CD;

	FILEPATH_DEVICE_PATH* FilePath;
	MEDIA_PROTOCOL_DEVICE_PATH* MediaProtocol;

	MEDIA_FW_VOL_DEVICE_PATH* FirmwareVolume;
	MEDIA_FW_VOL_FILEPATH_DEVICE_PATH* FirmwareFile;
	MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH* Offset;

	BBS_BBS_DEVICE_PATH* Bbs;
	UINT8* Raw;
} EFI_DEV_PATH_PTR;

#pragma pack()



typedef struct {

	UINT32 Type;

	EFI_PHYSICAL_ADDRESS PhysicalStart;

	EFI_VIRTUAL_ADDRESS VirtualStart;

	UINT64 NumberOfPages;

	UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;
typedef
EFI_STATUS
(*EFI_ALLOCATE_PAGES)(
	EFI_ALLOCATE_TYPE Type,
	EFI_MEMORY_TYPE MemoryType,
	UINTN Pages,
	EFI_PHYSICAL_ADDRESS* Memory
	);
typedef
EFI_STATUS
(*EFI_FREE_PAGES)(
	EFI_PHYSICAL_ADDRESS Memory,
	UINTN Pages
	);
typedef
EFI_STATUS
(*EFI_GET_MEMORY_MAP)(
	UINTN* MemoryMapSize,
	EFI_MEMORY_DESCRIPTOR* MemoryMap,
	UINTN* MapKey,
	UINTN* DescriptorSize,
	UINT32* DescriptorVersion
	);
typedef
EFI_STATUS
(*EFI_ALLOCATE_POOL)(
	EFI_MEMORY_TYPE PoolType,
	UINTN Size,
	void** Buffer
	);
typedef
EFI_STATUS
(*EFI_FREE_POOL)(
	void* Buffer
	);
typedef
EFI_STATUS
(*EFI_SET_VIRTUAL_ADDRESS_MAP)(
	UINTN MemoryMapSize,
	UINTN DescriptorSize,
	UINT32 DescriptorVersion,
	EFI_MEMORY_DESCRIPTOR* VirtualMap
	);
typedef
EFI_STATUS
(*EFI_CONNECT_CONTROLLER)(
	EFI_HANDLE ControllerHandle,
	EFI_HANDLE* DriverImageHandle,
	EFI_DEVICE_PATH_PROTOCOL* RemainingDevicePath,
	BOOLEAN Recursive
	);
typedef
EFI_STATUS
(*EFI_DISCONNECT_CONTROLLER)(
	EFI_HANDLE ControllerHandle,
	EFI_HANDLE DriverImageHandle,
	EFI_HANDLE ChildHandle
	);
typedef
EFI_STATUS
(*EFI_CONVERT_POINTER)(
	UINTN DebugDisposition,
	void** Address
	);
typedef
void
(*EFI_EVENT_NOTIFY)(
	EFI_EVENT Event,
	void* Context
	);
typedef
EFI_STATUS
(*EFI_CREATE_EVENT)(
	UINT32 Type,
	EFI_TPL NotifyTpl,
	EFI_EVENT_NOTIFY NotifyFunction,
	void* NotifyContext,
	EFI_EVENT* Event
	);
typedef
EFI_STATUS
(*EFI_CREATE_EVENT_EX)(
	UINT32 Type,
	EFI_TPL NotifyTpl,
	EFI_EVENT_NOTIFY NotifyFunction,
	void* NotifyContext,
	EFI_GUID* EventGroup,
	EFI_EVENT* Event
	);

typedef enum {

	TimerCancel,

	TimerPeriodic,

	TimerRelative
} EFI_TIMER_DELAY;
typedef
EFI_STATUS
(*EFI_SET_TIMER)(
	EFI_EVENT Event,
	EFI_TIMER_DELAY Type,
	UINT64 TriggerTime
	);
typedef
EFI_STATUS
(*EFI_SIGNAL_EVENT)(
	EFI_EVENT Event
	);
typedef
EFI_STATUS
(*EFI_WAIT_FOR_EVENT)(
	UINTN NumberOfEvents,
	EFI_EVENT* Event,
	UINTN* Index
	);
typedef
EFI_STATUS
(*EFI_CLOSE_EVENT)(
	EFI_EVENT Event
	);
typedef
EFI_STATUS
(*EFI_CHECK_EVENT)(
	EFI_EVENT Event
	);
typedef
EFI_TPL
(*EFI_RAISE_TPL)(
	EFI_TPL NewTpl
	);

typedef
void
(*EFI_RESTORE_TPL)(
	EFI_TPL OldTpl
	);
typedef
EFI_STATUS
(*EFI_GET_VARIABLE)(
	CHAR16* VariableName,
	EFI_GUID* VendorGuid,
	UINT32* Attributes,
	UINTN* DataSize,
	void* Data
	);
typedef
EFI_STATUS
(*EFI_GET_NEXT_VARIABLE_NAME)(
	UINTN* VariableNameSize,
	CHAR16* VariableName,
	EFI_GUID* VendorGuid
	);
typedef
EFI_STATUS
(*EFI_SET_VARIABLE)(
	CHAR16* VariableName,
	EFI_GUID* VendorGuid,
	UINT32 Attributes,
	UINTN DataSize,
	void* Data
	);

typedef struct {

	UINT32 Resolution;

	UINT32 Accuracy;

	BOOLEAN SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef struct {
	UINT16 Year;
	UINT8 Month;
	UINT8 Day;
	UINT8 Hour;
	UINT8 Minute;
	UINT8 Second;
	UINT8 Pad1;
	UINT32 Nanosecond;
	INT16 TimeZone;
	UINT8 Daylight;
	UINT8 Pad2;
} EFI_TIME;


typedef
EFI_STATUS
(*EFI_GET_TIME)(
	EFI_TIME* Time,
	EFI_TIME_CAPABILITIES* Capabilities
	);
typedef
EFI_STATUS
(*EFI_SET_TIME)(
	EFI_TIME* Time
	);
typedef
EFI_STATUS
(*EFI_GET_WAKEUP_TIME)(
	BOOLEAN* Enabled,
	BOOLEAN* Pending,
	EFI_TIME* Time
	);
typedef
EFI_STATUS
(*EFI_SET_WAKEUP_TIME)(
	BOOLEAN Enable,
	EFI_TIME* Time
	);

typedef
EFI_STATUS
(*EFI_IMAGE_LOAD)(
	BOOLEAN BootPolicy,
	EFI_HANDLE ParentImageHandle,
	EFI_DEVICE_PATH_PROTOCOL* DevicePath,
	void* SourceBuffer,
	UINTN SourceSize,
	EFI_HANDLE* ImageHandle
	);
typedef
EFI_STATUS
(*EFI_IMAGE_START)(
	EFI_HANDLE ImageHandle,
	UINTN* ExitDataSize,
	CHAR16** ExitData
	);
typedef
EFI_STATUS
(*EFI_EXIT)(
	EFI_HANDLE ImageHandle,
	EFI_STATUS ExitStatus,
	UINTN ExitDataSize,
	CHAR16* ExitData
	);
typedef
EFI_STATUS
(*EFI_IMAGE_UNLOAD)(
	EFI_HANDLE ImageHandle
	);
typedef
EFI_STATUS
(*EFI_EXIT_BOOT_SERVICES)(
	EFI_HANDLE ImageHandle,
	UINTN MapKey
	);
typedef
EFI_STATUS
(*EFI_STALL)(
	UINTN Microseconds
	);
typedef
EFI_STATUS
(*EFI_SET_WATCHDOG_TIMER)(
	UINTN Timeout,
	UINT64 WatchdogCode,
	UINTN DataSize,
	CHAR16* WatchdogData
	);

typedef enum {

	EfiResetCold,

	EfiResetWarm,

	EfiResetShutdown
} EFI_RESET_TYPE;
typedef
void
(*EFI_RESET_SYSTEM)(
	EFI_RESET_TYPE ResetType,
	EFI_STATUS ResetStatus,
	UINTN DataSize,
	void* ResetData
	);
typedef
EFI_STATUS
(*EFI_GET_NEXT_MONOTONIC_COUNT)(
	UINT64* Count
	);
typedef
EFI_STATUS
(*EFI_GET_NEXT_HIGH_MONO_COUNT)(
	UINT32* HighCount
	);
typedef
EFI_STATUS
(*EFI_CALCULATE_CRC32)(
	void* Data,
	UINTN DataSize,
	UINT32* Crc32
	);
typedef
void
(*EFI_COPY_MEM)(
	void* Destination,
	void* Source,
	UINTN Length
	);
typedef
void
(*EFI_SET_MEM)(
	void* Buffer,
	UINTN Size,
	UINT8 Value
	);

typedef enum {

	EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;
typedef
EFI_STATUS
(*EFI_INSTALL_PROTOCOL_INTERFACE)(
	EFI_HANDLE* Handle,
	EFI_GUID* Protocol,
	EFI_INTERFACE_TYPE InterfaceType,
	void* Interface
	);
typedef
EFI_STATUS
(*EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
	EFI_HANDLE* Handle,
	...
	);
typedef
EFI_STATUS
(*EFI_REINSTALL_PROTOCOL_INTERFACE)(
	EFI_HANDLE Handle,
	EFI_GUID* Protocol,
	void* OldInterface,
	void* NewInterface
	);
typedef
EFI_STATUS
(*EFI_UNINSTALL_PROTOCOL_INTERFACE)(
	EFI_HANDLE Handle,
	EFI_GUID* Protocol,
	void* Interface
	);
typedef
EFI_STATUS
(*EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
	EFI_HANDLE Handle,
	...
	);
typedef
EFI_STATUS
(*EFI_HANDLE_PROTOCOL)(
	EFI_HANDLE Handle,
	EFI_GUID* Protocol,
	void** Interface
	);
typedef
EFI_STATUS
(*EFI_OPEN_PROTOCOL)(
	EFI_HANDLE Handle,
	EFI_GUID* Protocol,
	void** Interface,
	EFI_HANDLE AgentHandle,
	EFI_HANDLE ControllerHandle,
	UINT32 Attributes
	);
typedef
EFI_STATUS
(*EFI_CLOSE_PROTOCOL)(
	EFI_HANDLE Handle,
	EFI_GUID* Protocol,
	EFI_HANDLE AgentHandle,
	EFI_HANDLE ControllerHandle
	);

typedef struct {
	EFI_HANDLE AgentHandle;
	EFI_HANDLE ControllerHandle;
	UINT32 Attributes;
	UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;
typedef
EFI_STATUS
(*EFI_OPEN_PROTOCOL_INFORMATION)(
	EFI_HANDLE Handle,
	EFI_GUID* Protocol,
	EFI_OPEN_PROTOCOL_INFORMATION_ENTRY** EntryBuffer,
	UINTN* EntryCount
	);
typedef
EFI_STATUS
(*EFI_PROTOCOLS_PER_HANDLE)(
	EFI_HANDLE Handle,
	EFI_GUID*** ProtocolBuffer,
	UINTN* ProtocolBufferCount
	);
typedef
EFI_STATUS
(*EFI_REGISTER_PROTOCOL_NOTIFY)(
	EFI_GUID* Protocol,
	EFI_EVENT Event,
	void** Registration
	);

typedef enum {

	AllHandles,

	ByRegisterNotify,

	ByProtocol
} EFI_LOCATE_SEARCH_TYPE;
typedef
EFI_STATUS
(*EFI_LOCATE_HANDLE)(
	EFI_LOCATE_SEARCH_TYPE SearchType,
	EFI_GUID* Protocol,
	void* SearchKey,
	UINTN* BufferSize,
	EFI_HANDLE* Buffer
	);
typedef
EFI_STATUS
(*EFI_LOCATE_DEVICE_PATH)(
	EFI_GUID* Protocol,
	EFI_DEVICE_PATH_PROTOCOL** DevicePath,
	EFI_HANDLE* Device
	);
typedef
EFI_STATUS
(*EFI_INSTALL_CONFIGURATION_TABLE)(
	EFI_GUID* Guid,
	void* Table
	);
typedef
EFI_STATUS
(*EFI_LOCATE_HANDLE_BUFFER)(
	EFI_LOCATE_SEARCH_TYPE SearchType,
	EFI_GUID* Protocol,
	void* SearchKey,
	UINTN* NoHandles,
	EFI_HANDLE** Buffer
	);
typedef
EFI_STATUS
(*EFI_LOCATE_PROTOCOL)(
	EFI_GUID* Protocol,
	void* Registration,
	void** Interface
	);

typedef struct {

	UINT64 Signature;

	UINT32 Revision;

	UINT32 HeaderSize;

	UINT32 CRC32;

	UINT32 Reserved;
} EFI_TABLE_HEADER;

typedef struct {

	UINT64 Length;
	union {

		EFI_PHYSICAL_ADDRESS DataBlock;

		EFI_PHYSICAL_ADDRESS ContinuationPointer;
	} Union;
} EFI_CAPSULE_BLOCK_DESCRIPTOR;

typedef struct {

	EFI_GUID CapsuleGuid;

	UINT32 HeaderSize;

	UINT32 Flags;

	UINT32 CapsuleImageSize;
} EFI_CAPSULE_HEADER;

typedef struct {

	UINT32 CapsuleArrayNumber;

	void* CapsulePtr[1];
} EFI_CAPSULE_TABLE;
typedef
EFI_STATUS
(*EFI_UPDATE_CAPSULE)(
	EFI_CAPSULE_HEADER** CapsuleHeaderArray,
	UINTN CapsuleCount,
	EFI_PHYSICAL_ADDRESS ScatterGatherList
	);
typedef
EFI_STATUS
(*EFI_QUERY_CAPSULE_CAPABILITIES)(
	EFI_CAPSULE_HEADER** CapsuleHeaderArray,
	UINTN CapsuleCount,
	UINT64* MaximumCapsuleSize,
	EFI_RESET_TYPE* ResetType
	);
typedef
EFI_STATUS
(*EFI_QUERY_VARIABLE_INFO)(
	UINT32 Attributes,
	UINT64* MaximumVariableStorageSize,
	UINT64* RemainingVariableStorageSize,
	UINT64* MaximumVariableSize
	);

typedef struct {

	EFI_TABLE_HEADER Hdr;

	EFI_GET_TIME GetTime;
	EFI_SET_TIME SetTime;
	EFI_GET_WAKEUP_TIME GetWakeupTime;
	EFI_SET_WAKEUP_TIME SetWakeupTime;

	EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
	EFI_CONVERT_POINTER ConvertPointer;

	EFI_GET_VARIABLE GetVariable;
	EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
	EFI_SET_VARIABLE SetVariable;

	EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;
	EFI_RESET_SYSTEM ResetSystem;

	EFI_UPDATE_CAPSULE UpdateCapsule;
	EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;

	EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
} EFI_RUNTIME_SERVICES;
typedef struct {

	EFI_TABLE_HEADER Hdr;

	EFI_RAISE_TPL RaiseTPL;
	EFI_RESTORE_TPL RestoreTPL;

	EFI_ALLOCATE_PAGES AllocatePages;
	EFI_FREE_PAGES FreePages;
	EFI_GET_MEMORY_MAP GetMemoryMap;
	EFI_ALLOCATE_POOL AllocatePool;
	EFI_FREE_POOL FreePool;

	EFI_CREATE_EVENT CreateEvent;
	EFI_SET_TIMER SetTimer;
	EFI_WAIT_FOR_EVENT WaitForEvent;
	EFI_SIGNAL_EVENT SignalEvent;
	EFI_CLOSE_EVENT CloseEvent;
	EFI_CHECK_EVENT CheckEvent;

	EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;
	EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
	EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;
	EFI_HANDLE_PROTOCOL HandleProtocol;
	void* Reserved;
	EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;
	EFI_LOCATE_HANDLE LocateHandle;
	EFI_LOCATE_DEVICE_PATH LocateDevicePath;
	EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

	EFI_IMAGE_LOAD LoadImage;
	EFI_IMAGE_START StartImage;
	EFI_EXIT Exit;
	EFI_IMAGE_UNLOAD UnloadImage;
	EFI_EXIT_BOOT_SERVICES ExitBootServices;

	EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount;
	EFI_STALL Stall;
	EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;

	EFI_CONNECT_CONTROLLER ConnectController;
	EFI_DISCONNECT_CONTROLLER DisconnectController;

	EFI_OPEN_PROTOCOL OpenProtocol;
	EFI_CLOSE_PROTOCOL CloseProtocol;
	EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation;

	EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;
	EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;
	EFI_LOCATE_PROTOCOL LocateProtocol;
	EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

	EFI_CALCULATE_CRC32 CalculateCrc32;

	EFI_COPY_MEM CopyMem;
	EFI_SET_MEM SetMem;
	EFI_CREATE_EVENT_EX CreateEventEx;
} EFI_BOOT_SERVICES;

typedef struct {

	EFI_GUID VendorGuid;

	void* VendorTable;
} EFI_CONFIGURATION_TABLE;

typedef struct {

	EFI_TABLE_HEADER Hdr;

	CHAR16* FirmwareVendor;

	UINT32 FirmwareRevision;

	EFI_HANDLE ConsoleInHandle;

	EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;

	EFI_HANDLE ConsoleOutHandle;

	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;

	EFI_HANDLE StandardErrorHandle;

	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdErr;

	EFI_RUNTIME_SERVICES* RuntimeServices;

	EFI_BOOT_SERVICES* BootServices;

	UINTN NumberOfTableEntries;

	EFI_CONFIGURATION_TABLE* ConfigurationTable;
} EFI_SYSTEM_TABLE;
