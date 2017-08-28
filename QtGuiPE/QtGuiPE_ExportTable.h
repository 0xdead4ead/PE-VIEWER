#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiPE_ExportTable.h"

class QtGuiPE_ExportTable : public QWidget
{
	Q_OBJECT

public:

	QtGuiPE_ExportTable(QWidget *parent = Q_NULLPTR);
	void fill_fields();
	void clear_fields_table();
private:
	Ui::QtGuiPE_ExportTableClass ui;
};
