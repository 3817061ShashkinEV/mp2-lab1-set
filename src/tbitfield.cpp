#include "tbitfield.h"
#include <string>

TBitField::TBitField(int len)
{
  if (len <= 0) throw - 1;
  bitLen = len;
  memLen = (bitLen + 31) >> 5;
  pMem = new uInr[memLen];
  for (int i = 0; i < memLen; i++)
    pMem[i] = 0;
}
// ---------------------------------------------------------------------------
TBitField::TBitField(const TBitField &bf)
{
  bitLen = bf.bitLen;
  memLen = bf.memLen;
  pMem = new uInr [memLen];
  for (int i = 0; i < memLen; i++)
    pMem[i] = bf.pMem[i];
}
// ---------------------------------------------------------------------------
TBitField::~TBitField()
{
  delete [] pMem;
}
// ---------------------------------------------------------------------------
int TBitField::GetMemIndex(const int n) const
{
  return n >> 5;
}
// ---------------------------------------------------------------------------
uInr TBitField::GetMemMask(const int n) const
{
  return 1 << (n & 31);
}
// ---------------------------------------------------------------------------
int TBitField::GetLength(void) const
{
  return bitLen;
}
// ---------------------------------------------------------------------------
void TBitField::SetBit(const int n)
{
  if (n < 0 || n >= bitLen) throw "Mem error";
  pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}
// ---------------------------------------------------------------------------
void TBitField::ClrBit(const int n)
{
  if (n < 0 || n >= bitLen) throw "Mem error";
  pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}
// ---------------------------------------------------------------------------
int TBitField::GetBit(const int n) const
{
  if (n < 0 || n >= bitLen) throw "Mem error";
  return pMem[GetMemIndex(n)] & GetMemMask(n);
}
// ---------------------------------------------------------------------------
TBitField& TBitField::operator=(const TBitField &bf)
{
  if (this != &bf)
  {
    delete[] pMem;
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new uInr [memLen];
    for (int i = 0; i < memLen; i++)
      pMem[i] = bf.pMem[i];
  }
  return *this;
}
// ---------------------------------------------------------------------------
int TBitField::operator==(const TBitField &bf) const
{
  int res = 1;
  if (bitLen != bf.bitLen)
    return 0;
  else
    for (int i = 0; i < memLen; i++)
      if (pMem[i] != bf.pMem[i])
      {
        res=0;
        break;
      }
  return res;
}
// ---------------------------------------------------------------------------
int TBitField::operator!=(const TBitField &bf) const
{
  return !(*this == bf);
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator|(const TBitField &bf)
{
  int len = bitLen;
  if (bf.bitLen > len)
    len = bf.bitLen;
  TBitField tmp(len);
  for (int i = 0; i < memLen; i++)
    tmp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.memLen; i++)
    tmp.pMem[i] = tmp.pMem[i] | bf.pMem[i];
  return tmp;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator&(const TBitField &bf)
{
  int len = bitLen;
  if (bf.bitLen > len)
    len = bf.bitLen;
  TBitField tmp(len);
  for (int i = 0; i < memLen; i++)
    tmp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.memLen; i++)
    tmp.pMem[i] = tmp.pMem[i] & bf.pMem[i];
  return tmp;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator~(void)
{
  TBitField tmp=*this;
  for (int i = 0; i < bitLen; i++)
  {
    if (tmp.GetBit(i))
      tmp.ClrBit(i);
    else
      tmp.SetBit(i);
  }
  return tmp;
}
// ---------------------------------------------------------------------------
istream &operator>>(istream &istr, TBitField &bf)
{
  string tmp;
  istr >> tmp;
  if (tmp.size() != bf.GetLength())
    throw "Incorrect length";
  for (int i = 0; i < bf.bitLen; i++)
  {
    if (tmp[i] == '0')
      bf.ClrBit(i);
    else if (tmp[i] == '1')
      bf.SetBit(i);
    else
      throw "Incorrect input";
  }
  return istr;
}
// ---------------------------------------------------------------------------
ostream &operator<<(ostream &ostr, const TBitField &bf)
{
  for (int i = 0; i < bf.bitLen; i++)
	  ostr << bf.GetBit(i);
  return ostr;
}
