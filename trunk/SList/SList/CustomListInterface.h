#pragma once


template<typename T,typename InputIterator,typename InputConst_Iterator >
class CustomListInterface{

public:

		
	virtual InputIterator begin() =  0;

	virtual InputConst_Iterator begin() const = 0;

	virtual InputConst_Iterator cbegin() const = 0;

	virtual InputIterator end() = 0;

	virtual InputConst_Iterator end() const = 0;

	virtual InputConst_Iterator cend() const  = 0;

	virtual T& front()= 0;

	virtual T& back() = 0;

	virtual bool empty() const = 0;

	virtual unsigned int size() const  = 0;

	virtual void push_back(T)  = 0;

	virtual void push_front(T)  = 0;

	virtual void pop_back()  = 0;

	virtual void pop_front()  = 0;

	virtual InputIterator insert(InputIterator,const T&)  = 0;

	virtual InputIterator erase(InputIterator,InputIterator) = 0 ;
	
	virtual InputIterator erase(InputIterator)  = 0;

	virtual void clear()  = 0;

	virtual void resize(std::size_t,T){}; 

	virtual void sort()  = 0;	

	virtual void remove(const T&)  = 0;

	virtual void reverse()  = 0;
	
};