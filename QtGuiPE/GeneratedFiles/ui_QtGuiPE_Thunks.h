/********************************************************************************
** Form generated from reading UI file 'QtGuiPE_Thunks.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIPE_THUNKS_H
#define UI_QTGUIPE_THUNKS_H

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

class Ui_QtGuiPE_ThunksClass
{
public:
    QFrame *frame;
    QFrame *frame_2;
    QLabel *label;
    QTableWidget *tableWidget;

    void setupUi(QWidget *QtGuiPE_ThunksClass)
    {
        if (QtGuiPE_ThunksClass->objectName().isEmpty())
            QtGuiPE_ThunksClass->setObjectName(QStringLiteral("QtGuiPE_ThunksClass"));
        QtGuiPE_ThunksClass->resize(945, 311);
        frame = new QFrame(QtGuiPE_ThunksClass);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 921, 291));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 10, 901, 271));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 81, 16));
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
        tableWidget->setGeometry(QRect(10, 20, 881, 241));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->horizontalHeader()->setDefaultSectionSize(170);
        tableWidget->horizontalHeader()->setMinimumSectionSize(170);
        tableWidget->verticalHeader()->setMinimumSectionSize(30);

        retranslateUi(QtGuiPE_ThunksClass);

        QMetaObject::connectSlotsByName(QtGuiPE_ThunksClass);
    } // setupUi

    void retranslateUi(QWidget *QtGuiPE_ThunksClass)
    {
        QtGuiPE_ThunksClass->setWindowTitle(QApplication::translate("QtGuiPE_ThunksClass", "QtGuiPE_Thunks", Q_NULLPTR));
        label->setText(QApplication::translate("QtGuiPE_ThunksClass", "THUNKS", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QtGuiPE_ThunksClass", "API Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QtGuiPE_ThunksClass", "Thunk Value", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QtGuiPE_ThunksClass", "Thunk RVA", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QtGuiPE_ThunksClass", "Thunk RAW", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("QtGuiPE_ThunksClass", "Hint", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGuiPE_ThunksClass: public Ui_QtGuiPE_ThunksClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIPE_THUNKS_H
