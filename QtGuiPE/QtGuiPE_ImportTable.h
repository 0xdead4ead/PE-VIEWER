#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiPE_ImportTable.h"
#include "QtGuiPE_Thunks.h"

class QtGuiPE_ImportTable : public QWidget
{
	Q_OBJECT

public:
	QtGuiPE_ImportTable(QWidget *parent = Q_NULLPTR);
	void fill_fields();
	void clear_fields_table();
private:
	QtGuiPE_Thunks thunks_table;
	Ui::QtGuiPE_ImportTableClass ui;
public Q_SLOTS:
	void import_thunks_slot(int row, int column);
};
