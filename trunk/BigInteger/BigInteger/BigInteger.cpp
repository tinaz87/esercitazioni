#include "BigInteger.h"


bigInt::bigInt(const std::string i_string){

	negative = false;
	if (i_string.at(0) == '-')
	{
		negative = true;
	}

	bigInt input_base = 10;
	bigInt support;
	support.base.pop_back();

	UINT32 exp = 0;

	int string_length =  i_string.length() -1;

	for(UINT32 i=0;i<i_string.length() ;++i){

		
		if (i_string.at(i) != '-')
		{		
			bigInt num(i_string.at(string_length) - 48);
			support += num*pow(input_base, (i-exp) );
			--string_length;
			
		}else{

			exp = 1;

		}


	}


	base = support.base;

}

bigInt pow(const bigInt& i_base,const bigInt& i_exponent){

	if (i_exponent.negative)
	{

		return 0;
	}

	if (i_exponent == 0)
	{

		return 1;
	}

	if (i_exponent == 1)
	{

		return i_base;
	}

	bigInt power = i_base;


	for(bigInt i = 0;i < i_exponent-1; ++i ){

		power *=i_base; 
	}

	/*if ( i_base.negative && i_exponent%2==0)
	{
		power.negative = false;
	}*/

	return power;

}

bigInt abs(const bigInt& i_value) {

	bigInt temp;
	if (i_value.negative)
	{
		temp = i_value;
		temp.negative = false;
		return temp;
	}else
		return i_value;

}



bigInt operator*(const bigInt&  i_val1,const bigInt&  i_val2){

	bigInt product = i_val1;

	product*=i_val2;

	return product;

}

bigInt operator/(const bigInt&  i_val1,const bigInt&  i_val2){


	bigInt quotient = i_val1;

	quotient/=i_val2;

	return quotient;

}

bigInt operator+(const bigInt&  i_val1,const bigInt&  i_val2){

	bigInt sum = i_val1;

	
	sum+=i_val2;

	return sum;

}

bigInt operator-(const bigInt&  i_val1,const bigInt&  i_val2){

	bigInt diff = i_val1;

	diff-=i_val2;

	return diff;

}

bigInt operator%(const bigInt&  i_val1,const bigInt&  i_val2){

	bigInt mod = i_val1;

	mod%=i_val2;

	return mod;

}

bigInt operator&(const bigInt& i_val1, const bigInt& i_val2){

	bigInt and_val = i_val1;

	and_val&=i_val2;

	return and_val;


}

bigInt operator|(const bigInt& i_val1, const bigInt& i_val2){

	bigInt or_val = i_val1;

	or_val|=i_val2;

	return or_val;

}

bigInt operator^(const bigInt& i_val1, const bigInt& i_val2){

	bigInt xor_val = i_val1;

	xor_val^=i_val2;

	return xor_val;

}




bigInt operator<<(const bigInt&  i_val,const UINT32&  shift_value){


	bigInt l_shift = i_val;

	l_shift<<=shift_value;

	return l_shift;
}

bigInt operator>>(const bigInt&  i_val,const UINT32&  shift_value){


	bigInt r_shift = i_val;

	r_shift>>=shift_value;

	return r_shift;
}




void ResizeBigInteger(bigInt& i_value){

	UINT32 index_zero = 0;
	for (UINT32 i = 1 ;i<i_value.base.size();++i)
	{
		if( i_value.base.at(i) != 0 )
			index_zero = i;
	}


	if (index_zero + 1 != i_value.base.size())
	{

		std::deque<UINT32> temp;

		for(UINT32 i = 0;i < index_zero+1  ;++i){


			temp.push_back(i_value.base.at(i));

		}

		i_value.base = temp;
	}



}

bigInt bigInt::fitBigIntegerZero(const bigInt& i_value){

	bigInt temp = i_value;

	while(this->base.size()<i_value.base.size()){
		this->base.push_back(0);
	}

	while( temp.base.size() < (this->base.size()) ){

		temp.base.push_back(0);
	}

	return temp;
}

