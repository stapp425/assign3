#pragma once
#include <stdint.h>
#include <stdbool.h>
#define PT_ENTRIES 32
#define PAGE_OFFSET 7
#define MAX_FRAMES 8

typedef struct pte {
  int frame_num;
  bool valid;
  unsigned int last_accessed;
} PageTableEntry;

typedef struct pt {
  unsigned int transaction_counter;
  unsigned int page_fault_count;
  PageTableEntry entries[PT_ENTRIES];
} PageTable;

PageTable* create_page_table(void);
uint64_t handle_pt_transaction(PageTable *pt, uint64_t v_addr);
static void handle_page_fault(PageTable *pt, uint64_t invalid_page_num, int *frame_num);
