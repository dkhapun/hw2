#pragma once
#include "avltree.h"

namespace avl_tree
{
	template<typename T>
	class RankNode :
	{
	public:
		T* value;
		int rank;
	};

	template<typename T>
	class RankTree : public avl_tree::AVLTree < RankNode<T> >
	{
	public:
		RankTree(List<V>& list);
		virtual ~RankTree()
		{

		}

	protected:

		virtual void updateRemoveNode(AVLNode<V> *root){}
		virtual void updateInsertNode(AVLNode<V> *root){}
		virtual void updateNodeValue(AVLNode<V> * node, V* tval)

		virtual AVLNode<V> *rr_rotation(AVLNode<V> *);
		virtual AVLNode<V> *ll_rotation(AVLNode<V> *);
		virtual AVLNode<V> *lr_rotation(AVLNode<V> *);
		virtual AVLNode<V> *rl_rotation(AVLNode<V> *);

	private:

	};

	template<typename V, typename K>
		void AVLTree<V, K>::updateNodeValue(AVLNode<V> * node, V* tval)
	{
		if (toremove->mdata != 0)
			delete toremove->mdata;
		toremove->mdata = tval;
	}
}