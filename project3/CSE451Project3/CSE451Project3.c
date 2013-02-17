/*++

Module Name:

    CSE451Project.c

Abstract:

    Defines the entry point for the console application

--*/

#include "stdafx.h"
#include "CSECopy.h"

//
//	Here is a local routine added for demonstration purposes
//

ULONG CSE451Cat( PWCHAR Src );


ULONG _tmain (
    LONG argc,
    WCHAR* argv[]
    )

/*++

Routine Description:

    This is the main routine for MtCopy.  It parses the command line,
    builds the source-destination file name pairs, and then calls
    the appropriate MtCopy function

--*/
{
	//
	//	Here are the user specified options with their default values
	//

	BOOLEAN AsyncIo = FALSE;
	LONG BufferSize = 4096;
	LONG ThreadCount = 1;
	BOOLEAN Verbose = FALSE;

	//
	//	Here are the local variables needed to munge the filenames into
	//	a the source-destination pairs
	//

	PWCHAR **SrcDst;
	ULONG IndexOfFirstSource;
	LONG NumberOfSourceFiles;
	ULONG SrcFileNameLength;
	ULONG DestDirectoryNameLength;

	LONG i, j, k;
	
	//
	//	A little bit a commented out debug code
	//
	//	for(i = 0; i < argc; i++) {
	//		//%S for unicode
	//		printf("%S\n",argv[i]);
	//	}
	//

	//
	//	First go through all the arguments that start with a slash
	//

	for (i = 1; i < argc; i++ ) {

		if (argv[i][0] != '/') break;

		switch (argv[i][1]) {

		case 'A':
		case 'a':
			AsyncIo = TRUE;
			break;

		case 'B':
		case 'b':
			if (argv[i][2] != ':') goto error;
			BufferSize = _wtoi(argv[i]+3);
			break;

		case 'T':
		case 't':
			if (argv[i][2] != ':') goto error;
			ThreadCount = _wtoi(argv[i]+3);
			break;

		case 'V':
		case 'v':
			Verbose = TRUE;
			break;

		default:
			goto error;
		}
	}

	//
	//	Now here is a little undocumented switch if the thread count is -1 then
	//	call our sample routine that simply writes out the first file.  See
	//	CSE451Cat for an explanation on why it's included here
	//

	if (ThreadCount == -1) {
		return CSE451Cat( argv[i] );
	}

	//
	//	Now we need to unpack the filenames.  We do this by taking each source
	//	name and prefixing on it the destination directory.  Then the final
	//	array that we pass to the MtCopy routines will have an array of pointer
	//	pairs, the source name and the destination name.
	//
	//	First compute the number of source file and allocate our top array
	//	which is an array of pointers to source/destination pairs.  We also
	//	need to null out the last entry in the array.
	//

	IndexOfFirstSource = i;

	if ((NumberOfSourceFiles = argc - IndexOfFirstSource - 1) < 1 ) {
		goto error;
	}

	SrcDst = malloc(sizeof(PWCHAR*) * (NumberOfSourceFiles + 1));
	SrcDst[NumberOfSourceFiles] = NULL;

	//
	//	Now for each source file we need to allocate a pair of source
	//	destination pointers.  And fill in the pointers
	//

	for (i = 0; i < NumberOfSourceFiles; i++) {

		SrcDst[i] = malloc( sizeof(PWCHAR*) * 2 );

		//
		//	Pointing to the source is easy.  It is just what is in argv
		//

		SrcDst[i][0] = &argv[IndexOfFirstSource + i][0];

		//
		//	For the destination we need to know the actual filename without any
		//	of the prefix stuff.  We do this by backwards looking at the source
		//	until we find a '\' or a ':' or we're at the start of the string.
		//	Once we find it we'll save it
		//

		for (j = k = (LONG)wcslen( SrcDst[i][0] ); j > 0; j--) {

			if ((SrcDst[i][0][j-1] == '\\') ||
				(SrcDst[i][0][j-1] == ':')) break;
		}

		SrcFileNameLength = k - j;

		//
		//	It's nice to know the destination directory name length, we'll need it
		//	later on
		//

		DestDirectoryNameLength = (LONG)wcslen(argv[argc-1]);

		//
		//	Now allocate space for the complete destination string, we need two
		//	extra spaces for a slash and a null
		//

		SrcDst[i][1] = malloc(sizeof(WCHAR)*(SrcFileNameLength + DestDirectoryNameLength + 2));

		//
		//	Now we copy over the destination directory, add the slash, copy
		//	over the source file name (minus any extra stuff preceding the file
		//	name), and lastly null terminate it.
		//
		//	N.B. we can skip the slash if the destination name already ends in a colon or slash
		//

		wcscpy(SrcDst[i][1], argv[argc-1]);

		if ((SrcDst[i][1][DestDirectoryNameLength-1] != ':') &&
			(SrcDst[i][1][DestDirectoryNameLength-1] != '\\')) {

			SrcDst[i][1][DestDirectoryNameLength] = '\\';
			DestDirectoryNameLength += 1;
		}

		wcscpy(&SrcDst[i][1][DestDirectoryNameLength], &SrcDst[i][0][j]);
		SrcDst[i][1][SrcFileNameLength + DestDirectoryNameLength] = '\0';
	}

	//
	//	Here is a little debug code that is currently commented out
	//
	//	printf("[%s:%d] ThreadCount = %d, BufferSize = %d, AsyncIo = %d\n", __FILE__, __LINE__, ThreadCount, BufferSize, AsyncIo);
	//

	//
	//	Now that we have everything to do the copy we'll do a verbose check to
	//	list the sources and destinations
	//

	if (Verbose) {

		for (i = 0; i < NumberOfSourceFiles; i++) {

			printf("SrcDst[%d] \"%S\" => \"%S\"\n", i, SrcDst[i][0], SrcDst[i][1]);
		}
	}

	//
	//	Now call the copy routines to do the actual work
	//
	if (!AsyncIo) {
		return CSE451MtCopy( ThreadCount, BufferSize, SrcDst, Verbose );
	} else {
		return CSE451MtCopyAsync( ThreadCount, BufferSize, SrcDst, Verbose );
	}

	//
	//	We get here only if the user gave us a bad parameter
	//

error:

	printf("mtcopy [/T:number] [/B:number] [/V] [/A] <source>+ destination\n");
	return ERROR_INVALID_FUNCTION;
}


