#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Структура для хранения узла дерева.
typedef struct node 
{
    int value;
    struct node *left; //ссылка налево
    struct node *right;//ссылка направо
    struct node *parent;//ссылка на родителя
} 
node;

// Структура для хранения дерева.
typedef struct tree 
{
    struct node *tmp; //для работы с деревом
    struct node *root; //корень
    int numbers; //количество элементов
} 
tree;

// Инициализация дерева
void init(tree* t);

//Функция рекурсивного удаления из любого места
node* Itachi(node* t);

// Удалить все элементы из дерева
void clean(tree* t);

// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(tree* t, int value);

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
int insert(tree* t, int value);

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree* t, int value);

// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента
int remove_min(node* n);

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно 
int rotate_right(node* n);

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(node* n);

// получение кол-во уровней в дереве
int get_levels(node* tmp);

//функция для вывода уровня
void print_level(node* tmp, int curl, int d, int first);

// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке. 
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
// Если дерево пусто, вывести -
void print(node* n);

// Вывести все значения дерева t, аналогично функции print
void print_tree(tree* t);

//Вывод количества элементов в списке
void print_num(tree* t); 

int main()
{
	int a, i, n1, n2;
	struct tree t;
	init(&t);
	
	//ввод первых 4х чисел
	for (i=0; i<4; i++)
	{
		scanf("%d", &a);
		insert(&t, a);
	}
	print_tree(&t);
	printf("\n");
	
	//ввод ещё 3х чисел
	for (i=0; i<3; i++)
	{
		scanf("%d", &a);
		insert(&t, a);
	}
	print_tree(&t);
	printf("\n");
	
	//вывод потомков и предка элемента
	scanf("%d", &n1);
	node *x = find(&t, n1);
    if(x==NULL)
    {
        printf("-");
        printf("\n");
    }
    else
    {
        if (x->parent != NULL)
        {
            printf("%d", x->parent->value);
            printf(" ");
        }
        else
        {
            printf("_ ");
        }
        if(x->left)
        {
            printf("%d", x->left->value);
        }
        else
        {
            printf("_");
        }
        printf(" ");
        if(x->right)
        {
            printf("%d", x->right->value);
        }
        else
        {
            printf("_");
        }
        printf("\n");
    }
    printf("\n");
    
    scanf("%d", &n2);
	x = find(&t, n2);
    if(x==NULL)
    {
        printf("-");
        printf("\n");
    }
    else
    {
        if (x->parent != NULL)
        {
            printf("%d", x->parent->value);
            printf(" ");
        }
        else
        {
            printf("_ ");
        }
        if(x->left)
        {
            printf("%d", x->left->value);
        }
        else
        {
            printf("_");
        }
        printf(" ");
        if(x->right)
        {
            printf("%d", x->right->value);
        }
        else
        {
            printf("_");
        }
        printf("\n");
    }
    printf("\n");
	
	//удаление элемента
	scanf("%d", &n1);
	remove_node(&t, n1);
	print_tree(&t);
	printf("\n");
	
	//левые вращения
	node* troot = t.root;
	if (troot != NULL)
	{
		while (troot->right != NULL)
		{
			 rotate_left(t.root);
	      if (t.root->parent != NULL)
	      {
		      t.root = t.root->parent;
	      }
        troot =t.root;
		}
	}
	printf("\n");
    print_tree(&t);
    
	//правые вращения
	troot = t.root;
	if(troot != NULL)
	{
        while (troot->left != NULL)
        {
          rotate_right(t.root);
	        if (t.root->parent != NULL)
	        {
	          t.root = t.root->parent;
	        }
          troot = t.root;
        }
    }
	printf("\n");
    print_tree(&t);
    
	//кол-во элементов
	printf("\n");
	print_num(&t);
	printf("\n\n");
	
	//очистка дерева
	clean(&t);
	troot = t.root;
	print_tree(&t);
	return 0;
}

