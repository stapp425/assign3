#include <stdio.h>
#include <stdlib.h>
#include "pagetable.h"
#include "phypages.h"

PageTable* create_page_table() {
  PageTable *pt = (PageTable*) malloc(sizeof(PageTable));
  int i;
  
  pt->page_fault_count = 0;
  pt->transaction_counter = 0;

  for (i = 0; i < PT_ENTRIES; i++) {
    pt->entries[i].frame_num = -1;
    pt->entries[i].valid = false;
    pt->entries[i].last_accessed = 0;
  }

  return pt;
}

// Handles various scenarios of page table handling
// insertion, eviction, and page fault handling
// All transactions will result in a physical address being returned for the application to use
uint64_t handle_pt_transaction(PageTable *pt, uint64_t v_addr) {
  printf("------------------------------------\n");
  pt->transaction_counter++;
  uint64_t offset = v_addr & 0x7f;
  uint64_t page_num = v_addr >> PAGE_OFFSET;
  int frame_num;
  
  PageTableEntry *pte = &pt->entries[page_num];
  
  // PTE validity check
  if (pte->valid) {
    pte->last_accessed = pt->transaction_counter;
    frame_num = pte->frame_num;
    printf("Page %llu referenced\n", page_num);
  } else {
    handle_page_fault(pt, page_num, &frame_num);
  }

  printf("%llu ---> %d\n", page_num, frame_num);

  uint64_t p_addr = (frame_num << PAGE_OFFSET) | offset;

  return p_addr;
}

static void handle_page_fault(PageTable *pt, uint64_t invalid_page_num, int *frame_num) {
  printf("Page fault encountered at page %llu\n", invalid_page_num);
  pt->page_fault_count++;

  PageTableEntry *pte = &pt->entries[invalid_page_num];
  *frame_num = get_frame(pt);
  
  // Page now maps to a frame
  pte->frame_num = *frame_num;
  pte->valid = true;
  pte->last_accessed = pt->transaction_counter;

  printf("Page %llu is now mapped to frame %d\n", invalid_page_num, *frame_num);
}