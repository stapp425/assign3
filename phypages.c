#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "pagetable.h"
#include "phypages.h"

static int free_frame = 1;

int get_frame(PageTable *pt) {
  if (free_frame < MAX_FRAMES) {
    return free_frame++;
  }

  // This point: No frames left (frame stack is full)
  return get_frame_from_LRU(pt);
}

static int get_frame_from_LRU(PageTable *pt) {
  int i, max = INT_MIN;
  int victim_page_num = 0;
  PageTableEntry *pte_least_ref = NULL;
  
  // Finding least used page
  // Longest time between current transaction int and pte's last access
  for(i = 0; i < PT_ENTRIES; i++) {
    PageTableEntry *curr_pte = &pt->entries[i];
    int time_diff = pt->transaction_counter - curr_pte->last_accessed;
    
    if (curr_pte->valid && time_diff > max) {
      max = time_diff;
      pte_least_ref = curr_pte;
      victim_page_num = i;
    }
  }

  // Save before deleting the reference
  int prev_frame_num = pte_least_ref->frame_num;

  // Invalidate the victim page
  // Reverts the victim page to its default status
  pte_least_ref->frame_num = -1;
  pte_least_ref->valid = false;
  pte_least_ref->last_accessed = 0;
  printf("Page %d evicted and invalidated\n", victim_page_num);

  return prev_frame_num;
}