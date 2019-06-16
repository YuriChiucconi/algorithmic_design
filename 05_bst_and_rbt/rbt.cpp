#include <iostream>
#include <typeinfo>
#include <vector>
#include <cassert>      // assert
#include <cstddef>      // ptrdiff_t
#include <iterator>     // iterator
#include <type_traits>  // remove_cv
#include <utility>      // swap
#include <cstdlib>      // rand()


template <typename K, typename V>
class RBT
{
private:

	struct Node
	{
		std::pair<const K, V> pair;
		Node* sx;
		Node* dx;
		Node* dad;

		bool red = true;

		Node(std::pair<const K, V> p)
			: pair(p), sx(0), dx(0), dad(0) {}

		~Node() = default;

		bool operator ==(const Node& rhs) const
		{
			return pair.first == rhs.pair.first;
		}
		bool operator !=(const Node& rhs) const
		{

			return pair.first != rhs.pair.first;
		}
	};

	Node* root;

private: // METHODS

	Node* CreateLeaf(const K key, V val)
	{
		return new Node(std::make_pair(key, val));;
	}

	void AddLeafPrivate(const K key, V val, Node* Ptr);

	void PrintInOrderPrivate(Node* Ptr);

	Node* ReturnNode(const K key)
	{
		return ReturnNodePrivate(key, root);
	}

	Node* ReturnNodePrivate(const K key, Node* Ptr)
	{
		if (Ptr != nullptr)
		{
			if (Ptr->pair.first == key)
			{
				return Ptr;
			}
			else
			{
				if (key < Ptr->pair.first)
				{
					return ReturnNodePrivate(key, Ptr->sx);
				}
				else
				{
					return ReturnNodePrivate(key, Ptr->dx);
				}
			}
		}
		else
		{
			std::cout << "Node with key " << key << " not found!" << std::endl;
			return nullptr;
		}

	}

	Node* FindSmallest(Node* Ptr)
	{
		if (Ptr->sx != nullptr)
		{
			return FindSmallest(Ptr->sx);
		}
		else
		{
			return Ptr;
		}
	}

	Node* FindBiggest(Node* Ptr)
	{
		while (Ptr->dx != nullptr)
		{
			Ptr = Ptr->dx;
		}
		return Ptr->dx;
	}
	
	void RemoveSubtree(Node* Ptr);

	std::ostream& stream_helper_Private(std::ostream& stream, Node* Ptr);

	std::vector<K>& MakeVectorPrivate(std::vector<K>& keys, Node* Ptr);

	std::vector<K> MakeVector()
	{
		std::vector<K> keys;
		return MakeVectorPrivate(keys, root);
	}

	void Violations(Node* Ptr)
	{
		
		// VIOLATION 0
		if (Ptr->dad == nullptr || Ptr->dad->dad == nullptr)
		{
			if (root->red = true)
			{
				root->red = false;
			}
			return;
		}

		///
		
		Node* a = Ptr->dad->dad;
		Node* b = Ptr->dad;
		Node* c;

		if (b == a->sx)
		{
			c = a->dx;
		}
		else
		{
			c = a->sx;
		}


	// Red uncle

		// VIOLATION 1
		if (Ptr->red == true && c != nullptr && c->red == true)
		{
			a->red = true;
			b->red = false;
			c->red = false;
			return Violations(b);
		}

		
	// Black uncle

		if (Ptr->red == true && (c == nullptr || c->red == false) && b->red == true)
		{
			// VIOLATION 2_1
			if (Ptr == b->dx && b == a->sx)
			{
				b->dx = Ptr->sx;
				b->dx->dad = b;
				b->dad = Ptr;

				Ptr->sx = b;
				Ptr->dad = a;
				a->sx = Ptr;

				return Violations(b);
			}

			// VIOLATION 2_2
			if (Ptr == b->sx && b == a->dx)
			{
				b->sx = Ptr->dx;
				b->sx->dad = b;
				b->dad = Ptr;

				Ptr->dx = b;
				Ptr->dad = a;
				a->dx = Ptr;

				return Violations(b);
			}

			// VIOLATION 3_1
			if (Ptr == b->sx && b == a->sx)
			{
				b->dad = a->dad;
				if (a->dad != nullptr)
				{
					a->dad->dx == a ? a->dad->dx = b : a->dad->sx = b;
				}
				else
				{
					root = b;
				}
				

				a->sx = b->dx;
				if (a->sx != nullptr)
				{
					a->sx->dad = a;
				}
				a->dad = b;
				a->red = true;

				b->dx = a;
				b->red = false;

				return Violations(Ptr);
			}

			// VIOLATION 3_2
			if (Ptr == b->dx && b == a->dx)
			{
				b->dad = a->dad;
				if (a->dad != nullptr)
				{
					a->dad->dx == a ? a->dad->dx = b : a->dad->sx = b;
				}
				else
				{
					root = b;
				}
				

				a->dx = b->sx;
				if (a->dx != nullptr)
				{
					a->dx->dad = a;
				}
				a->dad = b;
				a->red = true;

				b->sx = a;
				b->red = false;

				return Violations(Ptr);
			}
		}

		return Violations(b);
		
	}

public:

