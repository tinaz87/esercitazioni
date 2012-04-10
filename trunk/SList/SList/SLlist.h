
#pragma  once

#include <deque>
#include <list>
#include <algorithm>
#include <iterator>


namespace slst{		

	template<typename T>
	struct Node{

		Node(T i_val){

			value = i_val;
			next = nullptr;

		}

		Node(){

			value = static_cast<T>(0);
			next = nullptr;
		}

		void setValue(const T i_val){

			value = val;

		}

		T& getValue(){

			return value;
		}

		Node* getNext() const{

			return next;
		}

		void setNext(Node<T>& i_next){

			next = &i_next;
		}

		void setNextToNull(){

			next = NULL;
		}


	private:

		T value;
		Node* next;

	};



	template<typename T,typename A = std::allocator< Node<T> > >
	class Slist
	{


	private:	
		
		Node<T>* list;
		Node<T>* lst_end;

		unsigned int lst_size;

		A alloc;

		void init(){

			list = alloc.allocate(1);

			alloc.construct(list,Node<T>());

			lst_end = list;



		}

		void incrementListSize(){

			++lst_size;

		}

		void decrementListSize(){

			--lst_size;

		}		

	public:

		typedef Slist<T,A>							_Myt;

		typedef T									value_type;

		typedef A									allocator_type;

		typedef std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;

		typedef A&									reference;
		typedef const A&							const_reference;

		typedef T*									pointer;
		typedef const T*							const_pointer;


		template<typename T>
		class const_slistIterator{

		public:

			typedef typename T value_type;

			typedef typename std::ptrdiff_t difference_type;

			typedef typename const T*	pointer;
			typedef typename const T&	reference;

			typedef std::forward_iterator_tag iterator_category;

			const_slistIterator(const const_slistIterator<T>& i_val){

				current_node = i_val.current_node;
			}

			const_slistIterator(){ 

				current_node = NULL;
			}

			const_slistIterator(Node<T>& i_value){ 

				current_node = &i_value;
			}

			const_slistIterator operator=(const const_slistIterator<T>& other){

				if (this != &other )
				{

					(*this).~const_slistIterator();

					new(this)const_slistIterator(other);
				}

				return *this;

			}

			reference operator*() const{

				return (current_node->getValue());

			}

			pointer operator->() const{

				return &(*current_node.getValue());
			}

			const const_slistIterator* operator++(){

				current_node = (current_node->getNext());

				return this;

			}

			const_slistIterator* operator++(int){

				slistIterator iter = *this;

				current_node = (current_node->getNext());

				return &iter;

			}

			bool operator==(const const_slistIterator<T>& i_listiterator) const {

				return ( current_node == i_listiterator.current_node );

			}

			bool operator!=(const const_slistIterator<T>& i_listiterator) const{

				return ( current_node != i_listiterator.current_node );

			}

			

		private:

			Node<T>* getCurrentNode(){
				return current_node;
			}
			
			Node<T>* current_node;

			friend class Slist<T>;

		};

		template<typename T>
		class slistIterator{

		public:

			typedef typename T value_type;

			typedef typename std::ptrdiff_t difference_type;

			typedef typename T*	pointer;
			typedef typename T&	reference;

			typedef std::forward_iterator_tag iterator_category;

			slistIterator(const slistIterator<T>& i_val){

				current_node = i_val.current_node;
			}

			slistIterator(){ 

				current_node = NULL;
			}

			slistIterator(Node<T>& i_value){ 

				current_node = &i_value;
			}

			slistIterator operator=(const slistIterator<T>& other){

				if (this!= &other )
				{

					(*this).~slistIterator();

					new(this)slistIterator(other);
				}

				return *this;

			}

			reference operator*() const{

				return (current_node->getValue());

			}

			pointer operator->() const{

				return &(*current_node.getValue());
			}

			slistIterator* operator++(){

				current_node = (current_node->getNext());

				return this;

			}

			slistIterator* operator++(int){

				slistIterator iter = *this;

				current_node = (current_node->getNext());

				return &iter;

			}

			bool operator==(const slistIterator<T>& i_listiterator) const {

				return ( current_node == i_listiterator.current_node );

			}

			bool operator!=(const slistIterator<T>& i_listiterator) const{

				return ( current_node != i_listiterator.current_node );

			}

			
		private:
			
			Node<T>* getCurrentNode(){
				return current_node;
			}

			Node<T>* current_node;

			friend class Slist<T>;
		};
		
		typedef slistIterator<T >					iterator;
		typedef const_slistIterator<T >				const_iterator;


