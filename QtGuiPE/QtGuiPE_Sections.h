#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiPE_Sections.h"

class QtGuiPE_Sections : public QWidget
{
	Q_OBJECT

public:
	QtGuiPE_Sections(QWidget *parent = Q_NULLPTR);
	void fill_fields();
	void clear_fields_table();
private:
	Ui::QtGuiPE_SectionsClass ui;
};
