/*++

Module Name:

    CSECopy.h

Abstract:

    Declares the exported routines found in CSECopy.c

--*/

#include "stdafx.h"

ULONG CSE451MtCopy( ULONG ThreadCount, ULONG BufferSize, PWCHAR *SrcDst[2], BOOLEAN Verbose );

ULONG CSE451MtCopyAsync( ULONG ThreadCount, ULONG BufferSize, PWCHAR *SrcDst[2], BOOLEAN Verbose );

typedef struct _FILE_CHUNK {
	PWCHAR src;
	PWCHAR dst;
	ULONG index;
	ULONG start;
	ULONG length;
} FILE_CHUNK, *PFILE_CHUNK;

typedef struct _FILE_DATA {
	PWCHAR src;
	PWCHAR dst;
	ULONG index;
	ULONG size;
} FILE_DATA, *PFILE_DATA;

typedef struct _ASYNC_JOB {
	BOOL isread;
	ULONG hasRead;
	PFILE_CHUNK chunk;
	OVERLAPPED ovlp;
} ASYNC_JOB, *PASYNC_JOB;

ULONG ParseAndChunk(ULONG BufferSize, PWCHAR *SrcDst[2], BOOLEAN Verbose, PFILE_CHUNK * Chunks, PULONG NumChunks );
