#pragma once
#include <vector>
#include <cassert>
#include "CustomListInterface.h"


namespace fsl{	

	template<typename T>
	struct Node{

		Node(T i_val){
			value = i_val;
			next = -1;
		}

		Node(){

			value = static_cast<T>(0);
			next = -1;
		}

		void setValue(const T i_val){

			value = i_val;

		}

		T& getValue(){

			return value;
		}

		int getNext() const{

			return next;
		}
		void setNext(int i_next){

			next = i_next;
		}

		void setNextToNull(){

			next = -1;
		}

	private:

		T value;
		int next;


	};
	

	
	template< typename T, unsigned int N , typename A = std::allocator<Node<T> >>
	class FixedSList//:public CustomListInterface<T,fixedSListIterator<T>,const_fixedSListIterator<T> >
	{

	public:

		template<typename T>
		class const_fixedSListIterator{

		public:

			typedef typename T						value_type;

			typedef typename std::ptrdiff_t			difference_type;

			typedef typename const T*				pointer;
			typedef typename const T&				reference;

			typedef std::forward_iterator_tag		iterator_category;

			const_fixedSListIterator(const const_fixedSListIterator& other){ 

				index = other.index;
				current_array = other.current_array;
			}


			const_fixedSListIterator(){ 

				index = -1;
				current_array = nullptr;
			}

			const_fixedSListIterator(const Node<T>* i_array,const int i_index){ 

				current_array = i_array;
				index = i_index;	

			}

			const_fixedSListIterator operator=(const const_fixedSListIterator<T>& other){

				if ( this != &other) 
				{

					(*this).~const_fixedSListIterator();

					new(this)const_fixedSListIterator(other);
				}

				return *this;

			}

			reference operator*() const{

				Node<T> node = ( current_array[index] );

				return ( node.getValue() );
			}

			pointer operator->() const{

				return &( (current_array[index] ).getValue() );
			}

			const_fixedSListIterator& operator++(){

				index = (current_array[index]).getNext();

				return *this;

			}

			const_fixedSListIterator operator++(int){

				const_fixedSListIterator iter = *this;

				index = (current_array[index]).getNext();

				return iter;

			}

			bool operator == (const const_fixedSListIterator<T>& i_listArrayiterator) const {


				return (  index == i_listArrayiterator.index );



			}

			bool operator!=(const const_fixedSListIterator<T>& i_listArrayiterator) const{


				return ( index != i_listArrayiterator.index );

			}


		private:

			const Node<T>* current_array;
			int index;


			int getCurrentIndex() const{

				return index;

			}

			friend class FixedSList<T,N>;

		};

		template<typename T>
		class fixedSListIterator{

		public:

			typedef typename T value_type;

			typedef typename std::ptrdiff_t difference_type;

			typedef typename T*	pointer;
			typedef typename T&	reference;

			typedef std::forward_iterator_tag iterator_category;

			fixedSListIterator(const fixedSListIterator& other){ 

				index = other.index;
				current_array = other.current_array;
			}

			fixedSListIterator(){ 

				index = -1;
				current_array = nullptr;
			}

			fixedSListIterator(Node<T>* i_array,int i_index){ 

				current_array = i_array;
				index = i_index;	

			}


			fixedSListIterator operator=(const fixedSListIterator<T>& other){

				if ( this != &other)
				{

					(*this).~fixedSListIterator();

					new(this)fixedSListIterator(other);
				}

				return *this;

			}

			reference operator*() const{

				return ( (current_array[index] ).getValue() );

			}

			pointer operator->() const{

				return &( (current_array[index] ).getValue() );
			}

			fixedSListIterator& operator++(){

				index = (current_array[index]).getNext();

				return *this;

			}

			fixedSListIterator operator++(int){

				fixedSListIterator iter = *this;

				index = (current_array[index]).getNext();

				return iter;

			}

			bool operator == (const fixedSListIterator<T>& i_listArrayiterator) const {


				return (  index == i_listArrayiterator.index );



			}

