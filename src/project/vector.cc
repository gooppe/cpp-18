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

    void allocate_memory(size_t desiredCapacity)
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

  public:
    using iterator = T *;
    using const_iterator = const T *;
    Vector() : _size(0), _capacity(0)
    {
        this->allocate_memory(this->empty_alloc_memory);
    }

    Vector(Vector<T> &&x) : _first(x.begin()), _size(x.size()), _capacity(x.capacity())
    {
        x._first = nullptr;
    }

    Vector(const Vector<T> &x) : _size(x.size())
    {
        this->allocate_memory(this->_size);
        for (uint i = 0; i < x.size(); i++)
        {
            this->_first[i] = x[i];
        }
    }

    ~Vector()
    {
        // std::free(this->_first);
        delete[] this->_first;
    }

    Vector(std::initializer_list<T> data) : _size(0), _capacity(0)
    {
        this->allocate_memory(data.size());
        this->_size = 0;
        for (auto item : data)
        {
            this->_first[this->_size++] = item;
        }
    }

    T &operator[](size_t idx) const
    {
        return this->_first[idx];
    }

    Vector &operator=(Vector &&x)
    {
        this->_first = x.begin();
        this->_size = x.size();
        this->_capacity = x.capacity();
        x._first = nullptr;
        return *this;
    }

    Vector &operator=(const Vector &x)
    {
        if (this != &x)
        {
            delete this->_first;
            this->allocate_memory(x.size());
            for (uint i = 0; i < x.size(); i++)
            {
                this->_first[i] = x[i];
            }
        }
        return *this;
    }

    void push_back(const T &value)
    {
        this->allocate_memory(this->_size + 1);
        this->_first[this->_size++] = value;
    }

    void push_back(T &&value)
    {
        this->allocate_memory(this->_size + 1);
        // new (this->_first + this->_size++) T(std::move(value));
        this->_first[this->_size++] = std::move(value);
    }

    void pop_back()
    {
        if (this->_size > 0)
        {
            this->allocate_memory(--this->_size);
        }
    }

    iterator erase(iterator first, iterator last)
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

    iterator erase(iterator pos)
    {
        return this->erase(pos, pos + 1);
    }

    iterator begin() const
    {
        return this->_first;
    }

    iterator end() const
    {
        return this->_first + this->_size;
    }

    void swap(Vector &other)
    {
        std::swap(this->_first, other._first);
        std::swap(this->_capacity, other._capacity);
        std::swap(this->_size, other._size);
    }

    size_t size() const
    {
        return this->_size;
    }

    size_t capacity() const
    {
        return this->_capacity;
    }

    T &at(size_t idx) const
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
};

template <typename T>
void swap(Vector<T> &a, Vector<T> &b)
{
    a.swap(b);
}