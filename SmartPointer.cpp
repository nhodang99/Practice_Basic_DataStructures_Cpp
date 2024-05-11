#include <iostream>

///////////////////
////////////////// UNIQUE POINTER /////////////////////////
///////////////////
template <typename T>
class UniquePointer
{
   T *m_ptr{nullptr};

public:
   UniquePointer()
   {
      m_ptr = new T;
   }

   UniquePointer(T value)
   {
      m_ptr = new T;
      *m_ptr = value;
   }

   ~UniquePointer()
   {
      if (m_ptr)
      {
         delete m_ptr;
         std::cout << "Delete memory at address " << m_ptr << " done!\n";
         m_ptr = nullptr;
      }
   }

   UniquePointer(UniquePointer &&source) // Move constructor
   {
      delete m_ptr;
      m_ptr = source.m_ptr;

      source.m_ptr = nullptr;
   }

   UniquePointer &operator=(UniquePointer &&source) // Move assignment operator
   {
      if (this == &source)
      {
         return *this;
      }
      delete m_ptr;
      m_ptr = source.m_ptr;

      source.m_ptr = nullptr;

      return *this;
   }

   T &operator*()
   {
      if (m_ptr)
      {
         return *m_ptr;
      }
      throw "Null pointer exception";
   }

private:
   // Do not authorize copying policy in unique pointer
   UniquePointer &operator=(const UniquePointer &other); // Copy assignment operator
   UniquePointer(const UniquePointer &other);            // Copy constructor
};

///////////////////
////////////////// SHARED POINTER /////////////////////////
///////////////////
template <typename T>
class SharedPointer
{
   T *m_ptr{nullptr};
   int *m_pRefCounter{nullptr};

public:
   SharedPointer() // Constructor
   {
      m_ptr = new T;
      m_pRefCounter = new int;
      (*m_pRefCounter)++;

      std::cout << "address " << m_ptr << " ref counter " << *m_pRefCounter << std::endl;
   }

   SharedPointer(T value) // Constructor
   {
      m_ptr = new T;
      m_pRefCounter = new int;
      *m_ptr = value;
      (*m_pRefCounter)++;

      std::cout << "address " << m_ptr << " ref counter " << *m_pRefCounter << std::endl;
   }

   ~SharedPointer() // Destructor
   {
      if (m_ptr)
      {
         (*m_pRefCounter)--;
         std::cout << "Address " << m_ptr << " Ref counter remain " << *m_pRefCounter << std::endl;
         if (*m_pRefCounter == 0)
         {
            delete m_ptr;
            delete m_pRefCounter;
            std::cout << " Delete memory at " << m_ptr << " done!\n";
         }
         m_ptr = nullptr;
         m_pRefCounter = nullptr;
      }
   }

   SharedPointer(const SharedPointer &source) // Copy constructor
   {
      if (m_pRefCounter && *m_pRefCounter > 0)
      {
         (*m_pRefCounter)--;
         if (*m_pRefCounter == 0)
         {
            delete m_ptr;
            delete m_pRefCounter;
            std::cout << "Copy constructor delete memory at " << m_ptr << " done!\n";
         }
      }
      m_ptr = source.m_ptr;
      m_pRefCounter = source.m_pRefCounter;
      (*m_pRefCounter)++;
   }

   SharedPointer &operator=(const SharedPointer &source) // Copy assignment operator
   {
      if (this == &source)
      {
         return *this;
      }

      if (m_pRefCounter && *m_pRefCounter > 0)
      {
         (*m_pRefCounter)--;
         if (*m_pRefCounter == 0)
         {
            delete m_ptr;
            delete m_pRefCounter;
            std::cout << "Copy assignment delete memory at " << m_ptr << " done!\n";
         }
      }

      m_ptr = source.m_ptr;
      m_pRefCounter = source.m_pRefCounter;
      (*m_pRefCounter)++;

      return *this;
   }

   SharedPointer(SharedPointer &&source) // Move constructor
   {
      if (m_pRefCounter && *m_pRefCounter > 0)
      {
         (*m_pRefCounter)--;
         if (*m_pRefCounter == 0)
         {
            delete m_ptr;
            delete m_pRefCounter;
            std::cout << "Move consructor delete memory at " << m_ptr << " done!\n";
         }
      }

      m_ptr = source.m_ptr;
      m_pRefCounter = source.m_pRefCounter;
      (*m_pRefCounter)++;
   }

   SharedPointer &operator=(SharedPointer &&source) // Move assignment operator
   {
      if (this == &source)
      {
         return *this;
      }

      if (m_pRefCounter && *m_pRefCounter > 0)
      {
         (*m_pRefCounter)--;
         if (*m_pRefCounter == 0)
         {
            delete m_ptr;
            delete m_pRefCounter;
            std::cout << "Move assignment delete memory at " << m_ptr << " done!\n";
         }
      }

      m_ptr = source.m_ptr;
      m_pRefCounter = source.m_pRefCounter;
      (*m_pRefCounter)++;

      return *this;
   }

   T &operator*()
   {
      if (m_ptr)
      {
         return *m_ptr;
      }
      throw "Null pointer exception";
   }
};

int main()
{
   std::cout << "=================UNIQUE POINTER==========================\n\n";
   UniquePointer<int> intUniquePtr(4);
   std::cout << "intUniquePtr: " << *intUniquePtr << std::endl;

   UniquePointer<std::string> strUniquePtr("haha");
   std::cout << "strUniquePtr: " << *strUniquePtr << std::endl;

   UniquePointer<std::string> strUniquePtr2("ua");
   std::cout << "strUniquePtr2: " << *strUniquePtr2 << std::endl;

   UniquePointer<std::string> strUniquePtr3 = UniquePointer<std::string>("hehehe"); // move constructor
   std::cout << "strUniquePtr3: " << *strUniquePtr3 << std::endl;

   strUniquePtr2 = UniquePointer<std::string>("hohohohoho"); // move assignment
   std::cout << "strUniquePtr2: " << *strUniquePtr2 << std::endl;

   std::cout << "\n\n=================SHARED POINTER==========================\n\n";

   // SharedPointer<int> intSharedPointer(99);
   // std::cout << "intSharedPointer: " << *intSharedPointer << std::endl;

   SharedPointer<std::string> strSharedPtr("test1");
   std::cout << "strSharedPointer: " << *strSharedPtr << std::endl;

   SharedPointer<std::string> strSharedPtr2("hum");
   std::cout << "strSharedPointer2: " << *strSharedPtr2 << std::endl;

   SharedPointer<std::string> strSharedPtr3 = SharedPointer<std::string>("test2test2test2"); // move constructor
   std::cout << "strSharedPointer3: " << *strSharedPtr3 << std::endl;

   strSharedPtr2 = SharedPointer<std::string>("lalalalalalalalalalalalla"); // move assignment
   std::cout << "new strSharedPointer2: " << *strSharedPtr2 << std::endl;

   strSharedPtr3 = strSharedPtr; // Copy assignment operator
   std::cout << "new strSharedPointer3 = 2: " << *strSharedPtr2 << std::endl;

   SharedPointer<std::string> strSharedPtr4 = strSharedPtr; // copy constructor
   std::cout << "strSharedPointer4 = 2: " << *strSharedPtr2 << std::endl;

   std::cout << "\n\n=================DESTRUCTOR==========================\n\n";

   return 0;
}