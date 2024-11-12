#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PAGES 32
#define LOG2(X) ((unsigned) (8 * sizeof (unsigned long) - __builtin_clzll((X)) - 1))

typedef struct pte {
  unsigned long logical;
  unsigned long physical;
} PageTableEntry;

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Infile and outfile are the only parameters for this program.");
    return EXIT_FAILURE;
  }

  FILE *infile;
  FILE *outfile;
  unsigned long addrBuf[MAX_PAGES] = {0};

  memset(addrBuf, 0, MAX_PAGES);

  infile = fopen(argv[1], "rb");

  if (infile == NULL) {
    fprintf(stderr, "Infile (%s) could not be opened. Exiting...", argv[1]);
    return EXIT_FAILURE;
  }

  outfile = fopen(argv[2], "wb");

  if (outfile == NULL) {
    fprintf(stderr, "Outfile (%s) could not be opened. Exiting...", argv[2]);
    return EXIT_FAILURE;
  }

  // First frame is reserved for the OS
  PageTableEntry pageTable[] = {
    { 0, 2 },
    { 1, 4 },
    { 2, 1 },
    { 3, 7 },
    { 4, 3 },
    { 5, 5 },
    { 6, 6 }
  };
  
  while (fread(addrBuf, sizeof(unsigned long), 1, infile)) {
    fwrite(addrBuf, sizeof(unsigned long), 1, outfile);
  }  

  fclose(infile);
  fclose(outfile);
  
  return EXIT_SUCCESS;
}