void bigInt::doDiff(const bigInt* max,const bigInt* min){

	UINT32 size_val_max=max->base.size();
	UINT32 size_val_min=min->base.size();

	UINT32 prestito = 0;
	UINT32 val_pre = 0;
	UINT32 diff = 0;

	bigInt difference;
	bigInt upper = *max;
	
	difference.base.pop_back();

	for (UINT32 i=0;i<=size_val_max;++i)
	{
		if( i< size_val_min){

			if (min->base.at(i) > max->base.at(i)) 
			{
				int index = i+1;
				
				while(upper.base.at(index)==0){

					upper.base.at(index) = uint_max;

					++index;

				}
				
				upper.base.at(index) -= 1; 

				prestito = 1;

			}else
				prestito = 0;



			val_pre = Appoggio_Diff(min->base.at(i),upper.base.at(i),prestito,diff);

			difference.base.push_back( diff);

		}else{

			if(i < size_val_max){

				val_pre = Appoggio_Diff(0,upper.base.at(i),0,diff);
				difference.base.push_back( diff);

			}else{


				ResizeBigInteger(difference);

			}

		}
	}


	*this = difference;

}

void bigInt::doSum(const bigInt* max,const bigInt* min){

	int size_val_max= max->base.size();	/*limite massimo*/
	int size_val_min= min->base.size();

	int resto = 0;
	UINT32 sum = 0;

	for ( int i = 0 ;i<=size_val_max;++i) {

		if(i < size_val_min){

			resto = Appoggio_Sum(min->base[i],max->base[i],resto,sum);

			this->base[i] = sum;

		}else{

			if(i < size_val_max){

				resto = Appoggio_Sum(0,max->base[i],resto,sum);

				if(this == min){

					this->base.push_back(sum);

				}else{

					this->base[i] = sum;

				}
			}else{

				if( resto ) 
					this->base.push_back(resto);
			}

		}

	}

}

void bigInt::doProduct(const bigInt* max,const bigInt* min){


	UINT32 size_val_max= max->base.size();	
	UINT32 size_val_min= min->base.size();


	bigInt product;

	std::deque<std::deque<UINT32>> temp_product;

	UINT64 temp=0;
	

	for (UINT32 i = 0; i < size_val_min; ++i)
	{
		UINT64 carry = 0;
		
		UINT64 val1= min->base.at(i);
		
		bigInt temp_pro;
		
		std::deque<UINT32> vect;

		for (UINT32 k=0;k<i;++k)
		{
			vect.push_back(0);
		}

		temp_pro.base = vect;

		for(UINT32 j = 0; j<size_val_max;++j){


			temp = val1 * static_cast<UINT64>(max->base.at(j)) + carry;

			carry = temp / ( static_cast<UINT64>(uint_max) + 1 ) ;


			temp_pro.base.push_back( static_cast<UINT32>(temp % (( static_cast<UINT64>(uint_max)) + 1)) );

		}

		if (carry!=0)
		{
			temp_pro.base.push_back(static_cast<UINT32>(carry));
		}

		product+=temp_pro;

	}

	

	*this = product;

}

bool bigInt::doOperation(void (bigInt::*i_op)(const bigInt*,const bigInt*),const bigInt& i_value){


	const bigInt* max ;
	const bigInt* min ;

	if ( abs(*this) < abs(i_value))
	{
		min = this;
		max = &i_value;
		
	}else{

		min = &i_value;
		max = this;

	}



	(*this.*i_op)(max,min);


	return max->negative;


}

