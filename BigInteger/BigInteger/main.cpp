// 
//

#include <stdio.h>
#include <iostream>
#include "bigInteger.h"
#include <cassert>
#include <intsafe.h>

namespace Big{

	// Il test utilizzato è preso da quello fatto da Devis

	bigInt Fibonacci(UINT32 n)
	{
		if (n == 0) 
			return 0;
		if (n == 1)
			return 1;

		bigInt fn1 = 0;
		bigInt fn2 = 1;

		bigInt fn;

		for (UINT32 i = 1; i < n; ++i)
		{
			fn	= fn1 + fn2;
			fn2 = fn1;
			fn1 = fn;
		}

		return fn;
	}

	bigInt Factorial(unsigned int n)
	{
		if (n == 0)
			return 1;

		bigInt fn = n;

		for (unsigned int i = 2; i < n; ++i)
		{
			fn *= i;
		}

		return fn;
	}

	void bigIntBasicTest() 
	{
		std::cout << "****************************** bigIntBasicTest() *******************************" << std::endl << std::endl;

		const unsigned int N =200;

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		bigInt fib;

		for (UINT32 n = 0; n <= N; ++n)
		{
			fib = Fibonacci(n);
			//std::cout << "F(" << n << ") = " << fib << std::endl;
		}

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		bigInt fibn		= Fibonacci(N);
		bigInt fibn1	= Fibonacci(N - 1);
		bigInt fibn2	= Fibonacci(N - 2);

		std::cout << "F(" << N		<< ") = " << fibn	<< std::endl;
		std::cout << "F(" << N - 1	<< ") = " << fibn1	<< std::endl;
		std::cout << "F(" << N - 2	<< ") = " << fibn2	<< std::endl;

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		std::cout << "Let's check this relationship: F(" << N << ") - F(" << N - 2 << ") = F(" << N - 1 << ")" << std::endl; 

		bigInt diff1 = fibn - fibn2;

		std::cout << "F(" << N << ") - F(" << N - 2 << ") = " << diff1 << std::endl;
		assert(diff1 == fibn1);

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		std::cout << "Let's check this relationship: F(" << N - 2 << ") - F(" << N << ") = - F(" << N - 1 << ")" << std::endl;

		bigInt diff2 = fibn2 - fibn;

		std::cout << "F(" << N - 2 << ") - F(" << N << ") = " << diff2 << std::endl;
		assert(diff2 == -fibn1);

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		std::cout << "Let's check this relationship: F(" << N - 2 << ") < F(" << N << ").....";	
		assert(fibn2 < fibn);
		std::cout << "OK." << std::endl;

		std::cout << "Let's check this relationship: F(" << N - 2 << ") < F(" << N - 1 << ").....";	
		assert(fibn2 < fibn1);
		std::cout << "OK." << std::endl;

		std::cout << "Let's check this relationship: F(" << N << ") > F(" << N - 2 << ").....";	
		assert(fibn > fibn2);
		std::cout << "OK." << std::endl;

		std::cout << "Let's check this relationship: F(" << N << ") > F(" << N - 1 << ").....";	
		assert(fibn > fibn1);
		std::cout << "OK." << std::endl;

		std::cout << "Let's check this relationship: -F(" << N << ") < F(" << N - 2 << ")....";	
		assert(-fibn < fibn2);
		std::cout << "OK." << std::endl;

		std::cout << "Let's check this relationship: -F(" << N << ") < F(" << N - 1 << ")....";	
		assert(-fibn < fibn1);
		std::cout << "OK." << std::endl;

		std::cout << "Let's check this relationship: -F(" << N - 2 << ") < F(" << N << ")....";	
		assert(-fibn2 < fibn);
		std::cout << "OK." << std::endl;

		std::cout << "Let's check this relationship: -F(" << N - 2 << ") > -F(" << N << ")...";	
		assert(-fibn2 > -fibn);
		std::cout << "OK." << std::endl;

		std::cout << "Let's check this relationship: -F(" << N - 1 << ") > -F(" << N << ")...";	
		assert(-fibn1 > -fibn);
		std::cout << "OK." << std::endl;

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		bigInt prod1 = fibn * fibn;
		bigInt prod2 = fibn1 * fibn;
		bigInt prod3 = fibn2 * fibn;

		bigInt prod23	= prod2 + prod3;

		bigInt err		= prod1 - prod23;

		std::cout << "P1 = F(" << N << ") * F(" << N << ") = "		<< prod1 << std::endl;
		std::cout << "P2 = F(" << N - 1 << ") * F(" << N << ") = "	<< prod2 << std::endl;
		std::cout << "P3 = F(" << N - 2 << ") * F(" << N << ") = "	<< prod3 << std::endl;
		std::cout << "P2 + P3 = " << prod23 << std::endl;

		std::cout << "ERR = P1 - (P2 + P3) = " << err << std::endl;

		std::cout << "Let's check this relationship: ERR = 0...";
		assert(err == 0);
		std::cout << "OK." << std::endl;

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;
	}
	
	void FactorialTest() 
	{
		std::cout << "******************************* FactorialTest() ********************************" << std::endl << std::endl;

		const unsigned int m = 50;
		const unsigned int M = 100;

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		bigInt fact;

		for (unsigned int i = 0; i <= M; ++i)
		{
			fact = Factorial(i);
			std::cout << i << "!" << std::endl;
		}

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		for (unsigned int i = m; i <= M; ++i)
		{
			bigInt factn	= Factorial(i);
			bigInt factn1	= Factorial(i - 1);

			std::cout << "Let's check this relationship: " << i << "! / " << i - 1 << "! = " << i << std::endl;

			bigInt ratio = factn / factn1;

			std::cout << i << "! / " << i - 1 << "! = " << ratio << std::endl;
					assert(ratio == i);
		}


		
		bigInt f = Factorial(100);
		f /= 2;
		std::cout << 100 << "! / " << 2 << " = " << f << std::endl;

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;
	}
	
	void ShiftTest()
	{
		std::cout << "******************************* FactorialTest() ********************************" << std::endl << std::endl;

		const unsigned int N = 200;

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		bigInt toBeShifted		= 1;
		bigInt toBeMultiplied	= 1;

		for (unsigned int i = 1; i <= N; ++i)
		{
			std::cout << "Left shift check (" << i << ")...";
			toBeShifted		<<= 1;
			toBeMultiplied	*=	2;
			assert(toBeShifted == toBeMultiplied);
			std::cout << "OK." << std::endl;
		}

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		bigInt oneShotCheck		= 1;

		oneShotCheck <<= N;

		std::cout << "Left shift verificaion...";
		assert(oneShotCheck == toBeShifted);
		std::cout << "OK." << std::endl;

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		for (unsigned int i = 1; i <= N; ++i)
		{
			std::cout << "Right shift check (" << i << ")...";
			toBeShifted		>>= 1;
			toBeMultiplied	/=	2;
			assert(toBeShifted == toBeMultiplied);
			std::cout << "OK." << std::endl;
		}

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

		oneShotCheck >>= N;

		std::cout << "Right shift verificaion...";
		assert(oneShotCheck == 1);
		std::cout << "OK." << std::endl;

		std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;
	}
}

int main(int argc, char** argv)
{
	
	Big::ShiftTest();

	Big::FactorialTest();
	
	
	Big::bigIntBasicTest() ;	


	system("pause");

	return 0;
}
