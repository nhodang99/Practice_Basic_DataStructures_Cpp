#include <iostream>

template <typename T>
struct Node
{
  T m_value;
  Node<T> *m_pNext{nullptr};

  Node(T value) : m_value(value) {}
  ~Node()
  {
    m_pNext = nullptr;
  }
};

template <typename T>
class LinkedList
{
  Node<T> *m_pHead{nullptr};
  Node<T> *m_pTail{nullptr};
  int m_size{0};

public:
  ~LinkedList()
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
    m_pTail = newNode;
  }

  /// @brief insert value at the specified index
  /// @param idx index to insert
  /// @param value value to insert
  /// @return true upon success
  bool insert(int idx, T value)
  {
    if (idx < 0 || idx > m_size || (idx != 0 && m_size == 0))
      return false;

    auto newNode = new Node<T>(value);
    if (idx == 0)
    {
      newNode->m_pNext = m_pHead;
      m_pHead = newNode;
    }
    else if (idx == m_size)
    {
      m_pTail->m_pNext = newNode;
      m_pTail = newNode;
    }
    else
    {
      // Find the node right before the to-be-inserted index
      auto curNode = findNode(idx - 1);
      newNode->m_pNext = curNode->m_pNext;
      curNode->m_pNext = newNode;
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

    auto curNode = findNode(idx);
    curNode->m_value = value;
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
      m_pHead = m_pHead->m_pNext;
    }
    else
    {
      // Find the node before the to-be-removed index
      auto curNode = findNode(idx - 1);
      nodeToRemove = curNode->m_pNext;
      curNode->m_pNext = curNode->m_pNext->m_pNext;

      if (idx == m_size - 1)
      {
        // If the tail is deleted, update the tail to the previous node
        m_pTail = curNode;
        m_pTail->m_pNext = nullptr;
      }
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
    else if (idx == m_size - 1)
    {
      return m_pTail;
    }
    auto curNode = m_pHead;
    int curIdx = 0;
    while (curNode->m_pNext != nullptr && curIdx != idx)
    {
      curIdx++;
      curNode = curNode->m_pNext;
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
    std::cout << "Linked list size: " << m_size << std::endl;
    auto curNode = m_pHead;
    while (curNode != nullptr)
    {
      std::cout << curNode->m_value << " -> ";
      curNode = curNode->m_pNext;
    }
    std::cout << "null" << std::endl;
    std::cout << "------------------\n";
  }
};

int main()
{
  LinkedList<int> list;
  list.add(2);
  list.add(8);
  list.add(5);
  list.toString();

  list.update(0, 7);
  list.update(3, 234);
  list.toString();

  LinkedList<std::string> strList;
  strList.add("a");
  strList.add("c");
  strList.add("b");
  strList.add("g");
  strList.toString();

  strList.remove(0);
  strList.remove(3);
  strList.remove(2);
  strList.toString();

  strList.update(2, "l");
  strList.toString();

  strList.insert(2, "k");
  strList.insert(0, "f");
  strList.insert(5, "m");
  strList.toString();

  std::cout << strList.get(1) << std::endl;
}