bigInt bigInt::doDivision(const bigInt& divisore,bigInt& o_remainder,const bool return_quotient) const{

	bigInt quotient;

	quotient.base.pop_back();

	if(divisore==0){

		std::cerr<<"Attention : Divided by zero"<<std::endl;
		system("pause");
		std::exit(EXIT_FAILURE);

	}

	if (divisore == 1)
	{
		o_remainder = 0;

		return (return_quotient)? *this : o_remainder;

	}

	if ( this->base.size() == 1 && divisore.base.size() == 1  )
	{
		o_remainder = this->base.at(0)%divisore.base.at(0);
		
		quotient=(this->base.at(0)/divisore.base.at(0));

		return (return_quotient)? quotient : o_remainder;
	}
	else{

		if( abs(*this) < divisore){

			o_remainder = *this;
			quotient = 0;
			return (return_quotient)? quotient : o_remainder;

		}
	}

	UINT64  partial_boost = 1;
	UINT64  global_boost = 0;

	UINT32 index_dividend=0;


	bool division_find = false; 

	bigInt dividend;
	dividend.base.pop_back();


	while( dividend.base.size() < divisore.base.size() && index_dividend < divisore.base.size() ){

		dividend.base.push_front(this->base.at(this->base.size() - (++index_dividend) ) );
	}
	if ( dividend < divisore )
	{
		dividend.base.push_front(this->base.at(this->base.size() - (++index_dividend) ));
	}

	while(!division_find)
	{		
		UINT64 vvv = (partial_boost + global_boost);

		o_remainder = dividend - divisore * ( vvv );
		


		if (o_remainder < divisore) // ok first digit of quotient is 1
		{
			if (o_remainder<0)
			{
				o_remainder = dividend;
				quotient.base.push_front(0);
			}
			else{

				quotient.base.push_front(1);


			}

			//++index_dividend;

			if (index_dividend > this->base.size()-1 )
			{
				division_find =true;

			}else{

				dividend = o_remainder;

				dividend.base.push_front(this->base.at(this->base.size() - (index_dividend) ));

				partial_boost = 1;

				global_boost = 0;


			}

			


		}
		else{

			bool quotient_find = false;

			while ( !quotient_find )
			{

				o_remainder = dividend - divisore * ( (partial_boost + global_boost) );



				if ( o_remainder >= 0 )
				{

					if (o_remainder < divisore)
					{
						quotient.base.push_front(  static_cast<UINT32>(partial_boost + global_boost) );

						quotient_find = true;
					}


					if ( partial_boost * BOOST_FACTOR > uint_max) // overflow
					{


						global_boost += partial_boost;

						partial_boost = 1;

					}else{

						partial_boost *= BOOST_FACTOR;
					}




				}else{

					global_boost += (partial_boost / BOOST_FACTOR);
					partial_boost = 1;

				}

			}

			if (index_dividend >= this->base.size() )
			{
				division_find = true;
			}
					

		}

		dividend.base.erase(dividend.base.begin(),dividend.base.end());


		if (o_remainder >= 0 && !division_find)
		{		
			if (o_remainder != 0) 
			{
				dividend = o_remainder;
			}

			dividend.base.push_front(this->base.at(this->base.size() - (++index_dividend) ));

			partial_boost = 1;

			global_boost = 0;
		}



	}//while


	quotient.negative = divisore.negative ^ this->negative;

	return (return_quotient)? quotient : o_remainder;

}





 bool bigInt::operator==(const bigInt& r_value) const{

	int v=MinHelper(r_value);
	if (v == 2)
	{
		return true;
	}else{

		return false;

	}

}

 bool bigInt::operator!=(const bigInt& r_value) const{

	return !(*this==r_value);
}


 bool bigInt::operator<(const bigInt& r_value) const{

	int v=MinHelper(r_value);
	if (v == 2)
	{
		return false;

	}else{

		return (v == 1);
	}

}

 bool bigInt::operator>(const bigInt& r_value) const{

	int v=MinHelper(r_value);
	if (v == 2)
	{
		return false;
	}else{

		return !(v == 1);
	}


}

 bool bigInt::operator<=(const bigInt& r_value) const{

	return !(*this > r_value);

}

 bool bigInt::operator>=(const bigInt& r_value) const{

	return  !(*this < r_value);

}




