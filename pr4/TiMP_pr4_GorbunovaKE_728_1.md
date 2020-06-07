#Практическая работа №4

##1 Цель
Изучить материал, посвящённый двусвязным спискам, реализовать функции для работы с двусвязным списком в рамках языка C, используя функции реализовать программу, настроить Pipeline.

##1.1 Функции 
```c
// инициализация пустого списка
void init(list *l);

// удалить все элементы из списка
void clean(list *l);

// проверка на пустоту списка
bool is_empty(list *l);

// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value);

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value);

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value);

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, node *n, int value);

// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list *l, node *n, int value);

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_first(list *l, int value);

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_last(list *l, int value);

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l);

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l);
``` 

##1.2 Программа
Используя функции реализовать программу, которая:
1. считывает количество элементов n, 0 < n <= 2147483647;
2. создает пустой список, считывает n элементов a, |a| <= 2147483647 и заносит их в список;
3. выводит содержимое списка, используя функцию print;
4. считывает k1, k2, k3 (|k| <= 2147483647) и выводит "1", если в списке существует элемент с таким значением и "0" если нет (выводить через пробел, например "1 0 1");
5. считывает m, |m| <= 2147483647 и вставляет его в конец списка;
6. выводит содержимое списка, используя функцию print_invers;
7. считывает t, |t| <= 2147483647 и вставляет его в начало списка;
8. выводит содержимое списка, используя функцию print;
9. считывает j и x (0 < j <= 2147483647, |x| <= 2147483647) и вставляет значение x после j-ого элемента списка;
10. выводит содержимое списка, используя функцию print_invers;
11. считывает u и y (0 < u <= 2147483647, |y| <= 2147483647) и вставляет значение y перед u-ым элементом списка;
12. выводит содержимое списка, используя функцию print;
13. считывает z, |z| <= 2147483647 и удаляет первый элемент (при его наличии), хранящий значение z из списка;
14. выводит содержимое списка, используя функцию print_invers;
15. считывает r, |r| <= 2147483647 и удаляет последний элемент (при его наличии), хранящий значение r из списка;
16. выводит содержимое списка, используя функцию print;
17. очищает список.

##2 Ход работы
Двусвязный список - динамическая структура данных, состоящая из узлов, каждый из которых содержит как собственно данные, так и ссылки на следующий и предыдущий узлы списка.
```c
typedef struct list {
  struct node *head;  // начало списка
  struct node *tail;  // конец списка
} list;
```
Ниже представлена структура, описывающая узел в двусвязном списке:
```c
typedef struct node {
      int value;          // значение, которое хранит узел 
      struct node *next;  // ссылка на следующий элемент списка
      struct node *prev;  // ссылка на предыдущий элемент списка
} node;
```

