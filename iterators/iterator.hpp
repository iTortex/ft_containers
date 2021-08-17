#pragma once

# include <iostream>

namespace ft {

	template<class T>
	class iterator {
		protected:
			T* _ptr;

		public:
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef value_type iterator_category;
			typedef std::ptrdiff_t difference_type;

			iterator() : _ptr(0) {}
			iterator(const iterator &ref): _ptr(ref._ptr)  {}
			iterator(const pointer ref): _ptr(ref) {}
			iterator &operator=(iterator const &ref) { _ptr = ref._ptr; return (*this); }
			iterator &operator= (const pointer ptr) { _ptr = ptr; return (*this); }
			virtual ~iterator() {}

			iterator operator+ (difference_type n) { return iterator(_ptr + n); }
			iterator &operator+= (difference_type n) { _ptr += n; return(*this);}
			iterator operator- (difference_type n) { return iterator(_ptr - n); }
			iterator &operator-= (difference_type n) { _ptr -= n; return(*this);}
			iterator operator++ (int) { iterator tmp(*this); ++(*this); return (tmp); }
			iterator operator-- (int) { iterator tmp(*this); --(*this); return (tmp); }
			iterator &operator++ () { ++_ptr; return (*this);  }
			iterator &operator-- () { --_ptr; return (*this); }
			reference operator* () const { return (*_ptr); }
			difference_type operator-(iterator const &ref) { return (this->_ptr - ref._ptr); }
			difference_type operator+(iterator const &ref) { return (this->_ptr + ref._ptr); }
			iterator base() { return (this); }
			reference operator[] (difference_type n) const { return (_ptr[n]); }
			T* operator->() const { return (_ptr); }

			template <template <typename> class const_iterator>
			operator const_iterator<const value_type>() { return const_iterator<const value_type>(_ptr); }


			bool operator!= (const iterator &ref) const { return (this->_ptr != ref._ptr); }
			bool operator== (const iterator &ref) const { return (this->_ptr == ref._ptr); }
			bool operator< (const iterator &ref) const { return (this->_ptr < ref._ptr); }
			bool operator> (const iterator &ref) const { return (this->_ptr > ref._ptr); }
			bool operator>= (const iterator &ref) const {return (this->_ptr >= ref._ptr); }
			bool operator<= (const iterator &ref) const {return (this->_ptr <= ref._ptr); }
	};
}