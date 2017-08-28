#include "QtGuiPE_ImportTable.h"
#include "PE_FILE1.h"
QtGuiPE_ImportTable::QtGuiPE_ImportTable(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.tableWidget, SIGNAL(cellActivated(int, int)), this, SLOT(import_thunks_slot(int, int)));
}

void QtGuiPE_ImportTable::fill_fields() {
	DWORD RVA;
	if (file.PE32)
		RVA = file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	else
		RVA = file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;

	if (RVA) {
		for (int i = 0; i < file.import_table->import_headers.size(); i++) {

			ui.tableWidget->insertRow(i);
			ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString((*file.import_table->dll_names_of_import_desc)[i].c_str())));
			ui.tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(file.import_table->import_headers[i].OriginalFirstThunk, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(file.import_table->import_headers[i].TimeDateStamp, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(file.import_table->import_headers[i].ForwarderChain, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 4, new QTableWidgetItem(QString("%1").arg(file.import_table->import_headers[i].Name, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
			ui.tableWidget->setItem(i, 5, new QTableWidgetItem(QString("%1").arg(file.import_table->import_headers[i].FirstThunk, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper()));
		}
	}
}

void QtGuiPE_ImportTable::import_thunks_slot(int row, int column) {
	thunks_table.fill(row, column);
	thunks_table.setWindowTitle(QString("QtGuiPE ") + QString("THUNKS ") + QString((*file.import_table->dll_names_of_import_desc)[row].c_str()));
	thunks_table.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
	thunks_table.show();
}

void QtGuiPE_ImportTable::clear_fields_table() {
	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(0);
}