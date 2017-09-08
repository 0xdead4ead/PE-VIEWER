#include "QtGuiPE_ExceptTable.h"
#include "PE_FILE1.h"
QtGuiPE_ExceptTable::QtGuiPE_ExceptTable(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void QtGuiPE_ExceptTable::fill_fields() {
	if ((file.file_header->Machine == IMAGE_FILE_MACHINE_IA64) ||
		(file.file_header->Machine == IMAGE_FILE_MACHINE_AMD64)) {
		
		ui.tableWidget->insertColumn(0);
		ui.tableWidget->insertColumn(1);
		ui.tableWidget->insertColumn(2);
		ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "Begin Address" << "End Address" << "Unwind Info");
		for (DWORD i = 0; i < file.exception_table_x64.size(); i++) {
			ui.tableWidget->insertRow(i);
			ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(file.exception_table_x64[i].BeginAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(file.exception_table_x64[i].EndAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(file.exception_table_x64[i].UnwindInformation, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		}
	}
	else if (file.file_header->Machine == IMAGE_FILE_MACHINE_R3000) {
		ui.tableWidget->insertColumn(0);
		ui.tableWidget->insertColumn(1);
		ui.tableWidget->insertColumn(2);
		ui.tableWidget->insertColumn(3);
		ui.tableWidget->insertColumn(4);
		ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "Begin Address" << "End Address" << "Exception Handler" << "Handler Data" << "Prolog End Address");
		for (DWORD i = 0; i < file.exception_table_mips32.size(); i++) {
			ui.tableWidget->insertRow(i);
			ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(file.exception_table_mips32[i].BeginAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(file.exception_table_mips32[i].EndAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(file.exception_table_mips32[i].ExceptionHandler, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(file.exception_table_mips32[i].HandlerData, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 4, new QTableWidgetItem(QString("%1").arg(file.exception_table_mips32[i].PrologEndAdress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		}
	}
	else {
		ui.tableWidget->insertColumn(0);
		ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "Begin Address");
		for (DWORD i = 0; i < file.exception_table_other.size(); i++) {
			ui.tableWidget->insertRow(i);
			ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(file.exception_table_other[i].BeginAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		}
	}
}

void QtGuiPE_ExceptTable::clear_fields_table() {
	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(0);
	ui.tableWidget->setColumnCount(0);
}