#pragma once
#include <deque>
#include <cassert>
#include <intsafe.h>
#include <iostream>



#define uint_max static_cast<UINT64>(std::numeric_limits<UINT32>::max())

#define BOOST_FACTOR 10




class bigInt{

public:	

	bigInt ():negative(false),base(1,0){

	}


	explicit bigInt(const int i_num){ 
		
		base.insert(base.begin(),abs(i_num)); 
		negative = i_num < 0;
	
	}


	bigInt(const UINT64 i_num){

		UINT64 val = i_num;

		UINT64 reminder= val % (uint_max + 1);

		val/=(uint_max + 1);

		base.push_back(static_cast<UINT32>(reminder));

		while (val > 0)
		{
			reminder = val % (uint_max + 1);
			
			val/= (uint_max + 1);
			
			base.push_back(static_cast<UINT32>(reminder));
		}
		negative = false;

	}


	explicit bigInt(const std::string i_string);

	friend bigInt abs(const bigInt&);

	

	friend bigInt pow(const bigInt& ,const bigInt& );
	
	friend std::ostream& operator<<(std::ostream& i_os,bigInt i_value);


	inline bigInt& operator<<=(const UINT32);

	inline bigInt& operator>>=(const UINT32);

	
	bigInt& operator&=(const bigInt&);


	bigInt& operator|=(const bigInt&);

	bigInt& operator^=(const bigInt&);


	bigInt operator!() const{

		bigInt not = *this;

		for (UINT32 i=0; i<this->base.size();++i)
		{
			not.base.at(i)=!(not.base.at(i));
		}
		
		return not;
	}


	 bigInt& operator+=(const bigInt& );

	 bigInt& operator*=(const bigInt& );

	 bigInt& operator-=(const bigInt& );

	 bigInt& operator/=(const bigInt& );
	
	 bigInt& operator%=(const bigInt& );


	 bool operator<(const bigInt& ) const;

	 bool operator>(const bigInt& ) const;

	 bool operator<=(const bigInt& ) const;

	 bool operator>=(const bigInt& ) const;

	
	 bool operator==(const bigInt& ) const;

	 bool operator!=(const bigInt& ) const;


	bigInt& operator++(){

		*this+=1;
		return *this;

	}

	bigInt operator++(int){

		bigInt temp = *this;

		*this+=1;

		return temp;

	}

	bigInt operator-() const{

		bigInt inv_value = *this;

		inv_value.negative = inv_value.negative ^ true; 

		return inv_value;
	}

private :

	std::deque<UINT32> base;
	bool negative;
	

	const UINT32 Appoggio_Sum(const UINT32 i_val1,const UINT32 i_val2,const UINT32 resto,UINT32& sum);

	const UINT32 Appoggio_Diff(const UINT32 min,const UINT32 max,const UINT32 prestito,UINT32& diff);


	int MinHelper(const bigInt& r_value) const; // 1 true, 0 false, 2 equal

	bool doOperation(void (bigInt::*i_op)(const bigInt*,const bigInt*),const bigInt& i_value);

	void doSum(const bigInt* max,const bigInt* min);

	void doDiff(const bigInt* max,const bigInt* min);

	void doProduct(const bigInt* max,const bigInt* min);
	
	bigInt doDivision(const bigInt& i_val2,bigInt& o_remainder,const bool return_quotient = true) const;
	
	friend void ResizeBigInteger(bigInt& i_value);

	bigInt fitBigIntegerZero(const bigInt& i_value);

	bigInt DivisionForPrint(const bigInt& dividend,const bigInt& divisore,bigInt& o_remainder);

	
};

bigInt operator+(const bigInt&, const bigInt&);

bigInt operator-(const bigInt&, const bigInt&);

bigInt operator*(const bigInt&, const bigInt&);

bigInt operator/(const bigInt&, const bigInt&);

bigInt operator%(const bigInt&, const bigInt&);

bigInt operator&(const bigInt&, const bigInt&);

bigInt operator|(const bigInt&, const bigInt&);

bigInt operator^(const bigInt&, const bigInt&);