#include <iostream>

using namespace std;

template<typename T>class List{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;

		Node(T val)
			: data_(val), next_(0),prev_(0)
		{}
	};

	Node* head_;
	Node* tail_;
	int size_;

	void copy(const List& other){
		head_ = new Node(*other.head_);
		tail_ = new Node(*other.tail_);
		size_ = other.size_;
	}
public:
	List()
		: head_(0), tail_(0), size_(0)
	{}

	bool empty(){
		return size_== 0;
	}

	void push_back(T val){
		Node* ptr = new Node(val);

		if (!empty()){
			Node* back = tail_;
			tail_->next_ = ptr;
			tail_ = tail_->next_;
			tail_->prev_=back;
		}else{
			head_ = ptr;
			tail_ = ptr;
		}

		size_++;
	}

	void push_front(T val){
		Node* ptr = new Node(val);

		if (!empty()){
			ptr->next_ = head_;
			head_ = ptr;
			(head_->next_)->prev_ =head_;
		}
		else{
			head_ = ptr;
			tail_ = ptr;
		}

		size_++;
	}

	void pop_back(){
		if(empty())
			throw std :: exception();

		Node* ptr = tail_;
		tail_ = tail_->prev_;
		delete ptr;

		size_--;
	}

	void pop_front(){
		if(empty())
			throw std :: exception();

		Node* ptr = head_;
		head_ =head_->next_;
		delete ptr;

		size_--;
	}

	T& front(){
		if(empty())
			throw std :: exception();
		return head_->data_;
	}


	T& back(){
		if(empty())
			throw std :: exception();
		return tail_->data_;	
	}

	int size(){
		return size_;
	}


	void clear(){
		if(empty())
			throw std :: exception();

		for (int i = 0; i < size_; ++i)
			pop_front();
	}

	List(const List<T>& other){
		copy(other);
	}

	List&  operator=(const List<T>& other){
		copy(other);
		return *this;
	}

	void swap(List<T> &other){
		Node *head = head_;
		Node* tail = tail_;
		int size = size_;

		copy(other);

		other.head_ = new Node(*head);
		other.tail_= new Node(*tail);
		other.size_ = size;

	}

	class iterator{
		friend class List;
		int pos_;
		List l_;

		T& position(int pos){
			Node* ptr = l_.head_; 
			for(int i=0;i<pos;i++)
				ptr = ptr->next_;
			return ptr->data_;
		}
	public:
		iterator(List& list, int pos)
		: l_(list), pos_(pos)
		{}

		T& operator[](int pos){
			return position(pos);
		}

	};

	iterator begin(){
		return iterator(*this, 0);
	}
};


int main(){
	List<int> l1;

	l1.push_back(2);
	l1.push_back(3);
	l1.push_front(7);
	/*l1.pop_back();
	l1.pop_front();
	l1.clear();*/

	List<int> l2;

	l2=l1;

	List<int> l3;

	l3.push_back(5);
	l3.push_back(6);
	l3.push_front(9);


	l2.swap(l3);
	cout << l2.front() << endl;
	cout << l2.back() << endl;
	cout << "size: " << l2.size() << endl;
	List<int>::iterator it = l3.begin();

	for(int i=0;i<3;i++)
		cout << i <<": " << it[i] << endl;


	return 0;
}