#pragma once

# include "../iterators/list_iterator.hpp"
# include <typeinfo>
# include <sstream>


namespace ft {

	template <class Type, class Alloc = std::allocator<Type> >
	class list {
		public:
			typedef Type value_type;
			typedef Type *pointer;
			typedef Type &reference;
			typedef ft::literator<const Type> const_iterator;
			typedef ft::literator<Type> iterator;
			typedef std::ptrdiff_t difference_type;
			typedef ft::reverse_literator<Type> reverse_iterator;
			typedef ft::reverse_literator<const Type> const_reverse_iterator;
			typedef Alloc allocator_type;
			typedef size_t size_type;
			typedef Node<Type> *node_ptr;
			typedef typename allocator_type::template rebind<Node<Type> >::other       node_alloc;
			list()
			{
				_head = _nodalc.allocate(1);
				_tail = _nodalc.allocate(1);
				_head->_next = _tail;
				_tail->_prev = _head;
				_size = 0;
			}

			~list()
			{
				while (_size)
					pop_back();
				_nodalc.deallocate(_head, 1);
				_nodalc.deallocate(_tail, 1);
			}
			
			list(size_type n, const value_type& val = value_type())
			{
				_head = _nodalc.allocate(1);
				_tail = _nodalc.allocate(1);
				_head->_next = _tail;
				_tail->_prev = _head;
				_size = 0;
				assign(n, val);
			}

			list(iterator first, iterator second)
			{
				_head = _nodalc.allocate(1);
				_tail = _nodalc.allocate(1);
				_head->_next = _tail;
				_tail->_prev = _head;
				_size = 0;
				assign(first, second);
			}

			void	push_back(const Type &val)
			{
				node_ptr ptr = _nodalc.allocate(1);
				_alc.construct(&ptr->_val, val);
				ptr->_next = this->_tail;
				ptr->_prev = this->_tail->_prev;
				this->_tail->_prev->_next = ptr;
				this->_tail->_prev = ptr;
				_size++;
			}

			list &operator=(list const &val)
			{
				clear();
				assign(val.begin(), val.end());
				return (*this);
			}

			list(const list &val)
			{
				_head = _nodalc.allocate(1);
				_tail = _nodalc.allocate(1);
				_head->_next = _tail;
				_tail->_prev = _head;
				_size = 0;
				assign(val.begin(), val.end());
			}

			void	push_front(const Type &val)
			{
				node_ptr ptr = _nodalc.allocate(1);
				_alc.construct(&ptr->_val, val);
				ptr->_prev = this->_head;
				ptr->_next = this->_head->_next;
				this->_head->_next->_prev = ptr;
				this->_head->_next = ptr;
				_size++;
			}

			iterator begin()
			{
				return (_head->_next);
			}

			const_iterator begin() const 
			{
				return reinterpret_cast<Node<const value_type>*>(_head->_next);
			}

			iterator end()
			{
				return (_tail);
			}

			const_iterator end() const 
			{
				return reinterpret_cast<Node<const value_type>*>(_tail);
			}
			
			reverse_iterator rbegin()
			{
				return (_tail->_prev);
			}

			reverse_iterator rend()
			{
				return (_head);
			}

			const_reverse_iterator rbegin() const
			{
				return reinterpret_cast<Node<const value_type>*>(_tail->_prev);
			}

			const_reverse_iterator rend() const
			{
				return reinterpret_cast<Node<const value_type>*>(_head);
			}

			void	pop_back()
			{
				Node<Type> *ptr;
				if (_tail->_prev == _head)
					return ;
				ptr = _tail->_prev;
				_tail->_prev = _tail->_prev->_prev;
				_tail->_prev->_next = _tail;
				 _nodalc.deallocate(ptr, 1);
				_size--;
			}

			void	pop_front()
			{
				Node<Type> *ptr;
				if (_head->_next == _head)
					return ;
				ptr = _head->_next;
				_head->_next = _head->_next->_next;
				_head->_next->_prev = _head;
				_nodalc.deallocate(ptr, 1);
				_size--;
			}

			Type &back()
			{
				return(_tail->_prev->_val);
			}

			const Type &back() const
			{
				return(_tail->_prev->_val);
			}

			Type &front()
			{
				return(_head->_next->_val);
			}

			const Type &front() const
			{
				return(_head->_next->_val);
			}

			bool empty() const
			{
				if (_size == 0)
					return 	(1);
				return (0);
			}

			void assign(size_type n, const Type &val)
			{
				while (this->_size != 0)
					this->pop_back();
				while (n--)
					push_back(val);
			}

			void assign(iterator first, iterator second)
			{
				while (this->_size != 0)
					this->pop_back();
				while (first != second)
				{
					push_back(*first);
					first++;
				}
			}

