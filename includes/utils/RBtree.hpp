/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:24:07 by vico              #+#    #+#             */
/*   Updated: 2022/02/28 02:49:38 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "utils.hpp"

// Chaque node est soit rouge soit noir.
// Tous les nodes externes sont noirs.
// Un node rouge a toujorus des enfants rouges.
// Chaque chemin d'un node donné à l'un de ses nodes externes descendants passe par le même nombre de nodes noirs.

namespace ft
{
	enum color_node { BLACK, RED };

	template <class T>
	struct node
	{
		struct node		*parent;
		struct node		*left;
		struct node		*right;
		color_node 		color;
		T				data;
	
		node(const T &elem) : data(elem)
		{
		}
	};

	template <class Key, class T, class Compare, class Alloc = std::allocator<node<ft::pair<Key, T> > > >
	class RBtree
	{
		public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef Compare key_compare;
		typedef ft::pair<key_type, mapped_type> value_type;
		typedef size_t size_type;
		typedef Alloc allocator_type;

		typedef node<value_type>* nodePtr;

		private:

		allocator_type	_alloc;
		nodePtr			_root;
		nodePtr			_sentinel;
		size_type		_size;
		key_compare		_comp;

		void	deleteAllNode(nodePtr node)
		{
			if (node == NULL || node == _sentinel)
				return ;
			deleteAllNode(node->left);
			deleteAllNode(node->right);
			node->left = NULL;
			node->right = NULL;
			node->parent = NULL;
			_alloc.deallocate(node, 1);
		}
		nodePtr	newNode(const value_type& elem)
		{
			nodePtr	tmp;

			tmp = _alloc.allocate(1);
			_alloc.construct(tmp, elem);
			tmp->parent = _sentinel;
			tmp->left = _sentinel;
			tmp->right = _sentinel;
			tmp->color = RED;
			return tmp;
		}
		void leftRotate(nodePtr rot)
		{
			nodePtr	tmp(rot->right);

			rot->right = tmp->left;
			if (tmp->left != _sentinel)
				tmp->left->parent = rot;
			tmp->parent = rot->parent;
			if (rot->parent == NULL)
				_root = tmp;
			else if (rot == rot->parent->left)
				rot->parent->left = tmp;
			else
				rot->parent->right = tmp;
			tmp->left = rot;
			rot->parent = tmp;
		}
		void rightRotate(nodePtr rot)
		{
			nodePtr	tmp(rot->left);

			rot->left = tmp->right;
			if (tmp->right != _sentinel)
				tmp->right->parent = rot;
			tmp->parent = rot->parent;
			if (rot->parent == NULL)
				_root = tmp;
			else if (rot == rot->parent->right)
				rot->parent->right = tmp;
			else
				rot->parent->left = tmp;
			tmp->right = rot;
			rot->parent = tmp;
		}
		void	insertBalancing(nodePtr check)
		{
	    	nodePtr	tmp(NULL);

			while (check->parent->color == RED)
			{
	      		if (check->parent == check->parent->parent->right)
				{
					tmp = check->parent->parent->left;
					if (tmp->color == RED)
					{
						tmp->color = BLACK;
						check->parent->color = BLACK;
						check->parent->parent->color = RED;
						check = check->parent->parent;
					}
					else
					{
						if (check == check->parent->left)
						{
							check = check->parent;
							rightRotate(check);
						}
						check->parent->color = BLACK;
						check->parent->parent->color = RED;
						leftRotate(check->parent->parent);
					}
				}
				else
				{
					tmp = check->parent->parent->right;
					if (tmp->color == RED)
					{
						tmp->color = BLACK;
						check->parent->color = BLACK;
						check->parent->parent->color = RED;
						check = check->parent->parent;
					} 
					else
					{
						if (check == check->parent->right)
						{
	    					check = check->parent;
	            			leftRotate(check);
						}
						check->parent->color = BLACK;
						check->parent->parent->color = RED;
						rightRotate(check->parent->parent);
					}
				}
				if (check == _root)
					break ;
			}
			_root->color = BLACK;
		}
		void	deleteBalancing(nodePtr x)
		{
			nodePtr	tmp;

			while (x != _root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					tmp = x->parent->right;
					if (tmp->color == RED)
					{
						tmp->color = BLACK;
						x->parent->color = RED;
						leftRotate(x->parent);
						tmp = x->parent->right;
					}
					if (tmp->left->color == BLACK && tmp->right->color == BLACK)
					{
						tmp->color = RED;
						x = x->parent;
					}
					else
					{
						if (tmp->right->color == BLACK)
						{
							tmp->left->color = BLACK;
							tmp->color = RED;
							rightRotate(tmp);
							tmp = x->parent->right;
						}
						tmp->color = x->parent->color;
						x->parent->color = BLACK;
						tmp->right->color = BLACK;
						leftRotate(x->parent);
						x = _root;
					}
				}
				else
				{
					tmp = x->parent->left;
					if (tmp->color == RED)
					{
						tmp->color = BLACK;
						x->parent->color = RED;
						rightRotate(x->parent);
						tmp = x->parent->left;
					}
					if (tmp->right->color == BLACK && tmp->right->color == BLACK)
					{
						tmp->color = RED;
						x = x->parent;
					}
					else
					{
						if (tmp->left->color == BLACK)
						{
							tmp->right->color = BLACK;
							tmp->color = RED;
							leftRotate(tmp);
							tmp = x->parent->left;
						}
						tmp->color = x->parent->color;
						x->parent->color = BLACK;
						tmp->left->color = BLACK;
						rightRotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}
		void	rbTransplant(nodePtr u, nodePtr v)
		{
			if (u->parent == NULL)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}
		nodePtr	copyNode(nodePtr x)
		{
			nodePtr	tmp;

			tmp = _alloc.allocate(1);
			_alloc.construct(tmp, x->data);
			tmp->parent = _sentinel;
			tmp->left = _sentinel;
			tmp->right = _sentinel;
			tmp->color = x->color;
			return tmp;
		}
		void	copyAllNode(nodePtr fill, nodePtr copy, nodePtr sentinel)
		{
			if (copy == sentinel || copy == NULL)
				return ;
			if (copy->left != sentinel && copy->left != NULL)
			{
				fill->left = copyNode(copy->left);
				fill->left->parent = fill;
				copyAllNode(fill->left, copy->left, sentinel);
			}
			if (copy->right != sentinel && copy->right != NULL)
			{
				fill->right = copyNode(copy->right);
				fill->right->parent = fill;
				copyAllNode(fill->right, copy->right, sentinel);
			}
		}

		public:

		// Constructor
		RBtree(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _root(NULL), _sentinel(NULL), _size(0), _comp(comp)
		{
			ft::pair<key_type, mapped_type>	p;

			p.second = mapped_type();
			_sentinel = _alloc.allocate(1);
			_alloc.construct(_sentinel, p);
			_sentinel->parent = NULL;
			_sentinel->left = NULL;
			_sentinel->right = NULL;
			_sentinel->color = BLACK;
			_root = _sentinel;
		}
		RBtree(const RBtree& x) : _alloc(x._alloc), _root(NULL), _sentinel(NULL), _size(x.size()), _comp(x._comp)
		{
			ft::pair<key_type, mapped_type>	p;

			p.second = mapped_type();
			_sentinel = _alloc.allocate(1);
			_alloc.construct(_sentinel, p);
			_sentinel->parent = NULL;
			_sentinel->left = NULL;
			_sentinel->right = NULL;
			_sentinel->color = BLACK;
			_root = _sentinel;
			if (x.getRoot() != x.getSentinel())
			{
				_root = _alloc.allocate(1);
				_alloc.construct(_root, x.getRoot()->data);
				_root->parent = NULL;
				_root->left = _sentinel;
				_root->right = _sentinel;
				_root->color = x.getRoot()->color;
				copyAllNode(_root, x.getRoot(), x.getSentinel());
			}
		}
		// Destructor
		~RBtree()
		{
			deleteAllNode(_root);
			_alloc.deallocate(_sentinel, 1);
			_size = 0;
		}
		RBtree&	operator=(const RBtree& x)
		{
			clear();
			if (x.getRoot() != x.getSentinel())
			{
				_root = _alloc.allocate(1);
				_alloc.construct(_root, x.getRoot()->data);
				_root->parent = NULL;
				_root->left = _sentinel;
				_root->right = _sentinel;
				_root->color = x.getRoot()->color;
				copyAllNode(_root, x.getRoot(), x.getSentinel());
				_size = x.size();
			}
			_comp = x._comp;
			return *this;
		}
		nodePtr	getRoot() const
		{
			return _root;
		}
		nodePtr	getSentinel() const
		{
			return _sentinel;
		}
		size_type	size() const
		{
			return _size;
		}
		size_type	max_size() const
		{
			return _alloc.max_size();
		}
		nodePtr	minimum(nodePtr node) const
		{
			while (node->left != _sentinel && node->left)
				node = node->left;
			return node;
		}
		nodePtr	maximum(nodePtr node) const
		{
	    	while (node->right != _sentinel && node->right)
				node = node->right;
			return node;
		}
		void	insert(const value_type &elem)
		{
	    	nodePtr	tmp(newNode(elem));
	    	nodePtr	y(NULL);
	    	nodePtr	x(_root);

	    	while (x != _sentinel) 
			{
				y = x;
				if (tmp->data.first == x->data.first)
				{
					_alloc.deallocate(tmp, 1);
					return ;
				}
				else if (_comp(tmp->data.first, x->data.first)) 
					x = x->left;
				else if (!_comp(tmp->data.first, x->data.first))
	    		    x = x->right;
			}
			_size++;
			tmp->parent = y;
			if (y == NULL)
				_root = tmp;
			else if (_comp(tmp->data.first, y->data.first)) 
				y->left = tmp;
			else 
	    		y->right = tmp;
	    	if (tmp->parent == NULL)
			{
				tmp->color = BLACK;
				return ;
	    	}
	    	if (tmp->parent->parent == NULL)
			{
	    		return ;
			}
			insertBalancing(tmp);
		}
		void	deleteNode(const key_type &key)
		{
			nodePtr	tmp(_root);
			nodePtr	z(_sentinel);
			nodePtr	x(NULL);
			nodePtr	y(NULL);

			while (tmp != _sentinel)
			{
				if (tmp->data.first == key)
					z = tmp;
				if (tmp->data.first <= key)
					tmp = tmp->right;
				else
					tmp = tmp->left;
			}
			if (z == _sentinel)
				return ;
			y = z;
			color_node	y_color(y->color);

			if (z->left == _sentinel)
			{
				x = z->right;
				rbTransplant(z, z->right);
			}
			else if (z->right == _sentinel)
			{
				x = z->left;
				rbTransplant(z, z->left);
			}
			else
			{
				y = minimum(z->right);
				y_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					rbTransplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				rbTransplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			_alloc.deallocate(z, 1);
			_size--;
			if (y_color == BLACK)
			{
				deleteBalancing(x);
			}
		}
		void	swap(RBtree &x)
		{
			nodePtr			tmp_root(_root);
			nodePtr			tmp_sent(_sentinel);
			size_type		tmp_size(_size);

			_root = x._root;
			_sentinel = x._sentinel;
			_size = x._size;
			x._root = tmp_root;
			x._sentinel = tmp_sent;
			x._size = tmp_size;
		}
		nodePtr	find(const key_type &key)
		{
			nodePtr	tmp(_root);

			while (tmp != _sentinel)
			{
				if (key == tmp->data.first)
					return tmp;
				if (_comp(key, tmp->data.first))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return tmp;
		}
		void	clear()
		{
			deleteAllNode(_root);
			_root = _sentinel;
			_size = 0;
		}
	};
}

#endif
