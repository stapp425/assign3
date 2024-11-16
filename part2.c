#include <stdio.h>
#include <stdlib.h>
#include "pagetable.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Infile and outfile are the only parameters for this program.");
    return EXIT_FAILURE;
  }

  FILE *infile;
  FILE *outfile;

  infile = fopen(argv[1], "rb");
  
  if (infile == NULL) {
    fprintf(stderr, "Infile (%s) could not be opened. Exiting...", argv[1]);
    return EXIT_FAILURE;
  }

  outfile = fopen(argv[2], "wb");

  if (outfile == NULL) {
    fprintf(stderr, "Outfile (%s) could not be opened. Exiting...", argv[2]);
    fclose(infile);
    return EXIT_FAILURE;
  }
  
  PageTable *pt = create_page_table();

  if (pt == NULL) {
    fprintf(stderr, "Failed to allocate memory for page table.");
    fclose(infile);
    fclose(outfile);
    return EXIT_FAILURE;
  }
  
  uint64_t v_addr;
  
  while (fread(&v_addr, sizeof(uint64_t), 1, infile) == 1) {
    uint64_t p_addr = handle_pt_transaction(pt, v_addr);
    fwrite(&p_addr, sizeof(uint64_t), 1, outfile);
  }

  printf("Total number of page faults: %d\n", pt->page_fault_count);

  // Program cleanup
  free(pt);
  fclose(infile);
  fclose(outfile);
  
  return EXIT_SUCCESS;
}