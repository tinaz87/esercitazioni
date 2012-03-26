
/************************************************************************/
/* Nelle diverse strutture per implementare il SORT e il MERGE mi sono  */
/* appoggiato a quelli delle Standard Library							*/
/************************************************************************/


#include "SListArray.h"
#include "SLlist.h"
#include "FixedSList.h"
#include <list>
#include<iostream>



namespace Test{	

	using namespace sla;
	using namespace slst;
	using namespace fsl;
	

	template<typename T>
	void print(T& l){

		T::const_iterator b = l.cbegin();
		for(b = l.cbegin(); b!=l.cend();++b ){

		
			std::cout<<*b<<" ";
		}

		std::cout<<std::endl;
	}		

	void SlistTest(){

		
		std::cout<<"\n --------------------- SLIST TEST --------------------- \n"<<std::endl;


		Slist<int> list_1;
		Slist<int> list_2;
		
		Slist<int>::const_iterator itt=list_1.cbegin();
		//std::list<int> j(10,6);
		//j.push_back(45);
		//j.push_front(99);

		//
		//Slist<int> kk(j.begin(),j.end());

		for(int i = 0 ; i<100; ++i){

			int r = std::rand();
			if(i%2 ==  0){
				list_1.push_back(r);
				list_2.push_back(r-1);
			}
			else{

				list_1.push_front(r);
				list_2.push_front(r+1);
			}
		}
		

		std::cout<<"\nLista_1"<<std::endl;
		print<Slist<int> >(list_1);

		std::cout<<"\nLista_2"<<std::endl;
		print<Slist<int> >(list_2);

		list_2.reverse();

		std::cout<<"\nLista_2 Reverse"<<std::endl;
		print<Slist<int> >(list_2);

		list_1.sort();

		std::cout<<"\nLista_1 Ordinata"<<std::endl;
		print<Slist<int> >(list_1);


		std::cout<<"\nLista_2 Ordinata"<<std::endl;
		list_2.sort();
		print<Slist<int> >(list_2);

		std::cout<<"\nLista_1 Merge"<<std::endl;
		list_1.merge(list_2);
		print<Slist<int> >(list_1);


		list_2 = Slist<int>(20,7);
		
		std::cout<<"\nLista_2  - Slist<int>(20,7) -"<<std::endl;
		print<Slist<int> >(list_2);


		Slist<int>::iterator it_begin = list_1.begin();
		

		++it_begin;
		++it_begin;
		Slist<int>::iterator it_begin2 = it_begin;

		++it_begin2;
		++it_begin2;

		std::cout<<"\nLista_1 Erase elements from "<<*it_begin<<" to end() "<<std::endl;
		list_1.erase(it_begin,list_1.end());
		
		print<Slist<int> >(list_1);
		
		std::cout<<"\n Swap Lista_2 <-> Lista_1 "<<std::endl;
		swap(list_2,list_1);
		std::cout<<"\n Swap Lista_1"<<std::endl;
		print<Slist<int> >(list_1);
		std::cout<<"\n Swap Lista_2"<<std::endl;
		print<Slist<int> >(list_2);

	};	

