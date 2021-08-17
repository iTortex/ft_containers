#pragma once

#include "map_node.hpp"


template <class T, class Alloc = std::allocator<T> >
class avl_tree
{
	public:
		node_map<T> *_root;
		node_map<T>	*_end;
		typedef node_map<T>* node;
		typedef Alloc allocator_type;
		allocator_type _alc;
		typedef typename allocator_type::template rebind<node_map<T> >::other	node_alloc;
		node_alloc node_alc;

		avl_tree()	
		{
			_root = node_alc.allocate(1);
			_end = node_alc.allocate(1);
			_root->_left = NULL;
			_root->_right = _end;
			_root->_parent = NULL;
			_root->_check = 0;
			_root->_height = 1;
			_end->_parent = _root;
			_end->_right = NULL;
			_end->_left = NULL;
			_end->_height = 1;
			_end->_check = 0;
		}

		avl_tree(T k)
		{ 
			node_alc.allocate(1);
			_root->_val = k;
			_end = node_alc.allocate(1);
			_root->_left = NULL;
			_root->_right = _end;
			_root->_parent = NULL;
			_root->_check = 0;
			_root->_height = 1;
			_end->_parent = _root;
			_end->_right = NULL;
			_end->_left = NULL;
			_end->_height = 1;
			_end->_check = 0;
		}

		unsigned char	get_heigth(node p)	{ return (p?p->_height:0); }
		int				bfactor(node p)		{ return (get_heigth(p->_right) - get_heigth(p->_left)); }

		void			fixhigth(node p)
		{
			unsigned char hl = get_heigth(p->_left);
			unsigned char hr = get_heigth(p->_right);
			p->_height = (hl>hr?hl:hr) + 1;
		}

		node get_end()
		{
			return (_end);
		}

		node	rotate_right(node p)
		{
			node q = p->_left;
			p->_left = q->_right;
			if (p->_left)
				p->_left->_parent = p;
			else
				p->_left = NULL;
			q->_right = p;
			q->_parent = p->_parent;
			p->_parent = q;
			fixhigth(p);
			fixhigth(q);
			return (q);
		}

		node	rotate_left(node p)
		{
			node q = p->_right;
			p->_right = q->_left;
			if (p->_right)
				p->_right->_parent = p;
			else
				p->_right = NULL;
			q->_left = p;
			q->_parent = p->_parent;
			p->_parent = q;
			fixhigth(p);
			fixhigth(q);
			return (q);
		}

		node	balance(node p)
		{
			fixhigth(p);
			if (bfactor(p) == 2)
			{
				if (bfactor(p->_right) < 0)
					p->_right = rotate_right(p->_right);
				return (rotate_left(p));
			}
			if (bfactor(p) == -2)
			{
				if (bfactor(p->_left) > 0)
					p->_left = rotate_left(p->_left);
				return (rotate_right(p));
			}
			return (p);
		}

		node	insert(node prev ,node p, T k)
		{
			if (!p)
			{
				node x = node_alc.allocate(1);
				_alc.construct(&x->_val, k);
				x->_parent = prev;
				x->_height = 1;
				x->_check = 1;
				x->_right = NULL;
				x->_left = NULL;
				return (x);
			}
			if (k < p->_val)
				p->_left= insert(p, p->_left, k);
			else if (k >= p->_val)
				p->_right = insert(p ,p->_right, k);
			return balance(p);
		}

		void	insert(T k)
		{
			node tmp;
			tmp = _root;
			if (_root->_check == 0)
			{
				node_alc.deallocate(_root, 1);
				_root = node_alc.allocate(1);
				_alc.construct(&_root->_val, k);
				_root->_check = 1;
				_root->_height = 1;
				_root->_right = _end;
				_end->_parent = _root;
				_end->_left = NULL;
				_end->_right = NULL;
				_root->_left = NULL;
				_root->_parent = NULL;
				return ;
			}
			while (tmp->_right)
				tmp = tmp->_right;
			if (tmp->_parent)
				tmp->_parent->_right = NULL;
			_end->_parent = NULL;
			_root = insert(_root->_parent, _root, k);
			tmp = _root;
			while (tmp->_right != 0)
				tmp = tmp->_right;
			tmp->_right = _end;
			_end->_parent = tmp;
		}

		node findmin(node p) const	{ return (p->_left?findmin(p->_left):p); }
		node findmax(node p) const	{ return (p->_right?findmax(p->_right):p); }

		node removemin(node p)
		{
			if (!p->_left)
				return p->_right;
			p->_left = removemin(p->_left);
			return (balance(p));
		}

		node removemax(node p)
		{
			if (!p->_right)
				return p->_left;
			p->_right = removemax(p->_right);
			return (balance(p));
		}

		node remove(node p, T k)
		{
			if (!p)
				return 0;
			if (k < p->_val)
				p->_left = remove(p->_left, k);
			else if (k > p->_val)
				p->_right = remove(p->_right, k);
			else if (k == p->_val)
			{
				node q = p->_left;
				node r = p->_right;
				node parents = p->_parent;
				node_alc.deallocate(p, 1);
				p = NULL;
				if (q)
				{
					node max = findmax(q);
					max->_left = removemax(q);
					max->_right = r;
					if (max->_right)
						max->_right->_parent = max;
					if (max->_left)
						max->_left->_parent = max;
					max->_parent = parents;
					return (balance(max));
				}
				else if (r)
				{
					node min = findmin(r);
					min->_right = removemin(r);
					min->_left = q;
					if (min->_left)
						min->_left->_parent = min;
					if (min->_right)
						min->_right->_parent = min;
					min->_parent = parents;
					return (balance(min));
				}
			}
			return (p);
		}

		void	remove(T k)
		{
			node tmp;
			tmp = _root;
			if (_root->_check == 0)
				return ;
			while (tmp->_right)
				tmp = tmp->_right;
			if (tmp->_parent)
				tmp->_parent->_right = NULL;
			_end->_parent = NULL;
			_root = remove(_root, k);
			tmp = _root;
			if (tmp)
			{
				while (tmp->_right)
					tmp = tmp->_right;
				tmp->_right = _end;
				_end->_parent = tmp;
			}
		}

		node						deletes(node _head)
			{
				if (_head == NULL)
					return (_head);
				_head->_left = deletes (_head->_left); 
				_head->_right = deletes (_head->_right);
				node_alc.destroy(_head);
				node_alc.deallocate(_head, 1);
				_head = NULL;
				return (_head);
			}

		~avl_tree()
		{
			_root = deletes(this->_root);
		}
};