/*++

Module Name:

    test.c

Abstract:

	retrieves the SYSTEM_CSE451_INFORMATION and prints it out

--*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <nt.h>
#include <ntrtl.h>
#include <nturtl.h>

//a large number of dashes to use in the printing display below
#define BIG_UNDERLINE "-------------------------------------------------------------------"

/*
	Converts a Function enum into a string form and
	puts the string form into the char* dest
*/
VOID
functionToString(
	CSE451_APIS Function,
	char* dest
	) 
{
	switch(Function) {
		case CreateFile:
			strcpy(dest, "NtCreateFile");
			break;
		case OpenFile:
			strcpy(dest, "NtOpenFile");
			break;
		case ReadFile:
			strcpy(dest, "NtReadFile");
			break;
		case WriteFile:
			strcpy(dest, "NtWriteFile");
			break;
		case QueryInformationFile:
			strcpy(dest, "NtQueryInformationFile");
			break;
		case SetInformationFile:
			strcpy(dest, "NtSetInformationFile");
			break;
		case QueryDirectoryFile:
			strcpy(dest, "NtQueryDirectoryFile");
			break;
		default:
			strcpy(dest, "UNKNOWN");
	}
}

/*
	Converts a Action enum into a string form and
	puts the string form into the char* dest
*/
VOID
actionToString(
	CSE451_ACTIONS Action,
	char* dest
	)
{
	switch(Action) {
		case Call:
			strcpy(dest, "Call");
			break;
		case Return:
			strcpy(dest, "Return");
			break;
		case BufferOverflow:
			strcpy(dest, "Buffer Overflow");
			break;
		default:
			strcpy(dest, "UNKNOWN");
			break;
	}
}

/*
	Converts a Status code into a string (i.e. "Success", "Warning", etc.) form and
	puts the string form into the char* dest
*/
VOID
statusToTypeString(
	NTSTATUS Status,
	char* dest
	)
{
	if(NT_SUCCESS(Status)) {
		strcpy(dest, "SUCCESS");
	} else if(NT_INFORMATION(Status)) {
		strcpy(dest, "INFORMATION");
	} else if(NT_WARNING(Status)) {
		strcpy(dest, "WARNING");
	} else if(NT_ERROR(Status)) {
		strcpy(dest, "ERROR");
	} else {
		strcpy(dest, "UNKNOWN");
	}
}


/*
	prints the data in Cse451Info API data in the following format:
	                                  API      TOTAL    SUCCESS       INFO       WARN      ERROR      BYTES
	-------------------------------------  ---------  ---------  ---------  ---------  ---------  ---------
	                             API_NAME        ###        ###        ###        ###        ###        ###
								      ...        ...        ...        ...        ...        ...        ...
	
*/
VOID
printAbbrevStatus(
	PSYSTEM_CSE451_INFORMATION Cse451Info
	)
{
	ULONG total , success, info, warn, error;
	char functionString[30];
	USHORT i;
	USHORT j;
	ULONG count;
	NTSTATUS status;
	
	printf("%30s  %10s  %10s  %10s  %10s  %10s  %15s\n", "API", "TOTAL", "SUCCESS", "INFO", "WARN", "ERROR", "BYTES");
	printf("%.30s  %.10s  %.10s  %.10s  %.10s  %.10s  %.15s\n", BIG_UNDERLINE, BIG_UNDERLINE, BIG_UNDERLINE, BIG_UNDERLINE, BIG_UNDERLINE, BIG_UNDERLINE, BIG_UNDERLINE);
	for(j = 0; j < NUM_CSE451_APIS; j++) {
		total = 0;
		success = 0;
		info = 0;
		warn = 0;
		error = 0;
		count = 0;
		status = 0;
		for(i = 0; i < Cse451Info->ApiStatus[j].NumStatuses; i++) {
			count = Cse451Info->ApiStatus[j].StatusCounts[i].Count;
			status = Cse451Info->ApiStatus[j].StatusCounts[i].Status;
			total += count;
			if(NT_SUCCESS(status)) {
				success += count;
			} else if(NT_INFORMATION(status)) {
				info += count;
			} else if(NT_WARNING(status)) {
				warn += count;
			} else if(NT_ERROR(status)) {
				error += count;
			}
		}
		functionToString(j, functionString);
		printf("%30s  %10d  %10d  %10d  %10d  %10d  ", functionString, total, success, info, warn, error);
		if(j == ReadFile || j == WriteFile) {
			printf("%15d", Cse451Info->ApiStatus[j].BytesUsed);
		}
		printf("\n");
	}
}