			bool operator!=(const fixedSListIterator<T>& i_listArrayiterator) const{


				return ( index != i_listArrayiterator.index );

			}


		private:


			Node<T>* current_array;
			int index;



			int getCurrentIndex() const{

				return index;

			}

			friend class FixedSList<T,N>;


		};

	
		typedef FixedSList<T,N,A>							_Myt;

		typedef T											value_type;
	
		typedef A											allocator_type;
	
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;
	
		typedef A&											reference;
		typedef const A&									const_reference;
	
		typedef T*											pointer;
		typedef const T*									const_pointer;
	
		typedef fixedSListIterator<T >						iterator;
		typedef const_fixedSListIterator<T >				const_iterator;


		explicit FixedSList(const A& i_alloc = A() ):fsl_size(0),alloc(i_alloc),m_data(),head(0),tail(0){}

		explicit FixedSList(size_type count,const T& value = T(),const A& i_alloc = A()):fsl_size(0),alloc(i_alloc),head(0),tail(0){

			resize(count,value);

		}


		iterator begin(){

			return iterator(m_data,head);
		}

		const_iterator begin() const{ // Necessary for cbegin()

			return const_iterator(m_data,head);
		}

		const_iterator cbegin() const{

			return  (((const FixedSList<T,N,A>*)this)->begin());
		}


		iterator end(){


			if (fsl_size == 0)
			{
				return iterator(m_data,head);

			}else
				return iterator( m_data , m_data[tail].getNext());

		}

		const_iterator end() const{ // Necessary for cend()

			if (fsl_size == 0)
			{
				return const_iterator(m_data,head);

			}else
				return const_iterator( m_data , m_data[tail].getNext());
		}


		const_iterator cend() const{

			return (((const FixedSList<T,N,A> *)this)->end());
		}


		T& front(){

			return (m_data[head]).getValue();

		}


		T& back(){

			return (m_data[tail]).getValue();

		}

		bool empty() const{

			return fsl_size==0;
		}


		unsigned int size() const{

			return fsl_size;
		}


		void push_back(T i_value){

			assert( fsl_size+1 <= N);

			if (fsl_size == 0)
			{
			
				m_data[fsl_size].setValue(i_value);
			
				//m_data[fsl_size].setMyPosition(0);
			
				head = tail = 0;		

			}else{

				if( m_data[tail].getNext() == -1 ){				

					m_data[tail].setNext(fsl_size);

					m_data[fsl_size].setValue(i_value);
				
					//m_data[fsl_size].setMyPosition(fsl_size);

					tail = fsl_size;

				}
				else{

					int next_position =  m_data[tail].getNext();

					m_data[ next_position ].setValue(i_value);

					//m_data[ next_position ].setMyPosition(next_position );

					m_data[ next_position ].setNext( m_data[ m_data[tail].getNext() ].getNext() );

					tail = next_position;


				}
			}

			incrementListSize();
		}


		void push_front(T i_value){

			assert( fsl_size+1 <= N);

			if (fsl_size == 0)
			{
				push_back(i_value);

			}else{

				if( m_data[tail].getNext() == -1){

					m_data[fsl_size].setValue(i_value);

					//m_data[fsl_size].setMyPosition(fsl_size);

					m_data[fsl_size].setNext(head);

					head = (fsl_size);

				}
				else{

					int next_position = m_data[tail].getNext();

					m_data[tail].setNext( m_data[next_position].getNext() );

					m_data[next_position].setValue(i_value);

					m_data[next_position].setNext(head);			

					head = next_position;


				}

			}

			incrementListSize();

		}

		void pop_back(){

			int precedenttoDelete = head;


			while ( m_data[precedenttoDelete].getNext() != tail )
			{

				precedenttoDelete = m_data[precedenttoDelete].getNext();

			}

			tail = precedenttoDelete;

			decrementListSize();

		}


		void pop_front(){

			int new_head_position = m_data[head].getNext();

			if ( m_data[tail].getNext() != -1 )
			{		
				m_data[head].setNext( m_data[tail].getNext() );

			}else{

				m_data[head].setNext(-1);

			}

			m_data[tail].setNext(head);

			head = new_head_position ; 

			decrementListSize();

		}


