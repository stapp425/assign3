#pragma once
#include "pagetable.h"

typedef struct ft {
  int frame_count;
  Frame frames[];
} FrameTable;

typedef struct f {
  int ref_count;
  PageTableEntry *refPTE;
} Frame;

void free_frame(Frame *f);