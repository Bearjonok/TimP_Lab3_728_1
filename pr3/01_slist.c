#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node {
	int value; // ��������, ������� ������ ����
	struct node *next; // ������ �� ��������� ������� ������
} node;

typedef struct list {
	struct node *head; // ������ ������
} list;

// ������������� ������� ������
void init(list *l);

// ������� ��� �������� �� ������
void clean(list *l);

// �������� �� ������� ������
bool is_empty(list *l);

// ����� �������� �� ��������. ������� NULL ���� ������� �� ������
node *find(list *l, int value);

// ������� �������� � ����� ������, ������� 0 ���� �������
int push_back(list *l, int value);

// ������� �������� � ������ ������, ������� 0 ���� �������
int push_front(list *l, int value);

// ������� �������� ����� ���������� ����, ������� 0 ���� �������
int insert_after(node *n, int value);

// ������� ������ ������� �� ������ � ��������� ���������, 
// ������� 0 ���� �������
int remove_node(list *l, int value);

// ������� ��� �������� �� ������ � ������ ������� ����� ������,
// ����� ��������� ������ ������� �� ����� ������
void print(list *l);

// �������� ������� ��������
void find_id(list *l, int value); 


int main() {
  int n, digit, elem;
  int i = 1;
  list l = {0};
  int check = scanf("%d", &n);
  assert(check == 1);
  while (i <= n) {
    check = scanf("%d", &digit);
    assert(check == 1);
    push_back(&l, digit);
    i++;
  }
  print(&l);
  printf("\n");
  i = 1;   //���������� ��������� � ������
  while (i <= 3) {
    check = scanf("%d", &digit);
    assert(check == 1);
    find_id(&l, digit);
    i++;
  }
  printf("\n");
  check = scanf("%d", &digit);  //���������� � �����
  assert(check == 1);
  push_back(&l, digit);
  print(&l);
  printf("\n");
  check = scanf("%d", &digit);   //��������� � ������
  assert(check == 1);
  push_front(&l, digit);
  print(&l);
  printf("\n");
  check = scanf("%d", &digit);   //���������� ����� ���������� ��������
  assert(check == 1);
  check = scanf("%d", &elem);
  assert(check == 1);
  node *c_node = l.head;   //������� ��������� ���� � �������� � ������� insert_after
  int number = 1;
  while ((c_node != NULL)&&(number!= digit)) {
    c_node = c_node->next;
    number++;
  }
  node *insert_head = c_node;
  insert_after(insert_head, elem);
  print(&l);
  printf("\n");
  check = scanf("%d", &digit);   //������� ������ ������� ������ ����������
  assert(check == 1);
  remove_node(&l, digit);
  print(&l);
  printf("\n");
  clean(&l);   //�������� ������
  return 0;
};



// ������������� ������� ������
void init(list *l) {
  l->head = NULL;
}

// ������� ��� �������� �� ������
void clean(list *l) {
  node *c_node = l->head;
  node *n_node = c_node->next;
  while(n_node != NULL) {
    free(c_node);
    c_node = n_node;
    n_node = c_node->next;
  }
  l->head = NULL;
}


// �������� �� ������� ������
bool is_empty(list *l) {
  if(l->head == NULL) {
    return true;
  }
  return false;
}

// ����� �������� �� ��������. ������� NULL ���� ������� �� ������
node *find(list *l, int value) {
  node *c_node = l->head;
  while ((c_node != NULL)&&(c_node->value != value)) {
    c_node = c_node->next;
  }
  return c_node;
}

// ������� �������� � ����� ������, ������� 0 ���� �������
int push_back(list *l, int value) {
  node *push;
  push = malloc(sizeof(node));
  push->value = value;
  push->next = NULL;
  if(l->head == NULL) {
      l->head = push;
  } else {
      node *c_node = l->head;
      while(c_node->next != NULL) {
          c_node = c_node->next;
      }
      c_node->next = push;
  }
  return 0;
}

// ������� �������� � ������ ������, ������� 0 ���� �������
int push_front(list *l, int value) {
  node *push;
  push = malloc(sizeof(node));
  push->value = value;
  if(l->head == NULL) {
      push->next = NULL;
      l->head = push;
  } else {
      node *n = l->head;
      push->next = n;
      l->head = push;
  }
  return 0;
}

// ������� �������� ����� ���������� ����, ������� 0 ���� �������
int insert_after(node *n, int value) {
  node *c_node = calloc(1, sizeof(node));
  c_node->value = value;
  c_node->next = n->next;
  n->next = c_node;
  return 0;
}

// ������� ������ ������� �� ������ � ��������� ���������,
// ������� 0 ���� �������
int remove_node(list *l, int value) {
  if(l->head == NULL) {
    return -1;
  } else {
    node *c_node = l->head;
    node *p_node = NULL;
    while (c_node->next) {
      if (c_node->value == value) {
        if (p_node == NULL) {
          l->head = c_node->next;
          free(c_node);
          return 0;
        }       
        p_node->next = c_node->next;
        free(c_node);
        return 0;
      }
    p_node = c_node;
    c_node = c_node->next;
    }
    return -1;
  }
}

// ������� ��� �������� �� ������ � ������ ������� ����� ������,
// ����� ��������� ������ ������� �� ����� ������
void print(list *l) {
  node *c_node = l->head;
  while (c_node != NULL) {
    printf("%d ", c_node->value);
    c_node = c_node->next;
  }
  printf("\n");
}

// �������� ������� ��������
void find_id(list *l, int value) {
  if (find(l, value) != NULL) {
    printf("1 ");
  } else {
printf("0 ");
  }
}