	void SListArrayTest(){
	
		std::cout<<"\n\n --------------------- SLISTARRAY TEST ---------------------"<<std::endl;

		SListArray<char> lista;
		SListArray<char> lista2;

		SListArray<char> lista3(5,'a');

		SListArray<char>::iterator it;
		
		
		for (int i=0;i<100;++i)
		{
			if (i%2 == 0 )
			{	
				lista2.push_back('b'+i%25);
				lista.push_back('a');

			}else{
				lista.push_front('a'+i%26);
				lista2.push_front('b'+i%25);
			}
		}

		std::cout<<"\nLista_1"<<std::endl;
		print<SListArray<char> >(lista);
		
		std::cout<<"\nRemove if char == a"<<std::endl;
		lista.remove_if([](char p){  return p=='a'; });
		
		print<SListArray<char> >(lista);
		
		lista.push_back('a');
		lista.push_back('b');
		lista.push_back('c');

		lista.push_front('e');
		lista.push_front('d');
		lista.push_front('h');

		std::cout<<"\nLista_1 push_back- a b c - ; push_front - e d h -"<<std::endl;
		print<SListArray<char> >(lista);

		lista.pop_back();

		std::cout<<"\nPop_back Lista_1"<<std::endl;
		print<SListArray<char> >(lista);

		it = lista.begin();

		
		++it;
		lista.insert(it,'y');

		std::cout<<"\nInsert y in Lista_1 first of : "<<*it<<std::endl;
		print<SListArray<char> >(lista);


		lista.pop_front();
		std::cout<<"\nPop_front Lista_1"<<std::endl;
		print<SListArray<char> >(lista);

		lista.pop_back();
		

		lista.pop_back();
		std::cout<<"\n2 Pop_back Lista_1"<<std::endl;
		print<SListArray<char> >(lista);

		lista.push_back('z');
		lista.push_front('k');

		std::cout<<"\n2 Lista_1 Push_back z Push_front k "<<std::endl;
		print<SListArray<char> >(lista);

		SListArray<char>::iterator Erase_it = lista.begin();
		

		++Erase_it;
		++Erase_it;

		SListArray<char>::iterator Erase_it_e= Erase_it;

		++Erase_it_e;
		++Erase_it_e;
		++Erase_it_e;

		lista.erase(Erase_it,Erase_it_e);


		std::cout<<"\nLista_1 Erase elements from "<<*Erase_it<<" to "<<*Erase_it_e<<std::endl;
		
		print<SListArray<char> >(lista);

		lista.resize(10);

		std::cout<<"\n2 Lista_1 Resize 10 "<<std::endl;
		print<SListArray<char> >(lista);

		std::cout<<"\n Lista_1 "<<std::endl;
		print<SListArray<char> >(lista);

		std::cout<<"\n Lista_2 "<<std::endl;
		print<SListArray<char> >(lista2);

		lista.swap(lista2);

		std::cout<<"\nSWAP"<<std::endl;
		std::cout<<"\n Lista_1 "<<std::endl;
		print<SListArray<char> >(lista);

		std::cout<<"\n Lista_2 "<<std::endl;
		print<SListArray<char> >(lista2);


		lista.sort();
		lista2.sort();

		std::cout<<"\nSORT"<<std::endl;
		std::cout<<"\n Lista_1 "<<std::endl;
		print<SListArray<char> >(lista);

		std::cout<<"\n Lista_2 "<<std::endl;
		print<SListArray<char> >(lista2);

		lista.merge(lista2);

		std::cout<<"\nMERGE Lista_1 Lista_2"<<std::endl;
		std::cout<<"\n Lista_1 "<<std::endl;
		print<SListArray<char> >(lista);
		
	}

#define DIM1 100
#define DIM2 250
	void FixedSListTest(){

		std::cout<<"\n\n --------------------- FIXEDSLIST TEST ---------------------\n"<<std::endl;

		//FixedSList<int,1000> flist3(1001,1); crash is correct

		FixedSList<int,DIM1> flist;
		
		FixedSList<int,DIM2> flist2;

		for (int i=0;i<230;++i)
		{
			if (i%3==0)
			{
				flist2.push_back((i*2)+1);
			}else
				flist2.push_front((i*2)+ (std::rand())%10000 );

		}

		for (int i=0;i<DIM1;++i)
		{
			if (i%4==0)
			{
				flist.push_back((i*2) + (std::rand())%10000 );
			}else
				flist.push_front((i*2));

		}
	
		std::cout<<"FIXEDLIST 1"<<std::endl;
		print<FixedSList<int,DIM1> >(flist);

		std::cout<<"\nFIXEDLIST 2"<<std::endl;
		print<FixedSList<int,DIM2> >(flist2);

		auto it = flist2.begin();

		++it;
		++it;
		++it;

		std::cout<<"\nFIXEDLIST 2 INSERT BEFORE "<<*it<< " -> "<< "5999" <<std::endl;
		flist2.insert(it,5999);
		print<FixedSList<int,DIM2> >(flist2);
		
		auto delete_it =flist2.begin();


		++delete_it;
		++delete_it;
		++delete_it;

		auto delete_it2 = delete_it;

		++delete_it2;
		++delete_it2;
		++delete_it2;
		++delete_it2;
		++delete_it2;
		++delete_it2;

		std::cout<<"\nFIXEDLIST 2 ERASE FROM [ "<<*delete_it<< " , "<< *delete_it2 <<" )" <<std::endl;
		flist2.erase(delete_it,delete_it2);
		print<FixedSList<int,DIM2> >(flist2);

		std::cout<<"\nFIXEDLIST 2 REMOVE IF (VALUE % 5 == 0) "<<std::endl;
		flist2.remove_if([](int p){  return p%5==0; });
		print<FixedSList<int,DIM2> >(flist2);


		std::cout<<"\nFIXEDLIST 1 SORT"<<std::endl;
		flist.sort();
		print<FixedSList<int,DIM1> >(flist);

		std::cout<<"\nFIXEDLIST 2 SORT"<<std::endl;
		flist2.sort();
		print<FixedSList<int,DIM2> >(flist2);

		std::cout<<"\nFIXEDLIST 2 REVERSE"<<std::endl;
		flist2.reverse();
		print<FixedSList<int,DIM2> >(flist2);



	};
	
}


int main(){

	Test::FixedSListTest();
	
	Test::SlistTest();
	
	Test::SListArrayTest();

	system("PAUSE");

	return 0;
};

