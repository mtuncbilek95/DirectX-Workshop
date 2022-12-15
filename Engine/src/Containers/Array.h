// Copyright Metehan Tuncbilek, All Rights Reserved.

/*****************************************************************************************************
 *
 *  This is a standart Dynamic Array library which is created to use instead of std library.
 *
 *  Current capabilities:
 *  -   All written functions are working properly.
 *  -   [] operator is also working correctly.
 *
 *****************************************************************************************************/

#pragma once

namespace Engine
{
    template <typename T>
    class Array
    {
    public:
        Array();
        ~Array() = default;

        void Init(unsigned initSize);
        unsigned Size() const;

        T& At(unsigned int index);
        T& operator[](const unsigned index);

        void Add(const T& element);
        void InsertFirst(const T& element);
        void InsertByIndex(const T& element, unsigned index);
        void RemoveFirst();
        void Remove(const unsigned index);
        void RemoveAll();

        void Swap(const unsigned& swapItemIndex1, const unsigned& swapItemIndex2);
    private:
        
        unsigned int maximumSize = 5;
        unsigned int currentSize;
        T* ArrayPtr;

        void ChangeSize();
        void ClearMemory();
        unsigned MaxSize() const;
    };

    template <typename T>
    Array<T>::Array()
    {
        currentSize = 0;
        ArrayPtr = new T[this->maximumSize];
    }

    template <typename T>
    void Array<T>::Init(unsigned initSize)
    {
        maximumSize = initSize;
        ArrayPtr = new T*[this->maximumSize];
    }

    template <typename T>
    unsigned Array<T>::Size() const
    {
        return currentSize;
    }

    template <typename T>
    unsigned Array<T>::MaxSize() const
    {
        return maximumSize;
    }

    template <typename T>
    T& Array<T>::At(unsigned index)
    {
        return ArrayPtr[index];
    }

    template <typename T>
    T& Array<T>::operator[](const unsigned index)
    {
        return ArrayPtr[index];
    }

    template <typename T>
    void Array<T>::Add(const T& element)
    {
        if (currentSize == maximumSize)
        {
            ChangeSize();
        }
        ArrayPtr[currentSize] = element;
        currentSize++;
    }

    template <typename T>
    void Array<T>::InsertFirst(const T& element)
    {
        InsertByIndex(element, 0);
    }

    template <typename T>
    void Array<T>::InsertByIndex(const T& element, unsigned index)
    {
        if (currentSize == maximumSize)
        {
            maximumSize *= 2;
        }

        T* Temp = new T[maximumSize];

        for (unsigned i = 0; i < currentSize; i++)
        {
            Temp[i] = ArrayPtr[i];
        }

        ClearMemory();
        ArrayPtr = new T[maximumSize];

        for (unsigned i = 0; i < index; i++)
        {
            ArrayPtr[i] = Temp[i];
        }

        ArrayPtr[index] = element;

        for (unsigned i = index; i < currentSize; i++)
        {
            ArrayPtr[i + 1] = Temp[i];
        }
        delete[] Temp;
        currentSize ++;
    }

    template <typename T>
    void Array<T>::RemoveFirst()
    {
        for (unsigned i = 0; i < currentSize - 1; i++)
        {
            ArrayPtr[i] = ArrayPtr[i + 1];
        }
        currentSize--;
    }

    template <typename T>
    void Array<T>::Remove(const unsigned order)
    {
        if (order >= currentSize)
        {
            throw "Out of Range";
        }

        for (unsigned i = order; i < currentSize; i++)
        {
            ArrayPtr[i - 1] = ArrayPtr[i];
        }
        currentSize--;
    }

    template <typename T>
    void Array<T>::RemoveAll()
    {
        ClearMemory();
        maximumSize = 5;
        currentSize = 0;
    }

    template <typename T>
    void Array<T>::Swap(const unsigned& swapItemIndex1, const unsigned& swapItemIndex2)
    {
        if (swapItemIndex1 >= currentSize || swapItemIndex1 <= currentSize)
        {
            throw "Out of Range";
        }
        T TempData = ArrayPtr[swapItemIndex1];

        ArrayPtr[swapItemIndex1] = ArrayPtr[swapItemIndex2];
        ArrayPtr[swapItemIndex2] = TempData;
    }

    template <typename T>
    void Array<T>::ChangeSize()
    {
        T* TempData = nullptr;
        if (currentSize == maximumSize)
        {
            TempData = new T[maximumSize];
            {
                for (unsigned i = 0; i < currentSize; i++)
                {
                    TempData[i] = ArrayPtr[i];
                }
            }

            ClearMemory();

            maximumSize = maximumSize * 2;
            ArrayPtr = new T[maximumSize];

            for (unsigned i = 0; i < currentSize; i++)
            {
                ArrayPtr[i] = TempData[i];
            }
            delete[] TempData;
        }
    }

    template <typename T>
    void Array<T>::ClearMemory()
    {
        if (ArrayPtr == nullptr)
            return;

        delete[] ArrayPtr;
    }
}
