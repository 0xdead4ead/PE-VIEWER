#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiPE.h"
#include "PE_FILE1.h"
#include "PE_FILE1_EXCEPTION.h"
#include <qvector.h>
#include "QtGuiPE_DataDirectory.h"
#include "QtGuiPE_Sections.h"
#include "QtGuiPE_Characteristics.h"
#include "QtGuiPE_DLLCharacteristics.h"

class QtGuiPE : public QMainWindow
{
	Q_OBJECT

public:

	QtGuiPE(QWidget *parent = Q_NULLPTR);
	void fill_fields();
	bool ReadPE(const QString& pathfile);
private:


	QtGuiPE_DataDirectory data_directory;
	QtGuiPE_Sections sections;
	QtGuiPE_Characteristics characteristics_fh;
	QtGuiPE_DLLCharacteristics dllcharacteristics;
	
	
	Ui::QtGuiPEClass ui;
	//PE_FILE* file;
	



	
protected:
	void closeEvent(QCloseEvent *event) override;

private Q_SLOTS:
    void open_file_slot();
	void data_directory_slot();
	void sections_slot();
	void characteristics_slot();
	void dllcharacteristics_slot();
	
	
	void quit();
};
