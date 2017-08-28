#include "QtGuiPE_Sections.h"
#include "PE_FILE1.h"
QtGuiPE_Sections::QtGuiPE_Sections(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void QtGuiPE_Sections::fill_fields() {
	for (WORD i = 0; i < file.file_header->NumberOfSections; i++)
	{
		ui.tableWidget->insertRow(i);
		 ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString((char*)file.section_headers[i].Name)));
		 ui.tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(file.section_headers[i].Misc.VirtualSize, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(file.section_headers[i].VirtualAddress, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(file.section_headers[i].SizeOfRawData, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(i, 4, new QTableWidgetItem(QString("%1").arg(file.section_headers[i].PointerToRawData, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		//	 ui.tableWidget->setItem(i, 5, new QTableWidgetItem(QString("%1").arg(file.section_headers[i].PointerToRelocations, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		//	 ui.tableWidget->setItem(i, 6, new QTableWidgetItem(QString("%1").arg(file.section_headers[i].PointerToLinenumbers, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		//	 ui.tableWidget->setItem(i, 7, new QTableWidgetItem(QString("%1").arg(file.section_headers[i].NumberOfRelocations, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper()));
		//	 ui.tableWidget->setItem(i, 8, new QTableWidgetItem(QString("%1").arg(file.section_headers[i].NumberOfLinenumbers, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper()));
		 ui.tableWidget->setItem(i, 5, new QTableWidgetItem(QString("%1").arg(file.section_headers[i].Characteristics, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
	}
}

void QtGuiPE_Sections::clear_fields_table() {
	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(0);
}