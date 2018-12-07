#pragma once
#include <iostream>

using namespace std;

typedef unsigned int uInr;

class TBitField
{
private:
  int  bitLen; // длина битового поля - макс. к-во битов
  uInr *pMem; // память для представления битового поля
  int  memLen; // к-во эл-тов Мем для представления бит.поля

  int   GetMemIndex(const int n) const; // индекс в pМем для бита n
  uInr GetMemMask (const int n) const; // битовая маска для бита n
public:
  TBitField(int len); 
  TBitField(const TBitField &bf);
  ~TBitField();

  int GetLength(void) const;      // получить длину (к-во битов)
  void SetBit(const int n);       // установить бит
  void ClrBit(const int n);       // очистить бит
  int  GetBit(const int n) const; // получить значение бита

  int operator==(const TBitField &bf) const; // сравнение
  int operator!=(const TBitField &bf) const; // сравнение
  TBitField& operator=(const TBitField &bf); // присваивание
  TBitField  operator|(const TBitField &bf); // операция "или"
  TBitField  operator&(const TBitField &bf); // операция "и"
  TBitField  operator~(void);                // отрицание

  friend istream &operator>>(istream &istr, TBitField &bf);   
  friend ostream &operator<<(ostream &ostr, const TBitField &bf);
};//TBitField