			void assign(const_iterator first, const_iterator second)
			{
				while (this->_size != 0)
					this->pop_back();
				while (first != second)
				{
					push_back(*first);
					first++;
				}
			}

			size_type size() const
			{
				int i = 0;
				for (const_iterator it = begin(); it != end(); ++it)
					i++;
				return i;
			}

			iterator insert(iterator position, const Type &val)
			{
				node_ptr newptr = _nodalc.allocate(1);
				_alc.construct(&newptr->_val, val);
				newptr->_prev = position.getnode()->_prev;
				position.getnode()->_prev->_next = newptr;
				position.getnode()->_prev = newptr;
				newptr->_next = position.getnode();
				_size++;
				position = newptr;
				return (position);
			}

			void insert(iterator position, size_type n, const Type &val)
			{
				if (n <= 0)
					return ;
				while (n--)
					this->insert(position, val);
			}

			void insert(iterator position, iterator first, iterator second)
			{
				while (first != second)
				{
					this->insert(position, first.getnode()->_val);
					first++;
				}
			}

			iterator erase(iterator position)
			{
				if (!position.getnode()->_next || !position.getnode()->_prev)
					return (position);
				Node<Type> *tmp = position.getnode();
				iterator gg = position.getnode()->_next;
				tmp->_prev->_next = tmp->_next;
				tmp->_next->_prev = tmp->_prev;
				_size--;
				_nodalc.deallocate(tmp, 1);
				return (gg);
			}

			iterator erase(iterator first, iterator last)
			{
				while (first != last)
				{
					first = erase(first);
				}
				return (last);
			}

			void swap(list &x)
			{
				list tmp;
				tmp = x;
				x = *this;
				*this = tmp;
			}

			void clear()
			{
				while (_size)
					pop_back();
			}

			void resize(size_type n, value_type val = value_type())
			{
				if (n < 0)
					return ;
				while (_size > n)
					pop_back();
				while(_size < n)
					push_back(val);
			}

			void splice(iterator pos, list &x)
			{
				if (x._size == 0)
					return;
				x._tail->_prev->_next = pos.getnode();
				x._head->_next->_prev = pos.getnode()->_prev;
				pos.getnode()->_prev->_next = x._head->_next;
				pos.getnode()->_prev = x._tail->_prev;
				_size += x._size;
				x._head->_next = x._tail;
				x._tail->_prev = x._head;
				x._size = 0;
			}

			void splice(iterator pos, list &x, iterator i)
			{
				if (i.getnode()->getnext() == NULL)
					i = i.getnode()->_prev;
				if (i.getnode()->_prev != NULL)
					i.getnode()->_prev->_next = i.getnode()->_next;
				i.getnode()->_next->_prev = i.getnode()->_prev;
				i.getnode()->_next = pos.getnode();
				if (i.getnode()->_prev != NULL)
					i.getnode()->_prev = pos.getnode()->_prev;
				pos.getnode()->_prev->_next = i.getnode();
				pos.getnode()->_prev = i.getnode();
				_size++;
				x._size--;
			}

			void splice(iterator pos, list &x, iterator first, iterator last)
			{
				if (pos == _head)
					pos = pos.getnode()->_next;
				iterator ggs;
				ggs = first.getnode()->_next;
				while (first != last)
				{
					splice(pos, x, first);
					first = ggs;
					ggs = first.getnode()->_next;
				}
			}														

			void remove(const value_type &val)
			{
				Node<Type> *ptr = _head->_next;
				Node<Type> *del = NULL;
				while (ptr != _tail)
				{
					del = ptr->_next;
					if (ptr->_val == val)
					{
						ptr->_prev->_next = ptr->_next;
						ptr->_next->_prev = ptr->_prev;
						_nodalc.deallocate(ptr, 1);
						_size--;
					}
					ptr = del;
				}
			}

			template <class Pred>
			void remove_if(Pred pred)
			{
				Node<Type> *ptr = _head->_next;
				Node<Type> *del = NULL;
				while (ptr != _tail)
				{
					del = ptr->_next;
					if (pred(ptr->_val) == true)
					{
						ptr->_prev->_next = ptr->_next;
						ptr->_next->_prev = ptr->_prev;
						_nodalc.deallocate(ptr, 1);
						_size--;
					}
					ptr = del;
				}
			}
			
			void unique()
			{
				iterator its;
				for (iterator it = begin(); it != end(); it++)
				{
					if ((its = it.getnode()->_next) == end())
						return;
					if (it.getnode()->_val == its.getnode()->_val)
					{
						its = erase(its);
						it++;
					}
					if (it == end())
						return;
				}
			}

			template <class Pred>
			void unique (Pred pred)
			{
				iterator its;
				for (iterator it = begin(); it != end(); it++)
				{
					if ((its = it.getnode()->_next) == end())
						return;
					if (pred(it.getnode()->_val, its.getnode()->_val))
					{
						its = erase(its);
						it++;
					}
					if (it == end())
						return;
				}
			}