		iterator insert(iterator pos,const T& i_value){

			assert( fsl_size+1 <= N);

			if ( pos == begin())
			{
				push_front(i_value);

			}else{

				if ( pos == end())
				{
					push_back(i_value);

				}else{

					int val_at_pos = head;
					int precedent = head;

					while ( val_at_pos != pos.getCurrentIndex() )
					{
						precedent = val_at_pos;
						val_at_pos = m_data[val_at_pos].getNext();

					}

					if( m_data[tail].getNext() == -1){

						m_data[fsl_size].setNext(val_at_pos);

						m_data[precedent].setNext(fsl_size);

						//m_data[fsl_size].setMyPosition(fsl_size);

						m_data[fsl_size].setValue(i_value);

					}
					else{

						int tail_next_position = m_data[tail].getNext(); 

						m_data[tail].setNext( m_data[tail_next_position].getNext() );

						m_data[precedent].setNext(tail_next_position);

						m_data[tail_next_position].setValue(i_value);

						//m_data[tail_next_position].setMyPosition(tail_next_position);
					}

					incrementListSize();
				}
			}

			return pos;

		}

		iterator erase(iterator pos){


			if ( pos.getCurrentIndex() == tail)
			{
				pop_back();

				return end();

			}else{

				if ( pos.getCurrentIndex() == head)
				{
					pop_front();

					return iterator( m_data,m_data[head].getNext());

				}else{

					int toErase = head;
					int precedent;

					while (toErase != pos.getCurrentIndex() )
					{
						precedent = toErase;
						toErase = m_data[toErase].getNext();
					}

					int next = m_data[toErase].getNext();

					m_data[precedent].setNext( next );

					m_data[toErase].setNext(m_data[tail].getNext());

					m_data[tail].setNext(toErase);

					decrementListSize();

					return iterator(m_data, next );
				}

			}



		}

		iterator erase(iterator first,iterator last){

			if ( first == begin() && last == end() )
			{
				clear();

			}else{
				iterator it_next;

				if (last == end())
				{
					for ( iterator it = first; it != end() ; it = it_next )
					{
						it_next = erase(it);

					}
				}else{

					for ( iterator it = first; it != last ; it = it_next )
					{
						it_next = erase(it);

					}

				}


			}

			return last;

		}


		void clear(){
				
			head = 0;
			tail = 0;
			fsl_size = 0;

			for(int i=0; i<N && m_data[i].getNext() != -1  ;++i){

				m_data[i].setNextToNull();

			}
		}

		void resize(size_type count, T value = T()){

			assert( count <= N);

			if (count != fsl_size)
			{
				if (count > fsl_size)
				{
					while( fsl_size < count )
						push_back(value);

				}else{

					while ( fsl_size > count)
					{
						pop_back();
					}

				}
			}



		}


		void sort(){

			std::vector< T , A > toSort(begin(),end());

			clear();

			stable_sort(toSort.begin(),toSort.end());

			for(size_t index = 0 ; index < (toSort.size()) ; ++index)
			{
				push_back(toSort.at(index));

			}

		}	

		template< typename UnaryPredicate >
		void remove_if( UnaryPredicate p ){

			iterator it = begin(); 

			while( it != end() ){


				if ( p(*it) )
				{
					it = erase(it);

				}else
					++it;


			}

		

		}

		void remove( const T& value ){

			iterator it = begin(); 

			while(it!=end()){


				if ( (*it) == value )
				{
					it = erase(it);

				}else
					++it;


			}

		}

		void reverse(){

			FixedSList reverse_this;

			for (iterator it = begin(); it!=end() ; ++it)
			{
				reverse_this.push_front(*it);
			}

			*this = reverse_this;	

		}



	private:

			Node<T> m_data[N];

			A alloc;

			unsigned int fsl_size;

			int head;
			int tail;

			void incrementListSize(){

				++fsl_size;

			}

			void decrementListSize(){

				--fsl_size;

			}

	};


}