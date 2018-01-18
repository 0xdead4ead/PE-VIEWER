#include "QtGuiPE_HexMode.h"

QtGuiPE_HexMode::QtGuiPE_HexMode(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	qhw.setParent(ui.frame_2);
	qhw.setGeometry(QRect(9, 19, 631, 331));
}


void QtGuiPE_HexMode::setData(QHexView::DataStorage *pData) {
	qhw.setData(pData);
}


void QtGuiPE_HexMode::offset(std::size_t offset) {
	qhw.showFromOffset(offset);

}