#pragma once
#include <string>
#include "avltree.h"

namespace avl_tree
{
	template<typename T>
	class RankNode
	{
	public:
		RankNode() : value(0), rank(1){}
		RankNode(T* v) : value(v), rank(1){}
		//operator int() const { return value; }
		bool operator<(RankNode<T> & node)
		{
			return *value < *(node.value);
		}
		bool operator>(RankNode<T> & node)
		{
			return *value > *(node.value);
		}
		operator T()
		{
			return *value;
		}
		operator T() const
		{
			return *value;
		}
		T* value;
		int rank;

		virtual ~RankNode()
		{
			//delete value;
		}
	};

	template<typename T>
	class RankTree : public AVLTree < RankNode<T>, T>
	{
	public:
		RankTree(List<RankNode<T> >& list);
		RankTree() : AVLTree < RankNode<T>, T>::AVLTree(){}
		virtual ~RankTree()
		{

		}

		T* select(int k);
		void insert(T num);
	protected:
		virtual std::string nodeToString(const RankNode<T>& node) const;
		virtual void updateRemoveNode(AVLNode<RankNode<T> > *root);
		virtual void updateNode(AVLNode<RankNode<T> > *root);
		virtual void updateInsertNode(AVLNode<RankNode<T> > *root);
		virtual void updateNodeValue(AVLNode<RankNode<T> > * node, T* tval);
		int updateTreeRank(AVLNode<RankNode<T> >* node);

		T* select(AVLNode<RankNode<T> >* node, int k);

		virtual AVLNode<RankNode<T> > *rr_rotation(AVLNode<RankNode<T> > *n)
		{


			if (n->right != 0 && n->right->right != 0)
			{
				int a_rank  = 0;
				int bl_rank = 0;
				int al_rank = 0;

				//b is root-> b is right of root
				a_rank = n->mdata->rank;

				if (n->right->left != 0)
					bl_rank = n->right->left->mdata->rank;


				if (n->left != 0)
					al_rank = n->left->mdata->rank;
			
				n = AVLTree < RankNode<T>, T>::rr_rotation(n);

				n->mdata->rank = a_rank;
				n->left->mdata->rank = 1 + bl_rank + al_rank;
			}
			else
			{
				n = AVLTree < RankNode<T>, T>::rr_rotation(n);
			}
			return n;
		}
		virtual AVLNode<RankNode<T> > *ll_rotation(AVLNode<RankNode<T> > *n)
		{

			if (n->left != 0 && n->left->left != 0)
			{
				int b_rank  = 0;
				int ar_rank = 0;
				int br_rank = 0;

				//b is root-> b is right of root
				b_rank = n->mdata->rank;
				//al_rank = n->left->left->mdata->rank;

				if (n->left->right != 0)
					ar_rank = n->left->right->mdata->rank;

				if(n->right != 0 )
					br_rank = n->right->mdata->rank;

				n = AVLTree < RankNode<T>, T>::ll_rotation(n);

				n->mdata->rank = b_rank;
				n->right->mdata->rank = 1 + ar_rank + br_rank;
			}
			else
			{
				n = AVLTree < RankNode<T>, T>::ll_rotation(n);
			}
			return n;
		}
		virtual AVLNode<RankNode<T> > *lr_rotation(AVLNode<RankNode<T> > *n)
		{
			int a_rank = n->mdata->rank;

			n = AVLTree < RankNode<T>, T>::lr_rotation(n);

			n->mdata->rank = a_rank;
			n->left->mdata->rank -= n->right->mdata->rank;
			return n;
		}
		virtual AVLNode<RankNode<T> > *rl_rotation(AVLNode<RankNode<T> > *n)
		{
			int a_rank = n->mdata->rank;
			n = AVLTree < RankNode<T>, T>::rl_rotation(n);
			n->mdata->rank = a_rank;
			n->right->mdata->rank -= n->left->mdata->rank;
			return n;
		}

	private:
		int getRank(AVLNode<RankNode<T> >* node);
	};

	template<typename V>
	std::string RankTree<V>::nodeToString(const RankNode<V>& node) const
	{
		std::stringstream ss;
		ss << "(" << (int)(*node.value) << "," << node.rank << ")";
		return ss.str();
	}
	
	template<typename V>
	RankTree<V>::RankTree(List<RankNode<V> >& list) : AVLTree < RankNode<V>, V>::AVLTree(list)
	{
		updateTreeRank(this->mRoot);
	}

	template<typename V>
	int RankTree<V>::updateTreeRank(AVLNode<RankNode<V> >* node)
	{
		if(node == 0)
			return 0;
		node->mdata->rank = updateTreeRank(node->left) + updateTreeRank(node->right) + 1;
		return node->mdata->rank;
	}
	template<typename V>
	void RankTree<V>::insert(V num)
	{
		AVLTree < RankNode<V>, V>::insert(RankNode<V>(new V(num)));
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

	 template<typename V>
	 void RankTree<V>::updateNode(AVLNode<RankNode<V> > *root)
	 {
		 root->mdata->rank = getRank(root->left) + getRank(root->right) + 1;
	 }

	 template<typename V>
	 V* RankTree<V>::select(int k)
	 {
		 return select(this->mRoot, k);
	 }

	 template<typename V>
	 int RankTree<V>::getRank(AVLNode<RankNode<V> >* node)
	 {
		 if (node == 0)
			 return 0;
		 return node->mdata->rank;
	 }
	 template<typename V>
	 V* RankTree<V>::select(AVLNode<RankNode<V> >* node, int k)
	 {
		 if (getRank(node->left) == k - 1)
			 return node->mdata->value;
		 if (getRank(node->left) < k - 1)
			 return select(node->right, k - 1 - getRank(node->left));
		 //if (node->left->mdata->rank > k - 1)
			 return select(node->left, k);
	 }

}
