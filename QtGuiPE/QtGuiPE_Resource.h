#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiPE_Resource.h"
//#include "QtGuiPE.h"
class QtGuiPE_Resource : public QWidget
{
	Q_OBJECT

public:
	QtGuiPE_Resource(QWidget *parent = Q_NULLPTR);

	void fill_fields();
	void clear_fields();
private:
	Ui::QtGuiPE_ResourceClass ui;
};
