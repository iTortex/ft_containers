#pragma once

# include "../iterators/iterator.hpp"
# include "../iterators/reverse_iterator.hpp"
# include <typeinfo>
# include <sstream>
# include <limits>

namespace ft {

	template <class Type, class Allocator = std::allocator<Type> >
	class vector {
		public:
			typedef Type value_type;
			typedef Type *pointer;
			typedef Type &reference;
			typedef iterator<Type> iterator;
			typedef ft::iterator<const value_type> const_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef Allocator allocator_type;
			typedef size_t size_type;


			vector()
			{
				_size = 0;
				_capacity = 0;
				_ptr = _alc.allocate(_capacity);
			}

			explicit vector(size_type n, const value_type &val = value_type())
			{
				_size = 0;
				_capacity = n;
				_ptr = _alc.allocate(_capacity);
				assign(_capacity, val);
			}

			vector(iterator first, iterator last)
			{
				_size = 0;
				_capacity = 0;
				_ptr = _alc.allocate(_capacity);
				this->assign(first, last);
			}

			vector(const vector &x)
			{
				_size = 0;
				_capacity = 0;
				_ptr = _alc.allocate(_capacity);
				assign(x.begin(), x.end());
			}

			~vector()
			{
				_size = 0;
				_alc.deallocate(_ptr, _capacity);
				_capacity = 0;
			}
			vector<Type> &operator=(vector<Type> const &ref)
			{
				_alc.deallocate(_ptr, _capacity);
				this->_size = ref._size;
				this->_capacity = ref._capacity;
				this->_ptr = _alc.allocate(_capacity);
				for (size_type i = 0; i < _size && ref.size() != 0; i++)
					this->_ptr[i] = ref._ptr[i];
				return (*this);
			}

			const_iterator begin() const
			{
				return (_ptr);
			}

			iterator begin()
			{
				return (_ptr);
			}

			const_iterator end() const
			{
				return (_ptr + _size);
			}
			
			iterator end()
			{
				return (_ptr + _size);
			}

			void	assign(size_type count, const Type &value)
			{
				if (count < 0)
					return ;
				while (_capacity < count && _capacity != 0)
					_capacity *= 2;
				if (_capacity == 0)
					_capacity = count;
				_alc.deallocate(_ptr, _capacity);
				_size = count;
				_ptr = _alc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alc.construct(&_ptr[i], value);
			}
			
			template <typename _Val, template< typename > class _InputIterator>
			void	assign(_InputIterator<_Val> first, _InputIterator<_Val> second)
			{
				_InputIterator<_Val> it;
				it = begin();
				if (first == begin() && second == end())
					return ;
				_size = second - first;
				if (_size > max_size())
				{
					_size = 0;
					_capacity = 0;
					throw std::invalid_argument("vector");
				}
				if (_capacity < _size)
					_capacity = _size;
				while (it != first && it != second && it != end())
					it++;
				if (it != first && it != second)
					_alc.deallocate(_ptr, _capacity);
				int i = 0;
				_ptr = _alc.allocate(_capacity);

				while (first != second)
				{
					_ptr[i] = *first;
					i++;
					first++;
				}
			}


			size_type	size() const	{ return (_size); }
			size_type	max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }

			void		push_back(const Type &value)
			{
				ft::vector<Type> news;
				news = *this;
				Type _val = value;
				while (_capacity < (_size + 1) && _capacity != 0)
					_capacity *= 2;
				if (_capacity == 0)
					_capacity = (_size + 1);
				_alc.deallocate(_ptr, _capacity + 2);
				_ptr = _alc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_ptr[i] = news._ptr[i];
				_ptr[_size] = _val;
				_size++;
			}

			void		pop_back()
			{
				if (_size)
					_alc.destroy(&_ptr[--_size]);
			}

			reverse_iterator rbegin()	{ return (_ptr + _size - 1); }

			reverse_iterator rend()	{ return (_ptr - 1); }

			const_reverse_iterator rbegin() const	{ return (_ptr + _size - 1); }

			const_reverse_iterator rend() const	{ return (_ptr - 1); }

			reference	back() { return (_ptr[_size - 1]); }
			
			reference	at(size_type pos) { 
				if (pos > max_size())
					throw std::invalid_argument("vector");
				if (pos > _size)
					throw std::invalid_argument("vector");
				return (_ptr[pos]); 
			}
			
			reference	operator[](size_type pos) { return (_ptr[pos]); }

			void		resize(size_type n, value_type val = value_type())
			{
				ft::vector<Type> news;
				news = *this;
				if (n > max_size())
					throw std::invalid_argument("vector");
				if (n == _size || n < 0)
					return;
				while (_capacity < n)
					_capacity *= 2;
				_alc.deallocate(_ptr, _capacity);
				if (n < _size)
				{
					_size = n;
					_ptr = _alc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_ptr[i] = news._ptr[i];
				}
				else if (n > _size)
				{
					_ptr = _alc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_ptr[i] = news._ptr[i];
					for (; _size < n; _size++)
						_ptr[_size] = val;
					_size = n; 
				}
			}

