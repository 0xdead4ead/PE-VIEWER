/********************************************************************************
** Form generated from reading UI file 'QtGuiPE_Resource.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIPE_RESOURCE_H
#define UI_QTGUIPE_RESOURCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiPE_ResourceClass
{
public:
    QFrame *frame;
    QFrame *frame_2;
    QLabel *label;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *QtGuiPE_ResourceClass)
    {
        if (QtGuiPE_ResourceClass->objectName().isEmpty())
            QtGuiPE_ResourceClass->setObjectName(QStringLiteral("QtGuiPE_ResourceClass"));
        QtGuiPE_ResourceClass->resize(853, 400);
        frame = new QFrame(QtGuiPE_ResourceClass);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(9, 9, 831, 381));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 10, 811, 361));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 131, 16));
        QFont font;
        font.setFamily(QStringLiteral("Lucida Console"));
        font.setPointSize(11);
        font.setUnderline(true);
        label->setFont(font);
        label->setFrameShadow(QFrame::Raised);
        treeWidget = new QTreeWidget(frame_2);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(10, 20, 791, 331));
        treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeWidget->setHeaderHidden(false);
        treeWidget->header()->setVisible(true);
        treeWidget->header()->setDefaultSectionSize(135);

        retranslateUi(QtGuiPE_ResourceClass);

        QMetaObject::connectSlotsByName(QtGuiPE_ResourceClass);
    } // setupUi

    void retranslateUi(QWidget *QtGuiPE_ResourceClass)
    {
        QtGuiPE_ResourceClass->setWindowTitle(QApplication::translate("QtGuiPE_ResourceClass", "QtGuiPE_Resource", Q_NULLPTR));
        label->setText(QApplication::translate("QtGuiPE_ResourceClass", "RESOURCE TABLE", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(5, QApplication::translate("QtGuiPE_ResourceClass", "SUBLANG", Q_NULLPTR));
        ___qtreewidgetitem->setText(4, QApplication::translate("QtGuiPE_ResourceClass", "LANG", Q_NULLPTR));
        ___qtreewidgetitem->setText(3, QApplication::translate("QtGuiPE_ResourceClass", "Size", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("QtGuiPE_ResourceClass", "RAW", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("QtGuiPE_ResourceClass", "RVA", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("QtGuiPE_ResourceClass", "Type\\Name Resource", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGuiPE_ResourceClass: public Ui_QtGuiPE_ResourceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIPE_RESOURCE_H
