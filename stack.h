#ifndef STACK_H
#define STACK_H

#include <iostream.h>
#include <malloc.h>



typedef int stackdata; // ������� �����
                       // ������� ��� ���������� �� �����
                       // ������ �������� ���� ������ �����
                       // ��������, ��������, �������, ��������. 

// ������� ������������ ������
struct listitem
{
  stackdata data; // ������
  listitem* next; // ��������� �� ��������� ������� ������
};

// ����� ���������� ��� CStack
class EStack
{
  private:
    char* msg; // ��������� �� ������
  public:
    EStack(const char* errmsg) { msg = strdup(errmsg); }
    ~EStack() { free(msg); }
    const char* getmsg() { return msg; }
};

class CStack
{
  private:
    listitem* head; // ������ ������������ ������

  public:
    CStack();                              // �����������
    CStack(const CStack&);                 // ����������� �����������
    ~CStack() { clear(); }                 // ���������� 
    bool empty() const { return head==0; } // ���� ����?
      // ����� ��������� ��� ��������� ���������� inline
      // ����� ��� ����� ������ ����� ������ empty()
      // ���������� ������ ������ ��������� "�����" ������ ���
      // � ����� ������. ��� ����������� ������������������,
      // �.�. �� ����� ����� ������������ ��������� �������������� �����.
      // ������ �� ������� �������������� inline ������������ - �� �����
      // ������������ ������ ��� ��������� �������/�������.

    CStack& clear();                       // �������� ���� 
    CStack& push(const stackdata& data);   // �������� ������� � ����
    stackdata pop();                       // ������� ������� �� ����� 
    const stackdata& see() const;          // ���������� ������� � ������� �����
    CStack& operator = (const CStack&);    // �������� ������������
    friend ostream& operator << (ostream&, const CStack&);
      // �������� ������ ����� � �����
};

// ����������� �����
CStack::CStack()
{
  head = 0;
}

CStack::CStack(const CStack& stack)
{
  head = 0;
  *this = stack;
}

CStack& CStack::clear()
{
  while(head)
  {
    listitem* temp = head->next;
    delete head;
    head = temp;
  }
  return *this;
}

CStack& CStack::push(const stackdata& data)
  // ���� ����� ��������� ��������� ������� � ������� ����� �
  // � �������� ���������� ���������� ������ �� ��������� �����.
  // � �������� ����� ���� �� ������ �������� void. ��
  // ����� ��� �� ���������� ��������� �����:
  //   stack2 = stack1.push(10)
  // ��� �����:
  //   stack1.push(1).push(2).push(3)
  //
  // ����� �������� �������� �� ��, ��� �������� �������� data:
  //   const stackdata& data, �.�. �� ������
  // � ����� ������ (���� ����� �����) ��� ������, �.�. ��������
  // �������� �� ����� ���. �� ���� �� �������� ������� ���� �� ����� 
  // ������������ ��������, �� ������� ��� � ����� ������, �.�.
  // ����� ��� ������ ������ ����� ����������� ����� ������� (���������,
  // ������, � �.�.)
{
  listitem* item = new listitem;
  item->data = data;
  item->next = head;
  head = item;
    // ����� �� �������� ������ ��� ����� ������� ������������
    // ������, ����������� ������, � ������� ����� ������� ������
    // ��� ������� - �������� �����.
  
  return *this;
}

stackdata CStack::pop()
  // ��������� ������� �� ������� �����
  // ���� ���� ����, �� ���������� �������������� ��������
{
  if(empty()) throw (EStack("Stack is empty"));

  listitem* old = head;
  head = head->next;                 // �������� ������� �����
  stackdata data = old->data;
  delete old;                        // ������� ������ �������
  return data;
}

const stackdata& CStack::see() const
{
  if(empty()) throw (EStack("Stack is empty"));
  return head->data;  
}

CStack& CStack::operator = (const CStack& stack)
{
  if (this == &stack) return *this;
    // ���������� ������� ��������� ���� ������ ����
  clear();
  if(!stack.empty())
  {
    head = new listitem;
    listitem* cur = head;
    listitem* src = stack.head;
    while(src)
    {
      cur->data = src->data;
      if(src->next)
      {
        cur->next = new listitem;
        cur = cur->next;
      } else
        cur->next = 0;
      src = src->next;
    }
  }
  return *this;
}

ostream& operator << (ostream& s, const CStack& stack)
{
  listitem* item = stack.head;
  while(item)
  {
    s << item->data << endl;
    item = item->next;
  }
  return s;
}

#endif
