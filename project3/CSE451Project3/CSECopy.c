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

// Declaration of printError()
VOID printError();

/*
	Routine Description:
		
		Prints a formatted message from the call to GetLastError().
		Private helper function.
*/
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
	wprintf(L"Error: %s\n", lpMsgBuf);
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
	/*
		Proposed steps.

			- call ParseAndCopy to get list of jobs
			- make decision on number of threads to spawn
			- start the threads

			- each thread gets the next FILE_CHUNK to do
			- must have a lock on the list of FILE_CHUNKs
			- each thread, reads to local buffer and writes out to dest file

	*/

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
	/*
		Proposed steps
			
			- call ParseAndCopy to get list of jobs
			- create an event for each buffer
			- loop over WaitForMultipleObjects()
				- decide if read or write object
				- if read, call write
				- if write, get next job
	*/
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

ULONG ParseAndChunk (
    ULONG ThreadCount,
    ULONG BufferSize,
    PWCHAR *SrcDst[2],
    BOOLEAN Verbose,
    PFILE_CHUNK Chunks,
    ULONG NumChunks
    )

/*++

Routine Description:


	This function parses each file in SrcDst, creating an empty destination file
	for future writes. (note: give file creation protocols). It returns an array
	of FILE_CHUNK structs that represent jobs that need to be copied.

Arguments:

    ThreadCount - Specifies the number of buffers to allocate to perform
		the copy.  Note that the name is probably a misnomer, but such is life.

	BufferSize - Specifies the maximum buffer size allowed for each read
		and write operation

	SrcDst - A pointer to a null terminated array of pointers to the source
        and destination file names.

    Verbose - Indicates if the operation is to include a diagnostic printout

	Chunks - A pointer to a dynamically allocated array of FILE_CHUNK structs
		associated with the files to parse. (note: this could change)

	NumChunks - The number of chunks returned. (note: not sure if needed)
		

Return Value:

    Final results of the parse and copy (i.e., success or error)

--*/
{
	// TODO: Implement
	return ERROR_SUCCESS;
}