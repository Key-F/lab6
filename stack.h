#ifndef STACK_H
#define STACK_H

#include <iostream.h>
#include <malloc.h>



typedef int stackdata; // элемент стека
                       // изменяя это объявление вы легко
                       // можете получить стек других типов
                       // например, структур, классов, символов. 

// элемент односвязного списка
struct listitem
{
  stackdata data; // данные
  listitem* next; // указатель на следующий элемент списка
};

// Класс исключений для CStack
class EStack
{
  private:
    char* msg; // сообщение об ошибке
  public:
    EStack(const char* errmsg) { msg = strdup(errmsg); }
    ~EStack() { free(msg); }
    const char* getmsg() { return msg; }
};

class CStack
{
  private:
    listitem* head; // голова односвязного списка

  public:
    CStack();                              // конструктор
    CStack(const CStack&);                 // конструктор копирования
    ~CStack() { clear(); }                 // деструктор 
    bool empty() const { return head==0; } // стек пуст?
      // здесь применена так называеся технология inline
      // везде где будет стоять вызов метода empty()
      // компилятор вместо вызова процедуры "вшьет" данный код
      // в место вызова. Это увеличивает производительность,
      // т.к. на вызов любой подпрограммы требуется дополнительное время.
      // Однако не следует злоупотреблять inline подстановкой - ее нужно
      // использовать только для маленьких функций/методов.

    CStack& clear();                       // очистить стек 
    CStack& push(const stackdata& data);   // добавить элемент в стек
    stackdata pop();                       // извлечь элемент из стека 
    const stackdata& see() const;          // посмотреть элемент в вершине стека
    CStack& operator = (const CStack&);    // оператор присваивания
    friend ostream& operator << (ostream&, const CStack&);
      // Оператор вывода стека в поток
};

// конструктор стека
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
  // Этот метод добавляет указанный элемент в вершину стека и
  // в качестве результата возвращает ссылку на экземпляр стека.
  // В принципе можно было бы просто обойтись void. Но
  // тогда был бы невозможен следующий вызов:
  //   stack2 = stack1.push(10)
  // или такой:
  //   stack1.push(1).push(2).push(3)
  //
  // Также обратите внимание на то, как объявлен параметр data:
  //   const stackdata& data, т.е. по ссылке
  // В нашем случае (стек целых чисел) это лишнее, т.к. никакого
  // выйгрыша от этого нет. Но если вы захотите сделать стек из более 
  // рерурсоемких структур, то имеенно так и нужно делать, т.к.
  // иначе при вызове метода будет создаваться копия объекта (структуры,
  // класса, и т.п.)
{
  listitem* item = new listitem;
  item->data = data;
  item->next = head;
  head = item;
    // Здесь мы выделили память под новый элемент односвязного
    // списка, скопировали данные, и сделали новый элемент списка
    // его головой - вершиной стека.
  
  return *this;
}

stackdata CStack::pop()
  // Извлекает элемент из вершины стека
  // Если стек пуст, то генерирует исключительную ситуацию
{
  if(empty()) throw (EStack("Stack is empty"));

  listitem* old = head;
  head = head->next;                 // сдвигаем вершину стека
  stackdata data = old->data;
  delete old;                        // удаляем старую вершину
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
    // Игнорируем попытку присвоить стек самому себе
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