		explicit Slist(const A& i_alloc = A() ):lst_size(0),alloc(i_alloc){

			init();

		}

		
		explicit Slist(size_type count,const T& value = T(),const A& i_alloc = A()):lst_size(0),alloc(i_alloc){

			init();

			resize(count,value);


		}

		/*
		COSTRUTTORE CON ITERATORI
		*/
		
		/*template <typename InputIterator>
		Slist( InputIterator first, InputIterator last,const A& i_alloc = A() ):alloc(i_alloc),lst_size(0){

			init();

			for (InputIterator it = first; it != last ; ++it)
			{

				push_back( *it );

			}

		}*/
		


		Slist(const Slist& other):lst_size(0){		

			init();

			Node<T>* toScroll = other.list;

			for (size_t i=0; i<other.size();++i)
			{
				push_back(toScroll->getValue());
				toScroll = toScroll->getNext();
			}
		}



		Slist& operator=(const Slist& other){

			if (this != &other)
			{
				(*this).~Slist();

				new(this)Slist(other);

			}

			return *this;
		}


		~Slist(){

			clear();

		};


		iterator begin(){


			return iterator(*list);
		}

		const_iterator begin() const{ // Necessary for cbegin()

			return (const_iterator(*list));
		}

		const_iterator cbegin() const{

			return  (((const Slist<T,A> *)this)->begin() );
		}


		iterator end(){

			if (lst_size == 0)
			{
				return iterator( (*lst_end) );

			}else
				return iterator( *((*lst_end).getNext()));

		}

		const_iterator end() const{ // Necessary for cend()

			if (lst_size == 0)
			{
				return const_iterator( (*lst_end) );

			}else
				return const_iterator( *((*lst_end).getNext()));
		}


		const_iterator cend() const{

			return (((const Slist<T,A> *)this)->end());
		}


		T& front(){

			return  (*list).getValue();

		}

		T& back(){

			return (*lst_end).getValue();

		}



		bool empty() const{

			return (lst_size==0);
		}

		unsigned int size() const{

			return lst_size;
		}



		void push_back(T i_value){

			if (lst_size == 0)
			{
				push_front(i_value);

			}else{

				Node<T>* next = alloc.allocate(1);

				alloc.construct(next,Node<T>(i_value));

				(*lst_end).setNext(*next);

				lst_end = (*lst_end).getNext();

				incrementListSize();
			}		



		}

		void push_front(T i_value){


			if (lst_size == 0)
			{

				list = alloc.allocate(1);

				alloc.construct(list, Node<T>(i_value) );

				lst_end = list;

			}else{

				Node<T>* pre = alloc.allocate(1);

				alloc.construct( pre , Node<T>(i_value) );

				(*pre).setNext(*list);

				list = pre ;

			}

			incrementListSize();

		}


		void pop_back(){		

			Node<T>* toDelete;
			Node<T>* penultimate;

			if (lst_size > 1)
			{

				penultimate = list;
				toDelete = list;

				while ( (*toDelete).getNext() != NULL)
				{	
					penultimate = toDelete;
					toDelete = (*toDelete).getNext();
				}

				alloc.deallocate(toDelete,1);

				(*penultimate).setNextToNull();

				lst_end = penultimate;

				decrementListSize();

			}else{

				pop_front();
			}



		}

		void pop_front(){		

			Node<T>* toDelete = list;
			Node<T>* second;

			if ( lst_size > 1)
			{
				second = list->getNext();

				list = second;

			}else{

				list = NULL;
				lst_end = NULL;

			}

			alloc.deallocate(toDelete,1);		

			decrementListSize();

		}



		iterator insert(iterator pos,const T& i_value){


			if(pos == begin()){

				push_front(i_value);


			}else{

				if (pos == end())
				{
					push_back(i_value);

				}else{

					Node<T>* temp= list;
					Node<T>* penultimate = list;

					Node<T>* ins = alloc.allocate(1);

					while(temp != (pos.getCurrentNode()) ){

						penultimate = temp;
						temp = (*temp).getNext();

					}

					(*penultimate).setNext( *(new(ins)Node<T>(i_value)) );

					(penultimate->getNext())->setNext(*temp);

					incrementListSize();
				}
			}

			return pos;

		}


		iterator erase(iterator first,iterator last){ // [first,last)

			if ( first == begin() && last == end() )
			{
				clear();

			}else{

				iterator preToLast;

				for ( iterator it = first; it != last ; it = preToLast )
				{
					Node<T>* val = (*(it.getCurrentNode())).getNext(); 

					preToLast = iterator(*val);

					erase(it);
				}

			}



			return last;
		}

