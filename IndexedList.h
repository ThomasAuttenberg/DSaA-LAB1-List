#pragma once
#include <compare>
#include <stdexcept>
#include <sstream>
#include <stack>


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

	Node* storage; // linear (+=storageCapacity) growing Node* array.
	//std::stack<size_t> storageIndexes;
	size_t firstFreeNodeIndex = 1;
	size_t lastFreeNodeIndex = INIT_LIST_SIZE - 1;
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
		const_iterator(const List<T>* list, size_t targetIndex);
		const List<T>* associatedContainer = nullptr;
	public:
		const_iterator();
		const_iterator(const iterator&);
		const_iterator(const const_iterator& other);
		T operator*() const;
		const_iterator operator++(int);
		const_iterator operator--(int);
		const_iterator& operator++();
		const_iterator& operator--();
		bool operator==(const const_iterator& other) const;
	};

	class iterator {
	private:
		friend class List<T>;
		size_t targetIndex;
		iterator(const List<T>* list, size_t targetIndex);
		const List<T>* associatedContainer = nullptr;
	public:
		iterator();
		T& operator*() const;
		iterator operator++(int);
		iterator operator--(int);
		iterator& operator++();
		iterator& operator--();
		bool operator==(const iterator& other) const;
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
	bool contains(const T& value) const;
	int getIndexOf(const T& value) const;
	// Access:
	T& front();
	T front() const;
	T& back();
	T back() const;
	T& at(size_t index);
	T at(size_t index) const;
	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;
	// Modifying:
	void clear();
	void push_back(const T& val);
	void push_front(const T& val);
	void pop_front();
	void pop_back();
	void insert(const_iterator, const T& val);
	void insertAt(size_t index, const T& val);
	void erase(const_iterator);
	void erase(const_iterator from, const_iterator to);
	void removeValue(const T& value);
	void removeAt(size_t index);

	// ================================

	// ======== Destructor ============
	~List();
	// ================================

};

template <class T>
size_t List<T>::INIT_LIST_SIZE = 2;

template <class T>
List<T>::List() {
	storage = new Node[storageCapacity];
	Node endNode;
	endNode.nextNodeIndex = -1;
	endNode.previousNodeIndex = -1;
	storage[0] = endNode;
	for (int i = 1; i < storageCapacity - 1; i++) {
		storage[i].nextNodeIndex = i + 1;
	}
	lastFreeNodeIndex = storageCapacity - 1;
	storage[lastFreeNodeIndex].nextNodeIndex = -1;
}

template<class T>
inline List<T>::List(List<T>& other)
{
	this->storage = new Node[other.storageCapacity];
	this->storageCapacity = other.storageCapacity;
	//this->storageIndexes = other.storageIndexes;
	this->head_index = other.head_index;
	this->tail_index = other.tail_index;
	this->firstFreeNodeIndex = other.firstFreeNodeIndex;
	this->lastFreeNodeIndex = other.lastFreeNodeIndex;
	memcpy(storage, other.storage, sizeof(Node) * storageCapacity);
	this->realSize = other.realSize;
}
template<class T>
inline List<T>::List(List<T>&& other) {
	this->storage = other.storage;
	this->storageCapacity = other.storageCapacity;
	//this->storageIndexes = std::move(other.storageIndexes);
	this->head_index = other.head_index;
	this->tail_index = other.tail_index;
	this->firstFreeNodeIndex = other.firstFreeNodeIndex;
	this->lastFreeNodeIndex = other.lastFreeNodeIndex;
	other.storage = nullptr;
	other.storageCapacity = 0;
	this->realSize = other.realSize;
}

template<class T>
inline List<T>::~List() {
	delete[] storage;
}

