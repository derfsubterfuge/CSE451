/*++

Module Name:

    CSECopy.h

Abstract:

    Declares the exported routines found in CSECopy.c

--*/

#include "stdafx.h"

ULONG CSE451MtCopy( ULONG ThreadCount, ULONG BufferSize, PWCHAR *SrcDst[2], BOOLEAN Verbose );

ULONG CSE451MtCopyAsync( ULONG ThreadCount, ULONG BufferSize, PWCHAR *SrcDst[2], BOOLEAN Verbose );
