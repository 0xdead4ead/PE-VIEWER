#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiPE_Characteristics.h"

class QtGuiPE_Characteristics : public QWidget
{
	Q_OBJECT

public:
	QtGuiPE_Characteristics(QWidget *parent = Q_NULLPTR);


	Ui::QtGuiPE_CharacteristicsClass ui;
};
