/* ═══════════════════════════════════════════════════════════════════
 * 表达式计算：中缀/后缀/前缀 互相转换 + 求值
 * ═══════════════════════════════════════════════════════════════════ */

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>

using namespace std;

// 运算符优先级 (越高越优先)
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0; // '(' 或其它
}

// 判断是否为运算符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// 判断是否为操作数 (数字或字母)
bool isOperand(char c) {
    return isalnum(c);
}

// 执行运算 a op b
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                cerr << "错误: 除零" << endl;
                exit(1);
            }
            return a / b;
        case '^': return (int)pow(a, b);
    }
    return 0;
}

// ==================== 表达式转换 ====================

// 中缀 -> 后缀
string infixToPostfix(string infix) {
    stack<char> opStack;
    string postfix;
    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (isspace(c)) continue;               // 跳过空格

        if (isOperand(c)) {
            postfix += c;                       // 操作数直接输出
        }
        else if (c == '(') {
            opStack.push(c);
        }
        else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop(); // 弹出 '('
        }
        else if (isOperator(c)) {
            // 右结合的 '^' 仅当栈顶优先级更高时才弹出，同优先级不弹出
            if (c == '^') {
                while (!opStack.empty() && precedence(opStack.top()) > precedence(c)
                       && opStack.top() != '(') {
                    postfix += opStack.top();
                    opStack.pop();
                }
            } else {
                while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)
                       && opStack.top() != '(') {
                    postfix += opStack.top();
                    opStack.pop();
                }
            }
            opStack.push(c);
        }
    }
    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }
    return postfix;
}

// 中缀 -> 前缀
string infixToPrefix(string infix) {
    // 1. 反转中缀
    reverse(infix.begin(), infix.end());
    // 2. 互换 '(' 和 ')'
    for (size_t i = 0; i < infix.length(); i++) {
        if (infix[i] == '(') infix[i] = ')';
        else if (infix[i] == ')') infix[i] = '(';
    }
    // 3. 得到后缀（实际是前缀的逆序）
    string postfix = infixToPostfix(infix);
    // 4. 再反转即得前缀
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

// 后缀 -> 中缀
string postfixToInfix(string postfix) {
    stack<string> st;
    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (isspace(c)) continue;
        if (isOperand(c)) {
            st.push(string(1, c));
        }
        else if (isOperator(c)) {
            if (st.size() < 2) {
                cerr << "无效后缀表达式" << endl;
                return "";
            }
            string op2 = st.top(); st.pop();
            string op1 = st.top(); st.pop();
            string expr = "(" + op1 + c + op2 + ")";
            st.push(expr);
        }
    }
    return st.empty() ? "" : st.top();
}

// 前缀 -> 中缀
string prefixToInfix(string prefix) {
    stack<string> st;
    // 从右向左扫描
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isspace(c)) continue;
        if (isOperand(c)) {
            st.push(string(1, c));
        }
        else if (isOperator(c)) {
            if (st.size() < 2) {
                cerr << "无效前缀表达式" << endl;
                return "";
            }
            string op1 = st.top(); st.pop();
            string op2 = st.top(); st.pop();
            string expr = "(" + op1 + c + op2 + ")";
            st.push(expr);
        }
    }
    return st.empty() ? "" : st.top();
}

// 后缀 -> 前缀
string postfixToPrefix(string postfix) {
    stack<string> st;
    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (isspace(c)) continue;
        if (isOperand(c)) {
            st.push(string(1, c));
        }
        else if (isOperator(c)) {
            if (st.size() < 2) {
                cerr << "无效后缀表达式" << endl;
                return "";
            }
            string op2 = st.top(); st.pop();
            string op1 = st.top(); st.pop();
            string expr = c + op1 + op2;   // 构成前缀格式
            st.push(expr);
        }
    }
    return st.empty() ? "" : st.top();
}

// 前缀 -> 后缀
string prefixToPostfix(string prefix) {
    stack<string> st;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isspace(c)) continue;
        if (isOperand(c)) {
            st.push(string(1, c));
        }
        else if (isOperator(c)) {
            if (st.size() < 2) {
                cerr << "无效前缀表达式" << endl;
                return "";
            }
            string op1 = st.top(); st.pop();
            string op2 = st.top(); st.pop();
            string expr = op1 + op2 + c;   // 构成后缀格式
            st.push(expr);
        }
    }
    return st.empty() ? "" : st.top();
}

// ==================== 表达式求值 ====================

