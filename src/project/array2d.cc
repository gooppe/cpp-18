#include <cstddef>
#include <stdexcept>
#include <math.h>
#include <iostream>

template <class T>
class MaskedArray2d;

template <class T>
class Array2d
{
    T **data_ = nullptr;
    size_t rows_ = 0, cols_ = 0;

  public:
    Array2d(size_t r, size_t c) : rows_(r), cols_(c)
    {
        if (r < 1 || c < 1)
        {
            throw std::invalid_argument("Size of array should be neq 0");
        }
        data_ = new T *[rows_];
        for (size_t i = 0; i < rows_; i++)
        {
            data_[i] = new T[cols_];
        }
    }

    Array2d(size_t r, size_t c, T fill_value) : Array2d(r, c)
    {
        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                data_[i][j] = fill_value;
            }
        }
    }

    Array2d(size_t r, size_t c, std::initializer_list<T> data) : Array2d(r, c)
    {
        if (r * c != data.size())
        {
            throw std::invalid_argument("Data size and array shapes are not compatible");
        }

        size_t idx = 0;
        for (const T &value : data)
        {
            data_[idx / c][idx % c] = value;
            idx++;
        }
    }

    Array2d(const Array2d &array) : Array2d(array.cols_, array.rows_)
    {
        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                data_[i][j] = array.data_[i][j];
            }
        }
    }

    Array2d &operator=(const Array2d &array)
    {
        if (!is_compatible(array))
        {
            throw std::length_error("Shapes of arrays are not equal in Array2d::operator=");
        }

        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                data_[i][j] = array.data_[i][j];
            }
        }

        return *this;
    }

    T &operator()(size_t r, size_t c) const
    {
        return data_[r][c];
    }

    MaskedArray2d<T> operator()(Array2d<bool> mask)
    {
        return MaskedArray2d<T>(*this, mask);
    }

    Array2d &operator+=(const Array2d &array)
    {
        if (!is_compatible(array))
        {
            throw std::length_error("Shapes of arrays are not equal in Array2d::operator+");
        }

        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                data_[i][j] += array.data_[i][j];
            }
        }

        return *this;
    }

    friend Array2d operator+(Array2d a1, const Array2d &a2)
    {
        return a1 += a2;
    }

    Array2d operator-()
    {
        auto result = Array2d<T>(rows_, cols_);

        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                result.data_[i][j] = -data_[i][j];
            }
        }

        return result;
    }

    Array2d &operator-=(const Array2d &array)
    {
        if (!is_compatible(array))
        {
            throw std::length_error("Shapes of arrays are not equal in Array2d::operator-");
        }

        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                data_[i][j] -= array.data_[i][j];
            }
        }

        return *this;
    }

    friend Array2d operator-(Array2d a1, const Array2d &a2)
    {
        return a1 -= a2;
    }

    Array2d &operator*=(const Array2d &array)
    {
        if (!is_compatible(array))
        {
            throw std::length_error("Shapes of arrays are not equal in Array2d::operator*");
        }

        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                data_[i][j] *= array.data_[i][j];
            }
        }

        return *this;
    }

    friend Array2d operator*(Array2d a1, const Array2d &a2)
    {
        return a1 *= a2;
    }

    Array2d &operator/=(const Array2d &array)
    {
        if (!is_compatible(array))
        {
            throw std::length_error("Shapes of arrays are not equal in Array2d::operator/");
        }

        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                data_[i][j] /= array.data_[i][j];
            }
        }

        return *this;
    }

    friend Array2d operator/(Array2d a1, const Array2d &a2)
    {
        return a1 /= a2;
    }

    Array2d<bool> operator==(const Array2d &array)
    {
        if (!is_compatible(array))
        {
            throw std::length_error("Shapes of arrays are not equal in Array2d::operator==");
        }

        auto result = Array2d<bool>(rows_, cols_);

        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                result(i, j) = data_[i][j] == array.data_[i][j];
            }
        }

        return result;
    }

    Array2d<bool> operator!()
    {
        auto result = Array2d<bool>(rows_, cols_);

        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                result(i, j) = !data_[i][j];
            }
        }

        return result;
    }

    Array2d<bool> operator!=(const Array2d &array)
    {
        return !(*this == array);
    }

    Array2d<bool> operator<(const Array2d &array)
    {
        if (!is_compatible(array))
        {
            throw std::length_error("Shapes of arrays are not equal in Array2d::operator<");
        }

        auto result = Array2d<bool>(rows_, cols_);

        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                result(i, j) = data_[i][j] < array.data_[i][j];
            }
        }

        return result;
    }

    Array2d<bool> operator>(const Array2d &array)
    {
        if (!is_compatible(array))
        {
            throw std::length_error("Shapes of arrays are not equal in Array2d::operator>");
        }

        auto result = Array2d<bool>(rows_, cols_);

        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                result(i, j) = data_[i][j] > array.data_[i][j];
            }
        }

        return result;
    }

    Array2d<bool> operator<=(const Array2d &array)
    {
        return !(*this > array);
    }

    Array2d<bool> operator>=(const Array2d &array)
    {
        return !(*this < array);
    }

    template <class P>
    bool is_compatible(const Array2d<P> &array) const
    {
        return is_compatible(*this, array);
    }

    template <class P>
    static bool is_compatible(const Array2d<T> &a1, const Array2d<P> &a2)
    {
        return (a1.cols() == a2.cols() && a1.rows() == a2.rows());
    }

    bool equal(const Array2d<T> &array) const
    {
        return equal(*this, array);
    }

    static bool equal(const Array2d &a1, const Array2d &a2)
    {
        if (!is_compatible(a1, a2))
        {
            return false;
        }

        for (size_t i = 0; i < a1.rows(); i++)
        {
            for (size_t j = 0; j < a1.cols(); j++)
            {
                if (a1(i, j) != a2(i, j))
                {
                    return false;
                }
            }
        }

        return true;
    }

    T &at(size_t r, size_t c) const
    {
        if (r < rows_ && c < cols_)
        {
            return data_[r][c];
        }
        else
        {
            throw std::out_of_range("Array2d::(size_t,size_t)");
        }
    }

    size_t rows() const
    {
        return rows_;
    }

    size_t cols() const
    {
        return cols_;
    }

    ~Array2d()
    {
        for (size_t i = 0; i < rows_; i++)
        {
            delete[] data_[i];
        }
        delete[] data_;
    }
};

