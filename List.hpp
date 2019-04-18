// Assignment 1 COP4530
// Ryan Winter
// 10/12/17 (Fall 2017)
// Some code sourced from in lecture examples

template <class T>
List<T>::const_iterator::const_iterator(){
    current = nullptr;
}

template <class T>
const T & List<T>::const_iterator::operator*() const{
    return retrieve();
}

template <class T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++(){
    current = current->next;
    return(*this);
}

template <class T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int){
    const_iterator old = *this;
    ++(*this); // move one spot.. segfault if this is post increment
    return old;
}

template <class T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--(){
    current = current->prev;
    return(*this);
}

template <class T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int){
    const_iterator old = *this;
    --(*this); // move one spot
    return old;
}

template <class T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const{
	return(current == rhs.current);
}

template <class T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const{
	return(current != rhs.current);
}

template <class T>
T & List<T>::const_iterator::retrieve() const{
    return(current->data);
}

template <class T>                
List<T>::const_iterator::const_iterator(Node * p){
	current = p;
}

template <class T>
List<T>::iterator::iterator(){
    init();
}

template <class T>
T & List<T>::iterator::operator*(){
    return(const_iterator::retrieve());
}

template <class T>
const T & List<T>::iterator::operator*() const{
    return(const_iterator::operator*());
}

