#include "QtGuiPE_Thunks.h"
#include <qdebug.h>
#include "PE_FILE1.h"
QtGuiPE_Thunks::QtGuiPE_Thunks(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void QtGuiPE_Thunks::fill(int row, int column) {
	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(0);

	if (file.PE32) {
		if (file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress) {
			int ii = 0;
			DWORD th_rvafirst = file.import_table->import_headers[row].OriginalFirstThunk;
			for (vector<IMAGE_THUNK_DATA32>::iterator ptd32 = (*file.import_table->image_thunk32)[row].begin();
				ptd32 != (*file.import_table->image_thunk32)[row].end();
				ptd32++) {

				ui.tableWidget->insertRow(ii);
				ui.tableWidget->setItem(ii, 0, new QTableWidgetItem(QString((*file.import_table->func_names_of_import_desc)[row][ii].c_str())));
				ui.tableWidget->setItem(ii, 1, new QTableWidgetItem(QString("%1").arg(ptd32->u1.AddressOfData, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
				ui.tableWidget->setItem(ii, 2, new QTableWidgetItem(QString("%1").arg(th_rvafirst + (ii * sizeof(DWORD)), sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
				DWORD offset = rvaToOff(&file.section_headers, th_rvafirst + (ii * sizeof(DWORD)), file.op_header32->SectionAlignment);
				ui.tableWidget->setItem(ii, 3, new QTableWidgetItem(QString("%1").arg(offset, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
				WORD Hint = (*file.import_table->image_import_names)[row][ii].Hint;
				if(Hint == 0xFFFF)
					ui.tableWidget->setItem(ii, 4, new QTableWidgetItem(QString("???")));
				else 	
				    ui.tableWidget->setItem(ii, 4, new QTableWidgetItem(QString("%1").arg(Hint, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper()));
				ii++;
			}
		}
	}
	else {
		if (file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress) {
			int ii = 0;
			DWORD th_rvafirst = file.import_table->import_headers[row].OriginalFirstThunk;
			for (vector<IMAGE_THUNK_DATA64>::iterator ptd64 = (*file.import_table->image_thunk64)[row].begin();
				ptd64 != (*file.import_table->image_thunk64)[row].end();
				ptd64++) {

				ui.tableWidget->insertRow(ii);
				ui.tableWidget->setItem(ii, 0, new QTableWidgetItem(QString((*file.import_table->func_names_of_import_desc)[row][ii].c_str())));
				ui.tableWidget->setItem(ii, 1, new QTableWidgetItem(QString("%1").arg(ptd64->u1.AddressOfData, sizeof(ULONGLONG) * 2, 16, QLatin1Char('0')).toUpper()));
				ui.tableWidget->setItem(ii, 2, new QTableWidgetItem(QString("%1").arg(th_rvafirst + (ii * sizeof(DWORD)), sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
				DWORD offset = rvaToOff(&file.section_headers, th_rvafirst + (ii * sizeof(DWORD)), file.op_header64->SectionAlignment);
				ui.tableWidget->setItem(ii, 3, new QTableWidgetItem(QString("%1").arg(offset, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
				WORD Hint = (*file.import_table->image_import_names)[row][ii].Hint;
				if (Hint == 0xFFFF)
					ui.tableWidget->setItem(ii, 4, new QTableWidgetItem(QString("???")));
				else
					ui.tableWidget->setItem(ii, 4, new QTableWidgetItem(QString("%1").arg(Hint, sizeof(WORD) * 2, 16, QLatin1Char('0')).toUpper()));
				ii++;
			}
		}
	}
}