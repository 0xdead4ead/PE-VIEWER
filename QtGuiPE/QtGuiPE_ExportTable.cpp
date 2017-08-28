#include "QtGuiPE_ExportTable.h"
#include "PE_FILE1.h"
QtGuiPE_ExportTable::QtGuiPE_ExportTable(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void QtGuiPE_ExportTable::fill_fields() {
	DWORD RVA;
	if (file.PE32)
		RVA = file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	else
		RVA = file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

	if (RVA) {
		ui.Characteristics->setText(QString("%1").arg(file.export_table->export_header->Characteristics, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.TimeDateStamp->setText(QString("%1").arg(file.export_table->export_header->TimeDateStamp, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MajorVersion->setText(QString("%1").arg(file.export_table->export_header->MajorVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.MinorVersion->setText(QString("%1").arg(file.export_table->export_header->MinorVersion, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.Name->setText(QString("%1").arg(file.export_table->export_header->Name, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.Base->setText(QString("%1").arg(file.export_table->export_header->Base, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.NumberOfFunctions->setText(QString("%1").arg(file.export_table->export_header->NumberOfFunctions, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.NumberOfNames->setText(QString("%1").arg(file.export_table->export_header->NumberOfNames, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.AddressOfFunctions->setText(QString("%1").arg(file.export_table->export_header->AddressOfFunctions, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.AddressOfNames->setText(QString("%1").arg(file.export_table->export_header->AddressOfNames, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.AddressOfNameOrdinals->setText(QString("%1").arg(file.export_table->export_header->AddressOfNameOrdinals, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
		ui.DLLName->setText((*file.export_table->export_name).c_str());

		for (DWORD i = 0; i < file.export_table->export_header->NumberOfFunctions; i++) {
			ui.tableWidget->insertRow(i);
			ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg((*file.export_table->export_ordinals)[i], sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 1, new QTableWidgetItem((*file.export_table->export_names)[i].c_str()));
			ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString("%1").arg((*file.export_table->export_rva)[i], sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1").arg((*file.export_table->export_adress_names_rva)[i], sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			if (file.PE32) {
				DWORD offset = rvaToOff(&file.section_headers, (*file.export_table->export_rva)[i], file.op_header32->SectionAlignment);
				ui.tableWidget->setItem(i, 4, new QTableWidgetItem(QString("%1").arg(offset, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			}
			else {
				DWORD offset = rvaToOff(&file.section_headers, (*file.export_table->export_rva)[i], file.op_header64->SectionAlignment);
				ui.tableWidget->setItem(i, 4, new QTableWidgetItem(QString("%1").arg(offset, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			}
		}
	}
}

void QtGuiPE_ExportTable::clear_fields_table() {
	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(0);
}