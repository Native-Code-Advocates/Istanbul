#pragma once
#include "../Uefi.h"
#include "../Nca/Nca.h"

#define ACPI_APIC_SIGNATURE "APIC"
#define ACPI_BGRT_SIGNATURE "BGRT"
#define ACPI_BERT_SIGNATURE "BERT"
#define ACPI_CPEP_SIGNATURE "CPEP"
#define ACPI_DSDT_SIGNATURE "DSDT"
#define ACPI_ECDT_SIGNATURE "ECDT"
#define ACPI_EINJ_SIGNATURE "EINJ"
#define ACPI_ERST_SIGNATURE "ERST"
#define ACPI_FACP_SIGNATURE "FACP"
#define ACPI_FACS_SIGNATURE "FACS"
#define ACPI_HEST_SIGNATURE "HEST"
#define ACPI_MSCT_SIGNATURE "MSCT"
#define ACPI_MPST_SIGNATURE "MPST"
#define ACPI_OEMX_SIGNATURE "OEMx"
#define ACPI_PMTT_SIGNATURE "PMTT"
#define ACPI_PSDT_SIGNATURE "PSDT"
#define ACPI_RASF_SIGNATURE "RASF"
#define ACPI_RSDT_SIGNATURE "RSDT"
#define ACPI_SBST_SIGNATURE "SBST"
#define ACPI_SLIT_SIGNATURE "SLIT"
#define ACPI_SRAT_SIGNATURE "SRAT"
#define ACPI_SSDT_SIGNATURE "SSDT"
#define ACPI_XSDT_SIGNATURE "XSDT"

typedef struct {
	CHAR8 Signature[4];
	UINT32 Length;
	UINT8 Revision;
	UINT8 Checksum;
	CHAR8 OEMID[6];
	CHAR8 OEMTableId[8];
	UINT32 OEMRevision;
	UINT32 CreatorID;
	UINT32 CreatorRevision;
} ACPI_STD_HEADER;

typedef enum {
	AcpiAddressSpaceSystemMemory = 0,
	AcpiAddressSpaceSystemIO = 1,
	AcpiAddressSpacePCIConfig = 2,
	AcpiAddressSpaceEmbeddedController = 3,
	AcpiAddressSpaceSMBus = 4,
	AcpiAddressSpaceSystemCMOS = 5,
	AcpiAddressSpacePCIBarTarget = 6,
	AcpiAddressSpaceIPMI = 7,
	AcpiAddressSpaceGeneralPurposeIO = 8,
	AcpiAddressSpaceGenericSerialBus = 9,
	AcpiAddressSpacePlatformCommunicationChannel = 10,
	AcpiAddressSpaceFunctionalFixedHardware = 0x7F,
} AcpiAddressSpace;

typedef enum {
	AcpiAccessSizeUndefined = 0,
	AcpiAccessSizeByte = 1,
	AcpiAccessSizeWord = 2,
	AcpiAccessSizeDoubleWord = 3,
	AcpiAccessSizeQuadWord = 4,
} AcpiAccessSize;

typedef struct {
	UINT8 AddressSpace;
	UINT8 BitWidth;
	UINT8 BitOffset;
	UINT8 AddressSize;
	UINT64 Address;
} ACPI_GENERIC_ADDRESS;

typedef struct {
	CHAR8 Signature[8];
	INT8 Checksum;
	CHAR8 OEMID[6];
	UINT8 Revision;
	UINT32 RsdtAddress _Deprecated_;
	UINT32 Length;
	UINT64 XsdtAddress;
	INT8 ExtendedChecksum;
	INT8 Reserved[3];
} ACPI_RSDP;

typedef struct {
	ACPI_STD_HEADER Header;
	// Machine code follows...
} ACPI_DSDT;

typedef struct {
	ACPI_STD_HEADER Header;
} ACPI_SSDT;

typedef enum {
	AcpiMadtEntryLocalAPIC = 0,
	AcpiMadtEntryIoAPIC = 1,
	AcpiMadtEntryIoAPICOverride = 2,
	AcpiMadtEntryIoAPICNmiSource = 3,
	AcpiMadtEntryLocalAPICNmi = 4,
	AcpiMadtEntryLocalAPICOverride = 5,
	AcpiMadtEntryLocalx2APIC = 9,
} AcpiMadtEntryType;

#define ACPI_MADT_ENTRY_POLARITY_NO_OVERRIDE 0b00
#define ACPI_MADT_ENTRY_POLARITY_HIGH_OVERRIDE 0b01
#define ACPI_MADT_ENTRY_POLARITY_LOW_OVERRIDE 0b11

#define ACPI_MADT_ENTRY_TRIGGER_NO_OVERRIDE 0b0000
#define ACPI_MADT_ENTRY_TRIGGER_EDGE 0b0100
#define ACPI_MADT_ENTRY_TRIGGER_LEVEL 0b1100

typedef struct {
	UINT8 Type;
	UINT8 Length;
} ACPI_STD_MADT_ENTRY;

typedef struct {
	ACPI_STD_MADT_ENTRY Header;
	INT8 ACPIProcessorId;
	INT8 APICId;
	UINT32 Flags;
} ACPI_MADT_PROCESSOR_LOCAL_APIC;

