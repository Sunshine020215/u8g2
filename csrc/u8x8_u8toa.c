/*

  u8x8_u8toa.c

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
  
*/


#include "u8x8.h"

static const unsigned char u8x8_u8toa_tab[3]  = { 100, 10, 1 } ;
const char *u8x8_u8toap(char * dest, uint8_t v)
{
  uint8_t pos;
  uint8_t d;
  uint8_t c;
  for( pos = 0; pos < 3; pos++ )
  {
      d = '0';
      c = *(u8x8_u8toa_tab+pos);
      while( v >= c )
      {
	v -= c;
	d++;
      }
      dest[pos] = d;
  }  
  dest[3] = '\0';
  return dest;
}

/* v = value, d = number of digits */
const char *u8x8_u8toa(uint8_t v, uint8_t d)
{
  static char buf[4];
  d = 3-d;
  return u8x8_u8toap(buf, v) + d;
}

const char *u8x8_s8toa(int8_t v, uint8_t d)
{
  static char buf[5];
  uint16_t u = v;
  buf[0] = '+';
  if ( v < 0 )
  {
    buf[0] = '-';
    u = -v;
  }
  u8x8_u8toap(buf+1, (uint8_t)u);
  if ( d == 1 )
  {
    buf[1] = buf[3];
    buf[2] = '\0';
  }
  else if ( d == 2 )
  {
    buf[1] = buf[2];
    buf[2] = buf[3];
    buf[3] = '\0';
  }
  return buf;
}
 
const char *u8x8_u8tox(uint8_t v, uint8_t d)
{
  const char hexdigit[]="0123456789ABCDEF";
  static char buf[3];
  if ( d == 1 )
  {
    buf[0] = hexdigit[v & 0xF];
    buf[1] = '\0';
  }
  else if ( d == 2 )
  {
    buf[0] = hexdigit[v >> 4 & 0xF];
    buf[1] = hexdigit[v & 0xF];
    buf[2] = '\0';
  }
  return buf;
}
