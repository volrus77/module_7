#pragma once

#include <exception>

class IntArray
{
public:
    // конструкторы и деструктор
    IntArray() = default;
    IntArray(int length);
    IntArray(const IntArray& other);  // конструктор копирования
    ~IntArray();
   
    // функции
    int getLength() const { return length_; }  // геттер длины массива

    void erase(); // стирание всех данных
    
    int& operator[](int index); // обращение к элементу по индексу т.е. как геттер, так и сеттер

    void reallocate(int newLength); // стирание всех данных, создание нового пустого массива длиной newLength

    void resize(int newLength); // изменить размер массива с сохранением элементов с индексом меньше newLength

    void insertBefore(int value, int index); // вставить элемент по индексу

    void remove(int index); // удалить один елемент по индексу

    void insertAtBeginning(int value) { insertBefore(value, 0); } // вставить элемент первым в массиве
    void insertAtEnd(int value) { insertBefore(value, length_); } // вставить элемент последним в массиве
    void Show() const;
private:
    int length_{};
    int* data_{};
};


class BadRange : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "ERROR: bad_range!";
    }
};

class BadLength : public std::exception
{
    virtual const char* what() const noexcept override
    {
        return "ERROR: bad_length!";
    }
};

