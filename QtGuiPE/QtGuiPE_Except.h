#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiPE_Except.h"

class QtGuiPE_Except : public QWidget
{
	Q_OBJECT

public:
	//QtGuiPE_Except(const QString& TextError, QWidget *parent = Q_NULLPTR);
	QtGuiPE_Except(QWidget *parent = Q_NULLPTR);
	void SetTextError(const QString& TextError);

	Ui::QtGuiPE_ExceptClass ui;
};
