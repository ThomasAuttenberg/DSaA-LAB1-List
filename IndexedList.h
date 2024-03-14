#pragma once
#include <compare>
#include <stdexcept>
#include <sstream>


template <class T>
class List
{
static size_t INIT_LIST_SIZE;
private:
	size_t head_index = 0; // storage index where the first element is located
	size_t tail_index = 0; // ...
	
	struct Node {
		T value;
		size_t previousNodeIndex;
		size_t nextNodeIndex;
	};

	/*
	*  Structure graphic description:
	*________________________________________________________ 
	* array |
	* index |      [    1   ]  ...  [   115  ]  ...
	*_______|_______________________________________________ 
	* val:	|      [   5    ]       [  1.25  ] 
	* prev  |      [   115  ]  ...  [   -1   ]  ...    
	* next  |      [    2   ]       [   1    ]
	*_______|________________________________________________                     
	*       |          |               |
	* link: |          -----------------
	*/                             

	Node* storage; // exponentially growing Node* array.
	size_t storageCapacity = INIT_LIST_SIZE;
	size_t realSize = 0;

	size_t pushInContainer(Node& val);

public:


// ============ Iterators ==================
	class iterator;
	class const_iterator {
	private:
		friend class List;
		size_t targetIndex;
		const_iterator(size_t targetIndex);
	public:
		const_iterator(iterator);
		T operator*() const;
		const_iterator& operator++(int);
		const_iterator& operator--(int);
		const_iterator& operator++();
		const_iterator& operator--();
		bool operator==(const const_iterator& other);
		const_iterator& operator=(const const_iterator& other);
	};

	class iterator {
	private:
		friend class List<T>;
		size_t targetIndex;
		iterator(size_t targetIndex);
		List<T>& associatedContainer;
	public:
		iterator();
		T& operator*() const;
		iterator& operator++(int);
		iterator& operator--(int);
		iterator& operator++();
		iterator& operator--();
		bool operator==(const iterator& other) const;
		iterator& operator=(const iterator& other); // index copying
	};
	//using Iterator = IndexedList<T>::iterator;
// ============ Methods ==================
	
  // ===== the rule of five =========
	List();
	List(List<T>& other);
	List(List<T>&& other);
	List& operator=(List<T>& other);
	List& operator=(List<T>&& other);
  // ================================

  // ========= Operations ===========	
	// Informational:
	size_t size() const;
	bool isEmpty() const;
	//bool contains(T& value);
	int getIndexOf(T& value) const;
	// Access:
	T& at(size_t index);
	T at(size_t index) const;
	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;
	// Modifying:
	void clear();
	void push_back(T& val);
	void push_front(T& val);
	void insert(const_iterator, T& val);
	void insertAt(size_t index);
	void erase(const_iterator);
	void erase(const_iterator from, const_iterator to);
	void removeValue(T& value);
	void removeAt(size_t index);

  // ================================

  // ======== Destructor ============
	~List();
  // ================================

};

template <class T>
size_t List<T>::INIT_LIST_SIZE = 50;

template <class T>
List<T>::List() {
	storage = new Node[storageCapacity];
	Node endNode;
	endNode.nextNodeIndex = -1;
	endNode.previousNodeIndex = -1;
	storage[0] = endNode;
}

template<class T>
inline List<T>::List(List<T>& other)
{
	this->storage = new Node[other.storageCapacity];
	this->storageCapacity = other.storageCapacity;
	memcpy(storage, other.storage, sizeof(Node) * storageCapacity);
}
template<class T>
inline List<T>::List(List<T>&& other) {
	this->storage = other.storage;
	this->storageCapacity = other.storageCapacity;
	other.storage = nullptr;
	other.storageCapacity = 0;
}

template<class T>
inline List<T>& List<T>::operator=(List<T>& other)
{
	if (this != &other) {
		delete[] storage;
		this->storage = new Node[other.storageCapacity];
		this->storageCapacity = other.storageCapacity;
		memcpy(storage, other.storage, sizeof(Node) * storageCapacity);
	}
	return *this;
}

template<class T>
inline List<T>& List<T>::operator=(List<T>&& other)
{
	if (this != &other) {
		delete[] storage;
		this->storage = other.storage;
		this->storageCapacity = other.storageCapacity;
		other.storage = nullptr;
		other.storageCapacity = 0;
	}
	return *this;
}

template<class T>
inline size_t List<T>::size() const
{
	return realSize;
}

template<class T>
inline bool List<T>::isEmpty() const
{
	return realSize == 0;
}

template<class T>
inline int List<T>::getIndexOf(T& value) const
{
	const_iterator it = cbegin();
	const_iterator end = this->cend();
	int index = 0;
	while (it != end) {
		if (*it == value) return index;
		index++; it++;
	}
	return -1;
}

template<class T>
inline T& List<T>::at(size_t index)
{
	if (index > realSize || index < 0) {
		std::ostringstream message;
		message << "List operation at: out of range\n[list size : " << realSize << " | index got : " << index << "]";
		throw new std::out_of_range(message.str());
	}

	iterator it = begin();
	for (int i = 0; i <= index; i++) {
		it++;
	}
	return *it;
}

template<class T>
inline T List<T>::at(size_t index) const
{
	return at(index);
}

template<class T>
inline List<T>::iterator List<T>::begin()
{
	return iterator(head_index);
}

template<class T>
inline List<T>::iterator List<T>::end()
{
	return iterator(tail_index);
}

template<class T>
inline List<T>::const_iterator List<T>::cbegin() const
{
	return const_iterator(head_index);
}

template<class T>
inline List<T>::const_iterator List<T>::cend() const
{
	return const_iterator(tail_index);
}

template<class T>
inline void List<T>::clear()
{
	delete[] storage;
	storage = new Node[INIT_LIST_SIZE];
	storageCapacity = INIT_LIST_SIZE;
	realSize = 0;

}
template<class T>
inline void List<T>::push_back(T& val) {
	insert(end(), val);
}
template<class T>
inline void List<T>::push_front(T& val) {
	insert(begin(), val);
}
template<class T>
inline void List<T>::insert(const_iterator where, T& val) {
	
	const_iterator tempIter = where;
	const_iterator nextNodeIter = where;
	const_iterator prevNodeIter;
	if (where != begin()) prevNodeIter = (tempIter--).targetIndex;
	Node* prevNode = where == begin() ? nullptr : storage + ((prevNodeIter).targetIndex);
	Node* nextNode = storage + ((nextNodeIter).targetIndex);
	
	Node newNode;
	
	newNode.value = val;
	newNode.nextNodeIndex = nextNodeIter.targetIndex;
	//newNode.previousNodeIndex = prevNode == nullptr ? -1 : prevNodeIter.targetIndex;
	size_t newNodeIndex = pushInContainer(newNode);
	if (prevNode == nullptr) {
		newNode.previousNodeIndex = -1;
		head_index = newNodeIndex;
	}
	else {
		newNode.previousNodeIndex = prevNodeIter.
	}
	prevNode->nextNodeIndex = newNodeIndex;
	nextNode->previousNodeIndex = newNodeIndex;
}
template<class T>

inline size_t List<T>::pushInContainer(Node& val) {
	
	if (realSize-1 == storageCapacity) {
		Node* storage_ = new Node[storageCapacity + INIT_LIST_SIZE];
		memcpy(storage_, storage, sizeof(Node) * storageCapacity);
		storageCapacity += INIT_LIST_SIZE;
		delete[] storage;
		storage = storage_;
	}
	storage[++realSize] = val;
	return realSize;
}






