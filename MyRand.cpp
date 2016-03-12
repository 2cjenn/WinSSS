#include "stdafx.h"
#include "myrand.h"
#include <string.h>  // some compilers require <mem.h> instead
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

MyRand::MyRand(long int seed) {
  RandomInit(seed);}

MyRand::~MyRand(void)
{
}

// returns a random number between 0 and 1:
double MyRand::Random() {
  unsigned long x;
  // generate next random number
  x = randbuffer[p1] = _lrotl(randbuffer[p2], R1) + _lrotl(randbuffer[p1], R2);
  // rotate list pointers
  if (--p1 < 0) p1 = KK - 1;
  if (--p2 < 0) p2 = KK - 1;

  // fast conversion to float:
  union {
    double randp1;
    unsigned long randbits[2];};
  randbits[0] = x << 20;
  randbits[1] = (x >> 12) | 0x3FF00000;
  return randp1 - 1.0;}


// returns integer random number in desired interval:
int MyRand::IRandom(int min, int max) {
  int iinterval = max - min + 1;
  if (iinterval <= 0) return -0x80000000; // error
  int i = (int)iinterval * Random(); // truncate
  if (i >= iinterval) i = iinterval-1;
  return min + i;}
  

void MyRand::RandomInit (long int seed) {
  // this function initializes the random number generator.
  int i;
  unsigned long s = seed;

  // make random numbers and put them into the buffer
  for (i=0; i<KK; i++) {
    s = s * 2891336453 + 1;
    randbuffer[i] = s;}

  // check that the right data formats are used by compiler:
  union {
    double randp1;
    unsigned long randbits[2];};
  randp1 = 1.5;
  assert(randbits[1]==0x3FF80000); // check that IEEE double precision float format used

  // initialize pointers to circular buffer
  p1 = 0;  p2 = JJ;

  // randomize some more
  for (i=0; i<9; i++) Random();
}