	RBT()
	{
		root = 0;
	}

	~RBT()
	{
		RemoveSubtree(root);
	}

	RBT(const RBT& t);

	RBT& operator=(const RBT& t);

	RBT(RBT&& t) noexcept
		: root{ std::move(t.root) } {}

	RBT& operator=(RBT&& t) noexcept
	{
		root = std::move(t.root);
		return *this;
	}

	void AddLeaf(const K key, V val)
	{
		AddLeafPrivate(key, val, root);
	}

	void PrintInOrder()
	{
		PrintInOrderPrivate(root);
	}

	void PrintFamily(const K key);

	void PrintRoot()
	{
		std::cout << "Root: " << root->pair.first << std::endl;
	}

	void Clear()
	{
		RemoveSubtree(root);
		root = 0;
	}

	// Operator Overloading

	V& operator[](const K& key)
	{
		if (ReturnNode(key) == nullptr)
		{
			this->AddLeaf(key, V{});
			std::cout << "Node with key " << key << " has been added to the tree with value " << V{} << std::endl;
		}
		return ReturnNode(key)->pair.second;
	}

	std::ostream& stream_helper(std::ostream& stream) {
		return stream_helper_Private(stream, root);
	}

	friend std::ostream& operator <<(std::ostream& stream, RBT& bst)
	{
		bst.stream_helper(stream);
		return stream;
	}

	// Iterators

	class Iterator;
	class ConstIterator;

	Iterator begin() noexcept { return Iterator{ FindSmallest(root) }; }
	ConstIterator cbegin() const noexcept { return ConstIterator{ FindSmallest(root) }; }
	Iterator end() noexcept { return Iterator{ 0 }; }
	ConstIterator cend() const noexcept { return ConstIterator{ 0 }; }

	Iterator find(K key) noexcept
	{
		std::vector<K> keys = MakeVector();
		Iterator it = this->begin();
		for (int i = 0; i < static_cast<int>(keys.size()); ++i)
		{
			if (keys[i] == key) { return it; }
			++it;
		}
		return it;
	}
};

template <typename K, typename V>
class RBT<K, V>::Iterator
	: public std::iterator<std::forward_iterator_tag, K, std::ptrdiff_t, K*, K&>
{
	using Node = RBT<K, V>::Node;
	Node* itr;

public:

	Iterator(Node* n)
		: itr(n) {}

	Iterator()
		: itr(nullptr) {}

	const K& operator*() const { return itr->pair.first; }

	const K& operator-> () const
	{
		//assert(itr != nullptr && "Invalid iterator dereference!");
		return itr->pair.first;
	}

	Iterator& operator++();

	Iterator operator++ (int) // POST-increment
	{
		//assert(itr != nullptr && "Out-of-bounds iterator increment!");
		Iterator tmp(*this);
		++(*this);
		return tmp;
	}

	bool operator ==(const Iterator& rhs)
	{
		return itr == rhs.itr;
	}

	bool operator != (const Iterator& rhs) const
	{
		return !(itr == rhs.itr);
	}

};

template <typename K, typename V>
typename RBT<K, V>::Iterator& RBT<K, V>::Iterator::operator++()
{
	if (this->itr->dx != nullptr)
	{
		this->itr = this->itr->dx;
		while (this->itr->sx != nullptr)
		{
			this->itr = this->itr->sx;
		}
	}
	else if (this->itr->dad != nullptr)
	{
		if (this->itr->dad)
			while (this->itr->dad->dx == this->itr)
			{
				this->itr = this->itr->dad;
				if (this->itr->dad == nullptr)
				{
					this->itr = nullptr;
					return *this;
				}
			}
		this->itr = this->itr->dad;
	}
	else
	{
		this->itr = nullptr;
	}

	return *this;
}

template <typename K, typename V>
class RBT<K, V>::ConstIterator : public RBT<K, V>::Iterator {
public:
	using parent = RBT<K, V>::Iterator;
	using parent::Iterator;
	const K& operator*() const { return parent::operator*(); }
};

