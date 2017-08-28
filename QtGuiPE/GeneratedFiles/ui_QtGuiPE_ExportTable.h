/********************************************************************************
** Form generated from reading UI file 'QtGuiPE_ExportTable.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIPE_EXPORTTABLE_H
#define UI_QTGUIPE_EXPORTTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiPE_ExportTableClass
{
public:
    QFrame *frame;
    QFrame *frame_2;
    QLabel *label;
    QTableWidget *tableWidget;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *Characteristics;
    QLineEdit *TimeDateStamp;
    QLineEdit *MajorVersion;
    QLineEdit *MinorVersion;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *NumberOfFunctions;
    QLineEdit *NumberOfNames;
    QLineEdit *AddressOfFunctions;
    QLineEdit *AddressOfNames;
    QLineEdit *AddressOfNameOrdinals;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *Name;
    QLineEdit *Base;
    QLineEdit *DLLName;
    QLabel *label_13;

    void setupUi(QWidget *QtGuiPE_ExportTableClass)
    {
        if (QtGuiPE_ExportTableClass->objectName().isEmpty())
            QtGuiPE_ExportTableClass->setObjectName(QStringLiteral("QtGuiPE_ExportTableClass"));
        QtGuiPE_ExportTableClass->resize(1019, 420);
        frame = new QFrame(QtGuiPE_ExportTableClass);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 1001, 401));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 10, 981, 381));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 121, 16));
        QFont font;
        font.setFamily(QStringLiteral("Lucida Console"));
        font.setPointSize(11);
        font.setUnderline(true);
        label->setFont(font);
        tableWidget = new QTableWidget(frame_2);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
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
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 20, 701, 351));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->horizontalHeader()->setDefaultSectionSize(130);
        tableWidget->horizontalHeader()->setMinimumSectionSize(130);
        tableWidget->verticalHeader()->setMinimumSectionSize(30);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(720, 50, 81, 16));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(720, 80, 81, 20));
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(770, 110, 71, 20));
        Characteristics = new QLineEdit(frame_2);
        Characteristics->setObjectName(QStringLiteral("Characteristics"));
        Characteristics->setGeometry(QRect(870, 50, 101, 20));
        Characteristics->setReadOnly(true);
        TimeDateStamp = new QLineEdit(frame_2);
        TimeDateStamp->setObjectName(QStringLiteral("TimeDateStamp"));
        TimeDateStamp->setGeometry(QRect(870, 80, 101, 20));
        TimeDateStamp->setReadOnly(true);
        MajorVersion = new QLineEdit(frame_2);
        MajorVersion->setObjectName(QStringLiteral("MajorVersion"));
        MajorVersion->setGeometry(QRect(880, 110, 51, 20));
        MajorVersion->setReadOnly(true);
        MinorVersion = new QLineEdit(frame_2);
        MinorVersion->setObjectName(QStringLiteral("MinorVersion"));
        MinorVersion->setGeometry(QRect(880, 140, 51, 20));
        MinorVersion->setReadOnly(true);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(770, 140, 71, 21));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(720, 230, 131, 20));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(720, 260, 121, 20));
        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(720, 290, 131, 20));
        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(720, 320, 121, 20));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(720, 350, 151, 20));
        NumberOfFunctions = new QLineEdit(frame_2);
        NumberOfFunctions->setObjectName(QStringLiteral("NumberOfFunctions"));
        NumberOfFunctions->setGeometry(QRect(870, 230, 101, 20));
        NumberOfFunctions->setReadOnly(true);
        NumberOfNames = new QLineEdit(frame_2);
        NumberOfNames->setObjectName(QStringLiteral("NumberOfNames"));
        NumberOfNames->setGeometry(QRect(870, 260, 101, 20));
        NumberOfNames->setReadOnly(true);
        AddressOfFunctions = new QLineEdit(frame_2);
        AddressOfFunctions->setObjectName(QStringLiteral("AddressOfFunctions"));
        AddressOfFunctions->setGeometry(QRect(870, 290, 101, 20));
        AddressOfFunctions->setReadOnly(true);
        AddressOfNames = new QLineEdit(frame_2);
        AddressOfNames->setObjectName(QStringLiteral("AddressOfNames"));
        AddressOfNames->setGeometry(QRect(870, 320, 101, 20));
        AddressOfNames->setReadOnly(true);
        AddressOfNameOrdinals = new QLineEdit(frame_2);
        AddressOfNameOrdinals->setObjectName(QStringLiteral("AddressOfNameOrdinals"));
        AddressOfNameOrdinals->setGeometry(QRect(870, 350, 101, 20));
        AddressOfNameOrdinals->setReadOnly(true);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(720, 170, 71, 20));
        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(720, 200, 47, 20));
        Name = new QLineEdit(frame_2);
        Name->setObjectName(QStringLiteral("Name"));
        Name->setGeometry(QRect(870, 170, 101, 20));
        Name->setReadOnly(true);
        Base = new QLineEdit(frame_2);
        Base->setObjectName(QStringLiteral("Base"));
        Base->setGeometry(QRect(870, 200, 101, 20));
        Base->setReadOnly(true);
        DLLName = new QLineEdit(frame_2);
        DLLName->setObjectName(QStringLiteral("DLLName"));
        DLLName->setGeometry(QRect(870, 20, 101, 20));
        DLLName->setReadOnly(true);
        label_13 = new QLabel(frame_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(720, 20, 51, 20));

        retranslateUi(QtGuiPE_ExportTableClass);

        QMetaObject::connectSlotsByName(QtGuiPE_ExportTableClass);
    } // setupUi

    void retranslateUi(QWidget *QtGuiPE_ExportTableClass)
    {
        QtGuiPE_ExportTableClass->setWindowTitle(QApplication::translate("QtGuiPE_ExportTableClass", "QtGuiPE_ExportTable", Q_NULLPTR));
        label->setText(QApplication::translate("QtGuiPE_ExportTableClass", "EXPORT TABLE", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Ordinal", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QtGuiPE_ExportTableClass", "RVA", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QtGuiPE_ExportTableClass", "RVA Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("QtGuiPE_ExportTableClass", "RAW", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Characteristics", Q_NULLPTR));
        label_3->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Time Date Stamp", Q_NULLPTR));
        label_4->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Major Version", Q_NULLPTR));
        label_5->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Minor Version", Q_NULLPTR));
        label_6->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Number of Functions", Q_NULLPTR));
        label_7->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Number of Names", Q_NULLPTR));
        label_8->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Address of Functions(RVA)", Q_NULLPTR));
        label_9->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Address of Names(RVA)", Q_NULLPTR));
        label_10->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Address of Name Ordinal(RVA)", Q_NULLPTR));
        label_11->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Name(RVA)", Q_NULLPTR));
        label_12->setText(QApplication::translate("QtGuiPE_ExportTableClass", "Base", Q_NULLPTR));
        label_13->setText(QApplication::translate("QtGuiPE_ExportTableClass", "DLL Name", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGuiPE_ExportTableClass: public Ui_QtGuiPE_ExportTableClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIPE_EXPORTTABLE_H
