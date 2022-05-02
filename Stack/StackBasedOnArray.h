template <class T>
class ArrayStack
{
public:
    ArrayStack();
    ArrayStack(int count);
    ~ArrayStack();
    void push(T data);  //入栈
    T pop();    //出栈
    T peek();   //返回栈顶元素，不删除栈顶元素，栈顶指针不变
    int stackSize();
    int stackMaxSize();

private:
    int flag;   //栈顶标签，指向栈顶
    int count;  //栈容量
    T *array;   //指针

};