## 2.1 Описание функций
Функция init инициализирует пустой список.
```c
void init(list *l) {
    l->head = NULL;
    l->tail = NULL;
}
```
Функция clean будет отчищать текущую ноду, пока следующая существует.
```c
void clean(list *l) {
    node *c_node = l->head;
    node *n_node = c_node->next;
    while(n_node != NULL) {
        free(c_node);
        c_node = n_node;
        n_node = c_node->next;
    }
    l->head = NULL;
    l->tail = NULL;
}
```
Функция is_empty проверяет если начало и конец списка NULL, значит список пуст.
```c
bool is_empty(list *l) {
    if(l->head == NULL && l->tail == NULL) {
        return true;
    }
    return false;
}
```
Функция find будет в цикле проверять значение каждой ноды, пока не найдёт нужное.
```c
node *find(list *l, int value) {
    node *c_node = l->head;
    while(c_node != NULL) {
        if(c_node->value == value) {
            return c_node;
        }
        c_node = c_node->next;
    }
    return NULL;
}
```
Функция push_back работает следующим образом: сначала выделяется память размером sizeof(node), этому участку присваивается значение, которое нужно вставить, указание на то, что последующий элемент NULL, а предыдущий конец списка. И если начало списка NULL, то значение вставляется, иначе значение вставляется в конец списка.
```c
int push_back(list *l, int value) {
    node *push;
    push = malloc(sizeof(node));
    push->value = value;
    push->next = NULL;
    push->prev = l->tail; 
    if(l->head == NULL) {
        l->head = push;
        l->tail = push;
    } else {
        l->tail->next = push;
        l->tail = push;
    }
    return 0;
}
```
Функция push_front работает следующим образом: сначала выделяется память размером sizeof(node), этому участку присваивается значение, которое нужно вставить, указание на то, что последующий элемент начало списка, а предыдущий NULL. И если начало списка NULL, то значение вставляется, иначе значение вставляется перед первой нодой.
```c
int push_front(list *l, int value) {
    node *push;
    push = malloc(sizeof(node));
    push->value = value;
    push->next = l->head;
    push->prev = NULL;
    if(l->head == NULL) {
        l->head = push;
        l->tail = push;
    } else {
        l->head->prev = push;
        l->head = push;
    }
    return 0;
}
```
Функция insert_after вставляет значение после указнного узла, который ищется в теле программы. 
```c
int insert_after(list *l, node *n, int value) {
    node *insert;
    insert = malloc(sizeof(node));
    insert->value = value;
    insert->next = n->next;
    insert->prev = n;
    n->next->prev = insert;
    n->next = insert;
    if(insert->next == NULL) {
        l->head = insert;
    }
    return 0;
}
```
Функция insert_before вставляет значение перед указанным узлом, который ищется в теле программы. 
```c
int insert_before(list *l, node *n, int value) {
    node *insert;
    insert = malloc(sizeof(node));
    insert->value = value;
    insert->next = n;
    insert->prev = n->prev;
    n->prev->next = insert;
    n->prev = insert;
    if(insert->prev == NULL) {
        l->head = insert;
    }
    return 0;
}
```
Функция remove_firsrt проверяет варианты расположения элемента (в начале, конце и середине), при выолнении условий - удаляет.
```c
int remove_first(list *l, int value) {
    if(l->head == NULL) {
    return -1;
    }
    node *c_node = l->head;
    while (c_node->next) {
      if (c_node->value == value) {
        if (c_node->prev == NULL) {
          l->head = c_node->next;
          c_node -> next -> prev = NULL;
          free(c_node);
          return 0;
        }
        if (c_node->next == NULL) {
          l->tail = c_node->prev;
          c_node->prev->next = NULL;
          free(c_node);
          return 0;
        }   
        c_node->prev->next = c_node->next;
        c_node->next->prev = c_node->prev;
        free(c_node);
        return 0;
        }
      c_node = c_node->next;
    }
    return -1;
}
```
Функция remove_last делает всё тожесамое, что и remove_first, только с конца списка.
```c
int remove_last(list *l, int value) {
    if(l->tail == NULL) {
      return -1;
    }
    node *c_node = l->tail;
    while (c_node->prev) {
      if (c_node->value == value) {
        if (c_node->next == NULL) {
          l->tail = c_node->prev;
          c_node->prev->next = NULL;
          free(c_node);
          return 0;
        }
        if (c_node->prev == NULL) {
          l->head = c_node->next;
          c_node -> next -> prev = NULL;
          free(c_node);
          return 0;
        }
        c_node->prev->next = c_node->next;
        c_node->next->prev = c_node->prev;
        free(c_node);
        return 0;
      }
    c_node = c_node->prev;
    }
    return -1;
}
```
Функция print выводит все значени из списка в прямом порядке через пробел.
```c
void print(list *l) {
    node *c_node = l->head;
    while (c_node != NULL) {
      printf ("%d ", c_node -> value);
      c_node = c_node->next;
    }
    printf (" ");
}
```
Функция print_invers выводит все значени из списка в обратном порядке через пробел.
```c
void print_invers(list *l) {
    node *c_node = l->tail;
    do {
      printf ("%d ", c_node -> value);
      c_node = c_node->prev;
    } while (c_node != NULL);
    printf (" ");
}
```
На рисунке 2.1.1 представлен результат работы прогпрогарммы.
![Рисунок](img/1.png "Рисунок 2.1.1 - Пример работы программы")

Рисунок 2.1.1 - Пример работы программы

## Вывод
В ходе лабораторной работы был изучен материал, посвящённый двусвязным спискам, реализованы функции для работы с двусвязным списком в рамках языка C, используя функции реализована программу, настроен Pipeline.

## Приложение
Полный код программы, реализованный на языке C:
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node {
    int value;          // значение, которое хранит узел 
    struct node *next;  // ссылка на следующий элемент списка
    struct node *prev;  // ссылка на предыдущий элемент списка
} node;

typedef struct list {
    struct node *head;  // начало списка
    struct node *tail;  // конец списка
} list;

// инициализация пустого списка
void init(list *l);

// удалить все элементы из списка
void clean(list *l);

// проверка на пустоту списка
bool is_empty(list *l);

// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value);

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value);

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value);

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, node *n, int value);

// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list *l, node *n, int value);

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_first(list *l, int value);

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_last(list *l, int value);

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l);

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l);

// Проверка наличия элемента
void find_id(list *l, int value);

int main() {
    int n, x, elem;
    int i = 1;
    list l = {0};
    int check = scanf("%d", &n);
    assert(check == 1);
    while (i <= n) {
      check = scanf("%d", &x);
      assert(check == 1);
      push_back(&l, x);
      i++;
    }
    print(&l);
    printf("\n");
    i = 1;     //Нахождение элементов в списке
    while (i <= 3) {
      check = scanf("%d", &x);
      assert(check == 1);
      find_id(&l, x);
      i++;
    }
    printf("\n");
    check = scanf("%d", &x);     //Добавление в конец
    assert(check == 1);
    push_back(&l, x);
    print_invers(&l);
    printf("\n");
    check = scanf("%d", &x);     //Добавлние в начало
    assert(check == 1);
    push_front(&l, x);
    print(&l);
    printf("\n");
    check = scanf("%d", &x);     //Добавление после указанного элемента
    assert(check == 1);
    check = scanf("%d", &elem);
    assert(check == 1);
    node *c_node = l.head;     //Поиск номера элемента
    int numb = 1;
    while ((c_node != NULL)&&(numb!= x)) {
      c_node = c_node->next;
      numb++;
    }
    node *insert_head = c_node;
    insert_after(&l, insert_head, elem);
    print_invers(&l);
    printf("\n");
    check = scanf("%d", &x);     //Добавление перед указанным элементом
    assert(check == 1);
    check = scanf("%d", &elem);
    assert(check == 1);
    node *c_node1 = l.head;
    int numb1 = 1;
    while ((c_node1 != NULL)&&(numb1!= x)) {
      c_node1 = c_node1->next;
      numb1++;
    }
    node *insert_tail = c_node1;
    insert_before(&l, insert_tail, elem);
    print(&l);
    printf("\n");
    check = scanf("%d", &x);     //Удалить первый элемент равный введенному
    assert(check == 1);
    remove_first(&l, x);
    print_invers(&l);
    printf("\n");
    check = scanf("%d", &x);     //Удалить последний элемент равный введенному
    assert(check == 1);
    remove_last(&l, x);
    print(&l);
    printf("\n");
    clean(&l);     //Очистить список
    return 0;
}


