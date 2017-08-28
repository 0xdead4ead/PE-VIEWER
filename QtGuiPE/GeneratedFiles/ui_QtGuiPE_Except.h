/********************************************************************************
** Form generated from reading UI file 'QtGuiPE_Except.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIPE_EXCEPT_H
#define UI_QTGUIPE_EXCEPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiPE_ExceptClass
{
public:
    QPushButton *OKpushButton;
    QLabel *label;

    void setupUi(QWidget *QtGuiPE_ExceptClass)
    {
        if (QtGuiPE_ExceptClass->objectName().isEmpty())
            QtGuiPE_ExceptClass->setObjectName(QStringLiteral("QtGuiPE_ExceptClass"));
        QtGuiPE_ExceptClass->resize(455, 132);
        OKpushButton = new QPushButton(QtGuiPE_ExceptClass);
        OKpushButton->setObjectName(QStringLiteral("OKpushButton"));
        OKpushButton->setGeometry(QRect(370, 100, 75, 23));
        label = new QLabel(QtGuiPE_ExceptClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 431, 81));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);

        retranslateUi(QtGuiPE_ExceptClass);

        QMetaObject::connectSlotsByName(QtGuiPE_ExceptClass);
    } // setupUi

    void retranslateUi(QWidget *QtGuiPE_ExceptClass)
    {
        QtGuiPE_ExceptClass->setWindowTitle(QApplication::translate("QtGuiPE_ExceptClass", "QtGuiPE_Except", Q_NULLPTR));
        OKpushButton->setText(QApplication::translate("QtGuiPE_ExceptClass", "OK", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtGuiPE_ExceptClass: public Ui_QtGuiPE_ExceptClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIPE_EXCEPT_H
