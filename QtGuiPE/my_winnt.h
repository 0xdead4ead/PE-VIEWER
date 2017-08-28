#pragma once

#include <winnt.h>


#define MAGIC_NUMBER_NORMAL_EXEC 0x10B
#define MAGIC_NUMBER_PE32 0x10B
#define MAGIC_NUMBER_ROM_IMAGE 0x107
#define MAGIC_NUMBER_PE32PLUS 0x20B

//DLL
#define      IMAGE_LIBRARY_PROCESS_INIT            0x0001     
#define      IMAGE_LIBRARY_PROCESS_TERM            0x0002     
#define      IMAGE_LIBRARY_THREAD_INIT             0x0004     
#define      IMAGE_LIBRARY_THREAD_TERM             0x0008     


//data directory
#define IMAGE_DIRECTORY_ENTRY_RESERVED 15


//sections
#define IMAGE_FIRST_SECTION32( nth ) ((ULONGLONG)nth \
                                   + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) + sizeof(IMAGE_OPTIONAL_HEADER32)) 
#define IMAGE_FIRST_SECTION64( nth ) ((ULONGLONG)nth \
                                   + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) + sizeof(IMAGE_OPTIONAL_HEADER64)) 
//#define IMAGE_FIRST_SECTION64( p_ntheader ) ((PIMAGE_SECTION_HEADER)((&p_ntheader->OptionalHeader) \
  //                                 + p_ntheader->FileHeader.SizeOfOptionalHeader))    

#define CHARACTERISTICS_OFFSET(A) (((PIMAGE_DOS_HEADER)A)->e_lfanew \
                        + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) - sizeof(WORD))


//#define RVA_TO_RAW(rva,file_align,sect_align) (((rva / sect_align) * file_align) + (rva % sect_align))  

#define ALIGN_DOWN(x, align)  (x & ~(align-1))
#define ALIGN_UP(x, align)    ((x & (align-1)) ? ALIGN_DOWN(x,align)+align : x)

