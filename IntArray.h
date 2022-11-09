#pragma once

#include <exception>

class IntArray
{
public:
    // ������������ � ����������
    IntArray() = default;
    IntArray(int length);
    IntArray(const IntArray& other);  // ����������� �����������
    ~IntArray();
   
    // �������
    int getLength() const { return length_; }  // ������ ����� �������

    void erase(); // �������� ���� ������
    
    int& operator[](int index); // ��������� � �������� �� ������� �.�. ��� ������, ��� � ������

    void reallocate(int newLength); // �������� ���� ������, �������� ������ ������� ������� ������ newLength

    void resize(int newLength); // �������� ������ ������� � ����������� ��������� � �������� ������ newLength

    void insertBefore(int value, int index); // �������� ������� �� �������

    void remove(int index); // ������� ���� ������� �� �������

    void insertAtBeginning(int value) { insertBefore(value, 0); } // �������� ������� ������ � �������
    void insertAtEnd(int value) { insertBefore(value, length_); } // �������� ������� ��������� � �������
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