		iterator erase(iterator pos){

			Slist::iterator after_pos;

			if ( pos.getCurrentNode() == lst_end )
			{

				pop_back();
				after_pos = end();

			}else{			

				if ( pos.getCurrentNode() == list )
				{

					after_pos = iterator( *(list->getNext()) );

					pop_front();				

				}else{

					Node<T>* toErase = list;
					Node<T>* preToErease = list;

					while ( toErase != pos.getCurrentNode())
					{
						preToErease = toErase;
						toErase = toErase->getNext();
					}

					preToErease->setNext( *(toErase->getNext()) );

					after_pos = iterator( *(preToErease->getNext()) );

					alloc.deallocate(toErase,1);

					decrementListSize();
				}			

			}	

			return after_pos;

		}


		void clear(){

			while (lst_size > 0)
			{
				pop_front();
			}

		}



		void resize(size_type count, T value = T()){


			if (count != lst_size)
			{
				if (count > lst_size)
				{
					while( lst_size < count )
						push_back(value);

				}else{

					while ( lst_size > count)
					{
						pop_back();
					}

				}
			}

		}


		void swap(Slist& other){



			Node<T>* tmp_exchange_end = lst_end;

			Node<T>* tmp_exchange_list = list;

			unsigned int tmp_exchange_size = lst_size;



			lst_end = other.lst_end;
			list = other.list;
			lst_size = other.lst_size;


			other.lst_end = tmp_exchange_end;
			other.lst_size = tmp_exchange_size;
			other.list = tmp_exchange_list;

		}


		// i use the alghoritm's stable_sort on a deque that i fill with Slist data
		void sort(){

			std::deque<value_type> toSort;

			unsigned int size_tmp = size();

			while (toSort.size()< size_tmp)
			{
				toSort.push_front( this->back());
				this->pop_back();
			}

			stable_sort(toSort.begin(),toSort.end());

			while (toSort.size()>0)
			{
				this->push_back(toSort.front());
				toSort.pop_front();

			}

		}


		// i use the std::list merge to implement the slist merge
		void merge(Slist& other){

			std::list<T,A> list_other(other.begin(),other.end());

			std::list<T,A> list_this(begin(),end());		

			list_this.merge(list_other);

			other.clear();

			Slist<value_type> o_this;

			for(std::list<T,A>::iterator it = list_this.begin(); it!=list_this.end();++it)
			{
				o_this.push_back(*it);
			}

			*this = o_this;

		}


		template< typename UnaryPredicate >
		void remove_if( UnaryPredicate p ){

			iterator it = begin(); 

			while( it!=end() ){


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

			Slist reverse_this;

			for (iterator it = begin(); it!=end() ; ++it)
			{
				reverse_this.push_front(*it);
			}

			*this = reverse_this;

		}


	

	};

	template<typename T,typename Allocator>
	void swap(Slist<T,Allocator>& l_val,Slist<T,Allocator>& r_val){

		l_val.swap(r_val);

	}

	template<typename T,typename Allocator>
	bool operator==(Slist<T,Allocator>& l_val,Slist<T,Allocator>& r_val){

		if(l_val.size() != r_val.size())
			return false;

		Slist<T,Allocator>::iterator left_it = l_val.begin();
		Slist<T,Allocator>::iterator right_it = r_val.begin();

		while(left_it != l_val.end() && right_it != r_val.end())
		{
			if(*left_it!=*right_it)
				return false;

			++left_it;
			++right_it;
		}

		return true;

	}

	template<typename T,typename Allocator>
	bool operator!=(Slist<T,Allocator>& l_val,Slist<T,Allocator>& r_val){

		return !(l_val==r_val)

	}

	template<typename T,typename Allocator>
	bool operator<(Slist<T,Allocator>& l_val,Slist<T,Allocator>& r_val){

		//Returns true if range [first1,last1) compares lexicographically less than the range [first2,last2).
		return std::lexicographical_compare(l_val.begin(),l_val.end(),r_val.begin(),r_val.end());
	}

	template<typename T,typename Allocator>
	bool operator>(Slist<T,Allocator>& l_val,Slist<T,Allocator>& r_val){

		return !( l_val==r_val ) && !( l_val<r_val );
	}

	template<typename T,typename Allocator>
	bool operator>=(Slist<T,Allocator>& l_val,Slist<T,Allocator>& r_val){

		return !( l_val<r_val );
	}

	template<typename T,typename Allocator>
	bool operator<=(Slist<T,Allocator>& l_val,Slist<T,Allocator>& r_val){

		return !( l_val>r_val );
	}


}