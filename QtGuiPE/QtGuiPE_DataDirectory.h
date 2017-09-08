#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiPE_DataDirectory.h"
#include <qstringlist.h>
#include "QtGuiPE_ExportTable.h"
#include "QtGuiPE_ImportTable.h"
#include "QtGuiPE_Resource.h"
#include "QtGuiPE_ExceptTable.h"

class QtGuiPE_DataDirectory : public QWidget
{
	Q_OBJECT

public:
	QtGuiPE_DataDirectory(QWidget *parent = Q_NULLPTR);
	void fill_fields();
	void clear_fields_in_all_tables();
private:
	Ui::QtGuiPE_DataDirectoryClass ui;
	QtGuiPE_ExportTable export_table;
	QtGuiPE_ImportTable import_table;
	QtGuiPE_Resource resource;
	QtGuiPE_ExceptTable except_table;

public Q_SLOTS:
	void data_directory_tableActivated_slot(int row, int column);
};
