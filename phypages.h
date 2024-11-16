#pragma once
#include "pagetable.h"

int get_frame(PageTable *pt);
static int get_frame_from_LRU(PageTable *pt);