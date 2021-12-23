#pragma once

#include <dolphin/types.h>
#include "sdk/arc.h"

#pragma warn_padding off
typedef struct arcObj {
	u16 flags; //0x0
	//will pad 2 bytes
	ARCHandle handle; //0x4
	u32 field_0x20; //0x20
	u32 field_0x24; //0x24
} arcObj;
#pragma warn_padding on


void arcInit(void);
void* arcOpen(const char* filename, void** addr, u32* length);