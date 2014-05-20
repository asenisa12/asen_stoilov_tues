#include <iostream>
using namespace std;

class ListError{};

template<typename T>class List{
	struct Elem{
		T data_;
		Elem *next_;
		Elem *prev_;
		Elem(T val)
		: data_(val), next_(0), prev_(0)
		{}
	};
	Elem* head_;
	Elem* tail_;
	int size_;
public:	
	List()
	:  head_(new Elem(0)),size_(0)
	{
		head_->next_=head_;
		head_->prev_=head_;
		tail_ = head_;
	}

	List(const List<T> &other){
		head_ = new Elem(*other.head_);
		tail_ = new Elem(*other.tail_);
		size_ = other.size_;
	}

	List& operator=(const List<T> &other){
		head_ = new Elem(*other.head_);
		tail_ = new Elem(*other.tail_);
		size_ = other.size_;
		return *this;
	}

	void swap(List<T> &other){
		List<T> l(other);
		l.show_all();
		other=*this;
		other.show_all();
		head_ = new Elem(*l.head_);
		tail_ = new Elem(*l.tail_);
		size_ = l.size_;

	}

	~List(){
		while(!empty())
			pop_front();

		delete head_;
	}

	bool empty() const {
		return size_==0;
	}

	void push_back(int val){
		Elem* ptr= new Elem(val);
		Elem* back = tail_->prev_;
		
		tail_->prev_ = ptr;
		ptr-> prev_ = back;

		back->next_ = ptr;
		ptr->next_=tail_;

		size_++;
	}

	T& front(){
		if(empty())
			throw ListError();
		return head_->next_->data_;
	}

	T& back(){
		if(empty())
			throw ListError();
		return tail_->prev_->data_;
	}

	const T& front()const{
		if(empty())
			throw ListError();
		return head_->next_->data_;
	}
	const T& back() const{
		if(empty())
			throw ListError();
		return tail_->prev_->data_;
	}

	void push_front(int val){
		Elem* ptr= new Elem(val);
		Elem* front = head_->next_;
		
		head_->next_=ptr;
		ptr->next_=front;

		front->prev_=ptr;
		ptr->prev_=head_;

		size_++;
	}

	void pop_front(){
		if(empty())
			throw ListError();
		Elem *front = head_->next_;
		Elem *new_front = front-> next_;

		head_ -> next_ = new_front;
		new_front->prev_ = head_;

		delete front;
		size_--;
	}

	void pop_back(){
		if(empty())
			throw ListError();
		Elem *back = tail_->prev_;
		Elem *new_back = back->prev_;

		tail_->prev_ = new_back;
		new_back->prev_ = tail_;

		delete back;
		size_--;
	}

	int size()const{
		return size_;
	}

	void clear(){
		if(empty())
			throw ListError();
		while(!empty())
			pop_front();
	}

	void show_all(){
		Elem* ptr;
		ptr = head_->next_;
		for(int i=0;i<size_;i++){
			
			std::cout << ptr->data_ <<" ";
			ptr = ptr->next_; 
		}
		std::cout<<endl;
	}

	class iterator
	{
		List& l_;
		int pos_;
		
		T& position(int index){
			Elem* ptr;
			ptr = l_.head_->next_;
			for(int i=0;i<index;i++){
				ptr = ptr->next_; 
			}
			return ptr->data_;
		}
	public:
		iterator(List& l, int pos)
			: l_(l),
			  pos_(pos)
		{}

		iterator operator++() {
			if(pos_ >= l_.size()) {
				return;
			}

			pos_++;
		}

		T& operator[](int index) {
			return position(index);
		}

		T& operator*(){
			return position(pos_);
		}

		bool operator==(const iterator& other) const {
			return position(pos_)==*other;
		}
		
		bool operator!=(const iterator& other) const {
			return !position(pos_)==*other;
		}
	};

	iterator begin() {
		return iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this, size_-1);
	}
};


int main(){
	List<int> l;
	cout << l.empty() <<endl;
	l.push_back(1);
	l.push_back(2);
	l.push_front(3);
	l.pop_front();
	l.pop_back();
	cout << l.front() <<endl;
	cout << l.back() <<endl;
	cout << l.empty() <<endl;
	cout << l.size() <<endl;
	l.clear();
	cout << l.empty() <<endl;

	cout << l.size() <<endl;


	List<int> l1;
	List<int> l2;

	l1.push_back(1);
	l1.push_back(2);

	List<int> l3(l1);
	l2.push_back(8);
	l2.push_back(9);
	l2.push_back(11);
	l1=l2;

	cout << l1.back() <<endl;
	List<int>::iterator it = l1.begin();
	cout << it[3] <<endl;
	cout << (*it) << endl;
	cout << ((*it)==it[0]) << endl;
	List<int>::iterator it2 = l1.end();
	cout << (*it2) << endl;
	return 0;
}