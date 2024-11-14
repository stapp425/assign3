#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pagetable.h"

// Convert from virtual to physical address
// Assuming that pte sizes are 128 bytes (2^7)
uint64_t virtual_to_physical_addr(uint64_t v_addr, int frame_num) {
  if (frame_num < 0 || frame_num >= MAX_FRAMES) {
    fprintf(stderr, "Out-of-bounds frame number found.\n");
    return -1;
  }
  
  uint64_t offset = v_addr & 0x7f;
  uint64_t page_num = v_addr >> PAGE_OFFSET;
  uint64_t p_addr = (frame_num << PAGE_OFFSET) | offset;

  return p_addr;
}

int map_page_to_frame(PageTable *pt, int page_num, int frame_num) {
  // Accounts for the first frame to be allocated for the OS
  if (page_num < 0 || page_num >= PT_ENTRIES || frame_num <= 0 || frame_num >= MAX_FRAMES) {
    fprintf(stderr, "Failed to map page to frame.\n");
    return 1;
  }

  // Only map if the PTE does not point to a frame number
  if (!pt->entries[page_num].valid) {
    pt->entries[page_num].frame_num = frame_num;
    pt->entries[page_num].valid = 1;
  }

  return 0;
}

int handle_page_fault(PageTable *pt) {
  return 0;
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