std::ostream& operator<<(std::ostream& i_os,const bigInt i_value)
{
	bigInt remainder;
	remainder.base.pop_back();

	bigInt temp_to_print=i_value;

	std::deque<UINT64> vec64;

	while(abs(temp_to_print) > 0){

		temp_to_print = temp_to_print.doDivision(10000000000000000000,remainder);

		UINT64 to_print = 0;
		
		for (UINT16 j=0;j<remainder.base.size();++j)
		{
			to_print+= static_cast<UINT64>( std::pow(2.0,32.0 * j) ) * static_cast<UINT64>(remainder.base.at(j)); 

		}

		vec64.push_back(to_print);

		remainder.base.erase(remainder.base.begin(),remainder.base.end());
		
	}
	
	if(i_value.negative)
		i_os<<'-';

	for (int i=vec64.size()-1;i>=0;--i)
	{
		i_os<<vec64.at(i);
	}


	return i_os;
}



 bigInt& bigInt::operator<<=(const UINT32 i_shift_value){ 		// shift a sx  x me è lo shift a dx e viceversa
																
	bigInt out_shift_value;
	out_shift_value.base.pop_back();

	UINT64 temp_to_shift = 0;
	UINT64 temp_to_shift_2 = 0;
	UINT64 temp_to_shift_old = 0;

	if ( i_shift_value%32 == 0 )
	{

		UINT32 fast_shift = i_shift_value/32;

		while (out_shift_value.base.size() < fast_shift )
		{
			out_shift_value.base.push_back(0);
		}

		for (UINT32 i = 0; i< this->base.size(); ++i)
		{
			out_shift_value.base.push_back(this->base.at(i));

		}

	}else{

		bigInt out_shift_value_temp;
		out_shift_value_temp.base.pop_back();		

		UINT32 i_shift_value_temp = i_shift_value;

		if (i_shift_value>32)
		{
			
			UINT32 fast_shift = i_shift_value/32;

			while (out_shift_value_temp.base.size() < fast_shift )
			{
				out_shift_value_temp.base.push_back(0);
			}

			for (UINT32 i = 0; i< this->base.size(); ++i)
			{
				out_shift_value_temp.base.push_back(this->base.at(i));

			}

			*this = out_shift_value_temp;

			i_shift_value_temp =i_shift_value - 32*fast_shift;			

		}

		for( UINT32 i=0; i< this->base.size(); ++i ){

				temp_to_shift = base.at(i);		
				
				temp_to_shift<<= i_shift_value_temp;

				temp_to_shift = temp_to_shift | static_cast<UINT32>(temp_to_shift_old);

				UINT32 val = static_cast<UINT32>(temp_to_shift);

				out_shift_value.base.push_back(val);

				temp_to_shift_old = temp_to_shift>>32;
		}

		if (temp_to_shift_old != 0)
		{
			out_shift_value.base.push_back(static_cast<UINT32>(temp_to_shift_old));
		}

	}

	*this = out_shift_value;

	return *this;


}

 bigInt& bigInt::operator>>=(const UINT32 i_shift_value){ 

	bigInt out_shift_value;
	out_shift_value.base.pop_back();

	UINT64 temp_to_shift = 0;
	UINT32 temp_to_shift_old = 0;


	if ( i_shift_value%32 == 0)
	{

		UINT32 fast_shift = i_shift_value/32;

		if (fast_shift >= base.size()-1)
		{
			*this = 0;
			return *this;
		}

		for (UINT32 i = this->base.size()-1 ; i > fast_shift ; --i)
		{
			out_shift_value.base.push_front(this->base.at(i));

		}

	}else{


		UINT32 i_shift_value_temp = i_shift_value;

		if (i_shift_value>32)
		{
			bigInt out_shift_value_temp;
			out_shift_value_temp.base.pop_back();		

			UINT32 fast_shift = i_shift_value/32;

			while (out_shift_value_temp.base.size() < fast_shift )
			{
				out_shift_value_temp.base.push_front(0);
			}

			for (UINT32 i = 0; i< this->base.size() - fast_shift; ++i)
			{
				out_shift_value_temp.base.push_front(this->base.at(this->base.size() - i-1) );

			}

			*this = out_shift_value_temp;

			i_shift_value_temp =i_shift_value - 32*fast_shift;			

		}


		for( UINT32 i=0; i< this->base.size(); ++i ){

			temp_to_shift = base.at( this->base.size() - i-1 );		

			temp_to_shift<<=(32-i_shift_value_temp);


			UINT32 val_2 = static_cast<UINT32>(temp_to_shift); // quelli che vanno a sx

			temp_to_shift>>=32;	

			out_shift_value.base.push_front(static_cast<UINT32>(temp_to_shift | temp_to_shift_old));

			temp_to_shift_old = val_2;

		}


		ResizeBigInteger(out_shift_value);

	}

	*this = out_shift_value;

	return *this;


}


bigInt& bigInt::operator&=(const bigInt& i_value){

	bigInt temp = fitBigIntegerZero(i_value);

	for (UINT32 i=0; i<this->base.size();++i)
	{
		this->base.at(i)&=temp.base.at(i);
	}
	
	ResizeBigInteger(*this);
	
	return *this;
}

bigInt& bigInt::operator|=(const bigInt& i_value){

	bigInt temp = fitBigIntegerZero(i_value);

	for (UINT32 i=0; i<this->base.size();++i)
	{
		this->base.at(i)|=temp.base.at(i);
	}

	ResizeBigInteger(*this);

	return *this;
}

