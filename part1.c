#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define PAGE_OFFSET 7
#define LOG2(X) ((unsigned) (8 * sizeof (unsigned long) - __builtin_clzll((X)) - 1))

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

  // Program proceeds if both in and out files exist
  uint64_t v_addr;
  int page_table[] = {2, 4, 1, 7, 3, 5, 6};
  
  while (fread(&v_addr, sizeof(uint64_t), 1, infile) == 1) {
    // get offset
    uint64_t offset = v_addr & 0x7f;

    // get page number
    uint64_t page_num = v_addr >> PAGE_OFFSET;

    // get frame number
    uint64_t frame_num = page_table[page_num];

    // get physical address (combine frame number and offset)
    uint64_t p_addr = (frame_num << PAGE_OFFSET) | offset;
    
    fwrite(&p_addr, sizeof(uint64_t), 1, outfile);
  }

  fclose(infile);
  fclose(outfile);
  
  return EXIT_SUCCESS;
}