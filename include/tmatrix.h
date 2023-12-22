﻿#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_MATRIX_SIZE)
            throw - 1;

        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v)
    {
        if (v.sz <= 0)
            throw - 1;
        else
        {
            this->sz = v.sz;
            this->pMem = new T[this->sz];
            for (int i = 0; i < this->sz; i++)
                this->pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }

    ~TDynamicVector()
    {
        if (this->pMem != nullptr)
            delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;
        if (this->sz != v.sz) {
            if (this->pMem != nullptr)
                delete[] pMem;
            this->sz = v.sz;
            this->pMem = new T[this->sz];
        }
        std::copy(v.pMem, v.pMem + v.sz, pMem);

        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);

        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= this->sz || ind < 0)
            throw - 1;
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= this->sz || ind < 0)
            throw - 1;
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (this->sz != v.sz)
            return false;
        else
        {
            for (int i = 0; i < this->sz; i++)
                if (this->pMem[i] != v.pMem[i])
                    return false;
        }
        return true;

    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (*this == v)
            return false;
        else
            return true;
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(*this);

        for (int i = 0; i < tmp.sz; i++)
            tmp.pMem[i] += val;

        return tmp;

    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector tmp(*this);

        for (int i = 0; i < tmp.sz; i++)
            tmp.pMem[i] -= val;
        return tmp;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector tmp(*this);

        for (int i = 0; i < tmp.sz; i++)
            tmp.pMem[i] *= val;
        return tmp;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (this->sz != v.sz)
            throw - 1;
        TDynamicVector tmp(this->sz);

        for (int i = 0; i < this->sz; i++)
        {
            tmp.pMem[i] = this->pMem[i] + v.pMem[i];
        }

        return tmp;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (this->sz != v.sz)
            throw - 1;
        TDynamicVector tmp(this->sz);

        for (int i = 0; i < this->sz; i++)
        {
            tmp.pMem[i] = this->pMem[i] - v.pMem[i];
        }

        return tmp;
    }
    T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
    {
        if (this->sz != v.sz)
            throw - 1;
        int tmp = 0;

        for (int i = 0; i < this->sz; i++)
        {
            tmp += this->pMem[i] * v.pMem[i];
        }

        return tmp;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];
    size_t size() const noexcept { return sz; }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (this->sz != m.sz)
            return false;
        for (int i = 0; i < this->sz; i++)
            if (this->pMem[i] != m.pMem[i])
                return false;

        return true;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix tmp(*this);

        for (int i = 0; i < this->sz; i++)
            tmp.pMem[i] *= val;

        return tmp;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (this->sz != v.sz)
            throw - 1;

        TDynamicVector<T> tmp(*this);

        for (int i = 0; i < this->sz; i++)
            tmp.pMem[i] = v * this->pMem[i];

        return tmp;

    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (this->sz != m.sz)
            throw - 1;

        TDynamicMatrix tmp(*this);

        for (int i = 0; i < this->sz; i++)
            tmp.pMem[i] = this->pMem[i] + m.pMem[i];

        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (this->sz != m.sz)
            throw std::exception("123");

        TDynamicMatrix tmp(*this);

        for (int i = 0; i < this->sz; i++)
            tmp.pMem[i] = this->pMem[i] - m.pMem[i];

        return tmp;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw (-1);
        TDynamicMatrix tmp(sz);
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                for (int k = 0; k < sz; k++)
                    tmp.pMem[i] += pMem[i][k] * m.pMem[k][j];
        return tmp;

    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' ';
        return ostr;
    }
};

#endif
