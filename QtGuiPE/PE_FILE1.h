#pragma once
#include <Windows.h>
#include "my_winnt.h"
#include <memory>
#include <tchar.h>
#include <vector>
#include <string.h>

#pragma warning(disable: 4430)

#pragma warning(disable: 4723 )
#pragma warning(disable: 4577 ) //
class PE_FILE;

extern PE_FILE file;
using std::unique_ptr;
using std::vector;
using std::wstring;
using std::string;



typedef struct {
	unique_ptr<IMAGE_EXPORT_DIRECTORY> export_header;
	unique_ptr<string> export_name;
	unique_ptr<vector<DWORD> > export_rva;
	unique_ptr<vector<string> > export_names;
	unique_ptr<vector<DWORD> > export_adress_names_rva;
	unique_ptr<vector<WORD> > export_ordinals;
} PE_FILE_EXPORT_TABLE;

typedef struct {
	vector<IMAGE_IMPORT_DESCRIPTOR> import_headers;
	unique_ptr<vector<string> > dll_names_of_import_desc;
	unique_ptr<vector<vector<string> > > func_names_of_import_desc;
	unique_ptr<vector<vector<IMAGE_THUNK_DATA32> > > image_thunk32;
	unique_ptr<vector<vector<IMAGE_THUNK_DATA64> > > image_thunk64;
	unique_ptr<vector<vector<IMAGE_IMPORT_BY_NAME> > > image_import_names;
} PE_FILE_IMPORT_TABLE;


typedef struct {
	LPCTSTR lpszName;
	wstring szResName;
	DWORD RVAData;
	DWORD ResourceSize;
	WORD wIDLanguage;
} PE_FILE_RESOURCE_NAME;

typedef struct {
	LPTSTR lpszType;
	wstring szResType;
	vector<PE_FILE_RESOURCE_NAME> names;
} PE_FILE_RESOURCE_TYPE;

typedef struct {
	DWORD BeginAddress;
	DWORD EndAddress;
	DWORD ExceptionHandler;
	DWORD HandlerData;
	DWORD PrologEndAdress;
} __declspec(align(4)) PE_FILE_EXCEPTION_ENTRY_MIPS32;   //for MIPS32

typedef struct {
	DWORD BeginAddress;
	DWORD EndAddress;
	DWORD UnwindInformation;
} __declspec(align(4)) PE_FILE_EXCEPTION_ENTRY_X64;    //for x86-64, Itanium

typedef struct {
	union {
		DWORD PrologLength : 8;
		DWORD FunctionLength : 22;
		DWORD bit32Flag : 1;
		DWORD ExceptionFlag : 1;
		DWORD BeginAddress;
	};
} __declspec(align(4)) PE_FILE_EXCEPTION_ENTRY_OTHER;   //for PPC,ARM,SH3,SH4

BOOL read_char_cs_forcheck32bitPE(LONG e_lfanew, LPWORD CHAR_CS, HANDLE hFile);
BOOL read_dos_header(PIMAGE_DOS_HEADER dos, HANDLE hFile);
BOOL read_signature(LONG e_lfanew, LPDWORD sig, HANDLE hFile);
BOOL read_file_header(LONG e_lfanew, PIMAGE_FILE_HEADER fh, HANDLE hFile);
BOOL read_optional_header32(LONG e_lfanew, PIMAGE_OPTIONAL_HEADER32 op32, HANDLE hFile);
BOOL read_optional_header64(LONG e_lfanew, PIMAGE_OPTIONAL_HEADER64 op64, HANDLE hFile);
BOOL read_section_headers(LONG Distance, vector<IMAGE_SECTION_HEADER>* sections,  WORD NumberOfSections, HANDLE hFile);
BOOL read_export_table(DWORD AlignmentSection, vector<IMAGE_SECTION_HEADER>* sections, DWORD RVAoffset, PE_FILE_EXPORT_TABLE* expt, HANDLE hFile);
BOOL read_import_table(BOOL pe32,DWORD AlignmentSection, vector<IMAGE_SECTION_HEADER>* sections, DWORD RVAoffset, PE_FILE_IMPORT_TABLE* impt, HANDLE hFile);
BOOL read_except_table_mips32(DWORD AlignmentSection, vector<IMAGE_SECTION_HEADER>* sections,DWORD RVAoffset,vector<PE_FILE_EXCEPTION_ENTRY_MIPS32>* except_table, HANDLE hFile);
BOOL read_except_table_x64(DWORD AlignmentSection, vector<IMAGE_SECTION_HEADER>* sections,DWORD RVAoffset, vector<PE_FILE_EXCEPTION_ENTRY_X64>* except_table, HANDLE hFile);
BOOL read_except_table_other(DWORD AlignmentSection, vector<IMAGE_SECTION_HEADER>* sections,DWORD RVAoffset, vector<PE_FILE_EXCEPTION_ENTRY_OTHER>* except_table, HANDLE hFile);

BOOL getListResource(vector<PE_FILE_RESOURCE_TYPE>* res, LPCTSTR filename);
BOOL CALLBACK ListResourceTypes(HMODULE hModule, LPTSTR lpszType, LONG_PTR lParam);
BOOL CALLBACK ListResourceNames(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam);
BOOL CALLBACK ListResourceLanguages(HMODULE hModule, LPCTSTR lpszType, LPCTSTR lpszName, WORD wIDLanguage, LONG_PTR lParam);

WORD defSection(vector<IMAGE_SECTION_HEADER>* sections, DWORD rva, DWORD Alignment);
DWORD rvaToOff(vector<IMAGE_SECTION_HEADER>* sections, DWORD rva, DWORD Alignment);






//TYPICAL PORTABLE EXE FILE LAYOUT
class PE_FILE {
public:
	DWORD _STATE;


	unique_ptr<IMAGE_DOS_HEADER> dos_header;
	unique_ptr<DWORD> Signature; 
	unique_ptr<IMAGE_FILE_HEADER> file_header;
	unique_ptr<IMAGE_OPTIONAL_HEADER32> op_header32;
	unique_ptr<IMAGE_OPTIONAL_HEADER64> op_header64;

	vector<IMAGE_SECTION_HEADER> section_headers;

	unique_ptr<PE_FILE_EXPORT_TABLE> export_table;
	unique_ptr<PE_FILE_IMPORT_TABLE> import_table;

	vector<PE_FILE_RESOURCE_TYPE> resources;
	vector<PE_FILE_EXCEPTION_ENTRY_MIPS32> exception_table_mips32;
	vector<PE_FILE_EXCEPTION_ENTRY_X64> exception_table_x64;
	vector<PE_FILE_EXCEPTION_ENTRY_OTHER> exception_table_other;
	
	
	void read(LPCTSTR pathfile);

	//BOOL open()


	//CONSTRUCTORS DEFAULT???
	PE_FILE();
	explicit PE_FILE(const PE_FILE&) = delete;
	PE_FILE(PE_FILE&&) = default;
	PE_FILE& operator=(const PE_FILE&) = delete;
	PE_FILE& operator=(PE_FILE&&) = default;
	~PE_FILE() = default;

	//search index section



	HANDLE hFile;
	BOOL PE32; //for 32bit machine???


};

