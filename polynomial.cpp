#include <algorithm>   // Provides copy function 
#include <climits>     // Provides UINT_MAX 
#include <cmath>     // Provides POW 
#include <cassert>     // Provides assert function 
#include <iostream>		// Provides cout and cin
#include "polynomial.h" 

using namespace std; 

 	polynomial::polynomial( ) 
	{ 
		currArraySize = 4; 
		coeff_ptr = new double [currArraySize]();
		polyDegree=0;
	} 

	polynomial::polynomial(double a0) 
		//The polynomial created has an x^0 term with all other 
		// coefficients zero. 
	{
		currArraySize = 4; 
		coeff_ptr = new double [currArraySize]();
		coeff_ptr[0]=a0;
	
		polyDegree=1;
	}

	polynomial::polynomial(const polynomial& source)  
		//Library facilities used: algorithm
	{
		  coeff_ptr = new double [source.currArraySize];
		  currArraySize = source.currArraySize; 
		  polyDegree = source.polyDegree;
		  copy(source.coeff_ptr, source.coeff_ptr + polyDegree, coeff_ptr);

	}

	// DESTRUCTOR 
	polynomial::~polynomial( )
	{
		delete [] coeff_ptr;
	}


	// MODIFICATION MEMBER FUNCTIONS 
	void polynomial::add_to_coef(double amount, unsigned int k)
	{
    	if(amount!=0 && k>currArraySize)
		{
			reserve(k+1);
			size_t i;
			for (i=polyDegree; i<=k; i++)
			{
				coeff_ptr[i]=0;  //pad the missing values
			}
		  coeff_ptr[k]=coeff_ptr[k]+amount;
		  polyDegree=k+1;
		}
		else if(amount!=0 && k<currArraySize)
		{
			coeff_ptr[k]=coeff_ptr[k]+amount;
			polyDegree=k+1;
		}
	}

	void polynomial::assign_coef(double new_coefficient, unsigned int k)
	{
		if(k>currArraySize)
		{
			reserve(k+1);
			coeff_ptr[k]=new_coefficient;
			size_t i;
			for (i=polyDegree; i<k; i++)
			{
				coeff_ptr[i]=0;  //pad the missing values
			}
		  
		  polyDegree=k+1;
		}
		else if(k>polyDegree)
		{
			coeff_ptr[k]=new_coefficient;
			polyDegree=k+1;
		}

		else
		{
			coeff_ptr[k]=new_coefficient;
			
		}	

	}

	void polynomial::clear( )
	{
		size_t i;
		for (i=0; i<currArraySize; i++)
		{
			  coeff_ptr[i]=0;
	    }
		  polyDegree=0;
	}

	void polynomial::reserve(size_t number)
	{
		// Library facilities used: algorithm 
 
		double *larger_array; 
		if (number == currArraySize) 
			return; // The allocated memory is already the right size. 
		if (number < polyDegree)
			number = polyDegree; // Can’t allocate less than we are using. 

		larger_array = new double[number](); 
		copy(coeff_ptr, coeff_ptr + polyDegree, larger_array); 
		delete [ ] coeff_ptr; 
		coeff_ptr = larger_array; 
		currArraySize = number; 
	}

	polynomial polynomial::derivative( ) const
{
    polynomial dx;
    unsigned int n=next_term(0);
	    
    while(n!=0)
    {
	dx.assign_coef((n)*coefficient(n), n-1);
	n=next_term(n);
    }
    
    return dx;
}

    // MODIFICATION OPERATORS 

	polynomial&  polynomial::operator =(const polynomial& source)    
		// Library facilities used: algorithm 
	{
		double *new_coeff_ptr;
		
		// Check for possible self-assignment:
		if (this == &source) 
			return *this;
			

		 // If needed, allocate an array with a different size:
		if (currArraySize != source.currArraySize) 
		{ 
			new_coeff_ptr = new double[(source.currArraySize)](); 
			delete [ ] coeff_ptr; 
			coeff_ptr = new_coeff_ptr; 
			currArraySize = (source.currArraySize); 
		}
		// Copy the data from the source array:
		polyDegree=source.polyDegree;
		copy(source.coeff_ptr, source.coeff_ptr + (polyDegree), coeff_ptr);
		return *this;
	} 

	// CONSTANT MEMBER FUNCTIONS 
	double polynomial::coefficient(unsigned int k) const
	{
		assert(k <= currArraySize);

		double coeff=coeff_ptr[k];
		return coeff;
	}
	unsigned int polynomial::degree( ) const
	{
		int deg;
		if(currArraySize==0) 
		{
			deg=0;
		}
		else
		{
			size_t i;
			i=polyDegree;
			while(coeff_ptr[i]==0 && i>-1)
			{
				  i--;
				
			}
			deg=i-1;
		}
		
		return deg;
	}

	unsigned int polynomial::next_term(unsigned int k) const
	{
			unsigned int exponent=0;
			unsigned int i=k+1;
			
			while(coeff_ptr[i]==0 )
			{
				  i++;
				if(i>=polyDegree)
				{
				 exponent=UINT_MAX;
				}
				else 
				{
				 exponent=i;			
				}	
				
			}

	  return exponent;
	}

		unsigned int polynomial::previous_term(unsigned int k) const
	{
			
		unsigned int exponent=0;
		unsigned int i=k+1;
			
    if(exponent==0)
	return UINT_MAX;
    
    do
    {
	if(i>degree())
	    return degree();
	i--;
	if(coefficient(i)!=0.0)
	    return i;
    }while(i>0);
	    
    return UINT_MAX;

	}

	// CONSTANT OPERATORS 
	double polynomial::eval(double x) const
	{
		double answer=0;
		size_t i;
		for (i=0; i<=polyDegree-1; i++)
		  {
			  double s;
			  s=(double)i; 
			  answer=answer+coeff_ptr[i]*(pow(x,s));
		  }
		return answer;
	}
	double polynomial::operator( ) (double x) const
	 { 
	  return eval(x);
	 } 


	// FRIEND ARITHMETIC OPERATORS polynomial 

	polynomial operator +(const polynomial& p1, const polynomial& p2)
	{
		size_t j=p1.degree( );
		size_t q= p2.degree( );
		polynomial answer;

		if(j>=q)
		{
			answer.reserve(j+1);
			size_t i;
			for (i=0; i<=j; i++)
			{
				answer.add_to_coef((p1.coefficient(i)+p2.coefficient(i)),(i));
			}
		}
		else
		{
			answer.reserve(q+1);
			size_t i;
			for (i=0; i<=q; i++)
			{
				answer.add_to_coef((p1.coefficient(i)+p2.coefficient(i)),(i));
			}
		}
		return answer;
	}


	polynomial operator -(const polynomial& p1, const polynomial& p2)
	{
		size_t j=p1.degree( );
		size_t q= p2.degree( );
		polynomial answer;

		if(j>=q)
		{
			answer.reserve(j+1);
			size_t i;
			for (i=0; i<=j; i++)
			{
				answer.add_to_coef((p1.coefficient(i)-p2.coefficient(i)),(i));
			}
		}
		else
		{
			answer.reserve(q+1);
			size_t i;
			for (i=0; i<=q; i++)
			{
				answer.add_to_coef((p1.coefficient(i)-p2.coefficient(i)),(i));
			}
		}
		return answer;
	}

	polynomial operator *(const polynomial& p1, const polynomial& p2)
	{
		polynomial answer;
		size_t k=p1.degree( );
		size_t q=p2.degree( );
		answer.reserve((k+q)+2);
		
		size_t i;
		size_t j;

		for (i=0; i<=k; i++)
		  {
			  for (j=0; j<=q; j++)
				{

					answer.add_to_coef((p1.coefficient(i)*p2.coefficient(j)),(i+j));
					
				}
		}
		return answer;

	}

	ostream& operator << (ostream& out, const polynomial& p)
	{
	    unsigned int k = p.degree( );
	    double number;
	    
	    do
	    {
		// Get the coefficient:
		number = p.coefficient(k);

		if(k==p.degree() && number<0)
		    out << "-";
		else if(number<0)
		    out << " - ";
		else if(number>0 && k!=p.degree())
		    out << " + ";

		number = fabs(number);

		if(number!=1.0 || k==0)
		    out << number;

		if(k>1)
		    out << "x^" << k;
		if(k==1)
		    out << "x";

		k = p.previous_term(k);

	    }   while (k != UINT_MAX);

	    return out;     //return the output stream
	}