typedef struct {
	ACPI_STD_MADT_ENTRY Header;
	INT8 IoAPICId;
	INT8 Reserved;
	UINT32 IoAPICAddress;
	UINT32 GlobalSystemInterruptBase;
} ACPI_MADT_IO_APIC;

typedef struct {
	ACPI_STD_MADT_ENTRY Header;
	INT8 BusSource;
	INT8 IRQSource;
	UINT32 GlobalSystemInterrupt;
	UINT16 Flags;
} ACPI_MADT_IO_APIC_OVERRIDE;

typedef struct {
	ACPI_STD_MADT_ENTRY Header;
	INT8 NmiSource;
	INT8 Reserved;
	UINT16 Flags;
	UINT16 GlobalSystemInterrupt;
} ACPI__MADT_IO_APIC_NMI;

#define ACPI_PROCESSOR_ID_ALL 0xFF

typedef struct {
	ACPI_STD_MADT_ENTRY Header;
	// ACPI_PROCESSOR_ID_ALL is a possible value
	INT8 ACPIProcessorId;
	UINT16 Flags;
	INT8 Lint;
} ACPI_MADT_LOCAL_APIC_NMI;

typedef struct {
	ACPI_STD_MADT_ENTRY Header;
	UINT16 Reserved;
	UINTN LocalAPICAddress;
} ACPI_MADT_LOCAL_APIC_OVERRIDE;

typedef struct {
	ACPI_STD_MADT_ENTRY Header;
	UINT16 Reserved;
	UINT16 Localx2APICId;
	UINT32 Flags;
	UINT32 ACPIId;
} ACPI_MADT_PROCESSOR_LOCAL_XAPIC2;

typedef struct {
	ACPI_STD_HEADER Header;
	UINT32 LocalAPICAddress;
	UINT32 Flags;
	ACPI_STD_MADT_ENTRY Entries;
} _Packed_ ACPI_MADT;

#define ACPI_MADT_ENTRY_OFFSET(p, i) \
	(((ACPI_STD_MADT_ENTRY*)((INT8*)p + sizeof(ACPI_MADT) + 4 + 4)) * i)

typedef struct {
	UINTN BaseAddress;
	UINT16 PCISegmentGroupNumber;
	INT8 StartBusNumber;
	INT8 EndBusNumber;
	UINT32 Reserved;
} _Packed_ ACPI_MCFG_ENTRY;

typedef struct {
	ACPI_STD_HEADER Header;
	ACPI_MCFG_ENTRY Entries;
} ACPI_MCFG;

#define ACPI_MCFG_ENTRY_OFFSET(p, i) \
	(((ACPI_MCFG_ENTRY*)((INT8*)p + sizeof(ACPI_MCFG))) * i)

typedef struct {
	ACPI_STD_HEADER Header;
	UINT32 FirmwareControl;
	ACPI_DSDT* DifferentiatedDescriptionTable;
	
	UINT8 Reserved;

	UINT8 PreferredPowerManagementProfile;
	UINT16 SciInterrupt;
	UINT32 SmiCommandPort;
	UINT8 AcpiEnable;
	UINT8 AcpiDisable;
	UINT8 S4BiosReq;
	UINT8 PstateControl;
	UINT32 Pm1aEventBlock;
	UINT32 Pm1bEventBlock;
	UINT32 Pm1aControlBlock;
	UINT32 Pm1bControlBlock;
	UINT32 Pm2ControlBlock;
	UINT32 PmTimerBlock;
	UINT32 Gpe0Block;
	UINT32 Gpe1Block;
	UINT8 Pm1EventLength;
	UINT8 Pm1ControlLength;
	UINT8 Pm2ControlLength;
	UINT8 PmTimerLength;
	UINT8 Gpe0Length;
	UINT8 Gpe1Length;
	UINT8 Gpe1Base;
	UINT8 CStateControl;
	UINT16 WorstC2Latency;
	UINT16 WorstC3Latency;
	UINT16 FlushSize;
	UINT16 FlushStride;
	UINT8 DutyOffset;
	UINT8 DutyWidth;
	UINT8 DayAlarm;
	UINT8 MonthAlarm;
	UINT8 Century;

	UINT16 BootArchitectureFlags;
	UINT8 Reserved2;
	UINT32 Flags;

	ACPI_GENERIC_ADDRESS ResetReg;
	UINT8       ResetValue;
	UINT8       Reserved3[3];

	UINT64      XFirmwareControl;
	UINT64      XDsdt;

	ACPI_GENERIC_ADDRESS X_Pm1aEventBlock;
	ACPI_GENERIC_ADDRESS X_Pm1bEventBlock;
	ACPI_GENERIC_ADDRESS X_Pm1aControlBlock;
	ACPI_GENERIC_ADDRESS X_Pm1bControlBlock;
	ACPI_GENERIC_ADDRESS X_Pm2ControlBlock;
	ACPI_GENERIC_ADDRESS X_PmTimerBlock;
	ACPI_GENERIC_ADDRESS X_Gpe0Block;
	ACPI_GENERIC_ADDRESS X_Gpe1Block;
} ACPI_FADT;

typedef struct {
	ACPI_STD_HEADER Header;
	ACPI_FADT* FixedDescriptionTable;
	ACPI_SSDT* SecondaryDescriptorTable;
	ACPI_MADT* MultipleAPICDescriptionTable;
	ACPI_MCFG* PCIExpressConfigurationSpace;
} _Packed_ ACPI_XSDT;
