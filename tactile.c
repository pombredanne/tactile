
/* (c) 2011-02-17 Thomas Perl <thp.io>; public domain */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define VIBRA "/sys/class/leds/twl4030:vibrator/brightness"

typedef struct {
  const char *name;
  useconds_t delay;
  unsigned char pattern[128];
  int count;
} Pattern;

static Pattern patterns[] = {
  {"button", 70, {90, 20}, 2},
  {"appmenu", 40, {40, 70, 20, 50, 40, 20}, 6},
  {NULL},
};

int set(unsigned char value, useconds_t delay)
{
  FILE *fp;

  if ((fp = fopen(VIBRA, "w")) != NULL)
    {
      fprintf(fp, "%d\n", (int)value);
      fclose(fp);
      usleep(1000*delay);
      return 0;
    }

  return 1;
}

int play(Pattern *p)
{
  int i = 0;

  while (i < p->count)
    set(p->pattern[i++], p->delay);

  return set(0, 0);
}

int main(int argc, char **argv)
{
  Pattern *p;

  if (argc == 2)
    for (p = patterns; p->name; p++)
      if (!strcmp(p->name, argv[1]))
        return play(p);

  return 1;
}

