#pragma once
#include <stdint.h>
#include "phypages.h"
#define PT_ENTRIES 32
#define PAGE_OFFSET 7
#define MAX_FRAMES 8

typedef struct pte {
  int frame_num;
  int ref_count;
  Frame *frame;
} PageTableEntry;

typedef struct pt {
  int entries_num;
  int page_fault_count;
  PageTableEntry entries[];
} PageTable;

PageTable* create_page_table(int num_pages);

void allocate_physical_address(PageTable *pt);

uint64_t virtual_to_physical_addr(uint64_t v_addr);

void handle_page_fault(PageTable *pt);
