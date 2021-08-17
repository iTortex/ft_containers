#pragma once

# include "iterator.hpp"
# include <iostream>

namespace ft {

	template<class iterator>
	class reverse_iterator{

		public:
			typedef typename iterator::value_type value_type;
			typedef typename iterator::pointer pointer;
			typedef typename iterator::reference reference;
			typedef typename iterator::difference_type difference_type;

			reverse_iterator() : _ptr(0) {}
			reverse_iterator (const reverse_iterator &rev_it) : _ptr(rev_it._ptr) {}
			reverse_iterator (const pointer ptr): _ptr(ptr) {}
			reverse_iterator &operator=(reverse_iterator const &ref) { _ptr = ref._ptr; return (*this); }
			reverse_iterator &operator=(pointer const ptr) { _ptr = ptr; return (*this); }
			pointer operator-> () { return _ptr; }
			reference operator* () const { return *_ptr; }
			pointer base() const		{	
				pointer ptr = _ptr;
				ptr++;
				return(ptr);	}
			virtual ~reverse_iterator() {}

			reverse_iterator operator+ (difference_type n) { return reverse_iterator(_ptr - n); }
			reverse_iterator &operator+= (difference_type n) { _ptr -= n; return(*this);}
			reverse_iterator operator- (difference_type n) { return reverse_iterator(_ptr + n); }
			reverse_iterator &operator-= (difference_type n) { _ptr += n; return(*this);}
			reverse_iterator &operator++ (int) { --_ptr; return *this; }
			reverse_iterator operator++ () { return reverse_iterator(_ptr--); }
			reverse_iterator &operator-- (int) { ++_ptr; return *this; }
			reverse_iterator operator-- () { return reverse_iterator(_ptr++); }
			reference operator* () { return (*_ptr); }
			difference_type operator+ (reverse_iterator const &ref) { return (this->_ptr - ref._ptr); }
			difference_type operator- (reverse_iterator const &ref) { return (this->_ptr + ref._ptr); }
			pointer operator->() const { return (_ptr); }

			template <template <typename> class const_reverse_iterator>
			operator const_reverse_iterator<const value_type>() { return const_reverse_iterator<const value_type>(_ptr); }


			bool operator!= (const reverse_iterator &ref) const { return (this->_ptr != ref._ptr); }
			bool operator== (const reverse_iterator &ref) const { return (this->_ptr == ref._ptr); }
			bool operator> (const reverse_iterator &ref) const { return (this->_ptr > ref._ptr); }
			bool operator< (const reverse_iterator &ref) const { return (this->_ptr < ref._ptr); }
			bool operator>= (const reverse_iterator &ref) const { return (this->_ptr >= ref._ptr); }
			bool operator<= (const reverse_iterator &ref) const { return (this->_ptr <= ref._ptr); }

		protected:
			pointer _ptr;
	};
}