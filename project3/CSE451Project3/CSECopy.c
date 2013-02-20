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

//max number of threads is 8
#define MAX_THREADS 8

//max buffer size is 16MB
#define MAX_BUFFER_SIZE (16*1024*1024)

// Declaration of printError()
VOID PrintError();

typedef struct _COPY_THREAD_DATA {
	PFILE_CHUNK Chunks;
	ULONG NextChunk;
	ULONG NumChunks;
	HANDLE Mutex;
	ULONG BufferSize;
} COPY_THREAD_DATA, * PCOPY_THREAD_DATA;


DWORD WINAPI ThreadCopy(
	LPVOID threadData
	)
{
	PCOPY_THREAD_DATA cThreadData = (PCOPY_THREAD_DATA)threadData;
	PCHAR Buffer = (PCHAR)malloc(cThreadData->BufferSize);
	DWORD BytesRead = 0;
	DWORD BytesWrite = 0;
	DWORD Temp;
	HANDLE FileIn = NULL;
	PWCHAR FileInName = NULL;
	HANDLE FileOut = NULL;
	PWCHAR FileOutName = NULL;
	ULONG i;

	// keep copying until no more chunks to process 
	while(TRUE) {
		// get a lock on shared cThreadData
		WaitForSingleObject(cThreadData->Mutex, INFINITE);
		
		i = cThreadData->NextChunk++;
		
		// release the lock
		ReleaseMutex(cThreadData->Mutex);
		
		// if out of chunks then break
		if(i >= cThreadData->NumChunks)
			break;

		// if we need to change in files for this job
		if(FileInName != cThreadData->Chunks[i].src) {
			// close the current file handle
			if(FileIn != NULL)
				CloseHandle(FileIn);
			
			// create a new file handle
			FileInName = cThreadData->Chunks[i].src;
			FileIn = CreateFile(
				FileInName,
				GENERIC_READ,
				FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			if (FileIn == INVALID_HANDLE_VALUE) {
				PrintError();
				return GetLastError();
			}
		}

		// if we need to change out files for this job
		if(FileOutName != cThreadData->Chunks[i].dst) {
			// close the current file handle
			if(FileOut != NULL)
				CloseHandle(FileOut);
				
			// create a new file handle
			FileOutName = cThreadData->Chunks[i].dst;
			FileOut = CreateFile(
				FileOutName,
				GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			if (FileOut == INVALID_HANDLE_VALUE) {
				PrintError();
				return GetLastError();
			}
		}

		// Set the file pointers
		SetFilePointer(FileIn, (LONG)cThreadData->Chunks[i].start, NULL, FILE_BEGIN);
		SetFilePointer(FileOut, (LONG)cThreadData->Chunks[i].start, NULL, FILE_BEGIN);
		
		// read the chunk
		BytesRead = 0;
		while(BytesRead < cThreadData->Chunks[i].length) {
			if	(ReadFile(FileIn, Buffer+BytesRead, cThreadData->Chunks[i].length-BytesRead, &Temp, NULL) == FALSE) {
				PrintError();
				return GetLastError();
			}
			BytesRead += Temp;
		}
		
		// write the chunk
		BytesWrite = 0;
		while(BytesWrite < cThreadData->Chunks[i].length) {
			if (WriteFile(FileOut, Buffer+BytesWrite, cThreadData->Chunks[i].length-BytesWrite, &Temp, NULL) == FALSE) {
				PrintError();
				return GetLastError();
			}
			BytesWrite += Temp;
		}
	}
	
	// cleanup
	if(FileIn != NULL)
		CloseHandle(FileIn);
	if(FileOut != NULL)
		CloseHandle(FileOut);

	return ERROR_SUCCESS;
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

			- call ParseAndChunk to get list of jobs
			- make decision on number of threads to spawn
			- start the threads

			- each thread gets the next FILE_CHUNK to do
			- must have a lock on the list of FILE_CHUNKs
			- each thread, reads to local buffer and writes out to dest file

	*/

	ULONG i;
	PFILE_CHUNK Chunks;
	ULONG NumChunks;
	ULONG NumBytes = 0;
	PCOPY_THREAD_DATA ThreadData;
	PHANDLE Threads;
	PULONG ThreadIDs;
	HANDLE Mutex;

	SYSTEMTIME SystemTime;
	LARGE_INTEGER StartFileTime, EndFileTime;
	LARGE_INTEGER ElapsedTimeIn100ns;

	//get the starting time
	if(Verbose){
		GetSystemTime( &SystemTime );
		SystemTimeToFileTime( &SystemTime, (PFILETIME)&StartFileTime );
	}

	// parse the file into chunks
	if (ParseAndChunk(BufferSize, SrcDst, Verbose, &Chunks, &NumChunks, &NumBytes)) {
		return GetLastError();
	}

	// be smart about number of threads created
	if(ThreadCount > NumChunks)
		ThreadCount = NumChunks;

	// malloc data for threads
	ThreadData = (PCOPY_THREAD_DATA)malloc(sizeof(COPY_THREAD_DATA));
	ThreadIDs = (PULONG)malloc(sizeof(ULONG) * ThreadCount);
	Threads = (PHANDLE)malloc(sizeof(HANDLE) * ThreadCount);
	
	// initialize thread data
	ThreadData->Mutex = CreateMutex(NULL,FALSE,NULL);
	ThreadData->Chunks = Chunks;
	ThreadData->NextChunk = 0;
	ThreadData->BufferSize = BufferSize;
	ThreadData->NumChunks = NumChunks;

	// spawn threads
	for(i = 0; i < ThreadCount; i++) {
		Threads[i] = CreateThread(
					NULL, 
					0, 
					ThreadCopy,
					ThreadData,
					0,
					&(ThreadIDs[i]));
	}

	// wait for all threads to finish
	WaitForMultipleObjects(
		ThreadCount,
		Threads,
		TRUE,
		INFINITE);

	// close all threads
	for(i = 0; i < ThreadCount; i++) {
		CloseHandle(Threads[i]);
	}

	// cleanup
	free(Chunks);
	free(ThreadData);
	free(Threads);
	free(ThreadIDs);

	if (Verbose) {
		GetSystemTime( &SystemTime );
		SystemTimeToFileTime( &SystemTime, (PFILETIME)&EndFileTime );

		ElapsedTimeIn100ns.QuadPart = EndFileTime.QuadPart - StartFileTime.QuadPart;

		printf("ThreadCount = %d BufferSize = %d Elapsed Time in 100ns = %lld Throughput = %.2f MB/s \n", ThreadCount, BufferSize, ElapsedTimeIn100ns.QuadPart, (NumBytes * 10.0) / ElapsedTimeIn100ns.QuadPart);
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
			
			- call ParseAndChunk to get list of jobs
			- create an event for each buffer
			- loop over WaitForMultipleObjects()
				- decide if read or write object
				- if read, call write
				- if write, get next job
	*/
	ULONG i, NumChunks;
	ULONG NumBytes = 0;
	DWORD FinishedIndex;
	ULONG NumFiles = 0;
	ULONG NumProcessed = 0;
	ULONG NumFinished = 0;
	DWORD BytesRW = 0;

	PCHAR * buffers;
	PFILE_CHUNK Chunks;
	LPHANDLE FilesIn;
	LPHANDLE FilesOut;
	PASYNC_JOB aios;
	LPHANDLE events;
	PASYNC_JOB curr;

	SYSTEMTIME SystemTime;
	LARGE_INTEGER StartFileTime, EndFileTime;
	LARGE_INTEGER ElapsedTimeIn100ns;

	//get the starting time
	if(Verbose){
		GetSystemTime( &SystemTime );
		SystemTimeToFileTime( &SystemTime, (PFILETIME)&StartFileTime );
	}

	for (i = 0; SrcDst[i] != NULL; i++) {
		NumFiles++;
	}

	//parse the files into chunks
	if (ParseAndChunk(BufferSize, SrcDst, Verbose, &Chunks, &NumChunks, &NumBytes)) {
		return GetLastError();
	}

	//allocate an array of file handles to all the file src
	//allocate an array of file handles to all the file dst
	FilesIn = (LPHANDLE) malloc(sizeof(HANDLE) * NumFiles);
	FilesOut = (LPHANDLE) malloc(sizeof(HANDLE) * NumFiles);
	for(i = 0; i < NumFiles; i++){
		FilesIn[i] = CreateFile(SrcDst[i][SRC], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
		FilesOut[i] = CreateFile(SrcDst[i][DST], GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	}

	//allocate <ThreadCount> number of buffers each with size BufferSize
	// set <ThreadCount> to min of NumChunks and <ThreadCount>
	if (ThreadCount > NumChunks)
		ThreadCount = NumChunks;
	buffers = (PCHAR *) malloc(sizeof(PCHAR) * ThreadCount);
	for(i = 0; i < ThreadCount; i++){
		buffers[i] = (PCHAR) malloc(sizeof(CHAR) * BufferSize);	
	}

	//allocate async_job object
	aios = (PASYNC_JOB) malloc(sizeof(ASYNC_JOB) * ThreadCount);
	memset(aios,0,sizeof(ASYNC_JOB) * ThreadCount);

	//allocate events
	/*
		Buffers[i] is used by async job aios[i] with an event events[i]
		Need to update them correspondingly
	*/
	events = (LPHANDLE) malloc(sizeof(HANDLE) * ThreadCount);

	//start to read the first <ThreadCount> jobs
	for(i = 0; i < ThreadCount; i++){
		NumProcessed++;
		aios[i].chunk = &(Chunks[i]);
		aios[i].isread = TRUE;
		aios[i].ovlp.Offset = Chunks[i].start;
		events[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		aios[i].ovlp.hEvent = events[i];

		if (ReadFile(FilesIn[aios[i].chunk->index], buffers[i], Chunks[i].length, NULL, &(aios[i].ovlp)) == FALSE) {
			if (GetLastError() != ERROR_IO_PENDING) {
				PrintError();
				return GetLastError();
			}
		}
	}

	
	while(1){

		//wait for an event to be signaled
		if((FinishedIndex = WaitForMultipleObjects(ThreadCount, events, FALSE, INFINITE)) == WAIT_FAILED) {
			PrintError();
			return GetLastError();		
		}

		CloseHandle(events[FinishedIndex]);
		
		curr = &aios[FinishedIndex];



		if(curr->isread) {
			//the event is a readfile event

			if(GetOverlappedResult(FilesIn[curr->chunk->index], 
									&curr->ovlp,
									&BytesRW,
									FALSE))
			{
					curr->bytesRW += BytesRW;
					BytesRW = 0;
			}

			if(curr->bytesRW < curr->chunk->length){
				//if the read hasn't NumFinished the entire chunk, create another read event to finish the rest of the chunk

				events[FinishedIndex] = CreateEvent(NULL, TRUE, FALSE, NULL);

				//reset the overlap
				curr->isread = TRUE;
				curr->ovlp.Offset = curr->chunk->start + curr->bytesRW;
				curr->ovlp.hEvent = events[FinishedIndex];
				
				if (ReadFile(FilesIn[curr->chunk->index], buffers[FinishedIndex] + curr->bytesRW, curr->chunk->length - curr->bytesRW, NULL, &(curr->ovlp)) == FALSE) {
					if (GetLastError() != ERROR_IO_PENDING) {
						PrintError();
						return GetLastError();
					}
				}

			} else {
				//if all the this chunk has been read. write it to the dst


				events[FinishedIndex] = CreateEvent(NULL, TRUE, FALSE, NULL);

				//reset the overlap
				curr->isread = FALSE;
				curr->bytesRW = 0;
				curr->ovlp.Offset = curr->chunk->start;
				curr->ovlp.hEvent = events[FinishedIndex];
			
				if (WriteFile(FilesOut[curr->chunk->index], buffers[FinishedIndex], curr->chunk->length, NULL, &(curr->ovlp)) == FALSE) {
					if (GetLastError() != ERROR_IO_PENDING) {
						PrintError();
						return GetLastError();
					}
				}
			
			}
		
		
		} else {
			//the event is a WriteFileEvent

			//get the number of bytes written
			if(GetOverlappedResult(FilesOut[curr->chunk->index], 
								&curr->ovlp,
								&BytesRW,
								FALSE))
			{
				curr->bytesRW += BytesRW;
				BytesRW = 0;
			}


			
			if(curr->bytesRW < curr->chunk->length){
				//write hasn't NumFinished the current chunk

				events[FinishedIndex] = CreateEvent(NULL, TRUE, FALSE, NULL);

				//reset the overlap
				curr->isread = FALSE;
				curr->ovlp.Offset = curr->chunk->start + curr->bytesRW;
				curr->ovlp.hEvent = events[FinishedIndex];
				
				if (WriteFile(FilesOut[curr->chunk->index], buffers[FinishedIndex] + curr->bytesRW, curr->chunk->length - curr->bytesRW, NULL, &(curr->ovlp)) == FALSE) {
					if (GetLastError() != ERROR_IO_PENDING) {
						PrintError();
						return GetLastError();
					}
				}
		
			} else {
				//write has NumFinished the current chunk then move to the next one
			
				NumFinished++;

				if(NumFinished < NumChunks){

					if(NumProcessed < NumChunks ){
						//if there is a chunk that hasn't been NumProcessed

						events[FinishedIndex] = CreateEvent(NULL, TRUE, FALSE, NULL);

						//reset the overlap
						curr->isread = TRUE;

						curr->chunk = & Chunks[NumProcessed ++];
						curr->bytesRW = 0;
						curr->ovlp.Offset = curr->chunk->start;
						curr->ovlp.hEvent = events[FinishedIndex];
			
						if (ReadFile(FilesIn[curr->chunk->index], buffers[FinishedIndex], curr->chunk->length, NULL, &(curr->ovlp)) == FALSE) {
							if (GetLastError() != ERROR_IO_PENDING) {
								PrintError();
								return GetLastError();
							}
						}
					} else {
						//insert a dummy event that will never be signaled
						events[FinishedIndex] = CreateEvent(NULL, TRUE, FALSE, NULL);
					}
				} else {
					break;
				}
			}
		
		}
	}

	free(FilesIn);
	free(FilesOut);
	for(i = 0; i < ThreadCount; i++){
		free(buffers[i]);	
	}
	free(buffers);
	free(aios);
	free(events);

	if (Verbose) {
		GetSystemTime( &SystemTime );
		SystemTimeToFileTime( &SystemTime, (PFILETIME)&EndFileTime );

		ElapsedTimeIn100ns.QuadPart = EndFileTime.QuadPart - StartFileTime.QuadPart;

		printf("ThreadCount = %d BufferSize = %d Elapsed Time in 100ns = %lld Throughput = %.2f MB/s \n", ThreadCount, BufferSize, ElapsedTimeIn100ns.QuadPart, (NumBytes * 10.0) / ElapsedTimeIn100ns.QuadPart);
	}

	return ERROR_SUCCESS;
}




ULONG ParseAndChunk (
    ULONG BufferSize,
    PWCHAR *SrcDst[2],
    BOOLEAN Verbose,
	PFILE_CHUNK * Chunks,
    PULONG NumChunks,
	PULONG NumBytes
    )

/*++

Routine Description:


	This function parses each file in SrcDst, creating an empty destination file
	for future writes. (note: give file creation protocols). It returns an array
	of FILE_CHUNK structs that represent jobs that need to be copied.

Arguments:

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
	ULONG ChunkSize;
	HANDLE FileIn;
	HANDLE FileOut;
	PFILE_DATA SrcDstFileData;
	ULONG i;
	ULONG j;
	ULONG NumFiles;
	ULONG CurrentPos;

	// variables for insertion sort
	FILE_DATA ValueToInsert;
	ULONG HolePos;

	ChunkSize = BufferSize;

	// See how many files there are
	for (i = 0, NumFiles = 0; SrcDst[i] != NULL; i++) {
		NumFiles++;
	}

	// malloc space for keeping track of files
	SrcDstFileData = (PFILE_DATA) malloc(sizeof(FILE_DATA) * NumFiles);

	// open each file source
	// record sizes
	// record data in SrcFileData
	// keep track of how many total chunks we need
	// create destination files
	*NumBytes = 0;
	*NumChunks = 0;
	for (i = 0; SrcDst[i] != NULL; i++) {
		FileIn = CreateFile(SrcDst[i][SRC], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (FileIn == INVALID_HANDLE_VALUE) {
			PrintError();
			return GetLastError();
		}
		SrcDstFileData[i].src = SrcDst[i][SRC];
		SrcDstFileData[i].dst = SrcDst[i][DST];
		SrcDstFileData[i].index = i;
		SrcDstFileData[i].size = GetFileSize(FileIn, NULL); //TODO: handle large file sizes (second argument)
		(*NumBytes)	+= SrcDstFileData[i].size;
		(*NumChunks) += SrcDstFileData[i].size / ChunkSize;
		if ((SrcDstFileData[i].size % ChunkSize) > 0) {
			(*NumChunks)++;
		}
		CloseHandle(FileIn);

		//create destination files
		FileOut = CreateFile(SrcDst[i][DST], GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (FileOut == INVALID_HANDLE_VALUE) {
			PrintError();
			return GetLastError();
		}
		CloseHandle(FileOut);
	}

	// sort by sizes
	// insertion sort
	for (i = 1; i < NumFiles; i++) {
		ValueToInsert = SrcDstFileData[i];
		HolePos = i;
		while (HolePos > 0 && ValueToInsert.size < SrcDstFileData[HolePos - 1].size) {
			SrcDstFileData[HolePos] = SrcDstFileData[HolePos - 1];
			HolePos--;
		}
		SrcDstFileData[HolePos] = ValueToInsert;
	}

	// create chunks of the files in order
	(*Chunks) = (PFILE_CHUNK) malloc(sizeof(FILE_CHUNK) * (*NumChunks));

	// loop through each file
	for (i = 0, j = 0; i < NumFiles; i++) {
		// start at begining
		CurrentPos = 0;
		// while we can make another full chunk
		while ((CurrentPos + ChunkSize) < SrcDstFileData[i].size) {
			(*Chunks)[j].src = SrcDstFileData[i].src;
			(*Chunks)[j].dst = SrcDstFileData[i].dst;
			(*Chunks)[j].index = SrcDstFileData[i].index;
			(*Chunks)[j].start = CurrentPos;
			(*Chunks)[j].length = ChunkSize;
			CurrentPos += ChunkSize;
			j++;
		}
		// make partial chunk
		(*Chunks)[j].src = SrcDstFileData[i].src;
		(*Chunks)[j].dst = SrcDstFileData[i].dst;
		(*Chunks)[j].index = SrcDstFileData[i].index;
		(*Chunks)[j].start = CurrentPos;
		(*Chunks)[j].length = SrcDstFileData[i].size - CurrentPos;
		j++;
	}
	
	free(SrcDstFileData);
	return ERROR_SUCCESS;
}


/*
	Routine Description:
		
		Prints a formatted message from the call to GetLastError().
		Private helper function.
*/
VOID
PrintError() {
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