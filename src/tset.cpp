#include "tset.h"

TSet::TSet(int mp) : bitField(mp)
{
	maxPower = mp;
}
// ---------------------------------------------------------------------------
TSet::TSet(const TSet &s) : bitField(s.bitField)
{
	maxPower = s.maxPower;
	bitField = s.bitField;
}
// ---------------------------------------------------------------------------
TSet::TSet(const TBitField &bf) : bitField(bf)
{
	maxPower = bf.GetLength();
	bitField = bf;
}
// ---------------------------------------------------------------------------
TSet::operator TBitField()
{
	TBitField tmp(bitField);
	return tmp;
}
// ---------------------------------------------------------------------------
int TSet::GetMaxPower(void) const
{
	return maxPower;
}
// ---------------------------------------------------------------------------
int TSet::IsMember(const int elem) const
{
	if (elem < 0 || elem >= maxPower) throw "Mem error";
	return bitField.GetBit(elem);
}
// ---------------------------------------------------------------------------
void TSet::InsElem(const int elem)
{
	if (elem < 0 || elem >= maxPower) throw "Mem error";
	bitField.SetBit(elem);
}
// ---------------------------------------------------------------------------
void TSet::DelElem(const int elem)
{
	if (elem < 0 || elem >= maxPower) throw "Mem error";
	bitField.ClrBit(elem);
}
// ---------------------------------------------------------------------------
TSet& TSet::operator=(const TSet &s)
{
	if (this != &s)
	{
		maxPower = s.maxPower;
		bitField = s.bitField;
	}
	return *this;
}
// ---------------------------------------------------------------------------
int TSet::operator==(const TSet &s) const
{
	return (bitField == s.bitField);
}
// ---------------------------------------------------------------------------
int TSet::operator!=(const TSet &s) const
{
	return !(bitField == s.bitField);
}
// ---------------------------------------------------------------------------
TSet TSet::operator+(const TSet &s)
{
	int len = maxPower;
	if (s.maxPower > len)
		len = s.maxPower;
	TSet tmp(len);
	tmp.bitField = bitField | s.bitField;
	return tmp;
}
// ---------------------------------------------------------------------------
TSet TSet::operator+(const int elem)
{
	if (elem < 0 || elem >= maxPower) throw "Mem error";
	TSet tmp(*this);
	tmp.InsElem(elem);
	return tmp;
}
// ---------------------------------------------------------------------------
TSet TSet::operator-(const int elem)
{
	if (elem < 0 || elem >= maxPower) throw "Mem error";
	TSet tmp(*this);
	tmp.bitField.ClrBit(elem);
	return tmp;
}
// ---------------------------------------------------------------------------
TSet TSet::operator*(const TSet &s)
{
	int len = maxPower;
	if (s.maxPower>len)
		len = s.maxPower;
	TSet tmp(len);
	tmp.bitField = bitField & s.bitField;
	return tmp;
}
// ---------------------------------------------------------------------------
TSet TSet::operator~(void)
{
	TSet tmp(*this);
	tmp.bitField = ~tmp.bitField;
	return tmp;
}
// ---------------------------------------------------------------------------
istream &operator>>(istream &istr, TSet &s)
{
	int tmp;
	char q;
	do { istr >> q; } while (q != '{');
	do {
		istr >> tmp;
		s.InsElem(tmp);
		do { istr >> q; } while ((q != ',') && (q != '}'));
	} while (q != '}');
	return istr;
}
// ---------------------------------------------------------------------------
ostream& operator<<(ostream &ostr, const TSet &s)
{
	char q = ' ';
	ostr << '{';
	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		if (s.IsMember(i))
		{
			ostr << q << i;
			q = ', ';
		}
	}
	ostr << '}\n';
	return ostr;
}
