#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DlistNode
{
    struct DlistNode *prev; //前项指针
    struct DlistNode *next; //后项指针
    int data;               //数据
}stDlistNode;

typedef struct Dlisthead    //定义链表总体
{
    int size;           //链表长度
    stDlistNode *head;  //头指针
    stDlistNode *tail;  //尾部指针
}stDlistHead;


void dlist_init(stDlistHead *dlist)
{
    dlist->size = 0;
    dlist->head = NULL;
    dlist->tail = NULL;
    return ;
}

// 头插法
// 参数1：操作的链表；参数2：操作的节点；参数3：数据
int dlist_insert_head(stDlistHead *dlist, stDlistNode *pNode, int data)
{
    if(pNode == NULL)
    {
        pNode = (stDlistNode *)malloc(sizeof(stDlistNode));
        if(pNode == NULL)
        {
            printf("malloc fail ....\n");
            return -1;
        }
    }
    pNode->data = data;
    pNode->next = NULL;
    pNode->prev = NULL;

    //如果链表长度为0，即当前链表无节点
    if(dlist->size == 0)
    {
        dlist->head = pNode;
        dlist->tail = pNode;
    }
    else //如果链表已经有节点，则另新插入节点为头结点
    {
        pNode->next = dlist->head;
        dlist->head->prev = pNode;
        dlist->head = pNode;
    }
    dlist->size++;  //每成功调用一次，链表长度+1
    return 0;
}

//遍历链表
void dlist_dump(stDlistHead *dlist)
{
    int no = 0;
    stDlistNode *pNode = dlist->head;
    while(pNode)
    {
        printf(" [%d] = %d\n",no, pNode->data);
        pNode = pNode->next;
        no++;
    }
    return ;
}
//删除尾部节点，并返回删除节点
stDlistNode *dlist_remove_tail(stDlistHead *dlist)
{
    stDlistNode *pNode = NULL;
    if(dlist->size == 0)
    {
        return NULL;
    }
    pNode = dlist->tail;
    if(dlist->size > 1)
    {
        dlist->tail = dlist->tail->prev;
        dlist->tail->next = NULL;
    }
    else
    {
        dlist->tail = NULL;
        dlist->head = NULL;
    }
    dlist->size--;
    return pNode;
}
stDlistNode *dlist_search(stDlistHead *dlist, int data)
{
    stDlistNode *pNode = dlist->head;
    while(pNode != NULL)
    {
        if(pNode->data == data)
        {
            return pNode;
        }
        pNode = pNode->next;
    }
    return NULL;
}

void dlist_remove_node(stDlistHead *dlist, stDlistNode *pNode)
{
    if(dlist == NULL || pNode == NULL)
        return ;
    
    if(dlist->head == pNode)
    {
        dlist->tail = dlist->head->next;
    }
    else if(dlist->tail == pNode)
    {
        dlist->tail = pNode->prev;
        dlist->tail->next = NULL;
    }
    else
    {
        pNode->prev->next = pNode->next;
        pNode->next->prev = pNode->prev;
    }
    dlist->size--;
    pNode->next = NULL;
    pNode->prev = NULL;

    //将dlist占用内存块的所有值置为0，清空head、tail指针
    if(dlist->size == 0)
    {
        memset(dlist, 0, sizeof(stDlistHead));
    }
    return ;
}

// LRU(最近最少使用)缓存淘汰算法
void Lru_dlist(stDlistHead *dlist, int data)
{
    stDlistNode *pNode = NULL;
    pNode = dlist_search(dlist, data);
    if(pNode != NULL) //如果在链表中找到这个值，则删除储存这个值的节点，之后将该节点放在头部
    {
        dlist_remove_node(dlist, pNode);
    }
    else if(dlist->size >= 4)   //没在链表中找到，且链表长度大于4，则从链表中删除尾部借点，将新数据放在头部
    {
        dlist_remove_node(dlist, pNode);
    }
    dlist_insert_head(dlist, pNode, data);

    return ;
}

int main()
{
    stDlistHead dlist = {0};
    stDlistNode *pNode = NULL;

    dlist_init(&dlist);

    printf("\r\n insert 1,2,3");
    dlist_insert_head(&dlist, NULL, 1);
    dlist_insert_head(&dlist, NULL, 2);
    dlist_insert_head(&dlist, NULL, 3);

    dlist_dump(&dlist);
    printf("=================\n");
    
    pNode = dlist_remove_tail(&dlist);
    if(pNode != NULL)
    {
        printf("remove %d\n", pNode->data);
    }

    dlist_insert_head(&dlist, NULL, 4);
    dlist_dump(&dlist);
    printf("=================\n");

    Lru_dlist(&dlist,5);
	dlist_dump(&dlist);
    printf("=================\n");
    Lru_dlist(&dlist,6);
	dlist_dump(&dlist);
    printf("=================\n");

    Lru_dlist(&dlist,7);
	dlist_dump(&dlist);
    printf("=================\n");

    Lru_dlist(&dlist,5);
	dlist_dump(&dlist);

    while(dlist.size)
    {
        pNode = dlist_remove_tail(&dlist);
        if(pNode != NULL)
        {
            printf("remove %d\n",pNode->data);
            free(pNode);
        }
    }
    return 0;
}