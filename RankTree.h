#pragma once
#include "avltree.h"

namespace avl_tree
{
	template<typename T>
	class RankNode
	{
	public:
		RankNode() : value(0), rank(0){}
		operator int() { return (int)(*value); }
		T* value;
		int rank;
	};

	template<typename T>
	class RankTree : public AVLTree < RankNode<T>, int>
	{
	public:
		RankTree(List<RankNode<T> >& list);
		RankTree() : AVLTree < RankNode<T>, int>::AVLTree(){}
		virtual ~RankTree()
		{

		}

	protected:

		virtual void updateRemoveNode(AVLNode<RankNode<T> > *root);
		virtual void updateInsertNode(AVLNode<RankNode<T> > *root);
		virtual void updateNodeValue(AVLNode<RankNode<T> > * node, T* tval);

		virtual AVLNode<RankNode<T> > *rr_rotation(AVLNode<RankNode<T> > *n)
		{
			//b is root-> b is right of root
			int a_rank = n->mdata->rank;
			int bl_rank = n->right->left->mdata->rank;
			int br_rank = n->right->right->mdata->rank;
			int al_rank = n->left->mdata->rank;

			n = AVLTree < RankNode<T>, int>::rr_rotation(n);

			n->mdata->rank = brank;
			n->left->mdata->rank = 1 + bl_rank + al_rank;
			return n;
		}
		virtual AVLNode<RankNode<T> > *ll_rotation(AVLNode<RankNode<T> > *n)
		{
			//b is root-> b is right of root
			int b_rank = n->mdata->rank;
			int al_rank = n->left->left->mdata->rank;
			int ar_rank = n->left->right->mdata->rank;
			int br_rank = n->right->mdata->rank;
			
			n = AVLTree < RankNode<T>, int>::ll_rotation(n);
			
			n->mdata->rank = brank;
			n->right->mdata->rank = 1 + ar_rank + br_rank;
			return n;
		}
		virtual AVLNode<RankNode<T> > *lr_rotation(AVLNode<RankNode<T> > *n)
		{

			n = AVLTree < RankNode<T>, int>::lr_rotation(n);
			return n;
		}
		virtual AVLNode<RankNode<T> > *rl_rotation(AVLNode<RankNode<T> > *n)
		{
			n = AVLTree < RankNode<T>, int>::rl_rotation(n);
			return n;
		}

	private:

	};

	template<typename V>
	RankTree<V>::RankTree(List<RankNode<V> >& list) : AVLTree < RankNode<V>, int>::AVLTree(list)
	{

	}

	template<typename V>
	void RankTree<V>::updateNodeValue(AVLNode<RankNode<V> > * node, V* tval)
	{
		if (node->mdata != 0 && node->mdata->value != 0)
			delete node->mdata->value;
		node->mdata->value = tval;
	}

	 template<typename V>
	 void RankTree<V>::updateRemoveNode(AVLNode<RankNode<V> > *root)
	 {
		 --(root->mdata->rank);
	 }

	 template<typename V>
	 void RankTree<V>::updateInsertNode(AVLNode<RankNode<V> > *root)
	 {
		 ++(root->mdata->rank);
	 }
	 /*
	 template<typename V>
	 AVLNode<RankNode<V> >* RankTree<V>::*rr_rotation(AVLNode<RankNode<V> > *n)
	 {
		 return n;
	 }
/*
	 template<typename V>
	 AVLNode<RankNode<V> >* RankTree<V>::*ll_rotation(AVLNode<RankNode<V> > *n)
	 {
		 return n;
	 }
	 
	 template<typename V>
	 AVLNode<RankNode<V> >* RankTree<V>::*lr_rotation(AVLNode<RankNode<V> > *n)
	 {
		 return n;
	 }
	 
	 template<typename V>
	 AVLNode<RankNode<V> >* RankTree<V>::*rl_rotation(AVLNode<RankNode<V> > *n)
	 {
		 return n;
	 }
*/
}