#include "IntArray.h"
#include <iostream>

IntArray::IntArray(int length) :
    length_{ length }
{
    if (length < 0)
    {
        throw BadLength();
    }
    if (length > 0)
        data_ = new int[length] {};
}

IntArray::IntArray(const IntArray& other) : 
    IntArray(other.length_)
{
    for (int i = 0; i < length_; ++i)
    {
        data_[i] = other.data_[i];
    }
}

IntArray:: ~IntArray()
{
    delete[] data_;
    // we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
}

void IntArray::erase()
{
    delete[] data_;
    // We need to make sure we set m_data to nullptr here, otherwise it will
    // be left pointing at deallocated memory!
    data_ = nullptr;
    length_ = 0;
}

int& IntArray::operator[](int index)
{
    if (index < 0 || index >= length_)
    {
        throw BadRange();
    }
    return data_[index];
}

void IntArray::reallocate(int newLength)
{
    // First we delete any existing elements
    erase();

    // If our array is going to be empty now, return here
    if (newLength <= 0)
        return;

    // Then we have to allocate new elements
    data_ = new int[newLength] {};
    length_ = newLength;
}

void IntArray::resize(int newLength)
{
    // if the array is already the right length, we're done
    if (newLength == length_)
        return;

    // If we are resizing to an empty array, do that and return
    if (newLength <= 0)
    {
        erase();
        return;
    }

    // Now we can assume newLength is at least 1 element.  This algorithm
    // works as follows: First we are going to allocate a new array.  Then we
    // are going to copy elements from the existing array to the new array.
    // Once that is done, we can destroy the old array, and make m_data
    // point to the new array.

    // First we have to allocate a new array
    int* data{ new int[newLength] };

    // Then we have to figure out how many elements to copy from the existing
    // array to the new array.  We want to copy as many elements as there are
    // in the smaller of the two arrays.
    if (length_ > 0)
    {
        int elementsToCopy{ (newLength > length_) ? length_ : newLength };

        // Now copy the elements one by one
        for (int index{ 0 }; index < elementsToCopy; ++index)
            data[index] = data_[index];
    }

    // Now we can delete the old array because we don't need it any more
    delete[] data_;

    // And use the new array instead!  Note that this simply makes m_data point
    // to the same address as the new array we dynamically allocated.  Because
    // data was dynamically allocated, it won't be destroyed when it goes out of scope.
    data_ = data;
    length_ = newLength;
}

void IntArray::insertBefore(int value, int index)
{
    // Sanity check our index value
    if (index < 0 || index > length_)
    {
        throw BadRange();
    }

    // First create a new array one element larger than the old array
    int* data{ new int[length_ + 1] };

    // Copy all of the elements up to the index
    for (int before{ 0 }; before < index; ++before)
        data[before] = data_[before];

    // Insert our new element into the new array
    data[index] = value;

    // Copy all of the values after the inserted element
    for (int after{ index }; after < length_; ++after)
        data[after + 1] = data_[after];

    // Finally, delete the old array, and use the new array instead
    delete[] data_;
    data_ = data;
    ++length_;
}

void IntArray::remove(int index)
{
    // Sanity check our index value
    if (index < 0 || index >= length_)
    {
        throw BadRange();
    }

    // If we're removing the last element in the array, we can just erase the array and return early
    if (length_ == 1)
    {
        erase();
        return;
    }

    // First create a new array one element smaller than the old array
    int* data{ new int[length_ - 1] };

    // Copy all of the elements up to the index
    for (int before{ 0 }; before < index; ++before)
        data[before] = data_[before];

    // Copy all of the values after the removed element
    for (int after{ index + 1 }; after < length_; ++after)
        data[after - 1] = data_[after];

    // Finally, delete the old array, and use the new array instead
    delete[] data_;
    data_ = data;
    --length_;
}

void IntArray::Show() const
{
    std::cout << "IntArray: " ;
    for (int i{ 0 }; i < getLength(); ++i)
        std::cout << data_[i] << ' ';
    std::cout << '\n';
}