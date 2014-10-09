#include <math.h>

struct compl
{
	double Re, Im;

	compl( const double a, const double b ) : Re(a), Im(b)
	{}

	compl operator+( const compl &Z ) const
	{
		return compl(Re + Z.Re, Im + Z.Im);
	}
	compl operator*( const compl &Z ) const
	{
		return compl(Re * Z.Re - Im * Z.Im, Re * Z.Im + Z.Re * Im);
	}
	float operator!() const
	{
		return sqrt(Re * Re + Im * Im);
	}

	int Julia(const compl &C)
	{
		int n = 0;
		for (; !(*this) < 2 && n < 254; n++)
			(*this) = (*this) * (*this) + C;

		return n;
	}
};