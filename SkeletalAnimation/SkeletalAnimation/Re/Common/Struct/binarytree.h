#pragma once
#include <vector>
#include <memory>


/// Usage: inherit from binary tree and as Ty write inheriting class name
///		ParentTy should be equal to Ty or be its base class
template< typename Ty, typename ParentTy = Ty>
class BinaryTree
{
public:

	////// creation

	/// add child above
	void addUp(Ty *s)
	{
		if (childUp == nullptr)
		{
			s->parent = __this;
			childUp = unique_ptr<Ty>(s);
		}
		else
			childUp->addSibling(s);
	}
	/// add child under
	void addDown(Ty *s)
	{
		if (childDown == nullptr)
		{
			s->parent = __this;
			childDown = unique_ptr<Ty>(s);
		}
		else
			childDown->addSibling(s);
	}


	void setParent(ParentTy* s) { parent = s; }
	////// getters

	Ty* getChildUp() const { return childUp.get(); }
	Ty* getChildDown() const { return childUp.get(); }
	Ty* getSibling() const { return childUp.get(); }

	ParentTy* getParent() const { return parent; }


	////// utility

	/// puts ptrs to each child in specific order

	/// me -> child down -> child up -> sibling
	void rewriteTo_Dfs(std::vector<Ty*>& v);
	/// me -> sibling -> child down -> child up
	void rewriteTo_Bfs(std::vector<Ty*>& v);
	/// child down -> me -> sibling -> child up
	void rewriteTo_Rendering(std::vector<Ty*>& v);

private:
	ParentTy* parent;
	/// child can be placed either above or under
	/// which child ptr is used determine rendering order
	std::unique_ptr<Ty> childUp, childDown,
		/// sibling to this model
		/// shows all models on the same layer
		/// Rendering order: first this one then siblings
		sibling;

	/// adds a sibling to the model
	/// for internal purposes
	/// use addUp or addDown instead
	void addSibling(Ty *s)
	{
		if (sibling == nullptr)
		{
			sibling = unique_ptr<Ty>(s);
			s->parent = parent;
		}
		else
			sibling->addSibling(s);
	}
protected:
	void setThis(ParentTy* _this) { __this = _this; }
private:
	ParentTy* __this;
};
template<typename Ty, typename ParentTy>
void BinaryTree<Ty, ParentTy>::rewriteTo_Dfs(std::vector<Ty*>& v)
{
	v.push_back((Ty*)this);

	if (childDown)
		childDown->rewriteTo_Dfs(v);

	if (childUp)
		childUp->rewriteTo_Dfs(v);

	if (sibling)
		sibling->rewriteTo_Dfs(v);
}

template<typename Ty, typename ParentTy>
void BinaryTree<Ty, ParentTy>::rewriteTo_Bfs(std::vector<Ty*>& v)
{
	v.push_back((Ty*)this);

	if (sibling)
		sibling->rewriteTo_Bfs(v);

	if (childDown)
		childDown->rewriteTo_Bfs(v);

	if (childUp)
		childUp->rewriteTo_Bfs(v);
}

template<typename Ty, typename ParentTy>
void BinaryTree<Ty, ParentTy>::rewriteTo_Rendering(std::vector<Ty*>& v)
{
	if (childDown)
		childDown->rewriteTo_Rendering(v);

	v.push_back((Ty*)this);

	if (sibling)
		sibling->rewriteTo_Rendering(v);

	if (childUp)
		childUp->rewriteTo_Rendering(v);
}