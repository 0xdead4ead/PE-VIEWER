/********************************************************************************
** Form generated from reading UI file 'QtGuiPE_HexMode.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIPE_HEXMODE_H
#define UI_QTGUIPE_HEXMODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiPE_HexModeClass
{
public:
    QFrame *frame;
    QFrame *frame_2;
    QLabel *label;

    void setupUi(QWidget *QtGuiPE_HexModeClass)
    {
        if (QtGuiPE_HexModeClass->objectName().isEmpty())
            QtGuiPE_HexModeClass->setObjectName(QStringLiteral("QtGuiPE_HexModeClass"));
        QtGuiPE_HexModeClass->resize(689, 400);
        frame = new QFrame(QtGuiPE_HexModeClass);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 671, 381));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 10, 651, 361));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 91, 16));
        QFont font;
        font.setFamily(QStringLiteral("Lucida Console"));
        font.setPointSize(11);
        font.setUnderline(true);
        label->setFont(font);

        retranslateUi(QtGuiPE_HexModeClass);

        QMetaObject::connectSlotsByName(QtGuiPE_HexModeClass);
    } // setupUi

    void retranslateUi(QWidget *QtGuiPE_HexModeClass)
    {
        QtGuiPE_HexModeClass->setWindowTitle(QApplication::translate("QtGuiPE_HexModeClass", "QtGuiPE_HexMode", Q_NULLPTR));
        label->setText(QApplication::translate("QtGuiPE_HexModeClass", "HEX MODE", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGuiPE_HexModeClass: public Ui_QtGuiPE_HexModeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIPE_HEXMODE_H
