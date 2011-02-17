
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
  {"button", 15, {200}, 1},
  {"appmenu", 40, {40, 70, 20, 50, 40, 20}, 6},
  {"appmenu-out", 40, {30, 45, 30, 35, 30, 20}, 6},
  {"dialog", 30, {0, 60, 0, 70, 0, 80}, 6},
  {"dialog-out", 30, {0, 60, 0, 50, 0, 30}, 6},
  {"scroll-stop", 10, {120}, 1},
  {"slider-change", 20, {50, 40, 30, 20, 30, 40}, 6},
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

