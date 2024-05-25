#include <iostream>

using namespace std;

template <typename T>
class UniquePtr {
private:
    T* ptr; // Указатель на объект

public:
    explicit UniquePtr(T* p = nullptr) : ptr(p) {} // Конструктор класса

    ~UniquePtr() { // Деструктор
        delete ptr;
    }

    UniquePtr(const UniquePtr&) = delete; // Предотвращаем копирование объекта

    UniquePtr& operator=(const UniquePtr&) = delete; // Предотвращаем присваивание объекта

    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) { // Конструктор перемещения
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept { // Оператор перемещения
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T* operator->() const { // Оператор доступа к члену через указатель
        return ptr;
    }

    T& operator*() const { // Оператор разыменования указателя
        return *ptr;
    }
};


template <typename T>
class SharedPtr {
private:
    T* ptr; // Указатель на объект
    size_t* ref_count; // Указатель на счётчик ссылок

public:
    explicit SharedPtr(T* p = nullptr) : ptr(p), ref_count(new size_t(1)) {} // Конструктор класса

    ~SharedPtr() { // Деструктор
        if (--(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

    SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count) { // Конструктор копирования
        (*ref_count)++;
    }

    SharedPtr& operator=(const SharedPtr& other) { // Оператор присваивания
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

    T* operator->() const { // Оператор доступа к члену через указатель
        return ptr;
    }

    T& operator*() const { // Оператор разыменования указателя
        return *ptr;
    }
};


int main() {
    
    UniquePtr<int> up(new int(42)); // Создание UniquePtr для целого числа
    cout << *up << endl; // Вывод значения, на которое указывает умный указатель

    SharedPtr<int> sp1(new int(10)); // Создание SharedPtr для целого числа
    SharedPtr<int> sp2 = sp1; // Копирование SharedPtr
    cout << *sp1 << " " << *sp2 << endl; // Вывод значений, на которые указывают умные указатели

    return 0;
}