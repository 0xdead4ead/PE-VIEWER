#include "QtGuiPE_DataDirectory.h"
#include "qmessagebox.h"
#include "PE_FILE1.h"

QtGuiPE_DataDirectory::QtGuiPE_DataDirectory(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.tableWidget, SIGNAL(cellActivated(int, int)), this, SLOT(data_directory_tableActivated_slot(int, int)));
}

void QtGuiPE_DataDirectory::data_directory_tableActivated_slot(int row, int column) {
	switch (row) {
	case IMAGE_DIRECTORY_ENTRY_EXPORT: {
		if (file.PE32) {
			if (file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress) {
				export_table.setWindowTitle(QString("GuiPEBuilder ") + QString("EXPORT TABLE"));
				export_table.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
				export_table.show();
			}
			else {
				QMessageBox MsgBox;
				MsgBox.setText(QString::fromWCharArray(L"Export table not present"));
				MsgBox.setIcon(QMessageBox::Warning);
				MsgBox.setStandardButtons(QMessageBox::Ok);
				MsgBox.exec();
			}
		}
		else {
			if (file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress) {
				export_table.setWindowTitle(QString("GuiPEBuilder ") + QString("EXPORT TABLE"));
				export_table.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
				export_table.show();
			}
			else {
				QMessageBox MsgBox;
				MsgBox.setText(QString::fromWCharArray(L"Export table not present"));
				MsgBox.setIcon(QMessageBox::Warning);
				MsgBox.setStandardButtons(QMessageBox::Ok);
				MsgBox.exec();
			}
		}
		break;
	}
	case IMAGE_DIRECTORY_ENTRY_IMPORT: {
		if (file.PE32) {
			if (file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress) {
				import_table.setWindowTitle(QString("GuiPEBuilder ") + QString("IMPORT TABLE"));
				import_table.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
				import_table.show();
			}
			else {
				QMessageBox MsgBox;
				MsgBox.setText(QString::fromWCharArray(L"Import table not present"));
				MsgBox.setIcon(QMessageBox::Warning);
				MsgBox.setStandardButtons(QMessageBox::Ok);
				MsgBox.exec();
			}
		}
		else {
			if (file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress) {
				import_table.setWindowTitle(QString("GuiPEBuilder ") + QString("IMPORT TABLE"));
				import_table.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
				import_table.show();
			}
			else {
				QMessageBox MsgBox;
				MsgBox.setText(QString::fromWCharArray(L"Import table not present"));
				MsgBox.setIcon(QMessageBox::Warning);
				MsgBox.setStandardButtons(QMessageBox::Ok);
				MsgBox.exec();
			}
		}
		break;
	}
	case IMAGE_DIRECTORY_ENTRY_RESOURCE: {
		if (file.PE32) {
			if (file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress) {
				resource.setWindowTitle(QString("GuiPEBuilder ") + QString("RESOURCE TABLE"));
				resource.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
				resource.show();
			}
			else {
				QMessageBox MsgBox;
				MsgBox.setText(QString::fromWCharArray(L"Resource table not present"));
				MsgBox.setIcon(QMessageBox::Warning);
				MsgBox.setStandardButtons(QMessageBox::Ok);
				MsgBox.exec();
			}
		}
		else {
			if (file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress) {
				resource.setWindowTitle(QString("GuiPEBuilder ") + QString("RESOURCE TABLE"));
				resource.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
				resource.show();
			}
			else {
				QMessageBox MsgBox;
				MsgBox.setText(QString::fromWCharArray(L"Resource table not present"));
				MsgBox.setIcon(QMessageBox::Warning);
				MsgBox.setStandardButtons(QMessageBox::Ok);
				MsgBox.exec();
			}
		}
		break;
	}
	case IMAGE_DIRECTORY_ENTRY_EXCEPTION: {
		if (file.PE32) {
			if (file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress) {
				except_table.setWindowTitle(QString("GuiPEBuilder ") + QString("EXCEPTION TABLE"));
				except_table.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
				except_table.show();
				if ((file.file_header->Machine != IMAGE_FILE_MACHINE_IA64) 
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_AMD64)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_R3000)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_ARM)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_POWERPC)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_POWERPCFP)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_SH3)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_SH4)) {
					QMessageBox MsgBox;
					MsgBox.setText(QString::fromWCharArray(L"Exception table exists only for IA64, x86-64, MIPS R3000, ARM, PowerPC processors, SH3 and SH4.\nThe following data may be incorrect."));
					MsgBox.setIcon(QMessageBox::Warning);
					MsgBox.setStandardButtons(QMessageBox::Ok);
					MsgBox.exec();
				}
			}
			else {
				QMessageBox MsgBox;
				MsgBox.setText(QString::fromWCharArray(L"Exception table not present"));
				MsgBox.setIcon(QMessageBox::Warning);
				MsgBox.setStandardButtons(QMessageBox::Ok);
				MsgBox.exec();
			}
		}
		else {
			if (file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress) {
				except_table.setWindowTitle(QString("GuiPEBuilder ") + QString("EXCEPTION TABLE"));
				except_table.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
				except_table.show();
				if ((file.file_header->Machine != IMAGE_FILE_MACHINE_IA64)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_AMD64)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_R3000)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_ARM)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_POWERPC)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_POWERPCFP)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_SH3)
					&& (file.file_header->Machine != IMAGE_FILE_MACHINE_SH4)) {
					QMessageBox MsgBox;
					MsgBox.setText(QString::fromWCharArray(L"Exception table exists only for IA64, x86-64, MIPS R3000, ARM, PowerPC processors, SH3 and SH4.\nThe following data may be incorrect."));
					MsgBox.setIcon(QMessageBox::Warning);
					MsgBox.setStandardButtons(QMessageBox::Ok);
					MsgBox.exec();
				}
			}
			else {
				QMessageBox MsgBox;
				MsgBox.setText(QString::fromWCharArray(L"Exception table not present"));
				MsgBox.setIcon(QMessageBox::Warning);
				MsgBox.setStandardButtons(QMessageBox::Ok);
				MsgBox.exec();
			}
		}
		break; 
	}
	}
}


