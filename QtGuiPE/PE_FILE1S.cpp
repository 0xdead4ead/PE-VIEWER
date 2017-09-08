#include "PE_FILE1.h"
#include "PE_FILE1_EXCEPTION.h"
#include <qdebug.h>







WORD defSection(vector<IMAGE_SECTION_HEADER>* sections, DWORD rva, DWORD Alignment)
{
	if (!sections) return 0xFFFF;
	for (WORD i = 0; i < sections->size(); ++i)
	{
		DWORD start = (*sections)[i].VirtualAddress;
		DWORD end = start + ALIGN_UP((*sections)[i].Misc.VirtualSize, Alignment);

		if (rva >= start && rva < end)
			return i;
	}
	return 0xFFFF;
}

DWORD rvaToOff(vector<IMAGE_SECTION_HEADER>* sections, DWORD rva,DWORD Alignment) {
	WORD indexSection = defSection(sections,rva,Alignment);
	if (indexSection != USHRT_MAX)
		return rva - (*sections)[indexSection].VirtualAddress + (*sections)[indexSection].PointerToRawData;
	else
		return 0xFFFFFFFF;
}

BOOL read_char_cs_forcheck32bitPE(LONG e_lfanew, LPWORD CHAR_CS, HANDLE hFile) {
		DWORD tmpReadBytes;
		LONG offset = e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) - sizeof(WORD);
		if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) != 0xFFFFFFFF) {
			LockFile(hFile, offset, 0, sizeof(WORD), 0);
			BOOL result = ReadFile(hFile, CHAR_CS, sizeof(WORD), &tmpReadBytes, NULL);
			UnlockFile(hFile, offset, 0, sizeof(WORD), 0);
			return result;
		}
		return FALSE;
}

BOOL read_dos_header(PIMAGE_DOS_HEADER dos, HANDLE hFile) {
		DWORD tmpReadBytes;
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) != 0xFFFFFFFF) {
			LockFile(hFile, 0, 0, sizeof(IMAGE_DOS_HEADER), 0);
			BOOL result = ReadFile(hFile, dos, sizeof(IMAGE_DOS_HEADER), &tmpReadBytes, NULL);
			UnlockFile(hFile, 0, 0, sizeof(IMAGE_DOS_HEADER), 0);
			return result;
		}
		return FALSE;
}

BOOL read_signature(LONG e_lfanew,LPDWORD sig, HANDLE hFile) {
		DWORD tmpReadBytes;
		if (SetFilePointer(hFile, e_lfanew, NULL, FILE_BEGIN) != 0xFFFFFFFF) {
			LockFile(hFile, e_lfanew, 0, sizeof(DWORD), 0);
			BOOL result = ReadFile(hFile, sig, sizeof(DWORD), &tmpReadBytes, NULL);
			UnlockFile(hFile, e_lfanew, 0, sizeof(DWORD), 0);
			return result;
		}
		return FALSE;
}

BOOL read_file_header(LONG e_lfanew, PIMAGE_FILE_HEADER fh, HANDLE hFile) {
		DWORD tmpReadBytes;
		if (SetFilePointer(hFile, e_lfanew + sizeof(DWORD), NULL, FILE_BEGIN) != 0xFFFFFFFF) {
			LockFile(hFile, e_lfanew + sizeof(DWORD), 0, sizeof(IMAGE_FILE_HEADER), 0);
			BOOL result = ReadFile(hFile, fh, sizeof(IMAGE_FILE_HEADER), &tmpReadBytes, NULL);
			UnlockFile(hFile, e_lfanew + sizeof(DWORD), 0, sizeof(IMAGE_FILE_HEADER), 0);
			return result;
		}
		return FALSE;
}


