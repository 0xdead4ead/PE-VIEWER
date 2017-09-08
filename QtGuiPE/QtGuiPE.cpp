#include "QtGuiPE.h"
#include <qfile.h>
#include <qfiledialog.h>
#include <qdebug.h>
#include <ctime>
#include <qmessagebox.h>

extern TCHAR ErrorBuffer[PE_FILE_MAXCHAR_ERROR];

QtGuiPE::QtGuiPE(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.OpenFilePushButton, SIGNAL(clicked()), this, SLOT(open_file_slot()));
	QObject::connect(ui.DataDirectoryPushButton, SIGNAL(clicked()), this, SLOT(data_directory_slot()));
	QObject::connect(ui.SectionsPushButton, SIGNAL(clicked()), this, SLOT(sections_slot()));
	QObject::connect(ui.CharacteristicsPushButton, SIGNAL(clicked()), this, SLOT(characteristics_slot()));
	QObject::connect(ui.DLLCharacteristicsPushButton, SIGNAL(clicked()), this, SLOT(dllcharacteristics_slot()));
	//QObject::connect(this, SIGNAL(closeClicked()), this, SLOT(quit()));
	//QObject::connect(data_directory.ui.ImportTablePushButton, SIGNAL(clicked()), this, SLOT(import_view_slot()));
	//QObject::connect(data_directory.ui.ExportTablePushButton, SIGNAL(clicked()), this, SLOT(export_view_slot()));



	
	//
	QObject::connect(ui.ClosePushButton, SIGNAL(clicked()), this, SLOT(quit()));
}