ULONG CSE451Cat (
    PWCHAR Src
    )
/*++

Routine Description:

    This is a simple rouitine to illustrate how to open and read a file, and get
	the time.

Arguments:

    Src - Specifies the file to open

Return Value:

    ERROR_SUCCESS

--*/
{
	SYSTEMTIME SystemTime;
	LARGE_INTEGER StartFileTime, EndFileTime;
	LARGE_INTEGER ElapsedTimeIn100ns;

	BYTE Buffer[4096];
	LONG BytesRead;
	HANDLE File;

	//
	//	SystemTime is nice, but FileTime is really large integer that we can use to 
	//	calculate elapsed time.  And will do a little cheat here because we know that
	//	FileTime is really just a large integer containing the time as 100ns since
	//	the start of 1601.
	//

	GetSystemTime( &SystemTime );
	SystemTimeToFileTime( &SystemTime, (PFILETIME)&StartFileTime );

	//
	//	Now open and read file
	//

	File = CreateFile(Src, GENERIC_READ, 7, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	while(TRUE) {

		//
		//	-1 for a terminating null
		//

		ReadFile(File, Buffer, 4096 - 1, &BytesRead, NULL);

		if(BytesRead < 1) { break; }

		Buffer[BytesRead] = 0;
		printf("%s", Buffer);
	}

	CloseHandle(File);

	//
	//	Now get our ending time, then compute, and write out the difference
	//

	GetSystemTime( &SystemTime );
	SystemTimeToFileTime( &SystemTime, (PFILETIME)&EndFileTime );

	ElapsedTimeIn100ns.QuadPart = EndFileTime.QuadPart - StartFileTime.QuadPart;

	printf("Elapsed Time in 100ns = %d\n", ElapsedTimeIn100ns.QuadPart );

	return ERROR_SUCCESS;
}
