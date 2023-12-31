/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
    union {
        unsigned u;
        float f;
    } a;
    a.u = u;
    return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
    union {
        unsigned u;
        float f;
    } a;
    a.f = f;
    return a.u;
}
//2
long test_copyLSB(long x)
{
  return (x & 0x1L) ? -1 : 0;
}
long test_dividePower2(long x, long n)
{
    long p2n = 1L<<n;
    return x/p2n;
}
long test_getByte(long x, long n)
{
    unsigned char byte = 0;
    switch(n) {
    case 0:
      byte = x;
      break;
    case 1:
      byte = x >> 8;
      break;
    case 2:
      byte = x >> 16;
      break;
    case 3:
      byte = x >> 24;
      break;
    case 4:
      byte = x >> 32;
      break;
    case 5:
      byte = x >> 40;
      break;
    case 6:
      byte = x >> 48;
      break;
    case 7:
      byte = x >> 56;
      break;
    }
    return (long) (unsigned) byte;
}
long test_anyOddBit(long x) {
  int i;
  for (i = 1; i < 64; i+=2)
      if (x & (1L<<i))
          return 1L;
  return 0L;
}
//3
long test_conditional(long x, long y, long z)
{
  return x?y:z;
}
long test_subtractionOK(long x, long y)
{
  __int128 ldiff = (__int128) x - y;
  return (long) (ldiff == (long) ldiff);
}
long test_bitMask(long highbit, long lowbit)
{
  long result = 0L;
  int i;
  for (i = lowbit; i <= highbit; i++)
    result |= 1L << i;
  return result;
}
long test_rotateLeft(long x, long n) {
  unsigned long u = (unsigned long) x;
  long i;
  for (i = 0; i < n; i++) {
      unsigned long msb = u >> 63;
      unsigned long rest = u << 1;
      u = rest | msb;
  }
  return (long) u;
}
//4
long test_trueFiveEighths(long x)
{
  return (long) (((__int128) x * 5)/8);
}
long test_bitCount(long x) {
  long result = 0;
  long i;
  for (i = 0; i < 64; i++)
    result += (x >> i) & 0x1;
  return result;
}
long test_bitParity(long x) {
  long result = 0;
  int i;
  for (i = 0; i < 64; i++)
    result ^= (x >> i) & 0x1L;
  return result;
}