void QtGuiPE_DataDirectory::fill_fields() {
	if (file.PE32) {
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_EXPORT, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_EXPORT, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_IMPORT, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_IMPORT, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_RESOURCE, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_RESOURCE, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_EXCEPTION, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_EXCEPTION, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_SECURITY, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_SECURITY, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_BASERELOC, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_BASERELOC, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_DEBUG, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_DEBUG, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_GLOBALPTR, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_GLOBALPTR, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_TLS, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_TLS, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_IAT, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_IAT, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_RESERVED, 0, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESERVED].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_RESERVED, 1, new QTableWidgetItem(QString("%1").arg(file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESERVED].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
	}
	else {
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_EXPORT, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_EXPORT, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_IMPORT, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_IMPORT, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_RESOURCE, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_RESOURCE, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_EXCEPTION, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_EXCEPTION, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_SECURITY, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_SECURITY, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_BASERELOC, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_BASERELOC, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_DEBUG, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_DEBUG, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_GLOBALPTR, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_GLOBALPTR, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_TLS, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_TLS, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_IAT, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_IAT, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));

		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_RESERVED, 0, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESERVED].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(IMAGE_DIRECTORY_ENTRY_RESERVED, 1, new QTableWidgetItem(QString("%1").arg(file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESERVED].Size, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
	}
	export_table.fill_fields();
	import_table.fill_fields();
	resource.fill_fields();
	except_table.fill_fields();
}

void QtGuiPE_DataDirectory::clear_fields_in_all_tables() {
	export_table.clear_fields_table();
	import_table.clear_fields_table();
	resource.clear_fields();
	except_table.clear_fields_table();
}