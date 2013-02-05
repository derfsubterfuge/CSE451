/*++

Module Name:

    CSECopy.c

Abstract:

	This module contains the functions you must complete.  The code in both funtions are just place
	markers that you are free to delete.

--*/

#include "stdafx.h"
#include "CSECopy.h"


#define SRC 0
#define DST 1

VOID
printError() {
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);
	wprintf(L"Formatted message: %s\n", lpMsgBuf);
	LocalFree(lpMsgBuf);
}


ULONG CSE451MtCopy (
    ULONG ThreadCount,
    ULONG BufferSize,
    PWCHAR *SrcDst[2],
    BOOLEAN Verbose
    )

/*++

Routine Description:

    This functions performs a multithreaded copy using synchronous read and
    write operations

Arguments:

    ThreadCount - Specifies the number of threads the perform the copy

	BufferSize - Specifies the maximum buffer size allowed for each read
		and write operation

	SrcDst - A pointer to a null terminated array of pointers to the source
		and destination file names.

    Verbose - Indicates of the operation is to include a diagnostic printout

Return Value:

    Final results of the copy (i.e., success or error)

--*/
{
	int i;

	printf("CSE451MtCopy(%d, %d, %08x, %d)\n", ThreadCount, BufferSize, SrcDst, Verbose);

	for (i = 0; SrcDst[i] != NULL; i++) {
		printf("SrcDst[%d] = %08x => %08x, %08x => \"%S\" \"%S\"\n", i, SrcDst[i], SrcDst[i][0], SrcDst[i][1], SrcDst[i][0], SrcDst[i][1]);
	}

	return ERROR_SUCCESS;
}



ULONG CSE451MtCopyAsync (
    ULONG ThreadCount,
    ULONG BufferSize,
    PWCHAR *SrcDst[2],
    BOOLEAN Verbose
    )

/*++

Routine Description:


	This functions performs a multithreaded copy using asynchronous read and
	write operations

Arguments:

    ThreadCount - Specifies the number of buffers to allocate to perform
		the copy.  Note that the name is probably a misnomer, but such is life.

	BufferSize - Specifies the maximum buffer size allowed for each read
		and write operation

	SrcDst - A pointer to a null terminated array of pointers to the source
        and destination file names.

    Verbose - Indicates if the operation is to include a diagnostic printout

Return Value:

    Final results of the copy (i.e., success or error)

--*/
{
	ULONG i;
	PCHAR buffer;
	HANDLE FileIn;
	HANDLE FileOut;
	ULONG BytesInUseRead = BufferSize;
	ULONG BytesInUseWrite = BufferSize;
	BOOL Return;

	buffer = (PCHAR) malloc(BufferSize);
	printf("CSE451MtCopyAsync(%d, %d, %08x, %d)\n", ThreadCount, BufferSize, SrcDst, Verbose);

	for (i = 0; SrcDst[i] != NULL; i++) {
		printf("SrcDst[%d] = %08x => %08x, %08x => \"%S\" \"%S\"\n", i, SrcDst[i], SrcDst[i][0], SrcDst[i][1], SrcDst[i][SRC], SrcDst[i][DST]);
	}

	FileIn = CreateFile(SrcDst[0][SRC], GENERIC_READ, 7, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	printf("FileIn is NULL? %d\n", FileIn == NULL);
	FileOut = CreateFile(SrcDst[0][DST], GENERIC_WRITE, 7, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	printf("FileOut is NULL? %d\n", FileOut == NULL);
	while(BytesInUseRead > 0) {
		Return = ReadFile(FileIn, buffer, BufferSize, &BytesInUseRead, NULL);
		BytesInUseWrite = BytesInUseRead;
		Return = WriteFile(FileOut, buffer, BytesInUseRead, &BytesInUseWrite, NULL);
	}
	CloseHandle(FileIn);
	CloseHandle(FileOut);
	free(buffer);
	return ERROR_SUCCESS;
}