template <class T>
typename List<T>::iterator & List<T>::iterator::operator++(){ // increment overload
    this->current = this->current->next;
    return(*this);
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator++(int){ // increment overload
    iterator old = *this;
    ++(*this);
    return old;
}

template <class T>                
typename List<T>::iterator & List<T>::iterator::operator--(){ // decrement overload
    this->current = this->current->prev;
    return(*this);
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator--(int){ // decrement overload
    iterator old = *this;
    --(*this);
    return old;
}

template <class T>
List<T>::iterator::iterator(Node * p){
	this->current = p;
}

template <class T>
List<T>::List(){ // constructor
    init();
}

template <class T>
List<T>::List(const List &rhs){ // copy constructor
    init();
    auto itr = rhs.begin();
    for(int i = 0; i < rhs.size(); i++){
        push_back(*itr);
        itr++;
    }
}

template <class T>
List<T>::List(List && rhs){ // move constructor
    theSize = rhs.theSize;
    head = rhs.head;
    tail = rhs.tail;
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template <class T>
List<T>::List(int num, const T& val){ // constructor 
    init();
    for(int i = 0; i < num; i++){ // loop through list adding val
        push_back(val);
    }
}

template <class T>
List<T>::List(const_iterator start, const_iterator end){ // 2 param constructor
    init();
    auto itr = start;
	do{
		push_back(*itr);
		itr++;
	}while(itr != end);
} 

template <class T>
List<T>::List(std::initializer_list<T> iList){
    init();
    for(T i : iList)
		push_back(i);
}

template <class T>
List<T>::~List(){ // destructor
    if(empty() == false) // if empty just delete head/tail. if not empty, clear then delete head/tail
		clear();
    delete head;
    delete tail;
}

template <class T>
const List<T>& List<T>::operator=(const List &rhs){ // copy operator
    clear();
    auto itr = rhs.begin();
    for(int i = 0; i < rhs.size(); i++){
        push_back(itr.retrieve());
        itr++;
    }
    return *this;
}

template <class T>
List<T> & List<T>::operator=(List && rhs){ // move operator
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
}

template <class T>
List<T>& List<T>::operator=(std::initializer_list<T> iList){
	init();
    for(T i : iList)
        push_back(i);
}

template <class T>
int List<T>::size() const{ // return size
    return theSize;
}

template <class T>
bool List<T>::empty() const{ // return false if list great than 0, true otherwise
    if(theSize > 0)
		return false;
	else
		return true;
}

template <class T>
void List<T>::clear(){ // clear list
    auto itr = begin();
    while(itr.current != tail){
        itr = erase(itr);
    }
}

template <class T>
void List<T>::reverse(){ // reverse list
    auto itr = end();
	List<T> newlist;
    itr--;
    for(int i = 0; i < theSize; i++){
        newlist.push_back(*itr);  
        itr--;
    }
    *this = newlist; // reassign pointer
}

template <class T>
T& List<T>::front(){ // point to first item
    return(head->next->data);
}          

template <class T>
const T& List<T>::front() const{ // point to first item
    return(head->next->data);
}

template <class T>
T& List<T>::back(){ // point to last item
    return(tail->prev->data);
}
          
template <class T>
const T& List<T>::back() const{  // point to last item
    return(tail->prev->data);
}  

template <class T>
void List<T>::push_front(const T & val){ // push to front of list
	insert(begin(), val);
}

template <class T>
void List<T>::push_front(T && val){ // push to front of list
	insert(begin(), std::move(val));
}

template <class T>
void List<T>::push_back(const T & val){ // push to end of list
	insert(end(), val);
}

template <class T>
void List<T>::push_back(T && val){ // push to end of list
    insert(end(), std::move(val));
}

template <class T>
void List<T>::pop_front(){ // remove first 
    erase(begin());
}

template <class T>
void List<T>::pop_back(){ // remove last
    erase(end().current->prev);
}
template <class T>
void List<T>::remove(const T &val){ // remove val
    auto itr = begin();
	do{
		if(itr.retrieve() == val)
			itr = erase(itr);
        else 
			++itr;
	}while(itr != end());
}

template <class T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred){  // remove all elements for which Predicate pred
    auto itr = begin();
    do{
		if(pred(*itr) == true)
			itr = erase(itr);
        else
			++itr;
	}while(itr != end());
}

template <class T> 
void List<T>::print(std::ostream& os, char ofc) const{ // print
    const_iterator itr = begin();
    for(int i = 0; i < theSize - 1; i++){
        os << itr.retrieve() << ofc;
        itr++;
	}
    os << itr.retrieve();
}

template <class T>
typename List<T>::iterator List<T>::begin(){ // front of list
    return iterator(head->next);
}

template <class T>
typename List<T>::const_iterator List<T>::begin() const{ // const front of list
    return const_iterator(head->next);
}

template <class T>
typename List<T>::iterator List<T>::end(){ // end of list
    return iterator(tail);
}          

template <class T>
typename List<T>::const_iterator List<T>::end() const{ // const end of list
    return const_iterator(tail);
}

template <class T> 
typename List<T>::iterator List<T>::insert(iterator itr, const T& val){ // insert
    Node *p = itr.current; // sourced from lecture slides
    ++theSize;
    return iterator(p->prev = p->prev->next = new Node{val, p->prev, p});
}

template <class T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val){
	Node *p = itr.current; // sourced from lecture slides
    ++theSize;
    return iterator(p->prev = p->prev->next = new Node{val, p->prev, p});
}

template <class T>
typename List<T>::iterator List<T>::erase(iterator itr){ // remove
    Node *p = itr.current; // sourced from lecture slides
    iterator retval(p->next);
    p->prev->next = p->next;      
    p->next->prev = p->prev;
    delete p;
    theSize--;
    return retval;
}

template <class T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end){ // loop through and remove all
	iterator itr = start;
	for(int i = 0; i < theSize - 1; i++)
		itr = erase(itr);
}

template <class T>
void List<T>::init(){
	theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;	
}

template <typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs){ // == overload
    auto itrlhs = lhs.begin();
    auto itrrhs = rhs.begin();

	if(lhs.size() != rhs.size())
		return false;
	
	do{
		if(*itrlhs != *itrrhs) // iterate through list checking each one.. 
			return false;
        ++itrlhs;
        ++itrrhs;
	}while(itrlhs != lhs.end());
    
    return true;
}

template <typename T>
bool operator!=(const List<T> &lhs, const List<T> &rhs){ // opposite of == operation
    return !(lhs == rhs);
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l){ // output overload
    l.print(os);
}