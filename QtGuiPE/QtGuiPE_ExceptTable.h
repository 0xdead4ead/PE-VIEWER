#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiPE_ExceptTable.h"

class QtGuiPE_ExceptTable : public QWidget
{
	Q_OBJECT

public:
	QtGuiPE_ExceptTable(QWidget *parent = Q_NULLPTR);
	void fill_fields();
	void clear_fields_table();
private:
	Ui::QtGuiPE_ExceptTableClass ui;
};
