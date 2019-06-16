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
class BST
{
private:

	struct Node
	{
		std::pair<const K, V> pair;
		Node* sx;
		Node* dx;
		Node* dad;

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

	void RemoveNodePrivate(const K key, Node* current);

	void RemoveMatch(Node* match);

	void RemoveSubtree(Node* Ptr);

	std::ostream& stream_helper_Private(std::ostream& stream, Node* Ptr);

	std::vector<K>& MakeVectorPrivate(std::vector<K>& keys, Node* Ptr);

	std::vector<K> MakeVector()
	{
		std::vector<K> keys;
		return MakeVectorPrivate(keys, root);
	}

	void MakeOrder(typename std::vector<K>::iterator start, typename std::vector<K>::iterator stop, std::vector<K>& ord);

	void Connect(int i, int j, std::vector<K>& ord, std::vector<Node*>& nodes, int* left, int* right, bool* hasleft, bool* hasright, int* parent);

public:

	BST()
	{
		root = 0;
	}

	~BST()
	{
		RemoveSubtree(root);
	}

	BST(const BST& t);

	BST& operator=(const BST& t);

	BST(BST&& t) noexcept
		: root{ std::move(t.root) } {}

	BST& operator=(BST&& t) noexcept
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

	void RemoveNode(const K key)
	{
		return RemoveNodePrivate(key, root);
	}

	void PrintRoot()
	{
		std::cout << "Root: " << root->pair.first << std::endl;
	}

	void Clear()
	{
		RemoveSubtree(root);
		root = 0;
	}

	void Balance();

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

