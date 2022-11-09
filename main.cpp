// 7_7_intArray_with_exception.cpp 
#include <iostream>
#include "IntArray.h"

int main()
{
    try
    {
        IntArray array(10);    // создание массива
        for (int i{ 0 }; i < 10; ++i)  // заполнение массива
            array[i] = i + 1;
        array.Show();

        IntArray arrCopy = array;  // создание массива копированием
        arrCopy.Show();

        array.resize(8);   // изменение размера массива
        array.Show();

        array.insertBefore(20, 5);  // вставка нового элемента в масив
        array.Show();

        array.remove(3);   // удаление элемента из массива
        array.Show();

        array.insertAtEnd(30);  // вставка элемента в конец массива
        array.insertAtBeginning(40);  // вставка элемента в начало м
        array.Show();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}