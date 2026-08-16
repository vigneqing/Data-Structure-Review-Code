//
// Created by nebula on 2026/8/16.
//
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

/* ═══════════════════════════════════════════════════════════════════
 * 散列表（Hash Table）
 * ═══════════════════════════════════════════════════════════════════ */

// 散列表的核心思想：
// 通过哈希函数把关键字映射到表中某个位置，
// 以实现平均 O(1) 级别的查找、插入和删除。
// 但当冲突过多时，性能会退化，需要采用开放定址或拉链法处理冲突。

/* ─────────────────────────────────────────
 * 一、散列函数的构造
 * ───────────────────────────────────────── */

// ------------------------------------------------------------
// 1. 除留余数法
// h(key) = key % m
// ------------------------------------------------------------
int hash_Mod(int key, int m)
{
    return key % m;
}


// ------------------------------------------------------------
// 2. 直接定址法
// h(key) = key
//
// 适用于关键字范围比较小，并且关键字本身可以直接作为地址
// ------------------------------------------------------------
int hash_Direct(int key, int m)
{
    return key % m;
}


// ------------------------------------------------------------
// 3. 数字分析法
//
// 从关键字的各个数字中选择分布比较均匀的数字位作为地址
//
// 这里以十进制关键字为例，取关键字的某一位
// position = 0 表示个位
// position = 1 表示十位
// ------------------------------------------------------------
int hash_DigitalAnalysis(int key, int m, int position = 0)
{
    key = abs(key);

    for (int i = 0; i < position; i++)
        key /= 10;

    return (key % 10) % m;
}


// ------------------------------------------------------------
// 4. 平方取中法
//
// key^2 后取中间若干位
// ------------------------------------------------------------
int hash_MidSquare(int key, int m)
{
    long long square = 1LL * key * key;

    // 将平方数转换为字符串
    string s = to_string(square);

    // 取中间位置的数字
    int mid = s.length() / 2;

    int value;

    if (s.length() >= 2)
    {
        value = (s[mid - 1] - '0') * 10 + (s[mid] - '0');
    }
    else
    {
        value = square;
    }

    return value % m;
}


// ============================================================
// 二、拉链法处理冲突
// ============================================================

class ChainedHashTable
{
private:
    int size;
    vector<list<int>> table;

public:

    ChainedHashTable(int m)
    {
        size = m;
        table.resize(size);
    }

    // --------------------------------------------------------
    // 哈希函数
    // --------------------------------------------------------
    int hashFunction(int key)
    {
        return abs(key) % size;
    }

    // --------------------------------------------------------
    // 插入操作
    // --------------------------------------------------------
    void insert(int key)
    {
        int index = hashFunction(key);

        table[index].push_back(key);
    }

    // --------------------------------------------------------
    // 查找操作
    // --------------------------------------------------------
    bool search(int key)
    {
        int index = hashFunction(key);

        for (int x : table[index])
        {
            if (x == key)
                return true;
        }

        return false;
    }

    // --------------------------------------------------------
    // 删除操作
    // --------------------------------------------------------
    bool remove(int key)
    {
        int index = hashFunction(key);

        for (auto it = table[index].begin();
             it != table[index].end();
             ++it)
        {
            if (*it == key)
            {
                table[index].erase(it);
                return true;
            }
        }

        return false;
    }

    // --------------------------------------------------------
    // 输出散列表
    // --------------------------------------------------------
    void display()
    {
        cout << "\n========== 拉链法散列表 ==========\n";

        for (int i = 0; i < size; i++)
        {
            cout << "[" << i << "] -> ";

            for (int x : table[i])
            {
                cout << x << " -> ";
            }

            cout << "NULL\n";
        }
    }
};


// ============================================================
// 三、开放定址法处理冲突
// ============================================================

class OpenAddressHashTable
{
private:
    enum State
    {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Node
    {
        int key;
        State state;

        Node()
        {
            key = 0;
            state = EMPTY;
        }
    };

    int size;
    vector<Node> table;

public:

    OpenAddressHashTable(int m)
    {
        size = m;
        table.resize(size);
    }

