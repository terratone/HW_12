#include <iostream>

using namespace std;

template <typename T>
class UniquePtr {
private:
    T* ptr; // ��������� �� ������

public:
    explicit UniquePtr(T* p = nullptr) : ptr(p) {} // ����������� ������

    ~UniquePtr() { // ����������
        delete ptr;
    }

    UniquePtr(const UniquePtr&) = delete; // ������������� ����������� �������

    UniquePtr& operator=(const UniquePtr&) = delete; // ������������� ������������ �������

    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) { // ����������� �����������
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept { // �������� �����������
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T* operator->() const { // �������� ������� � ����� ����� ���������
        return ptr;
    }

    T& operator*() const { // �������� ������������� ���������
        return *ptr;
    }
};


template <typename T>
class SharedPtr {
private:
    T* ptr; // ��������� �� ������
    size_t* ref_count; // ��������� �� ������� ������

public:
    explicit SharedPtr(T* p = nullptr) : ptr(p), ref_count(new size_t(1)) {} // ����������� ������

    ~SharedPtr() { // ����������
        if (--(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

    SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count) { // ����������� �����������
        (*ref_count)++;
    }

    SharedPtr& operator=(const SharedPtr& other) { // �������� ������������
        if (this != &other) {
            if (--(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;
            (*ref_count)++;
        }
        return *this;
    }

    T* operator->() const { // �������� ������� � ����� ����� ���������
        return ptr;
    }

    T& operator*() const { // �������� ������������� ���������
        return *ptr;
    }
};


int main() {
    
    UniquePtr<int> up(new int(42)); // �������� UniquePtr ��� ������ �����
    cout << *up << endl; // ����� ��������, �� ������� ��������� ����� ���������

    SharedPtr<int> sp1(new int(10)); // �������� SharedPtr ��� ������ �����
    SharedPtr<int> sp2 = sp1; // ����������� SharedPtr
    cout << *sp1 << " " << *sp2 << endl; // ����� ��������, �� ������� ��������� ����� ���������

    return 0;
}