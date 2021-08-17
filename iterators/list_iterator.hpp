#pragma once

# include <iostream>
# include "../list/ft_node.hpp"

namespace ft {

	template<class T>
	class literator {
		protected:
			Node<T> *_ptr;
		public:
			typedef  T*		pointer;
			typedef  T&		reference;
			typedef  std::ptrdiff_t	difference_type;

			literator() : _ptr(0) {}
			literator(const literator &ref) { *this = ref; }

			literator(Node<T> *ref) : _ptr(ref) {}
			
			literator	&operator=(const literator &ref)
			{
				_ptr = ref._ptr;
				return (*this);
			}

			literator(const T *ref) : _ptr(ref) {}
			virtual ~literator() {}

			T &operator* () { return (_ptr->_val); }
			T *operator-> () { return (&_ptr->_val); }

			template <template <typename> class const_literator>
			operator const_literator<const T>() { return const_literator<const T>((Node<const T>*)_ptr); }
			
			literator operator++ (int) { literator it(*this); ++(*this); return (it); }
			literator operator-- (int) { literator it(*this); --(*this); return (it); }
			literator &operator-- () { _ptr = _ptr->_prev; return *this; }
			literator &operator++ () { _ptr = _ptr->_next; return *this; }
			Node<T> *getnode() 	{ return(_ptr); }

			bool operator<(const literator<T> &ref) { return (_ptr < ref._ptr); }
			bool operator>(const literator<T> &ref) { return (_ptr > ref._ptr); }
			bool operator== (const literator<T> &ref) { return (_ptr == ref._ptr); }
			bool operator!= (const literator<T> &ref) { return !(_ptr == ref._ptr); }
	};

	template<class T>
	class reverse_literator
	{
		private:
			Node<T> *_ptr;;
		public:
			reverse_literator() : _ptr(0) {}
			reverse_literator(const reverse_literator &ref) { *this = ref; }

			reverse_literator(Node<T> *ref) : _ptr(ref) {}
			
			reverse_literator	&operator=(const reverse_literator &ref)
			{
				_ptr = ref._ptr;
				return (*this);
			}

			reverse_literator(const T *ref) : _ptr(ref) {}
			virtual ~reverse_literator() {}

			T &operator* () { return (_ptr->_val); }
			T &operator-> () { return (_ptr->_val); }

			template <template <typename> class const_reverse_literator>
			operator const_reverse_literator<const T>() { return const_reverse_literator<const T>((Node<const T>*)_ptr); }
			
			reverse_literator operator++ (int) { reverse_literator it(*this); ++(*this); return (it); }
			reverse_literator operator-- (int) { reverse_literator it(*this); --(*this); return (it); }
			reverse_literator &operator-- () { _ptr = _ptr->next; return (*this); }
			reverse_literator &operator++ () { _ptr = _ptr->_prev; return (*this); }
			Node<T> *getnode() 	{ return(_ptr); }

			bool operator<(const reverse_literator &ref) { return (this->_ptr < ref._ptr); }
			bool operator>(const reverse_literator &ref) { return (this->_ptr > ref._ptr); }
			bool operator== (const reverse_literator &ref) { return (this->_ptr == ref._ptr); }
			bool operator!= (const reverse_literator &ref) const { return !(this->_ptr == ref._ptr); }
	};
}