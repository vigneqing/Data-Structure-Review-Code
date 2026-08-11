//括号匹配问题
#define MaxSize 100
typedef struct{
    char data[MaxSize];
    int top;
}SqStack;

//初始化栈
void InitStack(SqStack &S){
    S.top = -1;
}

//判断栈是否为空
bool StackEmpty(SqStack S){
    return S.top == -1;
}

//入栈
void Push(SqStack &S, char x){
    if(S.top == MaxSize - 1){
        printf("栈满");
        return;
    }
    S.data[++S.top] = x;
}

//出栈
void Pop(SqStack &S, char &x){
    if(StackEmpty(S)){
        printf("栈空");
        return;
    }
    x = S.data[S.top--];
}

//判断括号是否匹配
bool bracketCheck(char str[], int length){
    SqStack S;
    InitStack(S);
    for(int i = 0; i < length; i++){
        if(str[i] == '(' || str[i] == '[' || str[i] == '{'){
            Push(S, str[i]);
        }else{
           if(StackEmpty(S)) return false;

           char topElem;
           Pop(S, topElem);
           if((str[i] == ')' && topElem != '(') ||
              (str[i] == ']' && topElem != '[') ||
              (str[i] == '}' && topElem != '{'))
              return false;
              }
        }
    return StackEmpty(S);
}

//递归
//递归算法求阶乘
int factorial(int n){
    if(n == 0) return 1;
    return n * factorial(n - 1);
}

//递归算法求斐波那契数列
int fibonacci(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

//队列的应用
