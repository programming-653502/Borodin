#include <iostream>
#include <conio.h>
using namespace std;

struct stack // Стек в виде односвязного списка
{
    char data;
    stack* next;
};

void initialized_Stack(stack** pointer_to_the_stack)//инициализация стека
{
	*pointer_to_the_stack = nullptr;//NULL для указателей
}

int isEmpty(stack* pointer_to_the_stack)// проверка на пустоту
{
	if (pointer_to_the_stack == nullptr)
		return 1;// пустой
	return 0;// не пустой
}

void push(stack** pointer_to_the_stack, int variable)//занесение в стек
{
	stack* indicative_object = new stack();// indicative_object == указательный объект на структуру стек

	if (indicative_object == nullptr)
	{
		cout << "Could not allocate memory." << endl;
		return;
	}

	indicative_object -> data = variable;//перенаправление указателя на след элемент списка
	indicative_object -> next = *pointer_to_the_stack;
	*pointer_to_the_stack = indicative_object;
}

int pop(stack** pointer_to_the_stack)//выборка из стека
{
	int variable;
	stack* temp;
/*первый элемент возвращает, потом удаляет
=> происходит перенаправление указателя на след элемент списка*/

	variable = (*pointer_to_the_stack)->data;
	temp = *pointer_to_the_stack;
	(*pointer_to_the_stack) = (*pointer_to_the_stack)->next;
	delete temp;

	return variable;
}

int top(stack* pointer_to_the_stack)//возврат верхнего элемента без удаления
{
	return pointer_to_the_stack->data;
}

void sorted_Insert(stack** pointer_to_the_stack, int variable)//Отсортированная вставка
{
	if (isEmpty(*pointer_to_the_stack) || variable < top(*pointer_to_the_stack))
	{
		push(pointer_to_the_stack, variable);
		return;
	}

	//рекурсия
	int temp = pop(pointer_to_the_stack);
	sorted_Insert(pointer_to_the_stack, variable);
	push(pointer_to_the_stack, temp);
}

void sort_Stack(stack** pointer_to_the_stack)//Сортировка стека
{
	if (!isEmpty(*pointer_to_the_stack))
	{
		int variable = pop(pointer_to_the_stack); // Удаляем верхний элемент
		sort_Stack(pointer_to_the_stack); // Сортируем оставшийся стек
		sorted_Insert(pointer_to_the_stack, variable); // Возвращаем верхний элемент в сортированный стек
	}
}

void print_Stack(stack* pointer_to_the_stack)//печать стека
{
	while (pointer_to_the_stack)
	{
		cout << pointer_to_the_stack->data;
		pointer_to_the_stack = pointer_to_the_stack->next;
	}
	cout << endl;
}

void merge_Stack(stack*& object1, stack*& object2)//слияние стеков
{
	if (object1->next != nullptr)
		merge_Stack(object1->next, object2);//слияние
	push(&object2, object1->data);

	delete object1;
	object1 = nullptr;
}


struct list //Двусвязный циклический список
{
	stack* field;
	list *next, *prev;
};

list* init(stack* start)//инициализировать
{
	list* lst_element = new list();
//задается указатель на предыдущий и следующий элемент
	lst_element->field = start;
	lst_element->next = lst_element;
	lst_element->prev = lst_element;
	return lst_element;
}

list* add_element(list* lst_element, stack* number)//добавление
{
	list* temp = new list();
	list* pointer;

	pointer = lst_element->next;//получает значения след элемента
	lst_element->next = temp;
	temp->field = number;
	temp->next = pointer;
	temp->prev = lst_element;
	pointer->prev = temp;

	return temp;
}

void list_Print(list* lst_element)//печать
{
	list* pointer;
	pointer = lst_element;
	do
	{
		print_Stack(pointer->field);
		pointer = pointer->next;//получает значения след элемента
	}
	while (pointer != lst_element);
}

void merge_All(list* lst_element)//cлияние
{
	list* pointer;
	pointer = lst_element;
	do
	{
		merge_Stack(pointer->field, lst_element->field);
		pointer = pointer->next;
	}
	while (pointer != lst_element);
}

void sort_All(list* lst_element)//сортировка
{
	list* pointer;
	pointer = lst_element;
	do
	{
		sort_Stack(&pointer->field);
		pointer = pointer->next;
	}
	while (pointer != lst_element);
}

int main()
{
	stack* start;
	initialized_Stack(&start);
	push(&start, 0);

	list* list1;
	list1 = init(start);

	stack* stack_1;
	initialized_Stack(&stack_1);
	push(&stack_1, 'a');
	push(&stack_1, 'c');
	push(&stack_1, 'b');
	push(&stack_1, 'e');
	push(&stack_1, 'd');

	stack* stack_2;
	initialized_Stack(&stack_2);
	push(&stack_2, 'h');
	push(&stack_2, 'p');
	push(&stack_2, 'r');
	push(&stack_2, 'x');
	push(&stack_2, 'z');

	stack* stack_3;
	initialized_Stack(&stack_3);
	push(&stack_3, 'k');
	push(&stack_3, 'f');
	push(&stack_3, 'i');
	push(&stack_3, 'w');
	push(&stack_3, 't');
	push(&stack_3, 's');

	add_element(list1, stack_1);
	add_element(list1, stack_2);
	add_element(list1, stack_3);

	cout << "Initialized stacks: ";
	list_Print(list1);
	cout << endl;

	sort_All(list1);
	cout << "Sorted stacks: ";
	list_Print(list1);
	cout << endl;

	merge_All(list1);
	sort_All(list1);
	cout << "Merged stacks: ";
	list_Print(list1);

	getch();
}
