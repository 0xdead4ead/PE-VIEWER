/********************************************************************************
** Form generated from reading UI file 'QtGuiPE_ImportTable.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIPE_IMPORTTABLE_H
#define UI_QTGUIPE_IMPORTTABLE_H

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

class Ui_QtGuiPE_ImportTableClass
{
public:
    QFrame *frame;
    QFrame *frame_2;
    QLabel *label;
    QTableWidget *tableWidget;
    QLabel *label_2;

    void setupUi(QWidget *QtGuiPE_ImportTableClass)
    {
        if (QtGuiPE_ImportTableClass->objectName().isEmpty())
            QtGuiPE_ImportTableClass->setObjectName(QStringLiteral("QtGuiPE_ImportTableClass"));
        QtGuiPE_ImportTableClass->resize(977, 289);
        frame = new QFrame(QtGuiPE_ImportTableClass);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(9, 9, 951, 271));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 10, 931, 251));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 121, 21));
        QFont font;
        font.setFamily(QStringLiteral("Lucida Console"));
        font.setPointSize(11);
        font.setUnderline(true);
        font.setStrikeOut(false);
        label->setFont(font);
        tableWidget = new QTableWidget(frame_2);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 21, 911, 221));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->horizontalHeader()->setDefaultSectionSize(151);
        tableWidget->horizontalHeader()->setMinimumSectionSize(151);
        tableWidget->verticalHeader()->setMinimumSectionSize(30);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 0, 431, 20));
        QFont font1;
        font1.setPointSize(9);
        label_2->setFont(font1);
        label_2->setTextFormat(Qt::AutoText);
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(QtGuiPE_ImportTableClass);

        QMetaObject::connectSlotsByName(QtGuiPE_ImportTableClass);
    } // setupUi

    void retranslateUi(QWidget *QtGuiPE_ImportTableClass)
    {
        QtGuiPE_ImportTableClass->setWindowTitle(QApplication::translate("QtGuiPE_ImportTableClass", "QtGuiPE_ImportTable", Q_NULLPTR));
        label->setText(QApplication::translate("QtGuiPE_ImportTableClass", "IMPORT TABLE", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QtGuiPE_ImportTableClass", "DLL Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QtGuiPE_ImportTableClass", "Original First Thunk", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QtGuiPE_ImportTableClass", "Time Date Stamp", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QtGuiPE_ImportTableClass", "Forwarder Chain", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("QtGuiPE_ImportTableClass", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("QtGuiPE_ImportTableClass", "First Thunk", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtGuiPE_ImportTableClass", "Double click or Press Enter to view DLL import", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGuiPE_ImportTableClass: public Ui_QtGuiPE_ImportTableClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIPE_IMPORTTABLE_H
