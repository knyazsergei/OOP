#include "stdafx.h"
#include "Rational.h"
#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <stdexcept>
#include <iostream>


CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
//////////////////////////////////////////////////////////////////////////

double CRational::ToDouble()const
{
	return double(m_numerator) / double(m_denominator);
}


//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator+ () const
{
	return *this;
}

CRational const CRational::operator- ()	const
{
	return CRational(-m_numerator, m_denominator);
}


//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
//////////////////////////////////////////////////////////////////////////
CRational operator+(CRational const &rational1, CRational const &rational2)
{
	return (CRational((rational1.GetNumerator() * rational2.GetDenominator())
		 + (rational2.GetNumerator() * rational1.GetDenominator()),
		    rational1.GetDenominator() * rational2.GetDenominator()));
}

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
//////////////////////////////////////////////////////////////////////////
CRational operator -(CRational const &rational1, CRational const &rational2)
{
	return rational1 + -rational2;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator+=(CRational const & rational2)
{
	*this = *this + rational2;
	return *this;
}


//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator-=(CRational const & rational2)
{
	*this = *this - rational2;
	return *this;
}



//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
//////////////////////////////////////////////////////////////////////////
CRational operator*(CRational const & rational1, CRational const & rational2)
{
	return { rational1.GetNumerator() * rational2.GetNumerator(), 
			 rational1.GetDenominator() * rational2.GetDenominator() };
}


//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
//////////////////////////////////////////////////////////////////////////

CRational operator/(CRational const &lhs, CRational const &rhs)
{
	return { lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator() };
}


//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator *= (const CRational & num2)
{
	m_numerator *= num2.GetNumerator();
	m_denominator *= num2.GetDenominator();
	Normalize();
	return *this;
}


//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator /=(CRational const &value)
{
	m_numerator *= value.GetDenominator();
	m_denominator *= value.GetNumerator();
	Normalize();
	return *this;
}



//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////
bool operator == (CRational const & rational1, CRational const & rational2)
{
	return rational1.GetNumerator() == rational2.GetNumerator() &&
		   rational1.GetDenominator() == rational2.GetDenominator();
}

bool operator != (CRational const & rational1, CRational const & rational2)
{
	return rational1.GetNumerator() != rational2.GetNumerator() ||
		rational1.GetDenominator() != rational2.GetDenominator();
}



//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
//////////////////////////////////////////////////////////////////////////
bool const operator < (CRational const &rational1, CRational const &rational2)
{
	return rational1.GetNumerator() * rational2.GetDenominator() < rational2.GetNumerator() * rational1.GetDenominator();
}

bool const operator > (CRational const &rational1, CRational const &rational2)
{
	return rational1.GetNumerator() * rational2.GetDenominator() > rational2.GetNumerator() * rational1.GetDenominator();
}

bool const operator <= (CRational const &rational1, CRational const &rational2)
{
	return rational1 == rational2 || rational1 < rational2;
}

bool const operator >= (CRational const &rational1, CRational const &rational2)
{
	return rational1 == rational2 || rational1 > rational2;
}



//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//////////////////////////////////////////////////////////////////////////

std::istream & operator >> (std::istream & stream, CRational & rational)
{
	int numerator;
	int denominator;

	if ((stream >> numerator) && (stream.get() == '/') && (stream >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		stream.setstate(stream.rdstate() | std::ios_base::failbit);
	}
	return stream;
}




//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//////////////////////////////////////////////////////////////////////////
std::ostream & operator<<(std::ostream & stream, CRational const & rational)
{
	stream << rational.GetNumerator() << "/" << rational.GetDenominator();
	return stream;
}