    // ========================================================
    // 1. 线性探测法
    //
    // h_i(key) = (h(key) + i) % m
    // ========================================================

    int linearProbe(int key, int i)
    {
        int h = abs(key) % size;

        return (h + i) % size;
    }


    // ========================================================
    // 2. 平方探测法
    //
    // h_i(key) = (h(key) + i^2) % m
    // ========================================================

    int quadraticProbe(int key, int i)
    {
        int h = abs(key) % size;

        return (h + i * i) % size;
    }


    // ========================================================
    // 3. 双散列法
    //
    // h_i(key) = (h1(key) + i*h2(key)) % m
    //
    // h1(key) = key % m
    // h2(key) = 1 + key % (m - 1)
    // ========================================================

    int doubleHash(int key, int i)
    {
        int h1 = abs(key) % size;

        int h2;

        if (size > 1)
            h2 = 1 + abs(key) % (size - 1);
        else
            h2 = 1;

        return (h1 + i * h2) % size;
    }


    // ========================================================
    // 4. 伪随机序列法
    //
    // 使用伪随机数作为探测增量
    // ========================================================

    int pseudoRandomProbe(int key, int i)
    {
        int h = abs(key) % size;

        // 使用固定种子，保证每次探测结果一致
        srand(abs(key));

        int offset = 0;

        for (int j = 0; j <= i; j++)
        {
            offset = rand() % size;
        }

        return (h + offset) % size;
    }


    // ========================================================
    // 通用插入函数
    //
    // method:
    // 1 = 线性探测
    // 2 = 平方探测
    // 3 = 双散列
    // 4 = 伪随机序列
    // ========================================================

    bool insert(int key, int method)
    {
        for (int i = 0; i < size; i++)
        {
            int index;

            switch (method)
            {
                case 1:
                    index = linearProbe(key, i);
                    break;

                case 2:
                    index = quadraticProbe(key, i);
                    break;

                case 3:
                    index = doubleHash(key, i);
                    break;

                case 4:
                    index = pseudoRandomProbe(key, i);
                    break;

                default:
                    return false;
            }

            if (table[index].state == EMPTY ||
                table[index].state == DELETED)
            {
                table[index].key = key;
                table[index].state = OCCUPIED;

                return true;
            }
        }

        return false;
    }


    // ========================================================
    // 查找
    // ========================================================

    bool search(int key, int method)
    {
        for (int i = 0; i < size; i++)
        {
            int index;

            switch (method)
            {
                case 1:
                    index = linearProbe(key, i);
                    break;

                case 2:
                    index = quadraticProbe(key, i);
                    break;

                case 3:
                    index = doubleHash(key, i);
                    break;

                case 4:
                    index = pseudoRandomProbe(key, i);
                    break;

                default:
                    return false;
            }

            if (table[index].state == EMPTY)
            {
                return false;
            }

            if (table[index].state == OCCUPIED &&
                table[index].key == key)
            {
                return true;
            }
        }

        return false;
    }


    // ========================================================
    // 删除
    // ========================================================

    bool remove(int key, int method)
    {
        for (int i = 0; i < size; i++)
        {
            int index;

            switch (method)
            {
                case 1:
                    index = linearProbe(key, i);
                    break;

                case 2:
                    index = quadraticProbe(key, i);
                    break;

                case 3:
                    index = doubleHash(key, i);
                    break;

                case 4:
                    index = pseudoRandomProbe(key, i);
                    break;

                default:
                    return false;
            }

            if (table[index].state == EMPTY)
            {
                return false;
            }

            if (table[index].state == OCCUPIED &&
                table[index].key == key)
            {
                table[index].state = DELETED;

                return true;
            }
        }

        return false;
    }


    // ========================================================
    // 输出散列表
    // ========================================================