			void merge(list &x)
			{
				if (this == &x)
					return;
				iterator it;
				it = begin();
				iterator save;
				iterator its = x.begin();
				while (x._size != 0)
				{
					while (it.getnode()->_val <= its.getnode()->_val && it != end() )
						it++;
					if (it.getnode() == _tail)
					{
						while (x._size != 0)
						{
							save = its.getnode()->_next;
							splice(it, x, its);
							its = save;
						}
					}
					while (it.getnode()->_val > its.getnode()->_val && x._size != 0)
					{
						save = its.getnode()->_next;
						splice(it, x, its);
						its = save;
					}
				}
			}

			template <class Pred>
			void merge(list &x, Pred pred)
			{
				if (this == &x)
					return;
				iterator it;
				it = begin();
				iterator save;
				iterator its = x.begin();
				while (x._size != 0)
				{
					while (pred(it.getnode()->_val, its.getnode()->_val) && it != end())
						it++;
					if (it.getnode() == _tail)
					{
						while (x._size != 0)
						{
							save = its.getnode()->_next;
							splice(it, x, its);
							its = save;
						}
					}
					while (!(pred(it.getnode()->_val, its.getnode()->_val)) && x._size != 0)
					{
						save = its.getnode()->_next;
						splice(it, x, its);
						its = save;
					}
				}
			}

			void sort()
			{

				for (iterator it = begin(); it != end(); it++)
				{
					for (iterator its = it.getnode()->_next; its != end(); its++)
					{
						if (it.getnode()->_val > its.getnode()->_val)
							std::swap(it.getnode()->_val, its.getnode()->_val);
					}
				}
			}

			template <class Pred>
			void sort(Pred pred)
			{

				for (iterator it = begin(); it != end(); it++)
				{
					for (iterator its = it.getnode()->_next; its != end(); its++)
					{
						if (pred(its.getnode()->_val, it.getnode()->_val))
							std::swap(it.getnode()->_val, its.getnode()->_val);
					}
				}
			}

			void reverse()
			{
				if (_size <= 1)
					return;
				int i = _size / 2 + 1;
				node_ptr first = _head->_next;
				node_ptr last = _tail->_prev;
				Type tmp;
				while (--i)
				{
					tmp = first->_val;
					first->_val = last->_val;
					last->_val = tmp;
					first = first->_next;
					last = last->_prev;
				}
			}

			size_type max_size() const
			{
				return(_nodalc.max_size());
			}

			allocator_type get_allocator() const
			{
				return (_alc);
			}

		private:
			node_ptr _head;
			node_ptr _tail;
			size_type		_size;
			allocator_type	_alc;
			node_alloc		_nodalc;
	};

	template <class T, class Alloc>
	void swap (ft::list<T,Alloc>& x, ft::list<T,Alloc>& y)
	{
		ft::list<T,Alloc> tmp;
		tmp = x;
		x = y;
		y = tmp;
	}

	template <class T, class Alloc>
	bool operator== (const ft::list<T,Alloc> &lhs, const ft::list<T,Alloc> &rhs)
	{
		if (lhs.size() == rhs.size())
		{
			typename ft::list<T, Alloc>::const_iterator it;
			it = lhs.begin();
			typename ft::list<T, Alloc>::const_iterator itr;
			itr = rhs.begin();
			size_t n = lhs.size();
			while (n)
			{
				if (*it++ == *itr++)
					n--;
				else
					return false;
			}
			return (true);
		}
		return (false);
	}

	template <class T, class Alloc>
	bool operator!= (const ft::list<T,Alloc> &lhs, const ft::list<T,Alloc> &rhs)
	{
		if (!(lhs == rhs))
			return (true);
		return false;
	}

	template <class T, class Alloc>
	bool operator< (const ft::list<T,Alloc> &lhs, const ft::list<T,Alloc> &rhs)
	{
		if (lhs.size() >= rhs.size())
		{
			typename ft::list<T, Alloc>::const_iterator it;
			it = lhs.begin();
			typename ft::list<T, Alloc>::const_iterator itr;
			itr = rhs.begin();
			size_t n = rhs.size();
			while (n)
			{
				if (*it++ >= *itr++)
					n--;
				else
					return true;
			}
			return (false);
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator> (const ft::list<T,Alloc> &lhs, const ft::list<T,Alloc> &rhs)
	{
		if (rhs < lhs)
			return true;
		return false;
	}

	template <class T, class Alloc>
	bool operator<= (const ft::list<T,Alloc> &lhs, const ft::list<T,Alloc> &rhs)
	{
		if (!(rhs < lhs))
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator>= (const ft::list<T,Alloc> &lhs, const ft::list<T,Alloc> &rhs)
	{
		if (!(lhs < rhs))
			return true;
		return false;
	}
}