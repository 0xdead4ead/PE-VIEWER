#include "PE_FILE1.h"
#include "PE_FILE1_EXCEPTION.h"
#include <qdebug.h>


DWORD PE_FILE_Exception(DWORD dwExceptionCodeReceived,
	LPEXCEPTION_POINTERS lpExceptionInfo, LPTSTR szBuffer, PE_FILE* file)
{
	CloseHandle(file->hFile);
	LPTSTR error;
	switch (dwExceptionCodeReceived) {
	case PE_FILE_INVALID_DOS_HEADER: {
		error = _T("Code: %08X, trapped at %08X:%08X\nPE_FILE_INVALID_DOS_HEADER!!!");
		file->_STATE = PE_FILE_INVALID_DOS_HEADER;
		break;
	}
	case PE_FILE_INVALID_PE_HEADER: {
		error = _T("Code: %08X, trapped at %08X:%08X\nPE_FILE_INVALID_PE_HEADER!!!");
		file->_STATE = PE_FILE_INVALID_PE_HEADER;
		break;
	}
	case PE_FILE_BAD_READ: {
		error = _T("Code: %08X, trapped at %08X:%08X\nPE_FILE_BAD_READ!!!");
		file->_STATE = PE_FILE_BAD_READ;
		break;
	}
	case PE_FILE_BAD_WRITE: {
		error = _T("Code: %08X, trapped at %08X:%08X\nPE_FILE_BAD_WRITE!!!"); 
		file->_STATE = PE_FILE_BAD_READ;
		break;
	}
	case PE_FILE_NOT_OPEN: {
		error = _T("Code: %08X, trapped at %08X:%08X\nPE_FILE_NOT_OPEN!!!");
		file->_STATE = PE_FILE_NOT_OPEN;
		break;
	}
	}

	wsprintf(szBuffer, error,
		lpExceptionInfo->ExceptionRecord->ExceptionCode, lpExceptionInfo->ContextRecord->SegCs, lpExceptionInfo->ContextRecord->Rip);
	PE_FILE_WriteLog(szBuffer);
	return EXCEPTION_EXECUTE_HANDLER;
}

void PE_FILE_WriteLog(LPCTSTR str) {
	qDebug() << QString::fromWCharArray(str);
}