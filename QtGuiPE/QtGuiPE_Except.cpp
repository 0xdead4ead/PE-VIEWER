#include "QtGuiPE_Except.h"

QtGuiPE_Except::QtGuiPE_Except(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.OKpushButton, SIGNAL(clicked()), this, SLOT(close()));

}

void QtGuiPE_Except::SetTextError(const QString& TextError) {
	ui.label->setText(TextError);
}