#pragma once

# include "avl_tree.hpp"
# include "../iterators/map_iterator.hpp"
# include <functional>
# include <memory>

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map {
		public:
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef std::pair<const Key, T>				value_type;
			typedef size_t								size_type;
			typedef ptrdiff_t							difference_type;
			typedef Compare								key_compare;	
			typedef	Allocator							allocator_type;
			typedef	value_type&							reference;
			typedef const value_type&					const_reference;
			typedef	value_type*							pointer;
			typedef const value_type*					const_pointer;
			typedef iteratormap<value_type>				iterator;
			typedef iteratormap<const value_type>		const_iterator;
			typedef rev_iteratormap<value_type>			reverse_iterator;
			typedef	rev_iteratormap<const value_type>	const_reverse_iterator;
			typedef typename allocator_type::template rebind<avl_tree<value_type> >::other	avl_alloc;
			typedef typename allocator_type::template rebind<node_map<value_type> >::other	node_alloc;
			typedef avl_tree<value_type>	contein;


			template <class Keya, class Ta, class Comparea, class Alloca>
			class pair_comp
			{   
			protected:
			  Compare comp;
			public:
			  typedef bool result_type;
			  typedef value_type first_argument_type;
			  typedef value_type second_argument_type;
			  bool operator() (const value_type& x, const value_type& y) const
			  {
			    return comp(x.first, y.first);
			  }
			};

			typedef pair_comp<key_type, T, key_compare, allocator_type> 							value_compare;

			map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			{
				(void)comp;
				(void)alloc;
				_root._root->_height = 1;
				_counter = 0;
			}

			map(const map &ref)
			{
				_counter = ref._counter;
				for (const_iterator it = ref.begin(); it != ref.end(); it++)
					_root.insert(*it);
			}

			template <class inputiter>
			map(inputiter first, inputiter last)
			{
				for (inputiter it = first; it != last; it++)
					_counter++;
				for (; first != last; first++)
					_root.insert(*first);
			}

			std::pair<iterator,bool>	insert(const value_type &val)
			{ 
				iterator it = begin();
				for (; it != end(); ++it)
				{
					if (it->first == val.first)
						return (std::pair<iterator, bool>(it, 0));
				}
				_root.insert(val);
				_counter++;
				return (std::pair<iterator, bool>(it, 1));
			}

			iterator					insert(iterator position, const value_type &val)
			{	
				insert(val);
				return (position);
			}

			template <class inputiter>
			void						insert(inputiter first, inputiter last)
			{
				for (; first != last; first++)
				{
					_counter++;
					_root.insert(*first);
				}
			}

			void						erase(iterator position)
			{
				_root.remove(position._ptr->_val);
				_counter--;
			}

			void erase (iterator first, iterator last)
			{
				iterator tmp;
				while ( first != last)
				{
					tmp = first;
					first++;
					erase(tmp);
				}
				if (_counter == 0)
				{
					_root._root = nod_al.allocate(1);
					_root._root->_height = 1;
					_root._root->_left = NULL;
					_root._root->_right = _root._end;
					_root._end->_parent = _root._root;
					_root._root->_parent= NULL;
					return ;
				}
			}

			void						swap(map &x)
			{
				node_map<value_type>	*tmp = x._root._root;
				node_map<value_type> *tmpend = x._root._end;
				x._root._root = _root._root;
				x._root._end = _root._end;
				_root._root = tmp;
				_root._end = tmpend;
			}

			void						clear()
			{
				_root.~avl_tree();
				_root._root = nod_al.allocate(1);
				_root._end = nod_al.allocate(1);
				_root.node_alc.destroy(_root._root);
				_root._root->_left = NULL;
				_root._root->_right = _root._end;
				_root._root->_parent = NULL;
				_root._root->_check = 0;
				_root._root->_height = 1;
				_root._end->_parent = _root._root;
				_root._end->_right = NULL;
				_root._end->_left = NULL;
				_root._end->_height = 1;
				_root._end->_check = 0;
				_counter = 0;
			}

			key_compare					key_comp() const
			{
				return (key_compare());
			}

			value_compare				value_comp() const
			{
				return (value_compare());
			}

			iterator 					find (const key_type &k)
			{
				iterator it = begin();
				while (it != end() && it->first != k)
					it++;
				return (it);
			}

			const_iterator 				find (const key_type &k) const
			{
				const_iterator it = begin();
				while (it != end() && it->first != k)
					it++;
				return (it);
			}

			iterator					lower_bound (const key_type &k)
			{
				return (find(k));
			}

			const_iterator				lower_bound (const key_type &k) const
			{
				return (find(k));
			}

			iterator					upper_bound (const key_type &k)
			{
				return (++find(k));
			}

			const_iterator				upper_bound (const key_type &k) const
			{
				return (++find(k));
			}

			std::pair<const_iterator, const_iterator>	equal_range (const key_type &k)	const
			{
				return (std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			}

			std::pair<iterator, iterator>	equal_range (const key_type &k)
			{
				return (std::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}

			size_type 					count (const key_type &k)	const
			{
				if (find(k) == end())
					return (0);
				return (1);
			}

			iterator					begin()
			{
				if (_counter != 0)
					return iterator(_root.findmin(_root._root));
				return iterator(_root._end);
			}

			const_iterator				begin() const
			{
				if (_counter != 0)
					return iterator(_root.findmin(_root._root));
				return iterator(_root._end);
			}

			const_iterator				end()	const
			{
				return iterator(_root._end);
			}

			iterator					end()
			{
				return iterator(_root._end);
			}
			
			reverse_iterator 			rbegin()
			{
				return reverse_iterator(_root._end->_parent);
			}

			const_reverse_iterator		rbegin() const
			{
				return reverse_iterator(_root._end->_parent);
			}

			reverse_iterator			rend()
			{
				if (_counter != 0)
					return reverse_iterator(_root.findmin(_root._root));
				return reverse_iterator(_root._end);
			}

			const_reverse_iterator		rend() const
			{
				if (_counter != 0)
					return iterator(_root.findmin(_root._root));
				return reverse_iterator(_root._end);
			}

			bool						empty() const
			{
				if (_root._root->_right == _root._end)
					return (1);
				return (0);
			}

			size_type 					size() const
			{
				return (_counter);
			}

			allocator_type get_allocator() const
			{
				return (_alc);
			}

			size_type					max_size() const
			{
				return (_root.node_alc.max_size());
			}

			map							&operator=(const map &ref)
			{
				_counter = ref._counter;
				for (const_iterator it = ref.begin(); it != ref.end(); it++)
					_root.insert(*it);
				return (*this);
			}

			mapped_type 				&operator[] (const key_type &k)
			{
				iterator its = begin();
				for (iterator it = begin(); it != end(); ++it)
				{
					if (it->first == k)
						return (it->second);
				}
				insert(std::pair<key_type, mapped_type>(k, 0));
				for (iterator it = begin(); it != end(); ++it)
				{
					if (it->first == k)
						return (it->second);
				}
				return (its->second);
			}


			~map()
			{

			}
			
			friend bool operator==(const map &first, const map &second)
			{
				
				if (first.size() == second.size())
				{
					const_iterator it = first.begin();
					const_iterator its = second.begin();
					while (it != first.end() && it->first == its->first)
					{
						it++;
						its++;
					}
					if (its->first == it->first && it == first.end())
						return (true);
				}
				return (false);
			}

			friend bool operator!=(const map &first, const map &second)
			{
				return (!(first == second));
			}

			friend bool operator>(const map &first, const map &second)
			{
				
				if (first.size() > second.size())
				{
					const_iterator it = first.begin();
					const_iterator its = second.begin();
					while (its != second.end() &&  its->first <= it->first)
					{
						it++;
						its++;
					}
					if (it->first > its->first && its == second.end())
						return (true);
				}
				return (false);
			}
			friend bool operator<(const map &first, const map &second)
			{
				return (second > first);
			}
			friend bool operator>=(const map &first, const map &second)
			{
				return (!(first < second));
			}
			friend bool operator<=(const map &first, const map &second)
			{
				return (!(first > second));
			}


			private:
				contein  _root;
				Allocator							_alc;
				size_t								_counter;
				node_alloc							nod_al;
	};
}