// Инициализация дерева
void init(tree* t)
{
	t->root=NULL;
}



//Функция рекурсивного удаления из любого места
node* Itachi(node* t) 
{
	if(t!=NULL)
	{
		Itachi(t->left); 
		Itachi(t->right); 
		if(t->parent!=NULL)
			t->parent = NULL;
		if(t->left!=NULL)
			t->left = NULL;
		if(t->right!=NULL)
			t->right = NULL;
		free(t); 
	}
	return NULL;
}


// Удалить все элементы из дерева
void clean(tree* t)
{
        node* root = t->root;
        Itachi(root);
        t->root = NULL;
}


// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(tree* t, int value)
{
	t->tmp = t->root; 
	while(t->tmp->value != value)
	{
		if(t->tmp->value > value) 
		{
			t->tmp = t->tmp->left; 
		}
		else
		{
			t->tmp = t->tmp->right;
		}
		if(t->tmp == NULL) 
		{
			return NULL;
		}
	}
	return t->tmp;
}

 

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
int insert(tree* t, int value)
{
	node *a_root = t->root, *b_root = NULL; 
	t->tmp = malloc(sizeof(node)); 
	t->tmp->value = value; 
	if (t->root == NULL)
	{
		t->tmp->parent = NULL; 
		t->tmp->left = NULL; 
		t->tmp->right = NULL; 
		t->root = t->tmp; 
		t->numbers = 1; 
		return 0; 
	}
	while (a_root != NULL) 
	{
		b_root = a_root; 
		if (value == a_root->value) 
                {
                    return 1; 
                }
		if (value < a_root->value) 
		{
			a_root = a_root->left; 
		}
		else 
		{
			a_root = a_root->right; 
		}
	} 
	t->tmp->parent = b_root; 
	t->tmp->left = NULL; 
	t->tmp->right = NULL;
	if (value < b_root->value) 
	{
		b_root->left = t->tmp; 
		t->numbers = t->numbers + 1; 
		return 0; 
	}
	if (value > b_root->value) 
	{
		b_root->right = t->tmp; 
		t->numbers = t->numbers +1; 
		return 0;
	}
  return -1;
}



// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента

int remove_min(node* n)
{
	int val;
	node *tmp = n; 
	while (tmp->left != NULL) 
	{
		tmp = tmp->left;  
	}
	val = tmp->value; 
	if(tmp->right != NULL)
	{
		if(val < tmp->parent->value)
		{
			tmp->parent->left = tmp->right;
			free(tmp);
			return val;
		}
		else
		{
			tmp->parent->right = tmp->right;
			free(tmp);
			return val;
		}
	}
	else
	{
		if (val < tmp->parent->value)
		{
			tmp->parent->left = NULL;
			free(tmp);
			return val;
		}
		else
		{
			tmp->parent->right = NULL;
			free(tmp);
			return val;
		}
	}
}


// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree* t, int value)
{
	int val;
	node *tmp = find(t, value); 
	if (tmp == NULL) 
		return 1;
	if (tmp->left==NULL && tmp->right==NULL)
	{
		if(tmp != t->root) 
		{
			if (tmp->value < tmp->parent->value) 
			{
				tmp->parent->left = NULL; 
				free(tmp); 
				t->numbers = t->numbers-1; 
				return 0; 
			}
			else
			{
				tmp->parent->right = NULL; 
				free(tmp); 
				t->numbers = t->numbers-1; 
				return 0; //конец
			}
		}
		else 
		{
			free(tmp); 
			t->root = NULL; 
			t->numbers = 0;
			return 0;
		}
	}
	if (tmp->left==NULL && tmp->right!=NULL) 
	{
		if(tmp != t->root) 
		{
			if (tmp->value < tmp->parent->value) 
			{
				tmp->parent->left = tmp->right; 
				tmp->right->parent = tmp->parent; 
				free(tmp);
				t->numbers = t->numbers-1; 
				return 0; 
			}
			else 
			{
				tmp->parent->right = tmp->right; 
				tmp->right->parent = tmp->parent; 
				free(tmp); 
				t->numbers = t->numbers-1; 
				return 0; 
			}
		}
		else 
		{
			tmp->right->parent = NULL; 
			t->root = tmp->right; 
			free(tmp); 
			t->numbers = t->numbers-1; 
			return 0; 
		}
	}
	if (tmp->left!=NULL && tmp->right==NULL) 
	{
		if(tmp !=t->root) 
		{
			if (tmp->value < tmp->parent->value) 
			{
				tmp->parent->left = tmp->left;
				tmp->left->parent = tmp->parent;
				free(tmp);
				t->numbers = t->numbers-1;
				return 0;
			}
			else 
			{
				tmp->parent->right = tmp->left;
				tmp->left->parent = tmp->parent;
				free(tmp);
				t->numbers = t->numbers-1;
				return 0;
			}
		}
		else 
		{
			tmp->left->parent = NULL; 
			t->root = tmp->left; 
			free(tmp); 
			t->numbers = t->numbers-1; 
			return 0; 
		}
	}
	if(tmp->right!=NULL && tmp->left!=NULL) 
	{
		val = remove_min(tmp->right); 
		tmp->value = val; 
		t->numbers = t->numbers-1; 
		return 0; 
	}
  return -1;
}

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно 
int rotate_right(node* n)
{
	node* root = n;
	node* new_root = root->left;
        node* rotate = new_root->right;
        new_root->parent = root->parent;
        if(root->parent != NULL)
        {
            if(root->parent->value > root->value)
            {
                root->parent->left = new_root;
            }
            else
            {
                root->parent->right = new_root;
            }
        }
        
        if(rotate!=NULL)
        {
            rotate->parent = root;
        }
    root->left = rotate;
    root->parent = new_root;
    new_root->right = root;
    return 0;
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(node* n)
{
	node* root = n;
	node* new_root = root->right;
	node* rotate = new_root->left;
        new_root->parent = root->parent;
	if(root->parent != NULL)
	{
		if(root->parent->value > root->value)
		{
			root->parent->left = new_root;
		}
		else
		{
			root->parent->right = new_root;
		}
	}
	if(rotate!=NULL)
	{
	rotate->parent = root;
	}
	root->right = rotate;
	root->parent = new_root;
	new_root->left = root;
	return 0;
}



// получение кол-во уровней в дереве
int get_levels(node* tmp) 
{
	if (tmp == NULL)
	{
		return 0;
	}
	int leftmax = 1 + get_levels(tmp->left);
	int rightmax = 1 + get_levels(tmp->right);
	if (leftmax > rightmax)
	{
		return leftmax;
	}
	else
	{
		return rightmax;
	}
}



//функция для вывода уровня
void print_level(node* tmp, int curl, int d, int first) 
{
	if (curl == d)
	{
		if (first > 0)
		{
			printf(" ");
		}

		if (tmp == NULL) {
		printf("_");
		}
		else
		{
		printf("%d", tmp->value);
		}
	}
	else if (tmp != NULL) 
	{
		print_level(tmp->left, curl + 1, d, first);
		print_level(tmp->right, curl + 1, d, first + 1);
	}
	else 
	{
		print_level(tmp, curl + 1, d, first);
		print_level(tmp, curl + 1, d, first + 1);
	}
}


// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке. 
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
// Если дерево пусто, вывести -
void print(node* n)
{
	int num = get_levels(n);
	for (int i = 1; i <= num; i++)
	{
		print_level(n, 1, i, 0);
		printf("\n");
	}
}



// Вывести все значения дерева t, аналогично функции print
void print_tree(tree* t)
{
	node* n = t->root;
	if (n == NULL) 
	{
	printf("-");
	printf("\n");
	}
	print(t->root);
}

//Вывод количества элементов в списке
void print_num(tree* t) 
{
	printf("%d", t->numbers);
}

