#ifndef MAIN_CORYALLEN_POLYNOMIAL_H 
#define MAIN_CORYALLEN_POLYNOMIAL_H 

#include <cstdlib>  // Provides size_t  


class polynomial 
{ 
public: 

	// TYPEDEFS and MEMBER CONSTANTS 
	typedef std::size_t size_type; 

	// FRIEND ARITHMETIC OPERATORS polynomial 
	friend polynomial operator +(const polynomial& p1, const polynomial& p2); 
	//POSTCONDITION: return-value is a polynomial with each coefficient equal to the sum of the coefficients 
    //of p1 & p2 for any given exponent.

	friend polynomial operator -(const polynomial& p1, const polynomial& p2);
    //POSTCONDITION: return-value is a polynomial with each coefficient equal to the difference of the 
	//coefficients of p1 & p2 for any given exponent.

	friend polynomial operator *(const polynomial& p1, const polynomial& p2);
    //POSTCONDITION: Each term of p1 has been multiplied by each term of p2.

	friend std::ostream& operator << (std::ostream& out, const polynomial& p);
	//POSTCONDITION: The polynomial has been printed to ostream out.


	// CONSTRUCTORS
	polynomial( );
	polynomial(double a0); //The polynomial created has an x^0 term with all other coefficients zero. 
	polynomial(const polynomial& source);  //Prototype for the copy consructor

	// DESTRUCTOR 
	~polynomial( );

	// MODIFICATION MEMBER FUNCTIONS 
	void add_to_coef(double amount, unsigned int k);
	 //PRECONDITION: exponent <= MAX_EX.
    //POSTCONDITION: Adds the given amount to the coefficient of the specified exponent.


	void assign_coef(double new_coefficient, unsigned int k);
	//PRECONDITION: exponent <= MAX_EX.
    //POSTCONDITION: Sets the coefficient for the specified exponent.

	void clear( );
	//POSTCONDITION: All coefficients of this polynomial are set to zero.

	void reserve(size_t number);
	//POSTCONDITION: The size of the array is assured

	// MODIFICATION OPERATORS 
	polynomial& operator =(const polynomial& source);//Prototype for the overload operator =.
	  // Postcondition:  The polynomial that activated this function has the same items and capacity as source.
    polynomial& operator =(double a0); 



	// CONSTANT MEMBER FUNCTIONS 
	double coefficient(unsigned int k) const;
	//POSTCONDITION: Returns coefficient at specified exponent of this polynomial.

	unsigned int degree( ) const;
	 //POSTCONDITION: The function returns the value of the largest exponent with a non-zero coefficient. 

	polynomial derivative( ) const;
	 //POSTCONDITION: The return value is the first derivative of this polynomial.

	unsigned int next_term(unsigned int k) const;
	unsigned int previous_term(unsigned int k) const;

	// CONSTANT OPERATORS 
	double eval(double x) const;
	//POSTCONDITION: The return value is the value of this polynomial with the given value for the variable x.


	double operator( ) (double x) const;


private: 
	size_type currArraySize; //Current capacity of the Array
	size_type polyDegree;  //used
	double *coeff_ptr;

};
  
#endif 
