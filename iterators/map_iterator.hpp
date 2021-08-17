#pragma once

# include "../map/ft_map.hpp"

template <class T>
class iteratormap
{
	public:
		node_map<T> *_ptr;
		avl_tree<T> func;
		int ggs;
	public:
	typedef T *pointer;
	typedef T &reference;

	iteratormap() : _ptr(0), ggs(0){}

	iteratormap(node_map<T> *ref)
	{
		ggs = 0;
		_ptr = ref;
	}
	iteratormap(iteratormap const &ref)
	{
		*this = ref;
	}
	iteratormap &operator=(iteratormap const &ref) 
	{
		ggs = ref.ggs;
		_ptr = ref._ptr;
		return (*this);
	}
	pointer operator->() { return( &_ptr->_val ); }
	reference operator*() { return( _ptr->_val ); }


	template <template <typename> class const_iteratormap>
	operator const_iteratormap<const T>() { return const_iteratormap<const T>((node_map<const T>*)_ptr); }

	iteratormap &operator++()
	{
		if (_ptr->_right)
			_ptr = func.findmin(_ptr->_right);
		else if (_ptr != func.get_end())
		{
			while (_ptr->_parent && _ptr->_parent->_right == _ptr)
				_ptr = _ptr->_parent;
			_ptr = _ptr->_parent;
			if (_ptr == NULL)
				_ptr = func.get_end();
		}
		else
			_ptr->_left->_parent = NULL;
		return (*this);
	}

	iteratormap operator++(int)
	{
		iteratormap it = _ptr;
		iteratormap it_ret = _ptr;
		++it;
		_ptr = it._ptr;
		return (it_ret);
	}

	iteratormap &operator--()
	{
		if (_ptr->_left)
			_ptr = func.findmax(_ptr->_left);
		else
		{
			while (_ptr->_parent && _ptr->_parent->_left == _ptr)
				_ptr = _ptr->_parent;
			_ptr = _ptr->_parent;
		}
		return (*this);
	}

	iteratormap operator--(int)
	{
		iteratormap it = _ptr;
		iteratormap it_ret = _ptr;
		--it;
		_ptr = it._ptr;
		return (it_ret);
	}

	bool operator!= (const iteratormap<T> &ref) { return (_ptr != ref._ptr); }
	bool operator> (const iteratormap<T> &ref) { return (_ptr > ref._ptr); }
	bool operator< (const iteratormap<T> &ref) { return (_ptr < ref._ptr); }
	bool operator== (const iteratormap<T> &ref) { return (_ptr == ref._ptr); }
	
};

template <class T>
class rev_iteratormap
{
	public:
		node_map<T> *_ptr;
		avl_tree<T> func;
		int ggs;
	public:
	typedef T *pointer;
	typedef T &reference;

	rev_iteratormap() : _ptr(0), ggs(0){}

	rev_iteratormap(node_map<T> *ref)
	{
		ggs = 0;
		_ptr = ref;
	}
	rev_iteratormap(rev_iteratormap const &ref)
	{
		*this = ref;
	}
	rev_iteratormap &operator=(rev_iteratormap const &ref) 
	{
		ggs = ref.ggs;
		_ptr = ref._ptr;
		return (*this);
	}
	pointer operator->() { return( &_ptr->_val ); }
	reference operator*() { return( _ptr->_val ); }


	template <template <typename> class const_rev_iteratormap>
	operator const_rev_iteratormap<const T>() { return const_rev_iteratormap<const T>((node_map<const T>*)_ptr); }

	rev_iteratormap &operator--()
	{
		if (_ptr->_right)
			_ptr = func.findmin(_ptr->_right);
		else if (_ptr != func.get_end())
		{
			while (_ptr->_parent && _ptr->_parent->_right == _ptr)
				_ptr = _ptr->_parent;
			_ptr = _ptr->_parent;
			if (_ptr == NULL)
				_ptr = func.get_end();
		}
		else
			_ptr->_left->_parent = NULL;
		return (*this);
	}

	rev_iteratormap operator--(int)
	{
		rev_iteratormap it = _ptr;
		rev_iteratormap it_ret = _ptr;
		++it;
		_ptr = it._ptr;
		return (it_ret);
	}

	rev_iteratormap &operator++()
	{
		if (_ptr->_left)
			_ptr = func.findmax(_ptr->_left);
		else
		{
			while (_ptr->_parent && _ptr->_parent->_left == _ptr)
				_ptr = _ptr->_parent;
			_ptr = _ptr->_parent;
		}
		return (*this);
	}

	rev_iteratormap operator++(int)
	{
		rev_iteratormap it = _ptr;
		rev_iteratormap it_ret = _ptr;
		--it;
		_ptr = it._ptr;
		return (it_ret);
	}

	bool operator!= (const rev_iteratormap<T> &ref) { return (_ptr != ref._ptr); }
	bool operator> (const rev_iteratormap<T> &ref) { return (_ptr > ref._ptr); }
	bool operator< (const rev_iteratormap<T> &ref) { return (_ptr < ref._ptr); }
	bool operator== (const rev_iteratormap<T> &ref) { return (_ptr == ref._ptr); }
	
};