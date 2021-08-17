#pragma once

#include <iostream>

template <class T>
class node_map
{	
	public:
		T				_val;
		unsigned char	_height;
		node_map*		_left;
		node_map*		_right;
		node_map*		_parent;
		bool			_check;

		node_map() : _height(1), _left(0), _right(0), _parent(0), _check(0)  {}
		node_map(T k) :_val(k), _height(1), _left(0), _right(0), _parent(0), _check(1) {}
		node_map(node_map const &ref) { *this = ref; }
		node_map	&operator=(node_map const &ref)
		{
			_val = ref._val;
			_height = ref._height;
			_left = ref._left;
			_right = ref._right;
			_parent = ref._parent;
			_check = ref._check;
		}
};