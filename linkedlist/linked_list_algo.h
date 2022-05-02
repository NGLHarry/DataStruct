#ifndef LINKED_LIST_ALGO_H_
#define LINKED_LIST_ALGO_H_

template<typename T>
struct Node{
    using ptr_t = std::shared_ptr<Node<T>>;
    T data;
    ptr_t next;

    Node(T data_):data(data_),next(nullptr){}
    Node():next(nullptr){}
};


#endif
