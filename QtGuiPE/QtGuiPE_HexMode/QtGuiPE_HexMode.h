#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiPE_HexMode.h"
#include "QHexView.h"
class QtGuiPE_HexMode : public QWidget
{
	Q_OBJECT

public:
	QtGuiPE_HexMode(QWidget *parent = Q_NULLPTR);

	void setData(QHexView::DataStorage *pData);
	void offset(std::size_t offset);
private:
	Ui::QtGuiPE_HexModeClass ui;
	QHexView qhw;
};
