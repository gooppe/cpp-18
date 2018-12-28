#include <project/vector/vector.hh>

template <typename T>
void Vector<T>::allocate_memory(size_t desiredCapacity)
{
    if (this->_capacity < desiredCapacity || desiredCapacity * this->reduce_factor < this->_capacity)
    {
        this->_capacity = (size_t)(desiredCapacity * this->alloc_factor);
        // T *new_chunk = (T *)(realloc(this->_first, this->_capacity * sizeof(T)));
        // this->_first = new_chunk ?: throw std::bad_alloc();
        // T *new_chunk = new T[this->_capacity];
        T *old_chunk = new T[this->_capacity];
        std::swap(old_chunk, this->_first);
        for (size_t i = 0; i < this->_size; i++)
        {
            this->_first[i] = std::move(old_chunk[i]);
        }
        if (old_chunk != this->_first)
        {
            delete[] old_chunk;
        }
    }
}

template <typename T>
Vector<T>::Vector() : _size(0), _capacity(0)
{
    this->allocate_memory(this->empty_alloc_memory);
}

template <typename T>
Vector<T>::Vector(Vector<T> &&x) : _first(x.begin()), _size(x.size()), _capacity(x.capacity())
{
    x._first = nullptr;
}

template <typename T>
Vector<T>::Vector(const Vector<T> &x)
{
    this->allocate_memory(x.size());
    this->_size = x.size();
    for (uint i = 0; i < x.size(); i++)
    {
        this->_first[i] = x[i];
    }
}

template <typename T>
Vector<T>::~Vector()
{
    // std::free(this->_first);
    delete[] this->_first;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> data) : _size(0), _capacity(0)
{
    this->allocate_memory(data.size());
    this->_size = 0;
    for (auto item : data)
    {
        this->_first[this->_size++] = item;
    }
}

template <typename T>
T &Vector<T>::operator[](size_t idx) const
{
    return this->_first[idx];
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&x)
{
    delete[] this->_first;
    this->_first = nullptr;

    this->swap(x);

    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &x)
{
    if (this != &x)
    {
        this->_size = 0;
        this->allocate_memory(x.size());
        this->_size = x.size();
        for (uint i = 0; i < this->_size; i++)
        {
            this->_first[i] = x[i];
        }
    }
    return *this;
}

template <typename T>
void Vector<T>::push_back(const T &value)
{
    this->allocate_memory(this->_size + 1);
    this->_first[this->_size++] = value;
}

template <typename T>
void Vector<T>::push_back(T &&value)
{
    this->allocate_memory(this->_size + 1);
    // new (this->_first + this->_size++) T(std::move(value));
    this->_first[this->_size++] = std::move(value);
}

template <typename T>
void Vector<T>::pop_back()
{
    if (this->_size > 0)
    {
        this->allocate_memory(--this->_size);
    }
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last)
{
    if (first < last && first >= this->begin() && last <= this->end())
    {
        uint range = last - first;

        for (iterator i = first; i < this->end() - range; i++)
        {
            *i = *(i + range);
        }
        this->_size -= range;
        this->allocate_memory(this->_size);
        return first;
    }
    else
    {
        throw std::out_of_range("Vector::erase");
    }
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator pos)
{
    return this->erase(pos, pos + 1);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() const
{
    return this->_first;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() const
{
    return this->_first + this->_size;
}

template <typename T>
void Vector<T>::swap(Vector &other)
{
    std::swap(this->_first, other._first);
    std::swap(this->_capacity, other._capacity);
    std::swap(this->_size, other._size);
}

template <typename T>
size_t Vector<T>::size() const
{
    return this->_size;
}

template <typename T>
size_t Vector<T>::capacity() const
{
    return this->_capacity;
}

template <typename T>
T &Vector<T>::at(size_t idx) const
{
    if (idx < this->_size)
    {
        return this->_first[idx];
    }
    else
    {
        throw std::out_of_range("Vector::at");
    }
}

template <typename T>
void swap(Vector<T> &a, Vector<T> &b)
{
    a.swap(b);
}