#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pagetable.h"

// USE MALLOC!!

int page_table[] = {2, 4, 1, 7, 3, 5, 6};

PageTable* create_page_table(int num_pages) {
  return (PageTable*) malloc(sizeof(PageTable) + (num_pages * sizeof(PageTableEntry)));
}

// Convert from virtual to physical address
// Assuming that pte sizes are 128 bytes (2^7)
uint64_t virtual_to_physical_addr(uint64_t v_addr) {
  uint64_t offset = v_addr & 0x7f;
  uint64_t page_num = v_addr >> PAGE_OFFSET;
  uint64_t frame_num = page_table[page_num];
  uint64_t p_addr = (frame_num << PAGE_OFFSET) | offset;

  return p_addr;
}

void allocate_physical_address(PageTable *pt) {

}

void handle_page_fault(PageTable *pt) {
  pt->page_fault_count++;

  allocate_physical_address(pt);
}


/* 
  Allocate physical address from virtual address
  If frame is empty (free), increment page fault by count

  Selecting the victim frame
  -Find frame least accessed
  -FREE the space (free())
  -Add default values to new frame
  -Allocate new space that will be pointed by pte
*/