// 后缀求值 (操作数为一位数字)
int evaluatePostfix(string postfix) {
    stack<int> st;
    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (isspace(c)) continue;
        if (isdigit(c)) {
            st.push(c - '0');
        }
        else if (isOperator(c)) {
            if (st.size() < 2) {
                cerr << "无效后缀表达式" << endl;
                return 0;
            }
            int op2 = st.top(); st.pop();
            int op1 = st.top(); st.pop();
            st.push(applyOp(op1, op2, c));
        }
    }
    return st.empty() ? 0 : st.top();
}

// 前缀求值 (操作数为一位数字)
int evaluatePrefix(string prefix) {
    stack<int> st;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isspace(c)) continue;
        if (isdigit(c)) {
            st.push(c - '0');
        }
        else if (isOperator(c)) {
            if (st.size() < 2) {
                cerr << "无效前缀表达式" << endl;
                return 0;
            }
            int op1 = st.top(); st.pop();   // 注意顺序：先弹出的是左侧操作数
            int op2 = st.top(); st.pop();
            st.push(applyOp(op1, op2, c));
        }
    }
    return st.empty() ? 0 : st.top();
}

// 中缀求值 (双栈法，支持多位数整数)
int evaluateInfix(string infix) {
    stack<int> valStack;
    stack<char> opStack;

    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (isspace(c)) continue;

        if (isdigit(c)) {
            int num = 0;
            while (i < infix.length() && isdigit(infix[i])) {
                num = num * 10 + (infix[i] - '0');
                i++;
            }
            i--;                          // 回退一位，外层循环还会 i++
            valStack.push(num);
        }
        else if (c == '(') {
            opStack.push(c);
        }
        else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                if (valStack.size() < 2) { cerr << "无效表达式" << endl; return 0; }
                int val2 = valStack.top(); valStack.pop();
                int val1 = valStack.top(); valStack.pop();
                char op = opStack.top(); opStack.pop();
                valStack.push(applyOp(val1, val2, op));
            }
            if (!opStack.empty()) opStack.pop(); // 弹出 '('
        }
        else if (isOperator(c)) {
            // 处理结合性：'^' 右结合，其余左结合
            if (c == '^') {
                while (!opStack.empty() && precedence(opStack.top()) > precedence(c)
                       && opStack.top() != '(') {
                    if (valStack.size() < 2) { cerr << "无效表达式" << endl; return 0; }
                    int val2 = valStack.top(); valStack.pop();
                    int val1 = valStack.top(); valStack.pop();
                    char op = opStack.top(); opStack.pop();
                    valStack.push(applyOp(val1, val2, op));
                }
            } else {
                while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)
                       && opStack.top() != '(') {
                    if (valStack.size() < 2) { cerr << "无效表达式" << endl; return 0; }
                    int val2 = valStack.top(); valStack.pop();
                    int val1 = valStack.top(); valStack.pop();
                    char op = opStack.top(); opStack.pop();
                    valStack.push(applyOp(val1, val2, op));
                }
            }
            opStack.push(c);
        }
    }

    while (!opStack.empty()) {
        if (valStack.size() < 2) { cerr << "无效表达式" << endl; return 0; }
        int val2 = valStack.top(); valStack.pop();
        int val1 = valStack.top(); valStack.pop();
        char op = opStack.top(); opStack.pop();
        valStack.push(applyOp(val1, val2, op));
    }
    return valStack.empty() ? 0 : valStack.top();
}

// ==================== 主函数测试 ====================
int main() {
    string infix = "3+5*2/(7-2)";
    cout << "中缀表达式: " << infix << endl;

    // 转换
    string postfix = infixToPostfix(infix);
    string prefix  = infixToPrefix(infix);
    cout << "后缀表达式: " << postfix << endl;
    cout << "前缀表达式: " << prefix  << endl;

    cout << "\n--- 互相转换 ---" << endl;
    cout << "后缀 -> 中缀: " << postfixToInfix(postfix) << endl;
    cout << "前缀 -> 中缀: " << prefixToInfix(prefix)   << endl;
    cout << "后缀 -> 前缀: " << postfixToPrefix(postfix) << endl;
    cout << "前缀 -> 后缀: " << prefixToPostfix(prefix) << endl;

    cout << "\n--- 求值 (操作数需为数字) ---" << endl;
    cout << "后缀 " << postfix << " = " << evaluatePostfix(postfix) << endl;
    cout << "前缀 " << prefix  << " = " << evaluatePrefix(prefix)   << endl;
    cout << "中缀 " << infix   << " = " << evaluateInfix(infix)     << endl;

    // 测试右结合 '^'
    string infix2 = "2^3^2";                // 应为 2^(3^2) = 512
    string post2 = infixToPostfix(infix2);
    cout << "\n右结合测试: " << infix2 << " -> 后缀 " << post2
         << " 值 = " << evaluatePostfix(post2) << endl;

    return 0;
}