template <typename K, typename V>
void RBT<K, V>::AddLeafPrivate(const K key, V val, RBT<K, V>::Node* Ptr)
{
	if (root == nullptr)
	{
		root = CreateLeaf(key, val);
		root->red = false;
	}
	else if (key < Ptr->pair.first)
	{
		if (Ptr->sx != nullptr)
		{
			AddLeafPrivate(key, val, Ptr->sx);
		}
		else
		{
			Ptr->sx = CreateLeaf(key, val);
			Ptr->sx->dad = Ptr;
			Violations(Ptr->sx);
		}
	}
	else if (key > Ptr->pair.first)
	{
		if (Ptr->dx != nullptr)
		{
			AddLeafPrivate(key, val, Ptr->dx);
		}
		else
		{
			Ptr->dx = CreateLeaf(key, val);
			Ptr->dx->dad = Ptr;
			Violations(Ptr->dx);
		}
	}
	else
	{
		std::cout << "The key " << key << " has already been added to the tree." << std::endl;
	}
}

template <typename K, typename V>
void RBT<K, V>::PrintInOrderPrivate(RBT<K, V>::Node* Ptr)
{
	if (root != 0)
	{
		if (Ptr->sx != nullptr)
		{
			PrintInOrderPrivate(Ptr->sx);
		}
		//std::cout << "Key: " << Ptr->pair.first << "\t" << "Value: " << Ptr->pair.second << std::endl;

		std::cout << "Node -> " << Ptr->pair.first;

		if (Ptr->dad == nullptr)
		{
			std::cout << "\tdad -> root";
		}
		else
		{
			std::cout << "\tdad -> " << Ptr->dad->pair.first;
		}
		if (Ptr->sx == nullptr)
		{
			std::cout << "\tSX -> NULL";
		}
		else
		{
			std::cout << "\tSX -> " << Ptr->sx->pair.first << std::endl;;
		}
		if (Ptr->dx == nullptr)
		{
			std::cout << "\tDX -> NULL";
		}
		else
		{
			std::cout << "\tDX -> " << Ptr->dx->pair.first << std::endl;
		}
		if (Ptr->red == true)
		{
			std::cout << "\tRED" << std::endl;
		}
		else
		{
			std::cout << "\tBLACK" << std::endl;
		}
		if (Ptr->dx != nullptr)
		{
			PrintInOrderPrivate(Ptr->dx);
		}
	}
	else
	{
		std::cout << "The tree is empty" << std::endl;
	}
}

template <typename K, typename V>
void RBT<K, V>::RemoveSubtree(RBT<K, V>::Node* Ptr)
{
	if (Ptr != nullptr)
	{
		if (Ptr->sx != nullptr)
		{
			RemoveSubtree(Ptr->sx);
		}
		if (Ptr->dx != nullptr)
		{
			RemoveSubtree(Ptr->dx);
		}
		delete Ptr;
	}
}

template <typename K, typename V>
std::ostream& RBT<K, V>::stream_helper_Private(std::ostream& stream, RBT<K, V>::Node* Ptr)
{
	if (Ptr != nullptr) {
		stream_helper_Private(stream, Ptr->sx);
		stream << "{" << Ptr->pair.first << " : " << Ptr->pair.second << " }" << std::endl;
		stream_helper_Private(stream, Ptr->dx);
	}
	return stream;
}

template <typename K, typename V>
void RBT<K, V>::PrintFamily(const K key)
{
	Node* Ptr = ReturnNode(key);

	if (Ptr != nullptr)
	{
		std::cout << "Node -> " << Ptr->pair.first;

		if (Ptr->dad == nullptr)
		{
			std::cout << "\tdad -> root";
		}
		else
		{
			std::cout << "\tdad -> " << Ptr->dad->pair.first;
		}

		if (Ptr->sx == nullptr)
		{
			std::cout << "\tSX -> NULL";
		}
		else
		{
			std::cout << "\tSX -> " << Ptr->sx->pair.first;
		}


		if (Ptr->dx == nullptr)
		{
			std::cout << "\tDX -> NULL";
		}
		else
		{
			std::cout << "\tDX -> " << Ptr->dx->pair.first;
		}

		if (Ptr->red == true)
		{
			std::cout << "\tRED" << std::endl;
		}
		else
		{
			std::cout << "\tBLACK" << std::endl;
		}
	}
	else
	{
		std::cout << "Key " << key << " is not in the tree." << std::endl;
	}
}

template <typename K, typename V>
std::vector<K>& RBT<K, V>::MakeVectorPrivate(std::vector<K>& keys, RBT<K, V>::Node* Ptr)
{
	if (root != 0)
	{
		if (Ptr->sx != nullptr)
		{
			MakeVectorPrivate(keys, Ptr->sx);
		}
		keys.push_back(Ptr->pair.first);
		if (Ptr->dx != nullptr)
		{
			MakeVectorPrivate(keys, Ptr->dx);
		}
	}
	return keys;
}