	friend std::ostream& operator <<(std::ostream& stream, BST& bst)
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
class BST<K, V>::Iterator
	: public std::iterator<std::forward_iterator_tag, K, std::ptrdiff_t, K*, K&>
{
	using Node = BST<K, V>::Node;
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
typename BST<K, V>::Iterator& BST<K, V>::Iterator::operator++()
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
class BST<K, V>::ConstIterator : public BST<K, V>::Iterator {
public:
	using parent = BST<K, V>::Iterator;
	using parent::Iterator;
	const K& operator*() const { return parent::operator*(); }
};

template <typename K, typename V>
void BST<K, V>::AddLeafPrivate(const K key, V val, BST<K, V>::Node* Ptr)
{
	if (root == 0)
	{
		root = CreateLeaf(key, val);
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
		}
	}
	else
	{
		std::cout << "The key " << key << " has already been added to the tree." << std::endl;
	}
}

template <typename K, typename V>
void BST<K, V>::MakeOrder(typename std::vector<K>::iterator start, typename std::vector<K>::iterator stop, std::vector<K>& ord)
{
	int n = static_cast<int>(stop - start);
	int m;
	int caos = rand() % 2;
	if (n > 2)
	{
		n % 2 ? m = (n - 1) / 2 : m = (n / 2) - caos;
		ord.push_back(*(start + m));
		MakeOrder(start, start + m, ord);
		MakeOrder(start + m + 1, stop, ord);
	}
	else if (n == 2)
	{
		ord.push_back(*(start + caos));
		ord.push_back(*(start + 1 - caos));
	}
	else
	{
		ord.push_back(*start);
	}
}

template <typename K, typename V>
void BST<K, V>::PrintInOrderPrivate(BST<K, V>::Node* Ptr)
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
			std::cout << "\tSX -> " << Ptr->sx->pair.first;
		}
		if (Ptr->dx == nullptr)
		{
			std::cout << "\tDX -> NULL" << std::endl;
		}
		else
		{
			std::cout << "\tDX -> " << Ptr->dx->pair.first << std::endl;
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
void BST<K, V>::RemoveNodePrivate(const K key, BST<K, V>::Node* current)
{

	if (root != 0)
	{
		if (current->pair.first == key) { RemoveMatch(current); }
		else if (current->pair.first > key && current->sx != nullptr) { RemoveNodePrivate(key, current->sx); }
		else if (current->pair.first < key && current->dx != nullptr) { RemoveNodePrivate(key, current->dx); }
		else { std::cout << "The key " << key << " was not found in the tree." << std::endl; }
	}
	else { std::cout << "The tree is empty." << std::endl; }
}

template <typename K, typename V>
void BST<K, V>::RemoveMatch(BST<K, V>::Node* match)
{
	Node* delPtr = match;

	// caso 0 : 0 figli
	if (delPtr->sx == nullptr && delPtr->dx == nullptr)
	{
		if (delPtr == root) { root = 0; }
		else if (delPtr == delPtr->dad->sx) { delPtr->dad->sx = nullptr; }
		else if (delPtr == delPtr->dad->dx) { delPtr->dad->dx = nullptr; }
		delete delPtr;
	}

	// caso 1 : 1 figlio
	// caso 1.1 : figlio unico a destra

	else if (delPtr->sx == nullptr && delPtr->dx != nullptr)
	{
		if (delPtr == root)
		{
			root = delPtr->dx;
			root->dad = nullptr;
			delPtr->dx = nullptr;
			delete delPtr;
		}
		else
		{
			delPtr->dx->dad = delPtr->dad;
			delPtr->dad->sx == delPtr ? delPtr->dad->sx = delPtr->dx : delPtr->dad->dx = delPtr->dx;
			delPtr->dx = nullptr;
			delete delPtr;
		}
	}

	// caso 1.2 : figlio unico a sinistra

	else if (delPtr->sx != nullptr && delPtr->dx == nullptr)
	{
		if (delPtr == root)
		{
			root = delPtr->sx;
			root->dad = 0;
			delPtr->sx = nullptr;
			delete delPtr;
		}
		else
		{
			delPtr->sx->dad = delPtr->dad;
			delPtr->dad->sx == delPtr ? delPtr->dad->sx = delPtr->sx : delPtr->dad->dx = delPtr->sx;
			delPtr->sx = nullptr;
			delete delPtr;
		}
	}

	// caso 2 : due figli
	else
	{
		Node* replace = FindSmallest(delPtr->dx);

		/////////////////// 1

		if (replace != delPtr->dx)
		{
			if (replace->dx != nullptr) { replace->dx->dad = replace->dad; }
			replace->dad->sx = replace->dx;

			delPtr->sx->dad = replace;
			delPtr->dx->dad = replace;
			replace->sx = delPtr->sx;
			replace->dx = delPtr->dx;

			if (delPtr == root)
			{
				replace->dad = 0;
				root = replace;
			}
			else
			{
				replace->dad = delPtr->dad;
				delPtr == delPtr->dad->sx ? delPtr->dad->sx = replace : delPtr->dad->dx = replace;
			}

			delPtr->sx = nullptr;
			delPtr->dx = nullptr;
			delPtr->dad = nullptr;
			delete delPtr;
		}


		/////////////////////////// 2

		else /// (replace == delPtr->dx)
		{
			delPtr->sx->dad = replace;
			replace->sx = delPtr->sx;
			if (delPtr == root)
			{
				replace->dad = 0;
				root = replace;
			}
			else
			{
				replace->dad = delPtr->dad;
				delPtr == delPtr->dad->sx ? delPtr->dad->sx = replace : delPtr->dad->dx = replace;
			}

			delPtr->sx = nullptr;
			delPtr->dx = nullptr;
			delPtr->dad = nullptr;
			delete delPtr;
		}
	}
}

template <typename K, typename V>
void BST<K, V>::RemoveSubtree(BST<K, V>::Node* Ptr)
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
std::ostream& BST<K, V>::stream_helper_Private(std::ostream& stream, BST<K, V>::Node* Ptr)
{
	if (Ptr != nullptr) {
		stream_helper_Private(stream, Ptr->sx);
		stream << "{" << Ptr->pair.first << " : " << Ptr->pair.second << " }" << std::endl;
		stream_helper_Private(stream, Ptr->dx);
	}
	return stream;
}

template <typename K, typename V>
std::vector<K>& BST<K, V>::MakeVectorPrivate(std::vector<K>& keys, BST<K, V>::Node* Ptr)
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

template <typename K, typename V>
void BST<K, V>::Connect(int i, int j, std::vector<K>& ord, std::vector<BST<K, V>::Node*>& nodes, int* left, int* right, bool* hasleft, bool* hasright, int* parent)
{

	if (ord[i] < ord[j]) {

		if (!hasleft[j]) {
			left[j] = i;
			hasleft[j] = true;
			parent[i] = j;
			return;
		}
		else
		{
			Connect(i, left[j], ord, nodes, left, right, hasleft, hasright, parent);
		}
	}
	else
	{
		if (!hasright[j])
		{
			right[j] = i;
			hasright[j] = true;
			parent[i] = j;
			return;
		}
		else
		{
			Connect(i, right[j], ord, nodes, left, right, hasleft, hasright, parent);
		}
	}
}

template <typename K, typename V>
void BST<K, V>::Balance()
{

	std::vector<K> keys = MakeVector();
	int n = static_cast<int>(keys.size());

	std::vector<K> orderedkeys;
	MakeOrder(keys.begin(), keys.end(), orderedkeys);

	std::vector<Node*> nodes;
	for (int i = 0; i < n; ++i) { nodes.push_back(ReturnNode(orderedkeys[i])); }

	int* left = new int[n];
	bool* hasleft = new bool[n];
	for (int i = 0; i < n; ++i) { hasleft[i] = false; }

	int* right = new  int[n];
	bool* hasright = new bool[n];
	for (int i = 0; i < n; ++i) { hasright[i] = false; }

	int* parent = new int[n];

	for (int i = 1; i < n; ++i)
	{
		Connect(i, 0, orderedkeys, nodes, left, right, hasleft, hasright, parent);
	}


	for (int i = 0; i < n; ++i)
	{
		hasleft[i] ? nodes[i]->sx = nodes[left[i]] : nodes[i]->sx = nullptr;
		hasright[i] ? nodes[i]->dx = nodes[right[i]] : nodes[i]->dx = nullptr;

		if (i == 0)
		{
			nodes[i]->dad = 0;
			root = nodes[i];
		}
		else
		{
			nodes[i]->dad = nodes[parent[i]];
		}
	}

	delete[] left;
	delete[] right;
	delete[] parent;
	delete[] hasleft;
	delete[] hasright;

	std::cout << "----- Tree balanced -----" << std::endl;
}

template <typename K, typename V>
void BST<K, V>::PrintFamily(const K key)
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
			std::cout << "\tDX -> NULL" << std::endl;
		}
		else
		{
			std::cout << "\tDX -> " << Ptr->dx->pair.first << std::endl;
		}
	}
	else
	{
		std::cout << "Key " << key << " is not in the tree." << std::endl;
	}
}
