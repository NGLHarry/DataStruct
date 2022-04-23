#include <stdio.h>
#include <stdbool.h>

struct single_list
{
    struct single_list *next;
    int val;
};

struct single_list_head
{
    struct single_list *head;
};


void insert(struct single_list **prev, struct single_list *elem)
{
    if(!prev)
    {
        printf("pre is null\n");
        return ;
    }

    elem->next = *prev;
    *prev = elem;
}

void insert2(struct single_list **prev, struct single_list *elem)
{
    if(!prev)
    {
        printf("pre is null\n");
        return ;
    }
    
    elem->next = (*prev)->next;
    (*prev)->next = elem;
}

void insert_head(struct single_list_head *head, struct single_list *elem)
{
    insert(&head->head, elem);
}

void dump(struct single_list_head *head)
{
    struct single_list *tmp = head->head;
    int idx = 0;

    while(tmp)
    {
        printf("[%02d]:%08d\n",idx++, tmp->val);
        tmp = tmp->next;
    }
}

// 用法很巧妙
struct single_list** search(struct single_list_head *head, int target)
{   
    struct single_list **prev, *tmp;
    for(prev = &head->head, tmp = *prev;
        tmp && (tmp->val <target);
        prev = &tmp->next,tmp= *prev)
        ;
    
    return prev;
}

// 
// 入参：head ；elem
// 出参：elemAddr 如果包含elem，返回elem地址；如果不包含，返回应该插入的位置
// 返回值：找到返回0，未找到返回-1
int search(struct single_list_head *head, int elem, struct single_list **elemAddr)
{   
    struct single_list *prev, *last;

    prev = last = head->head;
    while(prev && last)
    {
        if(last == nullptr || last->val >= elem)
            break;

        prev = last;
        last = last->next;
       
    }
    *elemAddr = prev;
    
    printf("%d,elem:%d\n",prev->val,elem);
    if(last != nullptr && last->val == elem)
        return 0;
    else
        return -1;
}

struct single_list* del(struct single_list **prev)
{
    struct single_list *tmp;

    if(!prev)
        return NULL;
    if(*prev == NULL)
        return NULL;
    
    tmp = *prev;
    *prev = (*prev)->next;
    tmp->next = NULL;
    
    return tmp;
}

bool is_empty(struct single_list_head *head)
{
	return head->head == NULL;
}

struct single_list* delete_head(struct single_list_head *head)
{
    return del(&head->head);
}

void reverse(struct single_list_head *head)
{
    struct single_list_head tmp = {NULL};
    struct single_list *elem;

    while(!is_empty(head))
    {
        elem = delete_head(head);
        insert_head(&tmp, elem);
    }
    head->head = tmp.head;
}

bool is_cyclic(struct single_list_head *head)
{
    struct single_list *s1,*s2;

    s1 = s2 = head->head;
    while(s1 && s2)
    {
        s1 = s1->next;
        s2 = s2->next ? s2->next->next : s2->next;
        if(s1 == s2)
        {
            return true;
        }
    }
    return false;
}

struct single_list* middle(struct single_list_head *head)
{
    struct single_list *s1, *s2;
    struct single_list pseudo_head;
    
    pseudo_head.next = head->head;
    s1 = s2 = &pseudo_head;

    while(true)
    {
        if(!s2 || !s2->next)
            return s1;
        s1 = s1->next;
        s2 = s2->next->next;
    }
    return NULL;
}

int main()
{
    struct single_list_head head = {NULL};
    struct single_list lists[10];
    struct single_list *prev;
    struct single_list **prev2;

    int idx;
    for(idx = 0; idx < 10; idx++)
    {
        lists[idx].val = idx;
        lists[idx].next = NULL;
    }

    // 该链表为头插法，从小到大排列
    insert_head(&head, &lists[6]);
	insert_head(&head, &lists[5]);
	insert_head(&head, &lists[4]);
	insert_head(&head, &lists[1]);
	insert_head(&head, &lists[0]);

    printf("=== insert 0, 1, 4, 5, 6\n");
	
    dump(&head);
    int flag;
    flag = search(&head, 2, &prev);
    if(flag == -1)
        insert2(&prev, &lists[2]);
    else
        printf("find it\n");

    dump(&head);

    prev2 = search(&head, 2);
    if((*prev2) && ((*prev2)->val == 2))
        printf("The list contains 2\n");
    else
        printf("The list not contains 2\n");

    del(prev2);
    prev2 = search(&head, 2);
	printf("After remove 2\n");
	if ((*prev2) && ((*prev2)->val == 2))
		printf("The list contains 2\n");
	else
		printf("The list not contains 2\n");
	dump(&head);

    printf("After reverse \n");
    reverse(&head);
    dump(&head);

    printf("middle elem is %d\n", middle(&head)->val);
    lists[0].next = &lists[6];
    printf("list is%s cyclic\n", is_cyclic(&head)?"":" not");
   
    return 0;
}