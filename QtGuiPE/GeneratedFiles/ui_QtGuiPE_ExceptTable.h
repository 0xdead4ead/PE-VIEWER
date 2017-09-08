/********************************************************************************
** Form generated from reading UI file 'QtGuiPE_ExceptTable.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIPE_EXCEPTTABLE_H
#define UI_QTGUIPE_EXCEPTTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiPE_ExceptTableClass
{
public:
    QFrame *frame;
    QFrame *frame_2;
    QLabel *label;
    QTableWidget *tableWidget;

    void setupUi(QWidget *QtGuiPE_ExceptTableClass)
    {
        if (QtGuiPE_ExceptTableClass->objectName().isEmpty())
            QtGuiPE_ExceptTableClass->setObjectName(QStringLiteral("QtGuiPE_ExceptTableClass"));
        QtGuiPE_ExceptTableClass->resize(600, 400);
        frame = new QFrame(QtGuiPE_ExceptTableClass);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 581, 381));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 10, 561, 361));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 141, 21));
        QFont font;
        font.setFamily(QStringLiteral("Lucida Console"));
        font.setPointSize(11);
        font.setUnderline(true);
        font.setStrikeOut(false);
        label->setFont(font);
        tableWidget = new QTableWidget(frame_2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 20, 541, 331));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->horizontalHeader()->setDefaultSectionSize(151);
        tableWidget->horizontalHeader()->setMinimumSectionSize(151);
        tableWidget->verticalHeader()->setMinimumSectionSize(30);

        retranslateUi(QtGuiPE_ExceptTableClass);

        QMetaObject::connectSlotsByName(QtGuiPE_ExceptTableClass);
    } // setupUi

    void retranslateUi(QWidget *QtGuiPE_ExceptTableClass)
    {
        QtGuiPE_ExceptTableClass->setWindowTitle(QApplication::translate("QtGuiPE_ExceptTableClass", "QtGuiPE_ExceptTable", Q_NULLPTR));
        label->setText(QApplication::translate("QtGuiPE_ExceptTableClass", "EXCEPTION TABLE", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGuiPE_ExceptTableClass: public Ui_QtGuiPE_ExceptTableClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIPE_EXCEPTTABLE_H
