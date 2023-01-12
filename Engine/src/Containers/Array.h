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

        void Init(unsigned int initSize);
        T* GetSource() { return ArrayPtr; }
        
        unsigned int Length() const;
        unsigned int Size() const;
        
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
        
        unsigned int maximumLength = 5;
        unsigned int currentLength;
        T* ArrayPtr;

        void ChangeSize();
        void ClearMemory();
        unsigned MaxLength() const;
    };

    template <typename T>
    Array<T>::Array()
    {
        currentLength = 0;
        ArrayPtr = new T[this->maximumLength];
    }

    template <typename T>
    void Array<T>::Init(unsigned initSize)
    {
        maximumLength = initSize;
        ArrayPtr = new T*[this->maximumLength];
    }

    template <typename T>
    unsigned Array<T>::Length() const
    {
        return currentLength;
    }

    template <typename T>
    unsigned Array<T>::Size() const
    {
        return sizeof(T) * currentLength;
    }

    template <typename T>
    unsigned Array<T>::MaxLength() const
    {
        return maximumLength;
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
        if (currentLength == maximumLength)
        {
            ChangeSize();
        }
        ArrayPtr[currentLength] = element;
        currentLength++;
    }

    template <typename T>
    void Array<T>::InsertFirst(const T& element)
    {
        InsertByIndex(element, 0);
    }

    template <typename T>
    void Array<T>::InsertByIndex(const T& element, unsigned index)
    {
        if (currentLength == maximumLength)
        {
            maximumLength *= 2;
        }

        T* Temp = new T[maximumLength];

        for (unsigned i = 0; i < currentLength; i++)
        {
            Temp[i] = ArrayPtr[i];
        }

        ClearMemory();
        ArrayPtr = new T[maximumLength];

        for (unsigned i = 0; i < index; i++)
        {
            ArrayPtr[i] = Temp[i];
        }

        ArrayPtr[index] = element;

        for (unsigned i = index; i < currentLength; i++)
        {
            ArrayPtr[i + 1] = Temp[i];
        }
        delete[] Temp;
        currentLength ++;
    }

    template <typename T>
    void Array<T>::RemoveFirst()
    {
        for (unsigned i = 0; i < currentLength - 1; i++)
        {
            ArrayPtr[i] = ArrayPtr[i + 1];
        }
        currentLength--;
    }

    template <typename T>
    void Array<T>::Remove(const unsigned order)
    {
        if (order >= currentLength)
        {
            throw "Out of Range";
        }

        for (unsigned i = order; i < currentLength; i++)
        {
            ArrayPtr[i - 1] = ArrayPtr[i];
        }
        currentLength--;
    }

    template <typename T>
    void Array<T>::RemoveAll()
    {
        ClearMemory();
        maximumLength = 5;
        currentLength = 0;
    }

    template <typename T>
    void Array<T>::Swap(const unsigned& swapItemIndex1, const unsigned& swapItemIndex2)
    {
        if (swapItemIndex1 >= currentLength || swapItemIndex1 <= currentLength)
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
        if (currentLength == maximumLength)
        {
            TempData = new T[maximumLength];
            {
                for (unsigned i = 0; i < currentLength; i++)
                {
                    TempData[i] = ArrayPtr[i];
                }
            }

            ClearMemory();

            maximumLength = maximumLength * 2;
            ArrayPtr = new T[maximumLength];

            for (unsigned i = 0; i < currentLength; i++)
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
