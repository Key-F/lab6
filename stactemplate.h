#ifndef STACKTAMPLATE_H
#define STACKTAMPLATE_H



#include <iostream.h>
#include <malloc.h>

// ����� ���������� ��� �����
class EStack
{
  private:
    char* msg;  // ��������� �� ������
  public:
    EStack(const char* errmsg) { msg = strdup(errmsg); }
    ~EStack() { free(msg); }
    const char* getmsg() { return msg; }
};

// ��������� �� �������
#define ESTACK_EMPTY "Stack is empty"

// ������ �������� ������������ ������
template <class T>
struct l1item
{
  T data;
  l1item<T>* next;
};

// ������ ����� �� ������ ������������ ������
template <class T>
class stack
{
  private:
    l1item<T>* head; // ������ ������������ ������

  public:
    stack() { head = NULL; }                   // �����������
    stack(const stack<T>&);                    // ����������� �����������
    ~stack() { clear(); }                      // ���������� 
    bool empty() const { return head==NULL; }  // ���� ����?
    stack<T>& clear();                         // �������� ���� 
    stack<T>& del();                           // ������� ������� �� �����
    stack<T>& push(const T& data);             // �������� ������� � ����
    T pop();                                   // ������� ������� �� ����� 
    const T& see() const;                      // ���������� ������� � ������� �����
    stack<T>& operator = (const stack<T>&);    // �������� ������������
};

// ����������� �����������
template <class T>
stack<T>::stack(const stack<T>& Stack)
{
  head = NULL;
  *this = Stack;
}

// ������� ����� (�������� ���� ���������)
template <class T>
stack<T>& stack<T>::clear()
{
  while(!empty()) del();
  return *this;
}

// �������� �������� �� ������� �����
template <class T>
stack<T>& stack<T>::del()
{
  if(empty()) throw(EStack(ESTACK_EMPTY));

  l1item<T>* tmp = head->next;
  delete head;
  head = tmp;
  return *this;
}

// ���������� �������� � ����
template <class T>
stack<T>& stack<T>::push(const T& data)
{
  l1item<T>* item = new l1item<T>;
  item->data = data;
  item->next = head;
  head = item;
  return *this;
}

// ���������� �������� �� �����
template <class T>
T stack<T>::pop()
{
  if(empty()) throw (EStack(ESTACK_EMPTY));

  l1item<T>* old = head;
  head = head->next;
  T data = old->data;
  delete old;
  return data;
}

// �������� �������� � ������� �����
template <class T>
const T& stack<T>::see() const
{
  if(empty()) throw (EStack(ESTACK_EMPTY));
  return head->data;  
}

// �������� ������������
template <class T>
stack<T>& stack<T>::operator = (const stack<T>& Stack)
{
  if (this == &Stack) return *this;
  clear();
  if(!Stack.empty())
  {
    head = new l1item<T>;
    l1item<T>* cur = head;
    l1item<T>* src = Stack.head;
    while(src)
    {
      cur->data = src->data;
      if(src->next)
      {
        cur->next = new l1item<T>;
        cur = cur->next;
      } else
        cur->next = NULL;
      src = src->next;
    }
  }
  return *this;
}

#endif