BOOL read_optional_header32(LONG e_lfanew, PIMAGE_OPTIONAL_HEADER32 op32, HANDLE hFile) {
		DWORD tmpReadBytes;
		if (SetFilePointer(hFile, e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER), NULL, FILE_BEGIN) != 0xFFFFFFFF) {
			LockFile(hFile, e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER), 0, sizeof(IMAGE_OPTIONAL_HEADER32), 0);
			BOOL result = ReadFile(hFile, op32, sizeof(IMAGE_OPTIONAL_HEADER32), &tmpReadBytes, NULL);
			UnlockFile(hFile, e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER), 0, sizeof(IMAGE_OPTIONAL_HEADER32), 0);
			return result;
		}
		return FALSE;
}
BOOL read_optional_header64(LONG e_lfanew, PIMAGE_OPTIONAL_HEADER64 op64, HANDLE hFile) {
		DWORD tmpReadBytes;
		if (SetFilePointer(hFile, e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER), NULL, FILE_BEGIN) != 0xFFFFFFFF) {
			LockFile(hFile, e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER), 0, sizeof(IMAGE_OPTIONAL_HEADER64), 0);
			BOOL result = ReadFile(hFile, op64, sizeof(IMAGE_OPTIONAL_HEADER64), &tmpReadBytes, NULL);
			UnlockFile(hFile, e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER), 0, sizeof(IMAGE_OPTIONAL_HEADER64), 0);
			return result;
		}
		return FALSE;
}


BOOL read_section_headers(LONG Distance, vector<IMAGE_SECTION_HEADER>* sections,WORD NumberOfSections, HANDLE hFile) {
		sections->clear();
		//sections->reserve(NumberOfSections);
		//TCHAR buf[32] = _T("Read Section ");
		//TCHAR bufNumSec[10];
		DWORD tmpReadBytes;
		if (SetFilePointer(hFile, Distance, NULL, FILE_BEGIN) != 0xFFFFFFFF) {
			LockFile(hFile, Distance, 0, sizeof(IMAGE_SECTION_HEADER)*NumberOfSections, 0);
			BOOL result;
			for (WORD i = 0; i < NumberOfSections; i++)
			{
				sections->push_back(IMAGE_SECTION_HEADER());
				//PE_FILE_WriteLog(_tcscat(buf, _ultot(i + 1, bufNumSec, 10)));
				result = ReadFile(hFile, &(sections->back()), sizeof(IMAGE_SECTION_HEADER), &tmpReadBytes, NULL);
				if (!result) return FALSE;
			}
			UnlockFile(hFile, Distance, 0, sizeof(IMAGE_SECTION_HEADER)*NumberOfSections, 0);
			return TRUE;
		}
	return FALSE;
}


