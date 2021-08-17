#pragma once

template <class T>
class Node {
	public:
		T		_val;
		Node	*_next;
		Node	*_prev;

		Node() : _next(0), _prev(0) {}
		Node(const Node &ptr)	{ *this = ptr; }
		Node	&operator=(const Node &ptr)
		{
			if (this != &ptr)
			{
				this->_next = ptr->_next;
				this->_prev = ptr->_prev;
				this->_val = ptr->_val;
			}
			return (*this);
		}
		Node(const T &val) : _val(val), _next(0), _prev(0) {}
		Node *getnext() { return (_next); }
		Node *getprev() { return (_prev); }
		Node *getval() { return (_val); }		
};