void QtGuiPE::fill_fields() {
	//https://msdn.microsoft.com/ru-ru/library/windows/desktop/ms680547(v=vs.85).aspx
	ui.e_magic->setText(QString("%1").arg(file.dos_header->e_magic, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_cblp->setText(QString("%1").arg(file.dos_header->e_cblp, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_cp->setText(QString("%1").arg(file.dos_header->e_cp, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_crlc->setText(QString("%1").arg(file.dos_header->e_crlc, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_cparhdr->setText(QString("%1").arg(file.dos_header->e_cparhdr, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_minalloc->setText(QString("%1").arg(file.dos_header->e_minalloc, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_maxalloc->setText(QString("%1").arg(file.dos_header->e_maxalloc, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_ss->setText(QString("%1").arg(file.dos_header->e_ss, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_sp->setText(QString("%1").arg(file.dos_header->e_sp, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_csum->setText(QString("%1").arg(file.dos_header->e_csum, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_ip->setText(QString("%1").arg(file.dos_header->e_ip, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_cs->setText(QString("%1").arg(file.dos_header->e_cs, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_lfarlc->setText(QString("%1").arg(file.dos_header->e_lfarlc, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_ovno->setText(QString("%1").arg(file.dos_header->e_ovno, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_oemid->setText(QString("%1").arg(file.dos_header->e_oemid, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_oeminfo->setText(QString("%1").arg(file.dos_header->e_oeminfo, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.e_lfanew->setText(QString("%1").arg(file.dos_header->e_lfanew, sizeof(LONG) * 2, 16, QLatin1Char('0')).toUpper());
	ui.Machine->setText(QString("%1").arg(file.file_header->Machine, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	switch (file.file_header->Machine) {
	case IMAGE_FILE_MACHINE_I386: ui.Machine_Word->setText( QString("I386")); break;
	case IMAGE_FILE_MACHINE_R3000: ui.Machine_Word->setText(QString("MIPS R3000")); break;
	case IMAGE_FILE_MACHINE_R4000: ui.Machine_Word->setText(QString("MIPS R4000")); break;
	case IMAGE_FILE_MACHINE_R10000: ui.Machine_Word->setText(QString("MIPS R10000")); break;
	case IMAGE_FILE_MACHINE_WCEMIPSV2: ui.Machine_Word->setText(QString("MIPS WCE V2")); break;
	case IMAGE_FILE_MACHINE_ALPHA:  ui.Machine_Word->setText(QString("ALPHA AXP")); break;
	case IMAGE_FILE_MACHINE_SH3:  ui.Machine_Word->setText(QString("Hitachi SH3")); break;
	case IMAGE_FILE_MACHINE_SH3DSP:  ui.Machine_Word->setText(QString("Hitachi SH3DSP")); break;
	case IMAGE_FILE_MACHINE_SH3E: ui.Machine_Word->setText(QString("Hitachi SH3E")); break;
	case IMAGE_FILE_MACHINE_SH4:  ui.Machine_Word->setText(QString("Hitachi SH4")); break;
	case IMAGE_FILE_MACHINE_SH5:  ui.Machine_Word->setText(QString("Hitachi SH5")); break;
	case IMAGE_FILE_MACHINE_ARM:  ui.Machine_Word->setText(QString("ARM")); break;
	case IMAGE_FILE_MACHINE_THUMB:  ui.Machine_Word->setText(QString("ARM Thumb")); break;
	case IMAGE_FILE_MACHINE_ARMNT:  ui.Machine_Word->setText(QString("ARM Thumb2")); break;
	case IMAGE_FILE_MACHINE_POWERPC:  ui.Machine_Word->setText(QString("IBM PowerPC")); break;
	case IMAGE_FILE_MACHINE_POWERPCFP:  ui.Machine_Word->setText(QString("IBM PowerPCFP")); break;
	case IMAGE_FILE_MACHINE_IA64: ui.Machine_Word->setText(QString("Intel 64")); break;
	case IMAGE_FILE_MACHINE_MIPS16: ui.Machine_Word->setText(QString("MIPS 16")); break;
	case IMAGE_FILE_MACHINE_ALPHA64: ui.Machine_Word->setText(QString("ALPHA 64")); break;
	case IMAGE_FILE_MACHINE_MIPSFPU: ui.Machine_Word->setText(QString("MIPS FPU")); break;
	case IMAGE_FILE_MACHINE_MIPSFPU16: ui.Machine_Word->setText(QString("MIPS FPU16")); break;
	case IMAGE_FILE_MACHINE_TRICORE: ui.Machine_Word->setText(QString("Infineon")); break;
	case IMAGE_FILE_MACHINE_CEF: ui.Machine_Word->setText(QString("CEF")); break;
	case IMAGE_FILE_MACHINE_EBC: ui.Machine_Word->setText(QString("EFI Byte")); break;
	case IMAGE_FILE_MACHINE_AMD64: ui.Machine_Word->setText(QString("AMD64")); break;
	case IMAGE_FILE_MACHINE_M32R: ui.Machine_Word->setText(QString("M32R")); break;
	case IMAGE_FILE_MACHINE_CEE: ui.Machine_Word->setText(QString("CEE")); break;
	default: ui.Machine_Word->setText(QString("UNKNOWN")); break;
	}
	ui.NumberOfSections->setText(QString("%1").arg(file.file_header->NumberOfSections, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.TimeDateStamp->setText(QString("%1").arg(file.file_header->TimeDateStamp, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
	char strdate[50];
	char strtime[50];
	
	
	//tm* timeinfo;
	//time_t datetime = pef.file_header->TimeDateStamp;
	//QDateTime datetime;
	//datetime.setOffsetFromUtc(pef.file_header->TimeDateStamp);
	ui.TimeDateStamp_dateTimeEdit->setDateTime(QDateTime::fromSecsSinceEpoch(file.file_header->TimeDateStamp));
	//ui.TimeDateStamp_dateTimeEdit->setCurrentSection(QDateTimeEdit::AmPmSection);
	//timeinfo = localtime(&datetime);
	//if (strftime(strdate, 50, "%F", timeinfo))
	//	if (strftime(strtime, 50, "%I:%M:%S %p", timeinfo)) //ui.TimeDateStamp_Word->setText(QString(strdate) + " " + QString(strtime));
	//	{
	//		QDate date = QDate::fromString(QString(strdate));
	//		QTime time = QTime::fromString(QString(strtime));
	//		ui.TimeDateStamp_dateTimeEdit->setDateTime(QDateTime(date, time));
	//	}
	ui.PointerToSymbolTable->setText(QString("%1").arg(file.file_header->PointerToSymbolTable, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.NumberOfSymbols->setText(QString("%1").arg(file.file_header->NumberOfSymbols, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.SizeOfOptionalHeader->setText(QString("%1").arg(file.file_header->SizeOfOptionalHeader, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	ui.Characteristics->setText(QString("%1").arg(file.file_header->Characteristics, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
	characteristics_fh.ui.checkBox->setChecked(0);
	characteristics_fh.ui.checkBox_2->setChecked(0);
	characteristics_fh.ui.checkBox_3->setChecked(0);
	characteristics_fh.ui.checkBox_4->setChecked(0);
	characteristics_fh.ui.checkBox_5->setChecked(0);
	characteristics_fh.ui.checkBox_6->setChecked(0);
	characteristics_fh.ui.checkBox_7->setChecked(0);
	characteristics_fh.ui.checkBox_8->setChecked(0);
	characteristics_fh.ui.checkBox_9->setChecked(0);
	characteristics_fh.ui.checkBox_10->setChecked(0);
	characteristics_fh.ui.checkBox_11->setChecked(0);
	characteristics_fh.ui.checkBox_12->setChecked(0);
	characteristics_fh.ui.checkBox_13->setChecked(0);
	characteristics_fh.ui.checkBox_14->setChecked(0);
	characteristics_fh.ui.checkBox_15->setChecked(0);
	if ((file.file_header->Characteristics & IMAGE_FILE_RELOCS_STRIPPED)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_2->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_LINE_NUMS_STRIPPED)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_3->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_LOCAL_SYMS_STRIPPED)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_4->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_AGGRESIVE_WS_TRIM)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_5->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_6->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_BYTES_REVERSED_LO)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_7->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_32BIT_MACHINE)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_8->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_DEBUG_STRIPPED)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_9->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_10->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_NET_RUN_FROM_SWAP)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_11->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_SYSTEM)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_12->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_DLL)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_13->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_UP_SYSTEM_ONLY)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_14->setChecked(1);
	if ((file.file_header->Characteristics & IMAGE_FILE_BYTES_REVERSED_HI)
		& file.file_header->Characteristics) characteristics_fh.ui.checkBox_15->setChecked(1);

	if (file.PE32) {
		ui.MagicOp->setText(QString("%1").arg(file.op_header32->Magic, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		/*switch (pef.op_header32->Magic) {
		case MAGIC_NUMBER_PE32: qDebug().noquote() << QString("PE32"); break;
		case MAGIC_NUMBER_ROM_IMAGE: qDebug().noquote() << QString("ROM IMAGE"); break;
		case MAGIC_NUMBER_PE32PLUS: qDebug().noquote() << QString("PE32+"); break;
		default: qDebug().noquote() << QString("Unknown"); break;
		}*/
		ui.MajorLinkerVersion->setText(QString("%1").arg(file.op_header32->MajorLinkerVersion, sizeof(BYTE) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MinorLinkerVersion->setText(QString("%1").arg(file.op_header32->MinorLinkerVersion, sizeof(BYTE) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfCode->setText(QString("%1").arg(file.op_header32->SizeOfCode, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfInitializedData->setText(QString("%1").arg(file.op_header32->SizeOfInitializedData, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfUninitializedData->setText(QString("%1").arg(file.op_header32->SizeOfUninitializedData, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.AddressOfEntryPoint->setText(QString("%1").arg(file.op_header32->AddressOfEntryPoint, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.BaseOfCode->setText(QString("%1").arg(file.op_header32->BaseOfCode, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.BaseOfData->setEnabled(1);
		ui.BaseOfData->setText(QString("%1").arg(file.op_header32->BaseOfData, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.ImageBase->setText(QString("%1").arg(file.op_header32->ImageBase, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SectionAlignment->setText(QString("%1").arg(file.op_header32->SectionAlignment, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.FileAlignment->setText(QString("%1").arg(file.op_header32->FileAlignment, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MajorOperatingSystemVersion->setText(QString("%1").arg(file.op_header32->MajorOperatingSystemVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MinorOperatingSystemVersion->setText(QString("%1").arg(file.op_header32->MinorOperatingSystemVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MajorImageVersion->setText(QString("%1").arg(file.op_header32->MajorImageVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MinorImageVersion->setText(QString("%1").arg(file.op_header32->MinorImageVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MajorSubsystemVersion->setText(QString("%1").arg(file.op_header32->MajorSubsystemVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MinorSubsystemVersion->setText(QString("%1").arg(file.op_header32->MinorSubsystemVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.Win32VersionValue->setText(QString("%1").arg(file.op_header32->Win32VersionValue, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfImage->setText(QString("%1").arg(file.op_header32->SizeOfImage, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfHeaders->setText(QString("%1").arg(file.op_header32->SizeOfHeaders, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.CheckSum->setText(QString("%1").arg(file.op_header32->CheckSum, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.Subsystem->setText(QString("%1").arg(file.op_header32->Subsystem, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		switch (file.op_header32->Subsystem) {
		case  IMAGE_SUBSYSTEM_NATIVE: ui.Subsystem_Word->setText(QString("NATIVE")); break;
		case  IMAGE_SUBSYSTEM_WINDOWS_GUI: ui.Subsystem_Word->setText(QString("WIN GUI")); break;
		case  IMAGE_SUBSYSTEM_WINDOWS_CUI: ui.Subsystem_Word->setText(QString("WIN CUI")); break;
		case  IMAGE_SUBSYSTEM_OS2_CUI: ui.Subsystem_Word->setText(QString("OS2 CUI")); break;
		case  IMAGE_SUBSYSTEM_POSIX_CUI: ui.Subsystem_Word->setText(QString("POSIX CUI")); break;
		case  IMAGE_SUBSYSTEM_NATIVE_WINDOWS: ui.Subsystem_Word->setText(QString("WIN9x DRV")); break;
		case  IMAGE_SUBSYSTEM_WINDOWS_CE_GUI: ui.Subsystem_Word->setText(QString("WINCE GUI")); break;
		case  IMAGE_SUBSYSTEM_EFI_APPLICATION: ui.Subsystem_Word->setText(QString("EFI APP")); break;
		case  IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER: ui.Subsystem_Word->setText(QString("EFI BOOT DEVICE")); break;
		case  IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER: ui.Subsystem_Word->setText(QString("EFI RUN-TIME DRIVER")); break;
		case  IMAGE_SUBSYSTEM_EFI_ROM: ui.Subsystem_Word->setText(QString("EFI ROM")); break;
		case  IMAGE_SUBSYSTEM_XBOX: ui.Subsystem_Word->setText(QString("EFI XBOX")); break;
		case  IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION: ui.Subsystem_Word->setText(QString("EFI WIN BOOT APP")); break;
		default: ui.Subsystem_Word->setText(QString("UNKNOWN")); break;
		}
		ui.DllCharacteristics->setText(QString("%1").arg(file.op_header32->DllCharacteristics, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		dllcharacteristics.ui.checkBox->setChecked(0);
		dllcharacteristics.ui.checkBox_2->setChecked(0);
		dllcharacteristics.ui.checkBox_3->setChecked(0);
		dllcharacteristics.ui.checkBox_4->setChecked(0);
		dllcharacteristics.ui.checkBox_5->setChecked(0);
		dllcharacteristics.ui.checkBox_6->setChecked(0);
		dllcharacteristics.ui.checkBox_7->setChecked(0);
		dllcharacteristics.ui.checkBox_8->setChecked(0);
		dllcharacteristics.ui.checkBox_9->setChecked(0);
		dllcharacteristics.ui.checkBox_10->setChecked(0);
		dllcharacteristics.ui.checkBox_11->setChecked(0);
		dllcharacteristics.ui.checkBox_12->setChecked(0);
		dllcharacteristics.ui.checkBox_13->setChecked(0);
		dllcharacteristics.ui.checkBox_14->setChecked(0);
		dllcharacteristics.ui.checkBox_15->setChecked(0);
		if ((file.op_header32->DllCharacteristics & IMAGE_LIBRARY_PROCESS_INIT) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_LIBRARY_PROCESS_TERM) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_2->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_LIBRARY_THREAD_INIT) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_3->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_LIBRARY_THREAD_TERM) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_4->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_5->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_6->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_7->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_NX_COMPAT) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_8->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_NO_ISOLATION) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_9->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_NO_SEH) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_10->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_NO_BIND) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_11->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_APPCONTAINER) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_12->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_WDM_DRIVER) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_13->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_GUARD_CF) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_14->setChecked(1);
		if ((file.op_header32->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE) &
			file.op_header32->DllCharacteristics) dllcharacteristics.ui.checkBox_15->setChecked(1);

		ui.SizeOfStackReserve->setText(QString("%1").arg(file.op_header32->SizeOfStackReserve, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfStackCommit->setText(QString("%1").arg(file.op_header32->SizeOfStackCommit, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfHeapReserve->setText(QString("%1").arg(file.op_header32->SizeOfHeapReserve, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfHeapCommit->setText(QString("%1").arg(file.op_header32->SizeOfHeapCommit, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.LoaderFlags->setText(QString("%1").arg(file.op_header32->LoaderFlags, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.NumberOfRvaAndSizes->setText(QString("%1").arg(file.op_header32->NumberOfRvaAndSizes, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());

	}
    else {
		ui.MagicOp->setText(QString("%1").arg(file.op_header64->Magic, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		/*switch (file.op_header64->Magic) {
		case MAGIC_NUMBER_PE32: qDebug().noquote() << QString("PE32"); break;
		case MAGIC_NUMBER_ROM_IMAGE: qDebug().noquote() << QString("ROM IMAGE"); break;
		case MAGIC_NUMBER_PE32PLUS: qDebug().noquote() << QString("PE32+"); break;
		default: qDebug().noquote() << QString("Unknown"); break;
		}*/
		ui.MajorLinkerVersion->setText(QString("%1").arg(file.op_header64->MajorLinkerVersion, sizeof(BYTE) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MinorLinkerVersion->setText(QString("%1").arg(file.op_header64->MinorLinkerVersion, sizeof(BYTE) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfCode->setText(QString("%1").arg(file.op_header64->SizeOfCode, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfInitializedData->setText(QString("%1").arg(file.op_header64->SizeOfInitializedData, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfUninitializedData->setText(QString("%1").arg(file.op_header64->SizeOfUninitializedData, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.AddressOfEntryPoint->setText(QString("%1").arg(file.op_header64->AddressOfEntryPoint, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.BaseOfCode->setText(QString("%1").arg(file.op_header64->BaseOfCode, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.BaseOfData->setDisabled(1);
		ui.BaseOfData->clear();
		ui.ImageBase->setText(QString("%1").arg(file.op_header64->ImageBase, sizeof(ULONGLONG) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SectionAlignment->setText(QString("%1").arg(file.op_header64->SectionAlignment, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.FileAlignment->setText(QString("%1").arg(file.op_header64->FileAlignment, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MajorOperatingSystemVersion->setText(QString("%1").arg(file.op_header64->MajorOperatingSystemVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MinorOperatingSystemVersion->setText(QString("%1").arg(file.op_header64->MinorOperatingSystemVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MajorImageVersion->setText(QString("%1").arg(file.op_header64->MajorImageVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MinorImageVersion->setText(QString("%1").arg(file.op_header64->MinorImageVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MajorSubsystemVersion->setText(QString("%1").arg(file.op_header64->MajorSubsystemVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MinorSubsystemVersion->setText(QString("%1").arg(file.op_header64->MinorSubsystemVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.Win32VersionValue->setText(QString("%1").arg(file.op_header64->Win32VersionValue, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfImage->setText(QString("%1").arg(file.op_header64->SizeOfImage, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfHeaders->setText(QString("%1").arg(file.op_header64->SizeOfHeaders, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.CheckSum->setText(QString("%1").arg(file.op_header64->CheckSum, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.Subsystem->setText(QString("%1").arg(file.op_header64->Subsystem, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		switch (file.op_header64->Subsystem) {
		case  IMAGE_SUBSYSTEM_NATIVE: ui.Subsystem_Word->setText(QString("NATIVE ")); break;
		case  IMAGE_SUBSYSTEM_WINDOWS_GUI: ui.Subsystem_Word->setText(QString("WIN GUI ")); break;
		case  IMAGE_SUBSYSTEM_WINDOWS_CUI: ui.Subsystem_Word->setText(QString("WIN CUI ")); break;
		case  IMAGE_SUBSYSTEM_OS2_CUI: ui.Subsystem_Word->setText(QString("OS2 CUI ")); break;
		case  IMAGE_SUBSYSTEM_POSIX_CUI: ui.Subsystem_Word->setText(QString("POSIX CUI ")); break;
		case  IMAGE_SUBSYSTEM_NATIVE_WINDOWS: ui.Subsystem_Word->setText(QString("WIN9x DRV ")); break;
		case  IMAGE_SUBSYSTEM_WINDOWS_CE_GUI: ui.Subsystem_Word->setText(QString("WINCE GUI ")); break;
		case  IMAGE_SUBSYSTEM_EFI_APPLICATION: ui.Subsystem_Word->setText(QString("EFI APP ")); break;
		case  IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER: ui.Subsystem_Word->setText(QString("EFI BOOT DEVICE ")); break;
		case  IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER: ui.Subsystem_Word->setText(QString("EFI RUN-TIME DRIVER ")); break;
		case  IMAGE_SUBSYSTEM_EFI_ROM: ui.Subsystem_Word->setText(QString("EFI ROM ")); break;
		case  IMAGE_SUBSYSTEM_XBOX: ui.Subsystem_Word->setText(QString("EFI XBOX ")); break;
		case  IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION: ui.Subsystem_Word->setText(QString("EFI WIN BOOT APP ")); break;
		default: ui.Subsystem_Word->setText(QString("UNKNOWN ")); break;
		}
		ui.DllCharacteristics->setText(QString("%1").arg(file.op_header64->DllCharacteristics, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		dllcharacteristics.ui.checkBox->setChecked(0);
		dllcharacteristics.ui.checkBox_2->setChecked(0);
		dllcharacteristics.ui.checkBox_3->setChecked(0);
		dllcharacteristics.ui.checkBox_4->setChecked(0);
		dllcharacteristics.ui.checkBox_5->setChecked(0);
		dllcharacteristics.ui.checkBox_6->setChecked(0);
		dllcharacteristics.ui.checkBox_7->setChecked(0);
		dllcharacteristics.ui.checkBox_8->setChecked(0);
		dllcharacteristics.ui.checkBox_9->setChecked(0);
		dllcharacteristics.ui.checkBox_10->setChecked(0);
		dllcharacteristics.ui.checkBox_11->setChecked(0);
		dllcharacteristics.ui.checkBox_12->setChecked(0);
		dllcharacteristics.ui.checkBox_13->setChecked(0);
		dllcharacteristics.ui.checkBox_14->setChecked(0);
		dllcharacteristics.ui.checkBox_15->setChecked(0);
		if ((file.op_header64->DllCharacteristics & IMAGE_LIBRARY_PROCESS_INIT) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_LIBRARY_PROCESS_TERM) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_2->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_LIBRARY_THREAD_INIT) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_3->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_LIBRARY_THREAD_TERM) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_4->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_5->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_6->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_7->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_NX_COMPAT) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_8->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_NO_ISOLATION) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_9->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_NO_SEH) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_10->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_NO_BIND) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_11->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_APPCONTAINER) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_12->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_WDM_DRIVER) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_13->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_GUARD_CF) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_14->setChecked(1);
		if ((file.op_header64->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE) &
			file.op_header64->DllCharacteristics) dllcharacteristics.ui.checkBox_15->setChecked(1);

		ui.SizeOfStackReserve->setText(QString("%1").arg(file.op_header64->SizeOfStackReserve, sizeof(ULONGLONG) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfStackCommit->setText(QString("%1").arg(file.op_header64->SizeOfStackCommit, sizeof(ULONGLONG) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfHeapReserve->setText(QString("%1").arg(file.op_header64->SizeOfHeapReserve, sizeof(ULONGLONG) * 2, 16, QLatin1Char('0')).toUpper());
		ui.SizeOfHeapCommit->setText(QString("%1").arg(file.op_header64->SizeOfHeapCommit, sizeof(ULONGLONG) * 2, 16, QLatin1Char('0')).toUpper());
		ui.LoaderFlags->setText(QString("%1").arg(file.op_header64->LoaderFlags, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.NumberOfRvaAndSizes->setText(QString("%1").arg(file.op_header64->NumberOfRvaAndSizes, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());


    }
	sections.fill_fields();
	data_directory.fill_fields();

}


bool QtGuiPE::ReadPE(const QString& pathfile) {
	bool res;
	__try {
		file.read(pathfile.toStdWString().c_str());
		res = true;
		fill_fields();
	}
	__except (PE_FILE_Exception(GetExceptionCode(), GetExceptionInformation(), ErrorBuffer, &file)) {
		//messageBox
		res = false;
		QMessageBox MsgBox;
		MsgBox.setText(QString::fromWCharArray(ErrorBuffer));
		MsgBox.setIcon(QMessageBox::Critical);
		MsgBox.setStandardButtons(QMessageBox::Ok);
		MsgBox.exec();
	}
	return res;
}

void QtGuiPE::open_file_slot() {
	QString pathfile = QFileDialog::getOpenFileName(this, tr("OPEN FILE"), "", tr("COFF FORMAT OBJECTS (*.exe *.dll *.ocx *.cpl)"));
	if (!pathfile.isEmpty()) {
		__try {
			file.read(pathfile.toStdWString().c_str());

			setWindowTitle(pathfile);
			sections.clear_fields_table();
			data_directory.clear_fields_in_all_tables();
			fill_fields();
		}
		__except (PE_FILE_Exception(GetExceptionCode(), GetExceptionInformation(), ErrorBuffer, &file)) {
			//messageBox
			QMessageBox MsgBox;
			MsgBox.setText(QString::fromWCharArray(ErrorBuffer));
			MsgBox.setIcon(QMessageBox::Critical);
			MsgBox.setStandardButtons(QMessageBox::Ok);
			MsgBox.exec();
		}
	}
}

void QtGuiPE::data_directory_slot() {
	data_directory.setWindowTitle(QString("GuiPEBuilder ") + QString("DATA DIRECTORY"));
	data_directory.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
	data_directory.show();
}

void QtGuiPE::sections_slot() {
	sections.setWindowTitle(QString("GuiPEBuilder ") + QString("SECTIONS"));
	sections.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
	sections.show();
}

void QtGuiPE::characteristics_slot() {
	characteristics_fh.setWindowTitle(QString("GuiPEBuilder ") + QString("Characteristics"));
	characteristics_fh.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
	characteristics_fh.show();

}

void QtGuiPE::dllcharacteristics_slot() {
	dllcharacteristics.setWindowTitle(QString("GuiPEBuilder ") + QString("DllCharacteristics"));
	dllcharacteristics.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
	dllcharacteristics.show();
}








void QtGuiPE::quit() {
	exit(1);
}

void QtGuiPE::closeEvent(QCloseEvent *event)
{
	quit();
}