// инициализация пустого списка
void init(list *l) {
    l->head = NULL;
    l->tail = NULL;
}


// удалить все элементы из списка
void clean(list *l) {
    node *c_node = l->head;
    node *n_node = c_node->next;
    while(n_node != NULL) {
        free(c_node);
        c_node = n_node;
        n_node = c_node->next;
    }
    l->head = NULL;
    l->tail = NULL;
}


// проверка на пустоту списка
bool is_empty(list *l) {
    if(l->head == NULL && l->tail == NULL) {
        return true;
    }
    return false;
}


// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value) {
    node *c_node = l->head;
    while(c_node != NULL) {
        if(c_node->value == value) {
            return c_node;
        }
        c_node = c_node->next;
    }
    return NULL;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value) {
    node *push;
    push = malloc(sizeof(node));
    push->value = value;
    push->next = NULL;
    push->prev = l->tail; 
    if(l->head == NULL) {
        l->head = push;
        l->tail = push;
    } else {
        l->tail->next = push;
        l->tail = push;
    }
    return 0;
}


// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value) {
    node *push;
    push = malloc(sizeof(node));
    push->value = value;
    push->next = l->head;
    push->prev = NULL;
    if(l->head == NULL) {
        l->head = push;
        l->tail = push;
    } else {
        l->head->prev = push;
        l->head = push;
    }
    return 0;
}


// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, node *n, int value) {
    node *insert;
    insert = malloc(sizeof(node));
    insert->value = value;
    insert->next = n->next;
    insert->prev = n;
    n->next->prev = insert;
    n->next = insert;
    if(insert->next == NULL) {
        l->head = insert;
    }
    return 0;
}


// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list *l, node *n, int value) {
    node *insert;
    insert = malloc(sizeof(node));
    insert->value = value;
    insert->next = n;
    insert->prev = n->prev;
    n->prev->next = insert;
    n->prev = insert;
    if(insert->prev == NULL) {
        l->head = insert;
    }
    return 0;
}


// удалить первый элемент из списка с указанным значением,
// вернуть 0 если успешно
int remove_first(list *l, int value) {
    if(l->head == NULL) {
    return -1;
    }
    node *c_node = l->head;
    while (c_node->next) {
      if (c_node->value == value) {
        if (c_node->prev == NULL) {
          l->head = c_node->next;
          c_node -> next -> prev = NULL;
          free(c_node);
          return 0;
        }
        if (c_node->next == NULL) {
          l->tail = c_node->prev;
          c_node->prev->next = NULL;
          free(c_node);
          return 0;
        }   
        c_node->prev->next = c_node->next;
        c_node->next->prev = c_node->prev;
        free(c_node);
        return 0;
        }
      c_node = c_node->next;
    }
    return -1;
}

// удалить последний элемент из списка с указанным значением,
// вернуть 0 если успешно
int remove_last(list *l, int value) {
    if(l->tail == NULL) {
      return -1;
    }
    node *c_node = l->tail;
    while (c_node->prev) {
      if (c_node->value == value) {
        if (c_node->next == NULL) {
          l->tail = c_node->prev;
          c_node->prev->next = NULL;
          free(c_node);
          return 0;
        }
        if (c_node->prev == NULL) {
          l->head = c_node->next;
          c_node -> next -> prev = NULL;
          free(c_node);
          return 0;
        }
        c_node->prev->next = c_node->next;
        c_node->next->prev = c_node->prev;
        free(c_node);
        return 0;
      }
    c_node = c_node->prev;
    }
    return -1;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l) {
    node *c_node = l->head;
    while (c_node != NULL) {
      printf ("%d ", c_node -> value);
      c_node = c_node->next;
    }
    printf (" ");
}

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l) {
    node *c_node = l->tail;
    do {
      printf ("%d ", c_node -> value);
      c_node = c_node->prev;
    } while (c_node != NULL);
    printf (" ");
}

// Проверка наличия элемента
void find_id(list *l, int value) {
    if (find(l, value) != NULL) {
      printf("1 ");
    } else {
      printf("0 ");
    }
}
```