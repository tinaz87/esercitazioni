#pragma once
#include <vector>
//#include "CustomListInterface.h"

namespace sla{	

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

		//int getMyPosition() const{

		//	return position;

		//}
		//void setMyPosition(int my_pos){

		//position = my_pos;
		//}

		void setNext(int i_next){

			next = i_next;
		}

		void setNextToNull(){

			next = -1;
		}

	private:

		T value;
		int next;
		//int position;

	};


	template<typename T,typename A = std::allocator< Node<T> > >
	class SListArray//: public CustomListInterface<T,slistArrayIterator<T>,const_slistArrayIterator<T> >
	{

	public:

		template<typename T>
		class const_slistArrayIterator{

		public:

			typedef typename T						value_type;

			typedef typename std::ptrdiff_t			difference_type;

			typedef typename const T*				pointer;
			typedef typename const T&				reference;

			typedef std::forward_iterator_tag		iterator_category;

			const_slistArrayIterator(const const_slistArrayIterator& other){ 

				index = other.index;
				current_vector = other.current_vector;
			}


			const_slistArrayIterator(){ 

				index = -1;
				current_vector = nullptr;
			}

			const_slistArrayIterator(const std::vector<Node<T> >& i_vector,const int i_index){ 

				current_vector = &i_vector;
				index = i_index;	

			}

			const_slistArrayIterator operator=(const const_slistArrayIterator<T>& other){

				if ( this != &other) 
				{

					(*this).~const_slistArrayIterator();

					new(this)const_slistArrayIterator(other);
				}

				return *this;

			}

			reference operator*() const{

				Node<T> node = ( current_vector->at(index) );

				return ( node.getValue() );
			}

			pointer operator->() const{

				return &( (current_vector->at(index) ).getValue() );
			}

			const_slistArrayIterator& operator++(){

				index = (current_vector->at(index)).getNext();

				return *this;

			}

			const_slistArrayIterator operator++(int){

				const_slistArrayIterator iter = *this;

				index = (current_vector->at(index)).getNext();

				return iter;

			}

			bool operator == (const const_slistArrayIterator<T>& i_listArrayiterator) const {


				return (  index == i_listArrayiterator.index );



			}

			bool operator!=(const const_slistArrayIterator<T>& i_listArrayiterator) const{


				return ( index != i_listArrayiterator.index );

			}




		private:

			const std::vector<Node<T> >* current_vector;
			int index;

			int getCurrentIndex() const{

				return index;

			}

			friend class SListArray<T>;

		};


		template<typename T>
		class slistArrayIterator{

		public:

			typedef typename T value_type;

			typedef typename std::ptrdiff_t difference_type;

			typedef typename T*	pointer;
			typedef typename T&	reference;

			typedef std::forward_iterator_tag iterator_category;

			slistArrayIterator(const slistArrayIterator& other){ 

				index = other.index;
				current_vector = other.current_vector;
			}

			slistArrayIterator(){ 

				index = -1;
				current_vector = nullptr;
			}

			slistArrayIterator(std::vector<Node<T> >& i_vector,int i_index){ 

				current_vector = &i_vector;
				index = i_index;	

			}


			slistArrayIterator operator=(const slistArrayIterator<T>& other){

				if ( this != &other)
				{

					(*this).~slistArrayIterator();

					new(this)slistArrayIterator(other);
				}

				return *this;

			}

			reference operator*() const{

				return ( (current_vector->at(index) ).getValue() );

			}

			pointer operator->() const{

				return &( (current_vector->at(index) ).getValue() );
			}

			slistArrayIterator& operator++(){

				index = (current_vector->at(index)).getNext();

				return *this;

			}

			slistArrayIterator operator++(int){

				slistArrayIterator iter = *this;

				index = (current_vector->at(index)).getNext();

				return iter;

			}

			bool operator == (const slistArrayIterator<T>& i_listArrayiterator) const {


				return (  index == i_listArrayiterator.index );



			}

			bool operator!=(const slistArrayIterator<T>& i_listArrayiterator) const{


				return ( index != i_listArrayiterator.index );

			}


		private:


			std::vector<Node<T> >* current_vector;
			int index;

			int getCurrentIndex() const{

				return index;

			}

			friend class SListArray<T>;


		};



		typedef SListArray<T,A>							_Myt;

		typedef T										value_type;

		typedef A										allocator_type;

		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;

		typedef A&										reference;
		typedef const A&								const_reference;

		typedef T*										pointer;
		typedef const T*								const_pointer;

		typedef slistArrayIterator<T >					iterator;
		typedef const_slistArrayIterator<T >			const_iterator;


		explicit SListArray(const A& i_alloc = A() ):sla_size(0),alloc(i_alloc),m_data(),head(0),tail(0),threshold(0.6f){


		}

		explicit SListArray(size_type count,const T& value = T(),const A& i_alloc = A()):sla_size(0),threshold(0.6f){

			resize(count,value);

		}


		/*COSTRUTTORE CON ITERATOR*/


		/*
		template <typename InputIterator>
		Slist( InputIterator first, InputIterator last,const A& i_alloc = A() ):alloc(i_alloc),lst_size(0){

		head = 0;
		tail = 0;

		for (InputIterator it = first; it != last ; ++it)
		{

		push_back( *it );
		}

		}
		*/	


		SListArray& operator=(const SListArray& other){

			if (this != &other)
			{
				(*this).~SListArray();

				new(this)SListArray(other);

			}

			return *this;
		}


		iterator begin(){

			return iterator(m_data,head);
		}

		const_iterator begin() const{ // Necessary for cbegin()

			return const_iterator(m_data,head);
		}

		const_iterator cbegin() const{

			return  (((const SListArray<T,A>*)this)->begin());
		}


		iterator end(){


			if (sla_size == 0)
			{
				return iterator(m_data,head);

			}else
				return iterator( m_data , (m_data.at(tail)).getNext() );

		}

		const_iterator end() const{ // Necessary for cend()

			if (sla_size == 0)
			{
				return const_iterator(m_data,head);

			}else
				return const_iterator( m_data , m_data.at(tail).getNext());
		}


		const_iterator cend() const{

			return (((const SListArray<T,A> *)this)->end());
		}

		T& front(){

			return (m_data.at(head)).getValue();

		}


		T& back(){

			return (m_data.at(tail)).getValue();

		}

		bool empty() const{

			return sla_size==0;
		}



		unsigned int size() const{

			return sla_size;
		}

		void push_back(T i_value){

			Node<T>* next = alloc.allocate(1);

			alloc.construct(next,Node<T>(i_value));


			if (sla_size == 0)
			{
				//next->setMyPosition(0);
				m_data.push_back(*next);

				head = tail = 0;		

			}else{

				if( m_data.at(tail).getNext() == -1 ){

					//next->setMyPosition(m_data.size());

					m_data.at(tail).setNext(m_data.size());


					m_data.push_back(*next);



					tail = size();



				}
				else{

					//next->setMyPosition(m_data.at(tail).getNext());
					int next_position = m_data.at(tail).getNext();

					next->setNext( m_data.at( next_position ).getNext()  );



					m_data.at(next_position) = *next;

					tail = next_position;


				}
			}

			incrementListSize();

		}


		void push_front(T i_value){


			Node<T>* new_head = alloc.allocate(1);

			alloc.construct(new_head,Node<T>(i_value));

			if (sla_size == 0)
			{
				//new_head->setMyPosition(0);

				m_data.push_back(*new_head);

				head = tail = 0 ;

			}else{

				if( m_data.at(tail).getNext() == -1){

					//new_head->setMyPosition(m_data.size());

					new_head->setNext( head);

					m_data.push_back(*new_head);			

					head = (m_data.size()-1);

				}
				else{

					//new_head->setMyPosition(m_data.at(tail).getNext());

					new_head->setNext( head);

					int tail_next = m_data.at(tail).getNext();

					m_data.at(tail).setNext( m_data.at(tail_next).getNext() );

					m_data.at( tail_next ) = *new_head;				

					head = tail_next;


				}

			}

			incrementListSize();

		}

		void pop_back(){

			int precedenttoDelete = head;


			while ( m_data.at(precedenttoDelete).getNext() != tail )
			{

				precedenttoDelete = m_data.at(precedenttoDelete).getNext();

			}

			tail = precedenttoDelete;

			decrementListSize();

			ControlThreshold();


		}


		void pop_front(){

			int new_head_position = m_data.at(head).getNext();

			if ( m_data.at(tail).getNext() != -1 )
			{		
				m_data.at(head).setNext( m_data.at(tail).getNext() );

			}else{

				m_data.at(head).setNext(-1);

			}

			m_data.at(tail).setNext(head);

			head = new_head_position ; 

			decrementListSize();

			ControlThreshold();
		}

		iterator insert(iterator pos,const T& i_value){

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

					Node<T>* ins = alloc.allocate(1);

					alloc.construct(ins,Node<T>(i_value));

					while ( val_at_pos != pos.getCurrentIndex() )
					{
						precedent = val_at_pos;
						val_at_pos = m_data.at(val_at_pos).getNext();

					}


					ins->setNext(val_at_pos);

					if( m_data.at(tail).getNext() == -1){

						//ins->setMyPosition(m_data.size());

						m_data.push_back(*ins);

						m_data.at(precedent).setNext(m_data.size()-1);

					}
					else{

						int tail_next_position = m_data.at(tail).getNext(); 

						m_data.at(tail).setNext( m_data.at(tail_next_position).getNext() );

						m_data.at(precedent).setNext(tail_next_position);

						//ins->setMyPosition(tail_next_position);					

						m_data.at( tail_next_position ) = *ins;


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

					return iterator( m_data,m_data.at(head).getNext());

				}else{

					int toErase = head;
					int precedent;

					while (toErase != pos.getCurrentIndex() )
					{
						precedent = toErase;
						toErase = m_data.at(toErase).getNext();
					}

					int next = m_data.at(toErase).getNext();

					m_data.at(precedent).setNext( next );

					m_data.at(toErase).setNext(m_data.at(tail).getNext());

					m_data.at(tail).setNext(toErase);

					decrementListSize();

					return iterator(m_data, next );
				}

			}

			ControlThreshold();

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

			m_data.clear();
			m_data.shrink_to_fit();
			head = 0;
			tail = 0;
			sla_size = 0;


		}

		void resize(size_type count, T value = T()){

			if (count != sla_size)
			{
				if (count > sla_size)
				{
					while( sla_size < count )
						push_back(value);

				}else{

					while ( sla_size > count)
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



		void swap(SListArray& other){

			int exchange_head = head;
			int exchange_tail = tail;
			int exchange_size = sla_size;		

			head = other.head;
			tail = other.tail;
			sla_size = other.sla_size;

			other.head = exchange_head;
			other.tail = exchange_tail;
			other.sla_size = exchange_size;

			m_data.swap(other.m_data);

		}

		void merge(SListArray& other){

			std::list<T,A> this_vector(begin(),end());

			std::list<T,A> other_vector(other.begin(),other.end());

			this_vector.merge(other_vector);

			other.clear();

			clear();

			for(std::list<T,A>::iterator it = this_vector.begin(); it!=this_vector.end();++it)
			{
				push_back(*it);
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

			ControlThreshold();

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


			ControlThreshold();


		}

		void reverse(){

			SListArray reverse_this;

			for (iterator it = begin(); it!=end() ; ++it)
			{
				reverse_this.push_front(*it);
			}

			*this = reverse_this;	

		}


	private:

		std::vector<Node<T>,A > m_data;

		int head;
		int tail;

		float threshold;

		unsigned int sla_size;

		A alloc;

		void incrementListSize(){

			++sla_size;

		}

		void decrementListSize(){

			--sla_size;

		}

		void ControlThreshold(){

			float val = ( static_cast<float>(this->size()) / m_data.size() );
			if (threshold > val )
			{
				std::cout<<"\n * THRESHOLD EXCEEDED : REBUILD LIST * \n"<<std::endl;

				ReBuildSListArray();
			}

		}

		void ReBuildSListArray(){

			SListArray old_list = *this;

			clear();

			for (auto i = old_list.begin(); i!=old_list.end() ; ++i )
			{
				push_back(*i);
			}

		}

	};

	template<typename T,typename Allocator>
	void swap(SListArray<T,Allocator>& lhs,SListArray<T,Allocator>& rhs){

		lhs.swap(rhs);

	}

}
