#pragma once

#include <iostream>

// звено списка
template <class T>
struct Node
{
	Node<T>* pNext;
	T data;
	// конструктор с параметрами
	Node(T value = T(), Node<T>* pN = NULL) : data(value), pNext(pN) {}
};

template <class T>
class List
{
protected:
	size_t size; // размер списка
	Node<T>* head; // указатель на голову списка
public:
	// конструктор без параметров
	List()
	{
		size = 0;
		head = new Node<T>();
		head->pNext = head;
	}
	// конструктор с параметрами
	List(T val, Node<T>* p)
	{
		size = 1;
		head = new Node<T>();
		head->pNext = new Node<T>(val, p);
		head->pNext->pNext = head;
	}
	// конструктор копирования
	List(const List<T>& l)
	{
		head = new Node<T>(l.get_head()->data, NULL);
		head->pNext = head;
		size = 0;
		Iterator copier = begin();
		for (Iterator it = l.begin(); it != l.end(); it++)
		{
			insert(*copier, it->data);
				copier++;
		}
	}
	// деструктор
	~List()
	{
		while (!empty())
			pop_front();
		size = 0;
	}
	// получить количество элементов в списке
	size_t get_size() const
	{
		return size;
	}
	// получить указатель на голову списка
	Node<T>* get_head() const
	{
		return head;
	}
	// проверка списка на пустоту
	bool empty()
	{
		return head->pNext == head;
	}
	// положить элемент в конец списка
	void push_back(const T& Elem)
	{
		if (empty())
		{
			head->pNext = new Node<T>(Elem, head);
		}
		else
		{
			Node<T>* cur = head;
				while (cur->pNext != head)
					cur = cur->pNext;
			cur->pNext = new Node<T>(Elem, head);
		}
		size++;
	}
	// удалить элемент из конца списка
	void pop_back()
	{
		if (!empty())
		{
			Node<T>* last = head->pNext;
			while (last->pNext != head)
				last = last->pNext;
			last = head;
			size--;
		}
		else throw "List is empty!";
	}
	// положить элемент в начало списка
	void push_front(const T& Elem)
	{
		Node<T>* l = new Node<T>(Elem, head->pNext);
		head->pNext = l;
		size++;
	}
	// удалить первый элемент в списке
	void pop_front()
	{
		if (!empty())
		{
			Node<T>* del = head->pNext;
			head->pNext = head->pNext->pNext;
			delete del;
			size--;
		}
		else throw "List is empty!";
	}
	// положить элемент в произвольное место списка
	void insert(Node<T>* pos, const T& Elem)
	{
		if (pos == head)
			push_front(Elem);
		else
		{
			Node<T>* tmp = new Node<T>(Elem, pos->pNext);
			pos->pNext = tmp;
			size++;
		}
	}
	// удалить произвольный элемент в списке
	void erase(Node<T>* pos)
	{
		if (pos == head->pNext)
			pop_front();
		else
		{
			Node<T>* del = pos->pNext;
			pos->pNext = del->pNext;
			delete del;
			size--;
		}
	}
	// итератор
	class Iterator
	{
	private:
		Node<T>* current;
	public:
		// конструктор без параметров
		Iterator() { current = NULL; }
		// конструктор с параметром
		Iterator(Node<T>* node) { current = node; }
		// конструктор копирования
		Iterator(const Iterator& i) { current = i.current; }
		// разыменование 
		Node<T>*& operator*() { return current; }
		// обращение
		Node<T>* operator->() { return current; }
		// префиксный инкремент
		Iterator operator++() { current = current->pNext; return current; }
		// постфиксный инкремент
		Iterator operator++(int) { Iterator i(*this); ++(*this); return i; }
		// проверка на равенство
		bool operator==(Iterator i) { return current == i.current; }
		// проверка на неравенство
		bool operator!=(Iterator i) { return current != i.current; }
	};
	// начало итератора
	Iterator begin() const { Iterator i(head->pNext); return i; }
	// конец итератора
	Iterator end() const { Iterator i(head); return i; }
};