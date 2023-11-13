// @Doubly linked list
//
// @Pros: - Dynamic arrangement: Grow and shrink at run time -> Effiecient for large data
//        - No memory wastage: no need a pre-allocation
//        - Fast delete, fast insert: No need to shift element after that
//        - Scalability: add or remove elements at any position
//        - Easy reversing
// @Cons: - More memory uasge require since a pointer to next element is needed
//        - Random access (indexed base) is not possible
//        - Slow searching
// @Uses: - Navigation systems (maps, browser), MRU/LRU cache,...
#include <iostream>

template <typename T>
struct Node
{
  T m_value;
  Node<T> *m_pNext{nullptr};
  Node<T> *m_pPrev{nullptr};

  Node(T value) : m_value(value) {}
  ~Node()
  {
    m_pNext = nullptr;
    m_pPrev = nullptr;
  }
};

template <typename T>
class DoublyLinkedList
{
  Node<T> *m_pHead{nullptr};
  Node<T> *m_pTail{nullptr};
  int m_size{0};

public:
  ~DoublyLinkedList()
  {
    auto curNode = m_pHead;
    while (curNode != nullptr)
    {
      auto tmp = curNode;
      curNode = curNode->m_pNext;
      delete tmp;
    }
  }

  /// @brief Add new value to the list
  /// @param value new value to add
  void add(T value)
  {
    auto newNode = new Node<T>(value);
    m_size++;
    if (m_pHead == nullptr)
    {
      m_pHead = newNode;
      m_pTail = newNode;
      return;
    }

    m_pTail->m_pNext = newNode;
    newNode->m_pPrev = m_pTail;
    m_pTail = newNode;
  }

  /// @brief insert value at the specified index
  /// @param idx index to insert
  /// @param value value to insert
  /// @return true upon success
  bool insert(int idx, T value)
  {
    if (idx < 0 || idx > m_size || (idx != 0 && m_size == 0))
    {
      return false;
    }

    auto newNode = new Node<T>(value);
    if (idx == 0)
    {
      if (m_size == 0)
      {
        m_pHead = newNode;
        m_pTail = newNode;
      }
      else
      {
        m_pHead->m_pPrev = newNode;
        newNode->m_pNext = m_pHead;
        m_pHead = newNode;
      }
    }
    else if (idx == m_size)
    {
      m_pTail->m_pNext = newNode;
      newNode->m_pPrev = m_pTail;
      m_pTail = newNode;
    }
    else
    {
      // Retrieve the current node at the requested position
      auto nodeAtIdx = findNode(idx);

      nodeAtIdx->m_pPrev->m_pNext = newNode;
      newNode->m_pPrev = nodeAtIdx->m_pPrev;
      nodeAtIdx->m_pPrev = newNode;
      newNode->m_pNext = nodeAtIdx;
    }
    m_size++;
    return true;
  }

  /// @brief Update value at the specified index
  /// @param idx index of the node to update
  /// @param value new value
  /// @return true upon success
  bool update(int idx, T value)
  {
    if (m_size == 0 || idx < 0 || idx > m_size - 1)
    {
      return false;
    }

    auto node = findNode(idx);
    node->m_value = value;
    return true;
  }

  /// @brief Remove the node at index idx
  /// @param idx index of the node to remove
  /// @return true upon success
  bool remove(int idx)
  {
    if (m_size == 0 || idx < 0 || idx > m_size - 1)
    {
      return false;
    }

    Node<T> *nodeToRemove = nullptr;
    if (idx == 0)
    {
      nodeToRemove = m_pHead;
      m_pHead->m_pPrev = nullptr;
      m_pHead = m_pHead->m_pNext;
    }
    else if (idx == m_size - 1)
    {
      nodeToRemove = m_pTail;
      m_pTail = m_pTail->m_pPrev;
      m_pTail->m_pNext = nullptr;
    }
    else
    {
      nodeToRemove = findNode(idx);
      nodeToRemove->m_pPrev->m_pNext = nodeToRemove->m_pNext;
      nodeToRemove->m_pNext->m_pPrev = nodeToRemove->m_pPrev;
    }

    delete nodeToRemove;
    nodeToRemove = nullptr;
    m_size--;
    return true;
  }

  /// @brief Get the node with specified index in the list
  /// @param idx index to get
  /// @return the node at the index idx
  Node<T> *findNode(int idx)
  {
    if (idx == 0)
    {
      return m_pHead;
    }
    if (idx == m_size)
    {
      return m_pTail;
    }

    Node<T> *curNode = nullptr;
    int curIdx = 0;
    if (idx <= m_size / 2)
    {
      curNode = m_pHead;
      // Traverse from head
      while (curNode != nullptr && curIdx != idx)
      {
        curNode = curNode->m_pNext;
        curIdx++;
      }
    }
    else
    {
      // Traverse from tail
      curNode = m_pTail;
      curIdx = m_size - 1;
      while (curNode != nullptr && curIdx != idx)
      {
        curNode = curNode->m_pPrev;
        curIdx--;
      }
    }
    return curNode;
  }

  /// @brief returns the element at the specified position
  /// @param idx index
  /// @return value of the node
  T get(int idx)
  {
    return findNode(idx)->m_value;
  }

  /// @brief visualize the linked list
  void toString()
  {
    auto curNode = m_pHead;
    while (curNode != nullptr)
    {
      std::cout << curNode->m_value << " <-> ";
      if (curNode->m_pNext != nullptr && curNode->m_pNext->m_pPrev != curNode)
      {
        std::cout << "nodeLinkError!!! ";
        break;
      }
      curNode = curNode->m_pNext;
    }
    std::cout << "null" << std::endl;
  }
};

int main()
{
  DoublyLinkedList<int> intList;
  intList.add(12);
  intList.add(2);
  intList.add(1);
  intList.insert(0, 11);
  intList.insert(2, 7);
  intList.insert(4, 9);
  intList.insert(6, 8);
  intList.toString();

  intList.update(5, 33);
  intList.remove(6);
  intList.toString();

  std::cout << intList.get(4) << std::endl;

  DoublyLinkedList<std::string> strList;
  strList.insert(1, "a");
  strList.insert(0, "b");
  strList.insert(1, "c");
  strList.toString();

  strList.update(0, "d");
  strList.update(4, "r");
  strList.toString();

  strList.add("f");
  strList.add("h");
  strList.remove(2);
  strList.toString();
}