template<class T>
inline List<T>& List<T>::operator=(List<T>& other)
{
	if (this != &other) {
		delete[] storage;
		this->storage = new Node[other.storageCapacity];
		this->storageCapacity = other.storageCapacity;
		//this->storageIndexes = other.storageIndexes;
		memcpy(storage, other.storage, sizeof(Node) * storageCapacity);
		this->head_index = other.head_index;
		this->tail_index = other.tail_index;
		this->firstFreeNodeIndex = other.firstFreeNodeIndex;
		this->lastFreeNodeIndex = other.lastFreeNodeIndex;
		this->realSize = other.realSize;
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
		//this->storageIndexes = std::move(other.storageIndexes);
		other.storage = nullptr;
		other.storageCapacity = 0;
		this->head_index = other.head_index;
		this->tail_index = other.tail_index;
		this->firstFreeNodeIndex = other.firstFreeNodeIndex;
		this->lastFreeNodeIndex = other.lastFreeNodeIndex;
		this->realSize = other.realSize;
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
inline bool List<T>::contains(const T& val) const
{
	return getIndexOf(val) >= 0;
}

template<class T>
inline int List<T>::getIndexOf(const T& value) const
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
inline T& List<T>::front()
{
	if (size() == 0) throw std::exception("front call on empty list");
	return *begin();
}
template<class T>
inline T List<T>::front() const
{
	if (size() == 0) throw std::exception("front call on empty list");
	return *cbegin();
}
template<class T>
inline T& List<T>::back()
{
	if (size() == 0) throw std::exception("back call on empty list");
	return *end();
}
template<class T>
inline T List<T>::back() const
{
	if (size() == 0) throw std::exception("back call on empty list");
	return *cend();
}
template<class T>
inline T& List<T>::at(size_t index)
{
	if (index > realSize - 1 || index < 0) {
		std::ostringstream message;
		message << "List operation at: out of range\n[list size : " << realSize << " | index got : " << index << "]";
		throw new std::out_of_range(message.str());
	}

	iterator it = begin();
	for (int i = 0; i < index; i++) {
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
	return iterator(this, head_index);
}

template<class T>
inline List<T>::iterator List<T>::end()
{
	return iterator(this, tail_index);
}

template<class T>
inline List<T>::const_iterator List<T>::cbegin() const
{
	return const_iterator(this, head_index);
}

template<class T>
inline List<T>::const_iterator List<T>::cend() const
{
	return const_iterator(this, tail_index);
}

template<class T>
inline void List<T>::clear()
{

	this->realSize = 0;
	this->head_index = 0;
	this->tail_index = 0;
	//this->storageIndexes = std::move(std::stack<size_t>());
	for (int i = 1; i < storageCapacity-1; i++) {
		storage[i].nextNodeIndex = i + 1;
	}
	firstFreeNodeIndex = 1;
	lastFreeNodeIndex = storageCapacity - 1;

}
template<class T>
inline void List<T>::push_back(const T& val) {
	insert(end(), val);
}
template<class T>
inline void List<T>::push_front(const T& val) {
	insert(begin(), val);
}
template<class T>
inline void List<T>::pop_front() {
	if (size() == 0) throw std::exception("pop_front call on empty list");
	erase(begin());
}
template<class T>
inline void List<T>::pop_back() {
	if (size() == 0) throw std::exception("pop_back call on empty list");
	iterator it = --end();
	erase(it);
}
template<class T>
inline void List<T>::insert(const_iterator where, const T& val) {
	if (where.associatedContainer != this) throw new std::invalid_argument("Insert call using iterator isn't linked to that container");
	const_iterator tempIter = where;
	const_iterator nextNodeIter = where;
	const_iterator prevNodeIter;
	if (where != begin()) prevNodeIter = (--tempIter);

	Node newNode;

	newNode.value = val;
	newNode.nextNodeIndex = nextNodeIter.targetIndex;
	//newNode.previousNodeIndex = prevNode == nullptr ? -1 : prevNodeIter.targetIndex;
	size_t newNodeIndex = pushInContainer(newNode);

	Node* prevNode = where == begin() ? nullptr : storage + ((prevNodeIter).targetIndex);
	Node* nextNode = storage + ((nextNodeIter).targetIndex);

	if (prevNode == nullptr) {
		storage[newNodeIndex].previousNodeIndex = -1;
		head_index = newNodeIndex;
	}
	else {
		prevNode->nextNodeIndex = newNodeIndex;
		storage[newNodeIndex].previousNodeIndex = prevNodeIter.targetIndex;
	}
	nextNode->previousNodeIndex = newNodeIndex;
}
template<class T>
inline void List<T>::insertAt(size_t index, const T& val)
{
	iterator it = begin();
	for (int i = 0; i < index; i++) {
		it++;
	}
	insert(it, val);
}
template<class T>
inline void List<T>::erase(const_iterator it)
{
	if (it == end())
		throw std::invalid_argument("erase call using iterator pointing to the end of list");
	const_iterator a = it;
	a++;
	erase(it, a);
}
template<class T>
inline void List<T>::erase(const_iterator from, const_iterator to)
{
	if (from.associatedContainer != this || to.associatedContainer != this) throw new std::invalid_argument("erase call using iterator isn't linked to that container");
	if (from == to) return;
	bool isFromBegin = from == begin();
	const_iterator fromPrevious;
	if (!isFromBegin) { fromPrevious = --from; from++; };
	do {

		try {
			const_iterator tempIter = from++;
			storage[lastFreeNodeIndex].nextNodeIndex = tempIter.targetIndex;
			lastFreeNodeIndex = tempIter.targetIndex;
			Node* node = storage + tempIter.targetIndex;
			node->nextNodeIndex = -1;
			node->previousNodeIndex = -1;
			realSize--;
		}
		catch (std::logic_error) {
			throw new std::invalid_argument("erase call using invalid \"from\" iterator");
		}

	} while (from != to && from != end());

	if (!isFromBegin) {
		storage[to.targetIndex].previousNodeIndex = fromPrevious.targetIndex;
		storage[fromPrevious.targetIndex].nextNodeIndex = to.targetIndex;
	}
	else {
		head_index = to.targetIndex;
	}
}
template<class T>
inline void List<T>::removeValue(const T& value)
{
	const_iterator it = begin();

	while (it != end()) {
		const_iterator tempIter = it++;
		if (*tempIter == value)
			erase(tempIter);
	}

}
template<class T>
inline void List<T>::removeAt(size_t index)
{
	if (index >= realSize) throw new std::out_of_range("Out of range exception on calling removeAt");
	const_iterator it = begin();
	for (int i = 0; i < index; i++, it++);
	erase(it);
}
template<class T>
inline size_t List<T>::pushInContainer(Node& val) {

	if (realSize == storageCapacity - 1) { // 1 element is reserved to endNode
		Node* storage_ = new Node[storageCapacity + INIT_LIST_SIZE];
		memcpy(storage_, storage, sizeof(Node) * storageCapacity);
		for (int i = storageCapacity; i < storageCapacity - 1 + INIT_LIST_SIZE; i++) {
			//storageIndexes.push(i);
			storage_[i].nextNodeIndex = i + 1;
		}
		lastFreeNodeIndex = storageCapacity + INIT_LIST_SIZE - 1;
		firstFreeNodeIndex = storageCapacity;
		storageCapacity += INIT_LIST_SIZE;
		delete[] storage;
		storage = storage_;
	}
	size_t newElemIndex = firstFreeNodeIndex;
	if(firstFreeNodeIndex != lastFreeNodeIndex)
		firstFreeNodeIndex = storage[firstFreeNodeIndex].nextNodeIndex;
	
	storage[newElemIndex] = val;
	realSize++;
	return newElemIndex;
}

/*

		Iterators

*/

// const iterator

template<class T>
inline List<T>::const_iterator::const_iterator() {}

template<class T>
inline List<T>::const_iterator::const_iterator(const List<T>* list, size_t targetIndex) {
	this->targetIndex = targetIndex;
	this->associatedContainer = list;
}

template<class T>
inline List<T>::const_iterator::const_iterator(const List<T>::iterator& other) {
	this->targetIndex = other.targetIndex;
	this->associatedContainer = other.associatedContainer;
}
template<class T>
inline List<T>::const_iterator::const_iterator(const List<T>::const_iterator& other) {
	this->targetIndex = other.targetIndex;
	this->associatedContainer = other.associatedContainer;
}

template<class T>
inline T List<T>::const_iterator::operator*() const {
	if (*this == associatedContainer->cend()) throw std::logic_error("operator*: Can't get the value of the end element");
	if (this->associatedContainer == nullptr) throw std::logic_error("operator*: Iterator isn't linked to any container");
	return associatedContainer->storage[targetIndex].value;
}
template<class T>
inline List<T>::const_iterator& List<T>::const_iterator::operator++() {
	if (*this == associatedContainer->cend()) throw std::logic_error("operator++: Can't increment the iterator pointing at the end element");
	if (this->associatedContainer == nullptr) throw std::logic_error("operator++: Iterator isn't linked to any container");
	targetIndex = associatedContainer->storage[targetIndex].nextNodeIndex;
	return *this;
}
template<class T>
inline List<T>::const_iterator List<T>::const_iterator::operator++(int) {
	if (*this == associatedContainer->cend()) throw std::logic_error("operator++: Can't increment the iterator pointing at the end element");
	if (this->associatedContainer == nullptr) throw std::logic_error("operator++: Iterator isn't linked to any container");
	const_iterator tempIterator = *this;
	++(*this);
	return tempIterator;
}
template<class T>
inline List<T>::const_iterator& List<T>::const_iterator::operator--() {
	if (*this == associatedContainer->cbegin()) throw std::logic_error("operator--: Can't decriment the iterator pointing at the begin element");
	if (this->associatedContainer == nullptr) throw std::logic_error("operator--: Iterator isn't linked to any container");
	targetIndex = associatedContainer->storage[targetIndex].previousNodeIndex;
	return *this;
}
template<class T>
inline List<T>::const_iterator List<T>::const_iterator::operator--(int) {
	if (*this == associatedContainer->cbegin()) throw std::logic_error("operator--: Can't decriment the iterator pointing at the begin element");
	if (this->associatedContainer == nullptr) throw std::logic_error("operator--: Iterator isn't linked to any container");
	const_iterator tempIterator = *this;
	--(*this);
	return tempIterator;
}
template<class T>
inline bool List<T>::const_iterator::operator==(const List<T>::const_iterator& other) const {
	if (other.associatedContainer == this->associatedContainer && this->targetIndex == other.targetIndex)
		return true;
	return false;
}

// non const iterator

template<class T>
inline List<T>::iterator::iterator() {}

template<class T>
inline List<T>::iterator::iterator(const List<T>* list, size_t targetIndex) {
	associatedContainer = list;
	this->targetIndex = targetIndex;
}
template<class T>
inline T& List<T>::iterator::operator*() const {
	if (*this == associatedContainer->cend()) throw std::logic_error("operator*: Can't get the value of the end element");
	if (this->associatedContainer == nullptr) throw std::logic_error("operator*: Iterator isn't linked to any container");
	return (associatedContainer->storage[targetIndex].value);
}
template<class T>
inline List<T>::iterator& List<T>::iterator::operator++() {
	if (*this == associatedContainer->cend()) throw std::logic_error("operator++: Can't increment the iterator pointing at the end element");
	if (this->associatedContainer == nullptr) throw std::logic_error("operator++: Iterator isn't linked to any container");
	targetIndex = associatedContainer->storage[targetIndex].nextNodeIndex;
	return *this;
}
template<class T>
inline List<T>::iterator List<T>::iterator::operator++(int) {
	if (*this == associatedContainer->cend()) throw std::logic_error("operator++: Can't increment the iterator pointing at the end element");
	if (this->associatedContainer == nullptr) throw std::logic_error("operator++: Iterator isn't linked to any container");
	iterator tempIterator = *this;
	++(*this);
	return tempIterator;
}
template<class T>
inline List<T>::iterator& List<T>::iterator::operator--() {
	if (*this == associatedContainer->cbegin()) throw std::logic_error("operator--: Can't decriment the iterator pointing at the begin element");
	if (this->associatedContainer == nullptr) throw std::logic_error("operator--: Iterator isn't linked to any container");
	targetIndex = associatedContainer->storage[targetIndex].previousNodeIndex;
	return *this;
}
template<class T>
inline List<T>::iterator List<T>::iterator::operator--(int) {
	\
		if (*this == associatedContainer->cbegin()) throw std::logic_error("operator--: Can't decriment the iterator pointing at the begin element");
	if (this->associatedContainer == nullptr) throw std::logic_error("operator--: Iterator isn't linked to any container");
	iterator tempIterator = *this;
	--(*this);
	return tempIterator;
}
template<class T>
inline bool List<T>::iterator::operator==(const List<T>::iterator& other) const {
	if (other.associatedContainer == this->associatedContainer && this->targetIndex == other.targetIndex)
		return true;
	return false;
}
