#pragma once
#include <stdint.h>
#include "phypages.h"
#define PT_ENTRIES 32
#define PAGE_OFFSET 7
#define MAX_FRAMES 8

typedef struct pte {
  int frame_num;
  int valid;
  int referenced;
  unsigned int ref_count;
} PageTableEntry;

typedef struct pt {
  unsigned int page_fault_count;
  PageTableEntry entries[PT_ENTRIES];
} PageTable;

uint64_t virtual_to_physical_addr(uint64_t v_addr, int frame_num);

int map_page_to_frame(PageTable *pt, int page_num, int frame_num);

int handle_page_fault(PageTable *pt);