bigInt& bigInt::operator^=(const bigInt& i_value){

	bigInt temp = fitBigIntegerZero(i_value);

	for (UINT32 i=0; i<this->base.size();++i)
	{
		this->base.at(i)^=temp.base.at(i);
	}

	ResizeBigInteger(*this);

	return *this;
}




 bigInt& bigInt::operator+=(const bigInt& i_value1){


	void (bigInt::*operation)(const bigInt*,const bigInt*);


	switch ( ( i_value1.negative && this->negative ) | ( !i_value1.negative && !this->negative ) )
	{
		case true:

			operation = &bigInt::doSum;

			break;

		case false:

			operation = &bigInt::doDiff;
			
			break;
	}

	this->negative = doOperation(operation,i_value1) ; 

	return *this;
}

 bigInt& bigInt::operator*=(const bigInt& i_value){

	bigInt product;

	if (i_value == 1)
	{
		return *this;
	}
	if (i_value == 0)
	{
		return *this=product;
		return *this;
	}


	doOperation(&bigInt::doProduct,i_value);

	this->negative = i_value.negative ^ this->negative;

	return *this;
}

 bigInt& bigInt::operator-=(const bigInt& i_value1){

																/************************************************************************/
																/*    xor
																	0 0 0
																	0 1 1
																	1 0 1
																	1 1 0																*/
																/************************************************************************/
	bigInt temp = i_value1;	

	temp.negative = i_value1.negative ^ true;



	*this+=temp;



	return *this;
}

 bigInt& bigInt::operator/=(const bigInt& divisore){
	
	bigInt o_remainder;
	o_remainder.base.pop_back();

	*this = doDivision(divisore,o_remainder);

	return *this;
	
}

 bigInt& bigInt::operator%=(const bigInt& divisore){
	
	bigInt o_remainder;
	o_remainder.base.pop_back();

	*this = doDivision(divisore,o_remainder,false);

	return *this;
}





const UINT32 bigInt::Appoggio_Sum(const UINT32 i_val1,const UINT32 i_val2,const UINT32 resto,UINT32& sum){

	sum = i_val1 + i_val2 + resto;

	UINT32 max_v = (i_val1 > i_val2 ) ? i_val1 : i_val2;

	if(sum >= max_v && sum <= uint_max ){  // la sum max puo essere (2^32)-1  , la base è (2^32)

		return 0;

	}

	else{

		return 1;


	}

}

const UINT32 bigInt::Appoggio_Diff(const UINT32 min,const UINT32 max,const UINT32 prestito,UINT32& diff){  //max - min


	UINT64 diff_long = ( static_cast<UINT64>(max) + 
		static_cast<UINT64>(prestito) * (uint_max + 1) ) - 
		static_cast<UINT64>(min);

	diff = static_cast<UINT32>(diff_long);

	return prestito;
}

/* i know that not all branches return value*/
int bigInt::MinHelper(const bigInt& r_value) const{

	int modifier = 0;
	if ( this->negative && r_value.negative )
	{
		modifier = 1;
	}

	if(this->negative && !r_value.negative)
		return 1|modifier;
	else{

		if ( !this->negative && r_value.negative)
		{
			return 0^modifier;
		}
	}

	if ( this->base.size() < r_value.base.size() ) 
	{
		return 1^modifier;


	}
	else
	{
		if( this->base.size() == r_value.base.size() ){

			UINT32 temp_max = 0;

			for (UINT32 i=1;   i <= base.size() ; ++i)
			{
				if ( this->base[base.size()-i] < r_value.base[r_value.base.size()-i] )
				{
					return 1^modifier;


				}else{

					if(this->base[base.size()-i] > r_value.base[r_value.base.size()-i]){

						return 0^modifier;


					}else{ 

						if (i == this->base.size()) 
						{
							return 2;

						}

					}
				}
			}


		}else{

			return 0;


		}
	}
}


/*

bigInt pow(const bigInt& i_base,const int& i_exponent){

	

	if (i_exponent == 0)
	{
		
		return 1;
	}
	
	if (i_exponent == 1)
	{

		return i_base;
	}

	bigInt power = i_base;
	for(int i = 0;i<i_exponent-1;++i){

		power *=i_base; 
	}

	if ( i_base.negative && i_exponent%2==0)
	{
		power.negative = false;
	}

	return power;

}
*/