    void display()
    {
        cout << "\n========== 开放定址散列表 ==========\n";

        for (int i = 0; i < size; i++)
        {
            cout << "[" << setw(2) << i << "] ";

            if (table[i].state == EMPTY)
            {
                cout << "EMPTY";
            }
            else if (table[i].state == DELETED)
            {
                cout << "DELETED";
            }
            else
            {
                cout << table[i].key;
            }

            cout << endl;
        }
    }
};


// ============================================================
// 四、测试各种散列函数
// ============================================================

void testHashFunctions()
{
    int keys[] = {
        12, 25, 37, 48, 59
    };

    int m = 11;

    cout << "\n========================================\n";
    cout << "        散列函数测试\n";
    cout << "========================================\n";

    cout << "\n1. 除留余数法：\n";

    for (int key : keys)
    {
        cout << "key = " << key
             << " -> "
             << hash_Mod(key, m)
             << endl;
    }


    cout << "\n2. 直接定址法：\n";

    for (int key : keys)
    {
        cout << "key = " << key
             << " -> "
             << hash_Direct(key, m)
             << endl;
    }


    cout << "\n3. 数字分析法：\n";

    for (int key : keys)
    {
        cout << "key = " << key
             << " -> "
             << hash_DigitalAnalysis(key, m)
             << endl;
    }


    cout << "\n4. 平方取中法：\n";

    for (int key : keys)
    {
        cout << "key = " << key
             << " -> "
             << hash_MidSquare(key, m)
             << endl;
    }
}


// ============================================================
// 五、测试拉链法
// ============================================================

void testChainedHash()
{
    cout << "\n\n========================================\n";
    cout << "        拉链法测试\n";
    cout << "========================================\n";

    ChainedHashTable ht(7);

    // 插入
    ht.insert(10);
    ht.insert(17);
    ht.insert(24);
    ht.insert(31);
    ht.insert(5);
    ht.insert(12);

    ht.display();


    // 查找
    cout << "\n查找 24：";

    if (ht.search(24))
        cout << "找到\n";
    else
        cout << "未找到\n";


    cout << "查找 100：";

    if (ht.search(100))
        cout << "找到\n";
    else
        cout << "未找到\n";


    // 删除
    cout << "\n删除 24：";

    if (ht.remove(24))
        cout << "删除成功\n";
    else
        cout << "删除失败\n";


    ht.display();
}


// ============================================================
// 六、测试开放定址法
// ============================================================

void testOpenAddress()
{
    cout << "\n\n========================================\n";
    cout << "        开放定址法测试\n";
    cout << "========================================\n";


    // --------------------------------------------------------
    // 线性探测
    // --------------------------------------------------------

    cout << "\n----- 线性探测法 -----\n";

    OpenAddressHashTable linearTable(11);

    int keys[] = {
        12, 23, 34, 45, 56, 67
    };

    for (int key : keys)
    {
        linearTable.insert(key, 1);
    }

    linearTable.display();


    cout << "\n查找 34：";

    if (linearTable.search(34, 1))
        cout << "找到\n";
    else
        cout << "未找到\n";


    cout << "删除 34：";

    if (linearTable.remove(34, 1))
        cout << "删除成功\n";
    else
        cout << "删除失败\n";

    linearTable.display();


    // --------------------------------------------------------
    // 平方探测
    // --------------------------------------------------------

    cout << "\n----- 平方探测法 -----\n";

    OpenAddressHashTable quadraticTable(11);

    for (int key : keys)
    {
        quadraticTable.insert(key, 2);
    }

    quadraticTable.display();


    // --------------------------------------------------------
    // 双散列
    // --------------------------------------------------------

    cout << "\n----- 双散列法 -----\n";

    OpenAddressHashTable doubleHashTable(11);

    for (int key : keys)
    {
        doubleHashTable.insert(key, 3);
    }

    doubleHashTable.display();


    // --------------------------------------------------------
    // 伪随机序列
    // --------------------------------------------------------

    cout << "\n----- 伪随机序列法 -----\n";

    OpenAddressHashTable randomTable(11);

    for (int key : keys)
    {
        randomTable.insert(key, 4);
    }

    randomTable.display();
}


// ============================================================
// 七、主函数
// ============================================================

int main()
{
    // 测试散列函数
    testHashFunctions();

    // 测试拉链法
    testChainedHash();

    // 测试开放定址法
    testOpenAddress();

    return 0;
}