/*
	prints the data in Cse451Info API data in the following format:
	
	                                  API     STATUS      COUNT
	-------------------------------------  ---------  ---------
	                             API_NAME      0x###        ###
								               0x###        ###
									           0x###        ###
											     ...        ...
								 API_NAME      0x###        ###
												 ...        ...
*/
VOID
printDetailedStatus(
	PSYSTEM_CSE451_INFORMATION Cse451Info
	)
{
	USHORT i;
	USHORT j;
	char functionString[30];
	
	printf("%30s  %15s  %10s\n", "API", "STATUS", "COUNT");
	printf("%.30s  %.15s  %.10s\n", BIG_UNDERLINE, BIG_UNDERLINE, BIG_UNDERLINE);
	for(j = 0; j < NUM_CSE451_APIS; j++) {
		for(i = 0; i < Cse451Info->ApiStatus[j].NumStatuses; i++) {
			if(i == 0) {
				functionToString(j, functionString);
				printf("%30s  ", functionString);
			} else {
				printf("%30s  ", "");
			}
			printf("%5s0x%08x %10d\n", "", Cse451Info->ApiStatus[j].StatusCounts[i].Status, Cse451Info->ApiStatus[j].StatusCounts[i].Count);
		}
		printf("\n");
	}
}

/*
	prints the data in Cse451Info History data in the following format:
	                            timestamp         Action        Function       Status Type
	-------------------------------------  -------------  --------------  ----------------
	              yyyy/mm/dd HH:MM:SS:sss           Call    NtCreateFile       Information
								      ...            ...             ...               ...
	
*/
VOID
printHistory(
	PSYSTEM_CSE451_INFORMATION Cse451Info
	)
{	
	USHORT i;
	ULONG count = 0;
	TIME_FIELDS timestamp;
	char functionString[30];
	char actionString[30];
	char statusTypeString[30];
	
	printf("%24s  %20s  %30s  %20s\n", "Timestamp", "Action", "Function", "Status Type");
	printf("%.24s  %.20s  %.30s  %.20s\n", BIG_UNDERLINE, BIG_UNDERLINE, BIG_UNDERLINE, BIG_UNDERLINE);
	for(i = 0; i < Cse451Info->NumEvents; i++) {
		RtlTimeToTimeFields(&Cse451Info->History[i].Time, &timestamp);
		printf("%04d/%02d/%02d %02d:%02d:%02d:%03d", timestamp.Year, timestamp.Month, timestamp.Day, 
							timestamp.Hour, timestamp.Minute, timestamp.Second, timestamp.Milliseconds);
		actionToString(Cse451Info->History[i].Action, actionString);
		printf("  %20s", actionString);
		if(Cse451Info->History[i].Action == Call || Cse451Info->History[i].Action == Return) {
			functionToString(Cse451Info->History[i].Function, functionString);
			printf("  %30s", functionString);
		}
		
		if(Cse451Info->History[i].Action == Return) {
			statusToTypeString(Cse451Info->History[i].Status, statusTypeString);
			printf("  %20s", statusTypeString);
		}
		printf("\n");
	}
}


//retrieves the SYSTEM_CSE451_INFORMATION and prints it out
VOID
__cdecl
main (argc, argv)
	int argc;
	char *argv[];
{
    NTSTATUS Status;
    PSYSTEM_CSE451_INFORMATION Cse451Info;
    ULONG Size;
	if(argc != 2) {
		printf("Usage: %s <buffer_size>", argv[0]);
		return;
	}
	
	sscanf(argv[1], "%d", &Size);
	Size = Size / sizeof(HIST_EVENT);
	Cse451Info = (PSYSTEM_CSE451_INFORMATION) malloc(sizeof(SYSTEM_CSE451_INFORMATION)+sizeof(HIST_EVENT)*(Size-1));
	Cse451Info->NumEvents = Size;
	
	//gather the SYSTEM_CSE451_INFORMATION data from the statem
    if (!NT_SUCCESS(Status = NtQuerySystemInformation( SystemCSE451Information,
                                                       Cse451Info,
                                                       sizeof(SYSTEM_CSE451_INFORMATION),
                                                       &Size))) {

        printf("<<<Error>>>");

    } else {

        printf("<<<Success>>>");
    }
	
	//print out the SYSTEM_CSE451_INFORMATION that was gathered
	printf("\n\n");
	printAbbrevStatus(Cse451Info);
	printf("\n\n");
	printDetailedStatus(Cse451Info);
	printf("\n\n");
	printHistory(Cse451Info);
	free(Cse451Info);
}