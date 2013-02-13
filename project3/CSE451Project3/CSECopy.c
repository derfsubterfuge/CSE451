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
	PULONG NextChunk;
	ULONG NumChunks;
	PHANDLE Mutex;
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

	while(TRUE) {
		WaitForSingleObject(*(cThreadData->Mutex), INFINITE);
		
		i = *(cThreadData->NextChunk);
		(*(cThreadData->NextChunk))++;
		
		ReleaseMutex(*(cThreadData->Mutex));

		if(i >= cThreadData->NumChunks)
			break;

		if(FileInName != cThreadData->Chunks[i].src) {
			if(FileIn != NULL)
				CloseHandle(FileIn);
			
			FileInName = cThreadData->Chunks[i].src;
			FileIn = CreateFile(
				FileInName,
				GENERIC_READ,
				7,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
				//TODO: check for error
		}

		if(FileOutName != cThreadData->Chunks[i].dst) {
			if(FileOut != NULL)
				CloseHandle(FileOut);
				
			FileOutName = cThreadData->Chunks[i].dst;
			FileOut = CreateFile(
				FileOutName,
				GENERIC_WRITE,
				7,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			 //TODO: check for error
		}

		SetFilePointer(FileIn, /*TODO: convert to LONG from ULONG*/ (LONG)cThreadData->Chunks[i].start, NULL, FILE_BEGIN);
		SetFilePointer(FileOut, /*TODO: convert to LONG from ULONG*/ (LONG)cThreadData->Chunks[i].start, NULL, FILE_BEGIN);
		
		BytesRead = 0;
		while(BytesRead < cThreadData->Chunks[i].length) {
			ReadFile(FileIn, Buffer+BytesRead, cThreadData->Chunks[i].length-BytesRead, &Temp, NULL);
			//TODO: check for error
			BytesRead += Temp;
			printf("read: %d, temp: %d, length: %d\n",BytesRead, Temp, cThreadData->Chunks[i].length);
		}
		
		BytesWrite = 0;
		while(BytesWrite < cThreadData->Chunks[i].length) {
			WriteFile(FileOut, Buffer+BytesWrite, cThreadData->Chunks[i].length-BytesWrite, &Temp, NULL); 
			//TODO: check for error
			BytesWrite += Temp;
			printf("write: %d, temp: %d, length: %d\n",BytesWrite, Temp, cThreadData->Chunks[i].length);
		}
		
		printf("Chunk %d\n", i);
		printf("\tSrcName: %S\n", cThreadData->Chunks[i].src);
		printf("\tSrcName: %S\n", FileInName);
		printf("\tDstName: %S\n", cThreadData->Chunks[i].dst);
		printf("\tDstName: %S\n", FileOutName);
		printf("\tStart: %d\n", cThreadData->Chunks[i].start);
		printf("\tLength: %d\n", cThreadData->Chunks[i].length);
	}
	
	if(FileIn != NULL)
		CloseHandle(FileIn);
	if(FileOut != NULL)
		CloseHandle(FileOut);
		
	/*while((i = *(cThreadData->NextChunk)) < cThreadData->NumChunks) {
		(*(cThreadData->NextChunk))++;
		printf("Chunk %d\n", i);
		printf("\tSrcName: %S\n", cThreadData->Chunks[i].src);
		printf("\tDstName: %S\n", cThreadData->Chunks[i].dst);
		printf("\tStart: %d\n", cThreadData->Chunks[i].start);
		printf("\tLength: %d\n", cThreadData->Chunks[i].length);
	}*/

	return 0;
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
	PCOPY_THREAD_DATA ThreadData;
	PHANDLE Threads;
	PULONG ThreadIDs;
	ULONG NextChunk;
	HANDLE Mutex;

	printf("CSE451MtCopy(%d, %d, %08x, %d)\n", ThreadCount, BufferSize, SrcDst, Verbose);


	if(BufferSize > MAX_BUFFER_SIZE)
		BufferSize = MAX_BUFFER_SIZE;

	ParseAndChunk(BufferSize, SrcDst, Verbose, &Chunks, &NumChunks);

	/*for (i = 0; i < NumChunks; i++) {
		printf("Chunk %d\n", i);
		printf("\tSrcName: %S\n", Chunks[i].src);
		printf("\tDstName: %S\n", Chunks[i].dst);
		printf("\tStart: %d\n", Chunks[i].start);
		printf("\tLength: %d\n", Chunks[i].length);
	}

	for (i = 0; SrcDst[i] != NULL; i++) {
		printf("SrcDst[%d] = %08x => %08x, %08x => \"%S\" \"%S\"\n", i, SrcDst[i], SrcDst[i][SRC], SrcDst[i][DST], SrcDst[i][SRC], SrcDst[i][DST]);
	}*/

	if(ThreadCount > MAX_THREADS)
		ThreadCount = MAX_THREADS;
	if(ThreadCount > NumChunks)
		ThreadCount = NumChunks;

	ThreadData = (PCOPY_THREAD_DATA)malloc(sizeof(COPY_THREAD_DATA) * ThreadCount);
	ThreadIDs = (PULONG)malloc(sizeof(ULONG) * ThreadCount);
	Threads = (PHANDLE)malloc(sizeof(HANDLE) * ThreadCount);
	Mutex = CreateMutex(NULL,FALSE,NULL);

	NextChunk = 0;
	for(i = 0; i < ThreadCount; i++) {
		ThreadData[i].Chunks = Chunks;
		ThreadData[i].NextChunk = &NextChunk;
		ThreadData[i].NumChunks = NumChunks;
		ThreadData[i].Mutex = &Mutex;
		ThreadData[i].BufferSize = BufferSize;
		Threads[i] = CreateThread(
					NULL, 
					0, 
					ThreadCopy,
					&(ThreadData[i]),
					0,
					&(ThreadIDs[i]));
	}

	WaitForMultipleObjects(
		ThreadCount,
		Threads,
		TRUE,
		INFINITE);

	for(i = 0; i < ThreadCount; i++) {
		printf("%d\n", ThreadIDs[i]);
		CloseHandle(Threads[i]);
	}

	free(Chunks);
	free(ThreadData);
	free(Threads);
	free(ThreadIDs);

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
	DWORD FinishedEvent;
	ULONG NumFiles = 0;
	ULONG processed = 0;
	ULONG finished = 0;
	DWORD BytesRW = 0;

	PCHAR * buffers;
	PFILE_CHUNK Chunks;
	LPHANDLE FilesIn;
	LPHANDLE FilesOut;
	PASYNC_JOB aios;
	LPHANDLE events;
	PASYNC_JOB curr;

	printf("CSE451MtCopyAsync(%d, %d, %08x, %d)\n", ThreadCount, BufferSize, SrcDst, Verbose);

	for (i = 0; SrcDst[i] != NULL; i++) {
		NumFiles++;
		printf("SrcDst[%d] = %08x => %08x, %08x => \"%S\" \"%S\"\n", i, SrcDst[i], SrcDst[i][0], SrcDst[i][1], SrcDst[i][SRC], SrcDst[i][DST]);
	}

	//allocate an array of file handles to all the file src
	//allocate an array of file handles to all the file dst
	FilesIn = (LPHANDLE) malloc(sizeof(HANDLE) * NumFiles);
	FilesOut = (LPHANDLE) malloc(sizeof(HANDLE) * NumFiles);
	for(i = 0; i < NumFiles; i++){
		FilesIn[i] = CreateFile(SrcDst[0][SRC], GENERIC_READ, 7, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
		FilesOut[i] = CreateFile(SrcDst[0][DST], GENERIC_WRITE, 7, NULL, CREATE_NEW, FILE_FLAG_OVERLAPPED, NULL);
	}

	//parse the files into chunks
	ParseAndChunk(BufferSize, SrcDst, Verbose, &Chunks, &NumChunks);

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
		processed++;
		aios[i].chunk = &(Chunks[i]);
		aios[i].isread = TRUE;
		aios[i].ovlp.Offset = Chunks[i].start;
		events[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		aios[i].ovlp.hEvent = events[i];

		ReadFile(FilesIn[aios[i].chunk->index], buffers[i], Chunks[i].length, NULL, &(aios[i].ovlp));
	}

	
	while(1){

		//wait for an event to be signaled
		FinishedEvent = WaitForMultipleObjects(ThreadCount, events, FALSE, INFINITE);

		//TODO: error checking

		CloseHandle(events[FinishedEvent]);
		
		curr = &aios[FinishedEvent];



		if(curr->isread) {
			//the event is a readfile event

			if(GetOverlappedResult(FilesIn[curr->chunk->index], 
									&curr->ovlp,
									&BytesRW,
									FALSE))
			{
					curr->hasRead += BytesRW;
					BytesRW = 0;
			}

			if(curr->hasRead < curr->chunk->length){
				//if the read hasn't finished the entire chunk, create another read event to finish the rest of the chunk

				events[FinishedEvent] = CreateEvent(NULL, TRUE, FALSE, NULL);

				//reset the overlap
				memset(&(curr->ovlp),0,sizeof(OVERLAPPED));
				curr->isread = TRUE;
				curr->ovlp.Offset = curr->chunk->start + curr->hasRead;
				curr->ovlp.hEvent = events[FinishedEvent];
				
				ReadFile(FilesIn[curr->chunk->index], buffers[FinishedEvent] + curr->hasRead, curr->chunk->length - curr->hasRead, NULL, &(curr->ovlp));

			} else {
				//if all the this chunk has been read. write it to the dst


				events[FinishedEvent] = CreateEvent(NULL, TRUE, FALSE, NULL);

				//reset the overlap
				memset(&(curr->ovlp),0,sizeof(OVERLAPPED));
				curr->isread = FALSE;
				curr->hasRead = 0;
				curr->ovlp.Offset = curr->chunk->start;
				curr->ovlp.hEvent = events[FinishedEvent];
			
				WriteFile(FilesOut[curr->chunk->index], buffers[FinishedEvent], curr->chunk->length, NULL, &(curr->ovlp));
			
			}
		
		
		} else {
			//the event is a WriteFileEvent

			//get the number of bytes written
			if(GetOverlappedResult(FilesOut[curr->chunk->index], 
								&curr->ovlp,
								&BytesRW,
								FALSE))
			{
				curr->hasRead += BytesRW;
				BytesRW = 0;
			}


			
			if(curr->hasRead < curr->chunk->length){
				//write hasn't finished the current chunk

				events[FinishedEvent] = CreateEvent(NULL, TRUE, FALSE, NULL);

				//reset the overlap
				memset(&(curr->ovlp),0,sizeof(OVERLAPPED));
				curr->isread = FALSE;
				curr->ovlp.Offset = curr->chunk->start + curr->hasRead;
				curr->ovlp.hEvent = events[FinishedEvent];
				
				WriteFile(FilesOut[curr->chunk->index], buffers[FinishedEvent] + curr->hasRead, curr->chunk->length - curr->hasRead, NULL, &(curr->ovlp));				
		
			} else {
				//write has finished the current chunk then move to the next one
			
				finished++;

				if(finished < NumChunks){

					if(processed < NumChunks ){
						//if there is a chunk that hasn't been processed

						events[FinishedEvent] = CreateEvent(NULL, TRUE, FALSE, NULL);

						//reset the overlap
						memset(&(curr->ovlp),0,sizeof(OVERLAPPED));
						curr->isread = TRUE;

						curr->chunk = & Chunks[processed ++];
						curr->hasRead = 0;
						curr->ovlp.Offset = curr->chunk->start;
						curr->ovlp.hEvent = events[FinishedEvent];
			
						ReadFile(FilesIn[curr->chunk->index], buffers[FinishedEvent], curr->chunk->length, NULL, &(curr->ovlp));
					} else {
						//insert a dummy event that will never be signaled
						events[FinishedEvent] = CreateEvent(NULL, TRUE, FALSE, NULL);
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

	return ERROR_SUCCESS;
}




ULONG ParseAndChunk (
    ULONG BufferSize,
    PWCHAR *SrcDst[2],
    BOOLEAN Verbose,
	PFILE_CHUNK * Chunks,
    PULONG NumChunks
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

	//TODO: check for duplicate destination files

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
	*NumChunks = 0;
	for (i = 0; SrcDst[i] != NULL; i++) {
		//TODO: handle doesn't exist
		FileIn = CreateFile(SrcDst[i][SRC], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		SrcDstFileData[i].src = SrcDst[i][SRC];
		SrcDstFileData[i].dst = SrcDst[i][DST];
		SrcDstFileData[i].size = GetFileSize(FileIn, NULL); //TODO: handle large file sizes (second argument)
		(*NumChunks) += SrcDstFileData[i].size / ChunkSize;
		if ((SrcDstFileData[i].size % ChunkSize) > 0) {
			(*NumChunks)++;
		}
		CloseHandle(FileIn);

		//create destination files
		//TODO: always overwrite?
		//TODO: handle bad file path
		FileOut = CreateFile(SrcDst[i][DST], GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
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
			(*Chunks)[j].index = i;
			(*Chunks)[j].start = CurrentPos;
			(*Chunks)[j].length = ChunkSize;
			CurrentPos += ChunkSize;
			j++;
		}
		// make partial chunk
		(*Chunks)[j].src = SrcDstFileData[i].src;
		(*Chunks)[j].dst = SrcDstFileData[i].dst;
		(*Chunks)[j].index = i;
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