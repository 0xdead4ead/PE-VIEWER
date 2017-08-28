#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiPE_Thunks.h"

class QtGuiPE_Thunks : public QWidget
{
	Q_OBJECT

public:
	QtGuiPE_Thunks(QWidget *parent = Q_NULLPTR);
	void fill(int row, int column);
private:
	Ui::QtGuiPE_ThunksClass ui;

};
