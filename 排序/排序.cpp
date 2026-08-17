/* ═══════════════════════════════════════════════════════════════════
 * 排序算法
 * 经典排序方法：插入排序、交换排序、选择排序、堆排序、归并排序、基数排序
 * ═══════════════════════════════════════════════════════════════════ */

/* ─────────────────────────────────────────
 * 一、直接插入排序
 * ───────────────────────────────────────── */
void InsertSort(int A[], int n){
    int i,j,temp;
    for(i=1;i<n;i++)
        if(A[i]<A[i-1]){
            temp=A[i];
            for(j=i-1;j>=0 && A[j]>temp;--j)
                A[j+1]=A[j];
            A[j+1]=temp;
        }
}

/* ─── 1.1 带哨兵的直接插入排序 ─── */
void InsertSort2(int A[], int n){
    int i,j;
    for(i=2;i<=n;i++)
        if(A[i]<A[i-1]){
            A[0]=A[i];
            for(j=i-1;j>=1 && A[j]>A[0];--j)
                A[j+1]=A[j];
            A[j+1]=A[0];
        }
}

/* ─── 1.2 折半插入排序（优化版） ─── */
void InsertSort3(int A[], int n){
    int i,j，low,high,mid;
    for(i=2;i<=n;i++){
        A[0]=A[i];
        low=1;
        high=i-1;
        while(low<=high){
            mid=(low+high)/2;
            if(A[mid]>A[0])
                high=mid-1;
            else
                low=mid+1;
        }
        for(j=i-1;j>=low;--j)
            A[j+1]=A[j];
        A[low]=A[0];
    }
}

/* ─────────────────────────────────────────
 * 二、希尔排序
 * ───────────────────────────────────────── */
void ShellSort(int A[],int n){
    int d, i, j;
    for(d=n/2;d>=1;d=d/2)
        for(i=d+1; i<=n; ++i)
            if(A[i]<A[i-d]){
                A[0]=A[i];
                for(j=i-d; j>0 && A[j]>A[0]; j-=d)
                    A[j+d]=A[j];
                A[j+d]=A[0];
            }
}

/* ─────────────────────────────────────────
 * 三、冒泡排序
 * ───────────────────────────────────────── */
void swap(int &a, int &b){
    int temp=a;
    a=b;
    b=temp;
}

void BubbleSort(int A[], int n){
    for(int i=0;i<n-1;i++){
        bool flag=false;
        for(int j=n-1;j<i;j--){
            if(A[j-1]>A[j]){
                swap(A[j-1],A[j]);
                flag=true;
            }
        if(flag==false) return;
    }
}
/* ─────────────────────────────────────────
 * 四、快速排序
 * ───────────────────────────────────────── */
void Partition(int A[], int low, int high){
        int pivot=A[low];
        while(low<high){
            while(low<high && A[high]>=pivot) --high;
            A[low]=A[high];
            while(low<high && A[low]<=pivot) ++low;
            A[high]=A[low];
        }
        A[low]=pivot;
        return low;
}

void QuickSort(int A[], int low, int high){
        if(low<high){
            int pivotpos=Partition(A, low, high);
            QuickSort(A, low, pivotpos-1);
            QuickSort(A, pivotpos+1, high);
        }
}

/* ─────────────────────────────────────────
 * 五、简单选择排序
 * ───────────────────────────────────────── */
void SelectSort(int A[],int n){
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++)
            if(A[j]<A[min])min=j;
        if(min!=i)
            swap(A[i],A[min]);
    }
}

/* ─────────────────────────────────────────
 * 六、堆排序
 * ───────────────────────────────────────── */

/* ─── 6.1 建立大根堆 ─── */
void BuildMaxHeap(int A[], int len){
    for(int i=len/2;i>0;i--)
        HeadAdjust(A, i, len);
}

/* ─── 6.2 将以 k 为根的子树调整为大根堆 ─── */
void HeadAdjust(int A[], int k, int len){
    A[0]=A[k];
    for(int i=2*k;i<=len;i*=2){
        if(i<len && A[i]<A[i+1])
           i++;
        if(A[0]>=A[i]) break;
        else{
            A[k]=A[i];
            k=i;
        }
    }
    A[k]=A[0];
}

/* ─── 6.3 堆排序的完整逻辑 ─── */
void HeapSort(int A[], int len) {
    BuildMaxHeap(A, len);
    for (int i = len; i > 1; i--) {
        swap(A[1], A[i]);
        HeadAdjust(A, 1, i - 1);
    }
}

/* ─── 6.4 堆的插入和删除 ─── */
void InsertMaxHeap(int A[], int &n, int x){
    A[++n] = x;    // 插入到堆底
    int i = n;
    while(i > 1 && A[i / 2] < A[i]){
        swap(A[i / 2], A[i]);
        i /= 2;
    }
}

void DeleteMaxHeap(int A[], int &n){
    if(n == 0) return;  // 堆空
    A[1] = A[n];
    n--;
    int i = 1;
    int j = 2 * i;
    while(j <= n){
        if(j < n && A[j] < A[j + 1])
            j++;
        if(A[i] >= A[j]) break;
        swap(A[i], A[j]);
        i = j;
        j = 2 * i;
    }
}

/* ─────────────────────────────────────────
 * 七、归并排序
 * ───────────────────────────────────────── */
int *B=(int *)malloc(sizeof(int)*n);

void Merge(int A[], int low, int mid, int high){
    int i,j,k;
    for(k=low;k<=high;k++)
       B[k]=A[k];
    for(i=low,j=mid+1,k=i;i<=mid&&j<=high;k++){
        if(B[i]<B[j])
            A[k]=B[i++];
        else
            A[k]=B[j++];
    }
    while(i<=mid)
        A[k++]=B[i++];
    while(j<=high)
        A[k++]=B[j++];
}

void MergeSort(int A[], int low, int high){
    if(low<high){
        int mid=(low+high)/2;
        MergeSort(A, low, mid);
        MergeSort(A, mid+1, high);
        Merge(A, low, mid, high);
    }
}

/* ─────────────────────────────────────────
 * 八、基数排序
 * 按个位到高位依次分配，适用于非负整数
 * ───────────────────────────────────────── */
void RadixSort(int A[], int n){
    int maxValue = A[0];
    for (int i = 1; i < n; i++)
        if (A[i] > maxValue)
            maxValue = A[i];

    int *tmp = new int[n];
    int exp = 1;

    while (maxValue / exp > 0) {
        int count[10] = {0};

        for (int i = 0; i < n; i++)
            count[(A[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int digit = (A[i] / exp) % 10;
            tmp[--count[digit]] = A[i];
        }

        for (int i = 0; i < n; i++)
            A[i] = tmp[i];

        exp *= 10;
    }

    delete[] tmp;
}
