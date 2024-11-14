#include <stdio.h>
#include <stdlib.h>
#include "phypages.h"

void free_frame(PageTableEntry *pte, Frame *f) {
  if (f != NULL) {
    free(f); // Free the frame
    pte->frame = NULL; // The PTE pointing to the frame (f) points to nothing
  }
}