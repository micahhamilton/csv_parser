#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "utils.h"

int main(int argc, char *argv[])
{
  FILE *fp;
  char *prog = argv[0];
  char s[MAXLINE], *d, *f;
  char *sp;
  int i = 0, j = 0, l;
  alarmdata data;
  alarmdata *dataptr = &data;

  /* test for file name */
  if (argc == 1) {
    fprintf(stderr, "%s: No file!\n", prog);
    exit(1);
  } else {
    /* while there are still file names in the list, process them */
    while (--argc > 0) {
      /* test for valid file name */
      if ((fp = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "%s: Can't open %s\n", prog, *argv);
        exit(1);
      } else {
        /* while there are lines of text in the current file, process them */
        while (fgets(s, MAXLINE, fp)) {
          /***************************************************/
          /* this is where processing indivdual lines begins */
          /***************************************************/
          d = trim(s);
          parsedata(d, dataptr);
          printf("Tagname: %s\n", dataptr->tagname);
          printf("Description: %s\n", dataptr->desc);
          printf("Notes: %s\n", dataptr->notes);
          printf("Alarm: %s\n", dataptr->alarm);
          printf("Count: %ld\n", dataptr->count);
          printf("Percent: %0.2f\n", dataptr->percent);
          printf("Accum %%: %0.2f\n", dataptr->accumPercent);
          printf("Priority: %d\n", dataptr->alarmPriority);
          printf("Unit: %d\n", dataptr->unit);
          putchar('\n');
        }
        fclose(fp);
      }
    }
  }
  return 0;
}