BOOL read_export_table(DWORD AlignmentSection, vector<IMAGE_SECTION_HEADER>* sections, DWORD RVAoffset, PE_FILE_EXPORT_TABLE* expt, HANDLE hFile) {
#define MAX_CHAR_IN_STRING 256


	DWORD offset;
	DWORD tmpReadBytes;

	expt->export_header = unique_ptr<IMAGE_EXPORT_DIRECTORY>(new IMAGE_EXPORT_DIRECTORY());
	if ((offset = rvaToOff(sections, RVAoffset, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
	if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
	LockFile(hFile, offset, 0, sizeof(IMAGE_EXPORT_DIRECTORY), 0);
	if (!ReadFile(hFile, &*(expt->export_header), sizeof(IMAGE_EXPORT_DIRECTORY), &tmpReadBytes, NULL)) return FALSE;
	UnlockFile(hFile, offset, 0, sizeof(IMAGE_EXPORT_DIRECTORY), 0);


	expt->export_name = unique_ptr<string>(new string());
	expt->export_name->reserve(MAX_CHAR_IN_STRING);

	if ((offset = rvaToOff(sections, expt->export_header->Name, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
	if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
	LockFile(hFile, offset, 0, MAX_CHAR_IN_STRING, 0);
	if (!ReadFile(hFile,(char*) expt->export_name->c_str(), MAX_CHAR_IN_STRING, &tmpReadBytes, NULL)) return FALSE;
	UnlockFile(hFile, offset, 0, MAX_CHAR_IN_STRING, 0);


	expt->export_rva = unique_ptr<vector<DWORD> >(new vector<DWORD>(expt->export_header->NumberOfFunctions));
	expt->export_ordinals = unique_ptr<vector<WORD> >(new vector<WORD>(expt->export_header->NumberOfFunctions));
	expt->export_adress_names_rva = unique_ptr<vector<DWORD> >(new vector<DWORD>(expt->export_header->NumberOfFunctions));
	expt->export_names = unique_ptr<vector<string> >(new vector<string>(expt->export_header->NumberOfFunctions));

	if (expt->export_header->AddressOfFunctions && expt->export_header->AddressOfNames) {
		if ((offset = rvaToOff(sections, expt->export_header->AddressOfFunctions, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
		if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
		LockFile(hFile, offset, 0, sizeof(DWORD) * expt->export_header->NumberOfFunctions, 0);
		for (DWORD i = 0; i < expt->export_header->NumberOfFunctions; i++)
			if (!ReadFile(hFile, &(*expt->export_rva)[i], sizeof(DWORD), &tmpReadBytes, NULL)) return FALSE;
		UnlockFile(hFile, offset, 0, sizeof(DWORD) * expt->export_header->NumberOfFunctions, 0);

		if ((offset = rvaToOff(sections, expt->export_header->AddressOfNames, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
		if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
		LockFile(hFile, offset, 0, sizeof(DWORD) * expt->export_header->NumberOfFunctions, 0);
		for (DWORD i = 0; i < expt->export_header->NumberOfFunctions; i++)
			if (!ReadFile(hFile, &(*expt->export_adress_names_rva)[i], sizeof(DWORD), &tmpReadBytes, NULL)) return FALSE;
		UnlockFile(hFile, offset, 0, sizeof(DWORD) * expt->export_header->NumberOfFunctions, 0);


		for (DWORD i = 0; i < expt->export_header->NumberOfFunctions; i++) {
			(*expt->export_names)[i].reserve(MAX_CHAR_IN_STRING);
			if ((offset = rvaToOff(sections,  (*expt->export_adress_names_rva)[i], AlignmentSection)) == 0xFFFFFFFF) return FALSE;
			if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
			LockFile(hFile, offset, 0, MAX_CHAR_IN_STRING, 0);
			if (!ReadFile(hFile, (char*)(*expt->export_names)[i].c_str(), MAX_CHAR_IN_STRING, &tmpReadBytes, NULL)) return FALSE;
			UnlockFile(hFile, offset, 0, MAX_CHAR_IN_STRING, 0);
		}

		if ((offset = rvaToOff(sections, expt->export_header->AddressOfNameOrdinals, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
		if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
		LockFile(hFile, offset, 0, sizeof(WORD) * expt->export_header->NumberOfFunctions, 0);
		for (DWORD i = 0; i < expt->export_header->NumberOfFunctions; i++)
			if (!ReadFile(hFile, &(*expt->export_ordinals)[i], sizeof(WORD), &tmpReadBytes, NULL)) return FALSE;
		UnlockFile(hFile, offset, 0, sizeof(WORD) * expt->export_header->NumberOfFunctions, 0);
	}
	return TRUE;
}


BOOL read_import_table(BOOL pe32,DWORD AlignmentSection, vector<IMAGE_SECTION_HEADER>* sections, DWORD RVAoffset, PE_FILE_IMPORT_TABLE* impt, HANDLE hFile) {
#define MAX_CHAR_IN_STRING 256

	if (!hFile) return FALSE;
	DWORD offset;
	DWORD tmpReadBytes;

	if ((offset = rvaToOff(sections, RVAoffset, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
	
	DWORD start_offset = offset;
	if (SetFilePointer(hFile, start_offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
	uint ix = 0;
	while (1) {
		impt->import_headers.emplace_back();
		LockFile(hFile, start_offset + sizeof(IMAGE_IMPORT_DESCRIPTOR) * ix, 0, sizeof(IMAGE_IMPORT_DESCRIPTOR), 0);
		if (!ReadFile(hFile, &(impt->import_headers.back()), sizeof(IMAGE_IMPORT_DESCRIPTOR), &tmpReadBytes, NULL)) return FALSE;
		UnlockFile(hFile, start_offset + sizeof(IMAGE_IMPORT_DESCRIPTOR) * ix, 0, sizeof(IMAGE_IMPORT_DESCRIPTOR), 0);
		ix++;
		if (impt->import_headers.back().OriginalFirstThunk == 0) {
			impt->import_headers.pop_back(); break;
		}
	}

	impt->dll_names_of_import_desc = unique_ptr<vector<string> >(new vector<string>(impt->import_headers.size()));
	if (pe32)
		impt->image_thunk32 = unique_ptr<vector<vector<IMAGE_THUNK_DATA32> > >(new vector<vector<IMAGE_THUNK_DATA32> >(impt->import_headers.size()));
	else
		impt->image_thunk64 = unique_ptr<vector<vector<IMAGE_THUNK_DATA64> > >(new vector<vector<IMAGE_THUNK_DATA64> >(impt->import_headers.size()));
	
	impt->image_import_names = unique_ptr<vector<vector<IMAGE_IMPORT_BY_NAME> > >(new vector<vector<IMAGE_IMPORT_BY_NAME> >(impt->import_headers.size()));

	for (int i = 0; i < impt->import_headers.size(); i++) {
		(*impt->dll_names_of_import_desc)[i].reserve(MAX_CHAR_IN_STRING);
		if ((offset = rvaToOff(sections, impt->import_headers[i].Name, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
		if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
		LockFile(hFile, offset, 0, MAX_CHAR_IN_STRING, 0);
		if (!ReadFile(hFile, (char*)(*impt->dll_names_of_import_desc)[i].c_str(), MAX_CHAR_IN_STRING, &tmpReadBytes, NULL)) return FALSE;
		UnlockFile(hFile, offset, 0, MAX_CHAR_IN_STRING, 0);

	}

	for (int i = 0; i < impt->import_headers.size(); i++) {
		if ((offset = rvaToOff(sections, impt->import_headers[i].FirstThunk, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
		DWORD start_offset = offset;
		if (SetFilePointer(hFile, start_offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
		uint ix = 0;
		while (1) {
			if (pe32)
			{
				(*impt->image_thunk32)[i].push_back(IMAGE_THUNK_DATA32());
				LockFile(hFile, start_offset + sizeof(IMAGE_THUNK_DATA32) * ix, 0, sizeof(IMAGE_THUNK_DATA32), 0);
				if (!ReadFile(hFile, &(*impt->image_thunk32)[i].back(), sizeof(IMAGE_THUNK_DATA32), &tmpReadBytes, NULL)) return FALSE;
				UnlockFile(hFile, start_offset + sizeof(IMAGE_THUNK_DATA32) * ix, 0, sizeof(IMAGE_THUNK_DATA32), 0);
				ix++;
				if ((*impt->image_thunk32)[i].back().u1.AddressOfData == 0) {
					(*impt->image_thunk32)[i].pop_back();
					break;
				}
			}
			else
			{
				(*impt->image_thunk64)[i].push_back(IMAGE_THUNK_DATA64());
				LockFile(hFile, start_offset + sizeof(IMAGE_THUNK_DATA64) * ix, 0, sizeof(IMAGE_THUNK_DATA64), 0);
				if (!ReadFile(hFile, &(*impt->image_thunk64)[i].back(), sizeof(IMAGE_THUNK_DATA64), &tmpReadBytes, NULL)) return FALSE;
				UnlockFile(hFile, start_offset + sizeof(IMAGE_THUNK_DATA64) * ix, 0, sizeof(IMAGE_THUNK_DATA64), 0);
				ix++;
				if ((*impt->image_thunk64)[i].back().u1.AddressOfData == 0) {
					(*impt->image_thunk64)[i].pop_back();
					break;
				}
			}
		}
	}
	
	
	impt->func_names_of_import_desc = unique_ptr<vector<vector<string> > >(new vector<vector<string> >(impt->import_headers.size()));

	for (int i = 0; i < impt->import_headers.size(); i++) {

		if (pe32) {
			(*impt->func_names_of_import_desc)[i] = vector<string>((*impt->image_thunk32)[i].size());
			int ii = 0;
			for (vector<IMAGE_THUNK_DATA32>::iterator ptd32 = (*impt->image_thunk32)[i].begin(); ptd32 != (*impt->image_thunk32)[i].end();ptd32++)
			{
				if (ptd32->u1.AddressOfData & 0x80000000) {
					(*impt->func_names_of_import_desc)[i][ii].reserve(MAX_CHAR_IN_STRING);
					string buf = "ORDINAL ";
					char bufT2[32];
					buf += ultoa(ptd32->u1.AddressOfData & 0x7FFFFFFF, bufT2, 16);
					lstrcpyA((char*)(*impt->func_names_of_import_desc)[i][ii].c_str(), buf.c_str());
					(*impt->image_import_names)[i].push_back(IMAGE_IMPORT_BY_NAME());
					(*impt->image_import_names)[i].back().Hint = 0xFFFF;
					ii++;
				}
				else {
					if ((offset = rvaToOff(sections, ptd32->u1.AddressOfData, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
					if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
					(*impt->image_import_names)[i].push_back(IMAGE_IMPORT_BY_NAME());
					LockFile(hFile, offset, 0, sizeof(IMAGE_IMPORT_BY_NAME), 0);
					if (!ReadFile(hFile, &(*impt->image_import_names)[i].back(), sizeof(IMAGE_IMPORT_BY_NAME), &tmpReadBytes, NULL)) return FALSE;
					UnlockFile(hFile, offset, 0, sizeof(IMAGE_IMPORT_BY_NAME), 0);

					(*impt->func_names_of_import_desc)[i][ii].reserve(MAX_CHAR_IN_STRING);
					if ((offset = rvaToOff(sections, ptd32->u1.AddressOfData + sizeof(WORD), AlignmentSection)) == 0xFFFFFFFF) return FALSE;
					if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
					LockFile(hFile, offset, 0, MAX_CHAR_IN_STRING, 0);
					if (!ReadFile(hFile,(char*) (*impt->func_names_of_import_desc)[i][ii].c_str(), MAX_CHAR_IN_STRING, &tmpReadBytes, NULL)) return FALSE;
					UnlockFile(hFile, offset, 0, MAX_CHAR_IN_STRING, 0);
					ii++;
				}
			}
		}
		else 
		{
			(*impt->func_names_of_import_desc)[i] = vector<string>((*impt->image_thunk64)[i].size());
			int ii = 0;
			for (vector<IMAGE_THUNK_DATA64>::iterator ptd64 = (*impt->image_thunk64)[i].begin(); 
				ptd64 != (*impt->image_thunk64)[i].end();
				 ptd64++)
			{
				if (ptd64->u1.AddressOfData & 0x8000000000000000) {
					(*impt->func_names_of_import_desc)[i][ii].reserve(MAX_CHAR_IN_STRING);
					string buf = "ORDINAL "; 
					char bufT2[32];
					buf += _ui64toa(ptd64->u1.AddressOfData & 0x7FFFFFFFFFFFFFFF, bufT2, 16);
					lstrcpyA((char*)(*impt->func_names_of_import_desc)[i][ii].c_str(), buf.c_str());
					(*impt->image_import_names)[i].push_back(IMAGE_IMPORT_BY_NAME());
					(*impt->image_import_names)[i].back().Hint = 0xFFFF;
					ii++;
				}
				else { //image_import_by_name
					if ((offset = rvaToOff(sections, ptd64->u1.AddressOfData, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
					if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
					(*impt->image_import_names)[i].push_back(IMAGE_IMPORT_BY_NAME());
					LockFile(hFile, offset, 0, sizeof(IMAGE_IMPORT_BY_NAME), 0);
					if (!ReadFile(hFile, &(*impt->image_import_names)[i].back(), sizeof(IMAGE_IMPORT_BY_NAME), &tmpReadBytes, NULL)) return FALSE;
					UnlockFile(hFile, offset, 0, sizeof(IMAGE_IMPORT_BY_NAME), 0);

					(*impt->func_names_of_import_desc)[i][ii].reserve(MAX_CHAR_IN_STRING);
					if ((offset = rvaToOff(sections, ptd64->u1.AddressOfData + sizeof(WORD), AlignmentSection)) == 0xFFFFFFFF) return FALSE;
					if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
					LockFile(hFile, offset, 0, MAX_CHAR_IN_STRING, 0);
					if (!ReadFile(hFile, (char*)(*impt->func_names_of_import_desc)[i][ii].c_str(), MAX_CHAR_IN_STRING, &tmpReadBytes, NULL)) return FALSE;
					UnlockFile(hFile, offset, 0, MAX_CHAR_IN_STRING, 0);
					ii++;
				}
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK ListResourceLanguages(HMODULE hModule, LPCTSTR lpszType, LPCTSTR lpszName, WORD wIDLanguage, LONG_PTR lParam) {
	PE_FILE_RESOURCE_TYPE *rs = (PE_FILE_RESOURCE_TYPE*)lParam;
	PE_FILE_RESOURCE_NAME NewName;
	NewName.lpszName = lpszName;
	HRSRC hrsrc = FindResourceEx(hModule, lpszType, lpszName, wIDLanguage);
	NewName.RVAData = hrsrc->unused;

	//if (HGLOBAL hmem = LoadResource(hModule, hrsrc))
		//NewName.VAData = LockResource(hmem); else NewName.VAData = NULL;
	NewName.ResourceSize = SizeofResource(hModule, hrsrc);

	if ((ULONG_PTR)lpszName & 0xFFFFFFFFFFFF0000)
	{
		NewName.szResName = lpszName;
	}
	NewName.wIDLanguage = wIDLanguage;
	rs->names.push_back(NewName);
	return TRUE;
}



BOOL CALLBACK ListResourceNames(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam) {
	return EnumResourceLanguages(hModule, lpType, lpName, ListResourceLanguages, lParam);
}

BOOL CALLBACK ListResourceTypes(HMODULE hModule, LPTSTR lpszType, LONG_PTR lParam) {
	PE_FILE_RESOURCE_TYPE rs;
	rs.lpszType = lpszType;
	if ((ULONG_PTR)lpszType & 0xFFFFFFFFFFFF0000) //program is 64 bit only
		rs.szResType = lpszType;

	BOOL res = EnumResourceNames(hModule, lpszType, ListResourceNames, (LONG_PTR)&rs);
	((vector<PE_FILE_RESOURCE_TYPE>*)lParam)->push_back(rs);
	return res;
}

BOOL getListResource(vector<PE_FILE_RESOURCE_TYPE>* res, LPCTSTR filename) {
	HMODULE hModule;
	if (hModule = LoadLibraryEx(filename, NULL, LOAD_LIBRARY_AS_DATAFILE))
	{
		BOOL result = EnumResourceTypes(hModule, ListResourceTypes,
			(LONG_PTR)res);

		FreeLibrary(hModule);
		return result;
	}
	return FALSE;
}

BOOL read_except_table_mips32(DWORD AlignmentSection, vector<IMAGE_SECTION_HEADER>* sections,DWORD RVAoffset, vector<PE_FILE_EXCEPTION_ENTRY_MIPS32>* except_table, HANDLE hFile) {
	if (!hFile) return FALSE;
	DWORD offset;
	DWORD tmpReadBytes;

	if ((offset = rvaToOff(sections, RVAoffset, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
	DWORD start_offset = offset;
	if (SetFilePointer(hFile, start_offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
	UINT ix = 0;
	while (1) {
		except_table->push_back(PE_FILE_EXCEPTION_ENTRY_MIPS32());
		LockFile(hFile, start_offset + sizeof(PE_FILE_EXCEPTION_ENTRY_MIPS32) * ix, 0, sizeof(PE_FILE_EXCEPTION_ENTRY_MIPS32), 0);
		if (!ReadFile(hFile, &(except_table->back()), sizeof(PE_FILE_EXCEPTION_ENTRY_MIPS32), &tmpReadBytes, NULL)) return FALSE;
		UnlockFile(hFile, start_offset + sizeof(PE_FILE_EXCEPTION_ENTRY_MIPS32) * ix, 0, sizeof(PE_FILE_EXCEPTION_ENTRY_MIPS32), 0);
		if (except_table->back().BeginAddress == 0) {
			except_table->pop_back(); break;
		}
		ix++;
	}
	return TRUE;
}
BOOL read_except_table_x64(DWORD AlignmentSection, vector<IMAGE_SECTION_HEADER>* sections,DWORD RVAoffset, vector<PE_FILE_EXCEPTION_ENTRY_X64>* except_table, HANDLE hFile) {
	if (!hFile) return FALSE;
	DWORD offset;
	DWORD tmpReadBytes;

	if ((offset = rvaToOff(sections, RVAoffset, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
	DWORD start_offset = offset;
	if (SetFilePointer(hFile, start_offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
	UINT ix = 0;
	while (1) {
		except_table->push_back(PE_FILE_EXCEPTION_ENTRY_X64());
		LockFile(hFile, start_offset + sizeof(PE_FILE_EXCEPTION_ENTRY_X64) * ix, 0, sizeof(PE_FILE_EXCEPTION_ENTRY_X64), 0);
		if (!ReadFile(hFile, &(except_table->back()), sizeof(PE_FILE_EXCEPTION_ENTRY_X64), &tmpReadBytes, NULL)) return FALSE;
		UnlockFile(hFile, start_offset + sizeof(PE_FILE_EXCEPTION_ENTRY_X64) * ix, 0, sizeof(PE_FILE_EXCEPTION_ENTRY_X64), 0);
		if (except_table->back().BeginAddress == 0) {
			except_table->pop_back(); break;
		}
		ix++;
	}
	return TRUE;
}
BOOL read_except_table_other(DWORD AlignmentSection, vector<IMAGE_SECTION_HEADER>* sections,DWORD RVAoffset, vector<PE_FILE_EXCEPTION_ENTRY_OTHER>* except_table, HANDLE hFile) {
	if (!hFile) return FALSE;
	DWORD offset;
	DWORD tmpReadBytes;

	if ((offset = rvaToOff(sections, RVAoffset, AlignmentSection)) == 0xFFFFFFFF) return FALSE;
	DWORD start_offset = offset;
	if (SetFilePointer(hFile, start_offset, NULL, FILE_BEGIN) == 0xFFFFFFFF) return FALSE;
	UINT ix = 0;
	while (1) {
		except_table->push_back(PE_FILE_EXCEPTION_ENTRY_OTHER());
		LockFile(hFile, start_offset + sizeof(PE_FILE_EXCEPTION_ENTRY_OTHER) * ix, 0, sizeof(PE_FILE_EXCEPTION_ENTRY_OTHER), 0);
		if (!ReadFile(hFile, &(except_table->back()), sizeof(PE_FILE_EXCEPTION_ENTRY_OTHER), &tmpReadBytes, NULL)) return FALSE;
		UnlockFile(hFile, start_offset + sizeof(PE_FILE_EXCEPTION_ENTRY_OTHER) * ix, 0, sizeof(PE_FILE_EXCEPTION_ENTRY_OTHER), 0);
		if (except_table->back().BeginAddress == 0) {
			except_table->pop_back(); break;
		}
		ix++;
	}
	return TRUE;
}





PE_FILE::PE_FILE() {
	_STATE = PE_FILE_NOT_INITIALIZED;
	PE32 = FALSE;
	hFile = nullptr;
}

void PE_FILE::read(LPCTSTR pathfile) {

	//https://msdn.microsoft.com/ru-ru/library/windows/desktop/ms680547(v=vs.85).aspx
	BOOL PE32_T;
	PE_FILE_WriteLog(pathfile);
	if ((hFile = CreateFile(pathfile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL)) != INVALID_HANDLE_VALUE) {
		auto dos_h = unique_ptr<IMAGE_DOS_HEADER>(new IMAGE_DOS_HEADER());
		//read dos header
		if (!read_dos_header(&(*dos_h), hFile))
			RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
		

		if (dos_h->e_magic != 0x5A4D) RaiseException(PE_FILE_INVALID_DOS_HEADER, 0, 0, NULL);

		WORD char_cs;
		if (!read_char_cs_forcheck32bitPE(dos_h->e_lfanew, &char_cs, hFile))
			RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
		else if (char_cs & IMAGE_FILE_32BIT_MACHINE) PE32_T = TRUE; else PE32_T = FALSE; //PE32 or PE32+


		auto Sig = unique_ptr<DWORD>(new DWORD());
		auto file_h = unique_ptr<IMAGE_FILE_HEADER>(new IMAGE_FILE_HEADER());
		
		if(!read_signature(dos_h->e_lfanew,&(*Sig),hFile)) 
			RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
		
		if (*Sig != 0x4550) RaiseException(PE_FILE_INVALID_PE_HEADER, 0, 0, NULL);
	


		if(!read_file_header(dos_h->e_lfanew,&(*file_h),hFile)) 
			RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
		//read optional header

		auto op_h32 = unique_ptr<IMAGE_OPTIONAL_HEADER32>(new IMAGE_OPTIONAL_HEADER32());
		auto op_h64 = unique_ptr<IMAGE_OPTIONAL_HEADER64>(new IMAGE_OPTIONAL_HEADER64());
		
		if (PE32_T) {
			if (!read_optional_header32(dos_h->e_lfanew, &*op_h32, hFile)) RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
		}
		else {
			if (!read_optional_header64(dos_h->e_lfanew, &*op_h64, hFile)) RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
		}
		//read Section headers
		

		auto sect_hs = vector<IMAGE_SECTION_HEADER>();

		if (PE32_T) {
			if (!read_section_headers(dos_h->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) + sizeof(IMAGE_OPTIONAL_HEADER32),
				&sect_hs, file_h->NumberOfSections, hFile)) RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
		}
		else {
			if (!read_section_headers(dos_h->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) + sizeof(IMAGE_OPTIONAL_HEADER64),
				&sect_hs, file_h->NumberOfSections, hFile)) RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
		}
		
		

		auto expt_t = unique_ptr<PE_FILE_EXPORT_TABLE>(new PE_FILE_EXPORT_TABLE());
		auto impt_t = unique_ptr<PE_FILE_IMPORT_TABLE>(new PE_FILE_IMPORT_TABLE());
		auto res_s = vector<PE_FILE_RESOURCE_TYPE>();
		auto except_t_mips32 = vector<PE_FILE_EXCEPTION_ENTRY_MIPS32>();
		auto except_t_x64 = vector<PE_FILE_EXCEPTION_ENTRY_X64>();
		auto except_t_other = vector<PE_FILE_EXCEPTION_ENTRY_OTHER>();



		if (PE32_T) { //PE32
			if(op_h32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress)
				//read export sector
			if(!read_export_table(op_h32->SectionAlignment, &sect_hs, op_h32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress, &*expt_t, hFile)) 
				RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);

			if(op_h32->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress)
				//read import sector
			if(!read_import_table(PE32_T, op_h32->SectionAlignment, &sect_hs, op_h32->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, &*impt_t, hFile))
				RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
                

			if (op_h32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress) {
				//read exception table
				if ((file_h->Machine == IMAGE_FILE_MACHINE_IA64) ||
					(file_h->Machine == IMAGE_FILE_MACHINE_AMD64)) {
					if (!read_except_table_x64(op_h32->SectionAlignment, &sect_hs, op_h32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress, &except_t_x64, hFile))
						RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
				}
				else if (file_h->Machine == IMAGE_FILE_MACHINE_R3000) {
					if (!read_except_table_mips32(op_h32->SectionAlignment, &sect_hs, op_h32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress, &except_t_mips32, hFile))
						RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
				}
				else {
					if (!read_except_table_other(op_h32->SectionAlignment, &sect_hs, op_h32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress, &except_t_other, hFile))
						RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
				}
			}

		}
		else { //PE32+
			if(op_h64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress)
			if (!read_export_table(op_h64->SectionAlignment, &sect_hs, op_h64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress, &*expt_t, hFile))
				RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);


			if(op_h64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress)
			if (!read_import_table(PE32_T, op_h64->SectionAlignment, &sect_hs, op_h64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, &*impt_t, hFile))
				RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);

			if (op_h64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress) {
				if ((file_h->Machine == IMAGE_FILE_MACHINE_IA64) ||
					(file_h->Machine == IMAGE_FILE_MACHINE_AMD64)) {
					if (!read_except_table_x64(op_h64->SectionAlignment, &sect_hs, op_h64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress, &except_t_x64, hFile))
						RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
				}
				else if (file_h->Machine == IMAGE_FILE_MACHINE_R3000) {
					if (!read_except_table_mips32(op_h64->SectionAlignment, &sect_hs, op_h64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress, &except_t_mips32, hFile))
						RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
				}
				else {
					if (!read_except_table_other(op_h64->SectionAlignment, &sect_hs, op_h64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress, &except_t_other, hFile))
						RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
				}
			}
		}

		

		CloseHandle(hFile);
		
		//read resource sector
		if (PE32_T) {
			if (op_h32->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress)
				if (!getListResource(&res_s, pathfile)) RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
		}
		else {
			if (op_h64->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress)
				if (!getListResource(&res_s, pathfile)) RaiseException(PE_FILE_BAD_READ, 0, 0, NULL);
		}
		/////////////////////////////////////////////////////////

		dos_header = static_cast<unique_ptr<IMAGE_DOS_HEADER>&&>(dos_h);
		Signature = static_cast<unique_ptr<DWORD>&&>(Sig);
		file_header = static_cast<unique_ptr<IMAGE_FILE_HEADER>&&>(file_h);
		op_header32 = static_cast<unique_ptr<IMAGE_OPTIONAL_HEADER32>&&>(op_h32);
		op_header64 = static_cast<unique_ptr<IMAGE_OPTIONAL_HEADER64>&&>(op_h64);
		section_headers = sect_hs;
		export_table = static_cast<unique_ptr<PE_FILE_EXPORT_TABLE>&&>(expt_t);
		import_table = static_cast<unique_ptr<PE_FILE_IMPORT_TABLE>&&>(impt_t);
		resources = res_s;
		exception_table_mips32 = except_t_mips32;
		exception_table_x64 = except_t_x64;
		exception_table_other = except_t_other;
		_STATE = PE_FILE_NO_ERRORS;
		PE32 = PE32_T;
		//file = std::move( *this);
	}
	else {
		RaiseException(PE_FILE_NOT_OPEN, 0, 0, NULL);
	}
}



