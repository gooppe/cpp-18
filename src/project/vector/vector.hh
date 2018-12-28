#ifndef VECTOR_HH
#define VECTOR_HH

#include <stdexcept>
#include <initializer_list>

template <typename T>
class Vector
{
    T *_first = nullptr;

    size_t _size = 0;
    size_t _capacity = 0;
    const uint empty_alloc_memory = 0;
    const float alloc_factor = 1.5;
    const uint reduce_factor = 2;

    void allocate_memory(size_t desiredCapacity);

  public:
    using iterator = T *;
    using const_iterator = const T *;
    Vector();
    Vector(Vector<T> &&x);
    Vector(const Vector<T> &x);
    ~Vector();
    Vector(std::initializer_list<T> data);
    T &operator[](size_t idx) const;
    Vector &operator=(Vector &&x);
    Vector &operator=(const Vector &x);
    void push_back(const T &value);
    void push_back(T &&value);
    void pop_back();
    iterator erase(iterator first, iterator last);
    iterator erase(iterator pos);
    iterator begin() const;
    iterator end() const;
    void swap(Vector &other);
    size_t size() const;
    size_t capacity() const;
    T &at(size_t idx) const;
};

template <typename T>
void swap(Vector<T> &a, Vector<T> &b);

#endif