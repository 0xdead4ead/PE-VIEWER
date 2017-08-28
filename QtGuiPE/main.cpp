#include "QtGuiPE.h"
#include <QtWidgets/QApplication>
#include <qfiledialog.h>
#include <qtextstream.h>
#include <qdebug.h>
void message_to_file(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
	//???
}

TCHAR ErrorBuffer[PE_FILE_MAXCHAR_ERROR];
PE_FILE file;


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	//qInstallMessageHandler(message_to_file);
	QtGuiPE w;
	QString pathfile = QFileDialog::getOpenFileName(nullptr,"OPEN FILE", "", "COFF FORMAT OBJECTS (*.exe *.dll *.ocx *.cpl)");
	
	if (!pathfile.isEmpty()) {
		if (w.ReadPE(pathfile)) {
			w.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
			w.setWindowTitle("QtGuiPE " + pathfile);

			w.show();
			return a.exec();
		}
	}

	//__try {
	//	w.ReadPE(pathfile);

	//		////
	//	//w.file.read(pathfile.toStdWString().c_str());
	//}
	//__except (PE_FILE_Exception(GetExceptionCode(), GetExceptionInformation(),ErrorBuffer)) {
	//	//messageBox
	//}
	
		
	
	
	/*if (!w.open_file(fileName_DATA))
	{
		w.setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
		w.setWindowTitle("QtGuiPE " + fileName_DATA);
		
		w.show();
	}*/
	/*else {
		return a.exec();
	}*/
	return EXIT_SUCCESS;
}