template <class T>
std::ostream &operator<<(std::ostream &out, const Array2d<T> &array)
{
    size_t printed_rows = array.rows() < 5 ? array.rows() : 2;
    size_t printed_cols = array.cols() < 5 ? array.cols() : 2;

    out << "Array2d of shape (" << array.rows() << " , " << array.cols() << "):" << std::endl;

    for (size_t i = 0; i < printed_rows; i++)
    {
        for (size_t j = 0; j < printed_cols - 1; j++)
        {
            out << array(i, j) << ",\t";
        }
        if (array.cols() >= 5)
        {
            out << array(i, printed_cols - 1) << ",\t...,\t";
        }
        out << array(i, array.cols() - 1) << std::endl;
    }
    if (array.rows() >= 5)
    {
        for (size_t j = 0; j < std::min(array.cols(), (size_t)4) - 1; j++)
        {
            out << "...,\t";
        }
        out << "..." << std::endl;
        for (size_t j = 0; j < printed_cols - 1; j++)
        {
            out << array(3, j) << ",\t";
        }
        if (array.cols() >= 5)
        {
            out << array(3, printed_cols - 1) << ",\t...,\t";
        }
        out << array(3, array.cols() - 1) << std::endl;
    }

    return out;
}

template <class T>
class MaskedArray2d
{
  public:
    Array2d<T> array;
    Array2d<bool> mask;

    MaskedArray2d(const Array2d<T> &a, const Array2d<bool> &m) : array(a), mask(m)
    {
        if (!array.is_compatible(mask))
        {
            throw std::length_error("Array and mask are not compatible");
        }
    }

    Array2d<T> operator=(const T value)
    {
        auto result = Array2d<T>(array.rows(), array.cols());
        for (size_t i = 0; i < array.rows(); i++)
        {
            for (size_t j = 0; j < array.cols(); j++)
            {
                result(i, j) = mask(i, j) ? value : array(i, j);
            }
        }
        return result;
    }
};
