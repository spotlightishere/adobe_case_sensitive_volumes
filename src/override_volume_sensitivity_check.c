#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include "dyld-interposing.h"
#include <CoreServices/CoreServices.h>
#include <objc/objc-class.h>

static OSErr _PBHGetVolParmsSync(HParmBlkPtr paramBlock) {
	OSErr result = PBHGetVolParmsSync(paramBlock);
	if (result < 0) {
		return result;
	}

	HIOParam ioParam = paramBlock->ioParam;
	GetVolParmsInfoBuffer* buffer = (GetVolParmsInfoBuffer*)ioParam.ioBuffer;

	// Check if we have the case sensitivity bit set.
	int isCaseSensitive = !!(buffer->vMExtendedAttributes & (1 << bIsCaseSensitive));

	if(isCaseSensitive) {
		printf("== PBHGetVolParmsSync - lying and saying the volume is case insensitive, though it is case sensitive. ==\n");
		buffer->vMExtendedAttributes &= ~(1 << bIsCaseSensitive);
	}

	return result;
}

DYLD_INTERPOSE(_PBHGetVolParmsSync, PBHGetVolParmsSync);
