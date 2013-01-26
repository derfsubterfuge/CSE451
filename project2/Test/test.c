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
	prints the data in Cse451Info class in the following format:
	                                  API      TOTAL    SUCCESS       INFO       WARN      ERROR      BYTES
	-------------------------------------  ---------  ---------  ---------  ---------  ---------  ---------
	                             API_NAME        ###        ###        ###        ###        ###        ###
								      ...        ...        ...        ...        ...        ...        ...
	
*/
VOID
printAbbrevStatus(SYSTEM_CSE451_INFORMATION Cse451Info) {
	ULONG total , success, info, warn, error;
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
		for(i = 0; i < Cse451Info.ApiStatus[j].NumStatuses; i++) {
			count = Cse451Info.ApiStatus[j].StatusCounts[i].Count;
			status = Cse451Info.ApiStatus[j].StatusCounts[i].Status;
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

		printf("%30s  %10d  %10d  %10d  %10d  %10d  ", CSE451_APIS_STRINGS[j], total, success, info, warn, error);
		if(j == ReadFile || j == WriteFile) {
			printf("%15d", Cse451Info.ApiStatus[j].BytesUsed);
		}
		printf("\n");
	}
}

/*
	prints the data in Cse451Info class in the following format:
	
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
printDetailedStatus(SYSTEM_CSE451_INFORMATION Cse451Info) {
	USHORT i;
	USHORT j;
	
	printf("%30s  %15s  %10s\n", "API", "STATUS", "COUNT");
	printf("%.30s  %.15s  %.10s\n", BIG_UNDERLINE, BIG_UNDERLINE, BIG_UNDERLINE);
	for(j = 0; j < NUM_CSE451_APIS; j++) {
		for(i = 0; i < Cse451Info.ApiStatus[j].NumStatuses; i++) {
			if(i == 0) {
				printf("%30s  ",CSE451_APIS_STRINGS[j]);
			} else {
				printf("%30s  ", "");
			}
			printf("%5s0x%08x %10d\n", "", Cse451Info.ApiStatus[j].StatusCounts[i].Status, Cse451Info.ApiStatus[j].StatusCounts[i].Count);
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
    SYSTEM_CSE451_INFORMATION Cse451Info;
    ULONG Size;
			
	//gather the SYSTEM_CSE451_INFORMATION data from the statem
    if (!NT_SUCCESS(Status = NtQuerySystemInformation( SystemCSE451Information,
                                                       &Cse451Info,
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
}