			size_type	capacity() const
			{
				return (_capacity);
			}

			bool		empty() const
			{
				if (_size == 0)
					return (true);
				return false;
			}

			void		reserve(size_type n)
			{
				if (n > max_size())
					throw std::invalid_argument("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				if (n < 0 || _capacity >= n)
					return ;
				ft::vector<Type> news;
				news = *this;
				_capacity = n;
				_alc.deallocate(_ptr, _capacity);
				_ptr = _alc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_ptr[i] = news._ptr[i];
			}

			reference front()
			{
				return (_ptr[0]);
			}

			iterator insert (iterator position, const Type &val)
			{
				Type value = val;
				if (_capacity < _size + 1 && _capacity != 0)
					_capacity *= 2;
				if (_capacity == 0)
					_capacity = 1;
				size_t i = 0;
				ft::vector<Type> news;
				news = *this;
				iterator check = begin();
				_alc.deallocate(_ptr, _capacity);
				_ptr = _alc.allocate(_capacity);
				while (check != position)
				{
					_ptr[i] = news._ptr[i];
					i++;
					check++;
				}
				_ptr[i] = value;
				check = &_ptr[i];
				i++;
				_size++;
				while (i < _size)
				{
					_ptr[i] = news._ptr[i - 1];
					i++;
				}
				return (check);
			}
			
			void	insert(iterator position, size_type n, const value_type &val)
			{
				Type value = val;
				if (_capacity < n)
					_capacity = _size + n;
				while (_capacity < _size + n && _capacity != 0)
					_capacity *= 2;
				if (_capacity == 0)
					_capacity = _size + n;
				size_type i = 0;
				pointer ptr = _ptr;
				ft::vector<Type> news;
				news = *this;
				iterator check = ptr;
				_alc.deallocate(_ptr, _capacity);
				_ptr = _alc.allocate(_capacity);
				while (check != position)
				{
					_ptr[i] = news._ptr[i];
					i++;
					check++;
				}
				for (size_type j = 0; j < n; j++)
				{
					_ptr[i] = value;
					i++;
				}
				_size += n;
				while (i < _size)
				{
					_ptr[i] = news._ptr[i - n];
					i++;
				}
			}

			void insert(iterator position, iterator first, iterator last)
			{
				size_type n = last - first;
				vector<Type> tmp;
				if (n > max_size())
					throw std::invalid_argument("vector");
				if (_capacity < _size + n)
				{
					if (_capacity * 2 < _size + n)
						_capacity = _size + n;
					else
						_capacity *= 2;
					if (_capacity == 0)
						_capacity = _size + n;
				}
				vector news;
				news = *this;
				int i = 0;
				for (iterator it = begin(); it != position; it++)
					i++;
				iterator it = news.begin();
				for (int j = 0; j != i; j++)
					it++;
				for (; first != last; first++)
				{
					it = news.insert(it, *first);
					it++;
				}
				*this = news;
			}

			iterator erase(iterator position)
			{
				iterator it;
				it = begin();
				size_type i = 0;
				_size--;
				while (it != position)
				{
					it++;
					i++;
				}
				_ptr[i] = 0;
				while (i < _size)
				{
					_ptr[i] = _ptr[i + 1];
					i++;
				}
				return (it);
			}

			iterator erase(iterator first, iterator last)
			{
				iterator it;
				difference_type n;
				n = last - first;
				it = begin();
				size_t i = 0;
				_size -= n;
				while (it != first)
				{
					it++;
					i++;
				}
				while (i < _size)
				{
					_ptr[i] = _ptr[i + n];
					first++;
					i++;
				}
				return (it);
			}

			void swap(vector &x)
			{
				vector<Type> news;
				news = x;
				x = *this;
				*this = news;
			}

			void clear()
			{
				size_t cap = _capacity;
				vector<Type>().swap(*this);
				_capacity = cap;
			}

			allocator_type get_allocator() const
			{
				return (this->_alc);
			}

		private:
			Type	*_ptr;
			size_t	_size;
			size_t	_capacity;
			allocator_type _alc;
	};

	template <class T, class Alloc>
	bool operator== (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
	{
		if (lhs.size() - rhs.size())
				return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template <class T, class Alloc>
	bool operator!= (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
	{
		if (!(lhs == rhs))
			return true;
		return false;
	}

	template <class T, class Alloc>
	bool operator< (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
	{
		size_t i = 0;
		if (lhs.size() > rhs.size() && lhs.size() != 0 && rhs.size() != 0)
		{
			while (i != lhs.size() && i != rhs.size() && lhs.at(i) > rhs.at(i))
				i++;
			if (i == rhs.size() || i == lhs.size())
				return (false);
			if ((i != rhs.size() || i != lhs.size()) && lhs.at(i) < rhs.at(i))
				return (true);
		}
		if (lhs.size() < rhs.size())
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator> (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
	{
		if (rhs < lhs)
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator<= (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
	{
		if (!(rhs < lhs))
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator>= (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
	{
		if (!(lhs < rhs))
			return (true);
		return (false);
	}

}
