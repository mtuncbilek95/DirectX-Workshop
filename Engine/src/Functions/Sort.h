// Copyright Metehan Tuncbilek, All Rights Reserved.

/*****************************************************************************************************
 *
 *  This is a standart Dynamic Array Sorting Library which is created to use with the current array library.
 *  
 *****************************************************************************************************/

#pragma once

namespace Engine
{
    class Sort
    {
    public:
        template <typename tArray>
        static void BubbleSort(tArray& arrayValue);
        template <typename tArray, typename tValue>
        static void QuickSort(tArray& arrayValue, tValue min, tValue max);
        template <typename tArray>
        static void SelectionSort(tArray& arrayValue);
        template <typename tArray>
        static void InsertionSort(tArray& arrayValue);
        template <typename tArray>
        static void MergeSort(tArray& arrayValue);

    private:
        template <typename tValue>
        static void Swap(tValue& v1, tValue& v2);
    };

    template <typename tArray>
    void Sort::BubbleSort(tArray& arrayValue)
    {
        for(unsigned i = 0; i < arrayValue.Size() - 1; i++)
        {
            for(unsigned j = 0; j < arrayValue.Size() - i - 1; j++)
            {
                if(arrayValue[j] > arrayValue[j+1])
                    Sort::Swap(arrayValue[j], arrayValue[j+1]);
            }
        }
    }

    template <typename tArray>
    void Sort::Swap(tArray& v1, tArray& v2)
    {
        tArray temp = v1;
        v1 = v2;
        v2 = temp;
    }
}
