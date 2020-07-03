#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <iostream>

using namespace std;

#define MAX 100
#define MAX1 1000
#define MAX2 10000
#define MAX3 100000

struct node
{
    int left, right;
    struct node *next;
};
struct Stack
{
    node *top;
};
FILE *f;

//------------------------------------------
void textColor(int a, int k);
void wait(int seconds);

// nhập dãy số cần sắp xếp vào file Sinhngaunhien.bin
void Sinh(int &n);
void NhapTuBanPhim(int &n);

// hiện dữ liệu mảng
void hienmang(int a[], int n);

// đọc ghi file
// đẩy dãy số chưa sắp xếp từ file Sinhngaunhien.bin lên mảng
void FileToArray(int n, int a[]);
// ghi kết quả sắp xếp vào file KetquaSapxep.bin
void ghiKQmang(int a[], int n);
// đẩy kết quả sắp xếp từ file KetquaSaoxep lên mảng
void docKQsapxepMang(int a[],int n);

void hoanvi(int &a, int &b);

// quick sort bằng mảng
void mophongthuattoan(int a[], int n, int L, int R, int lo, int hi, int pivot);
int partition (int arr[], int n, int low, int high);
void quickSortmang(int arr[], int n, int low, int high);

// quicksort bằng stack
void quickSortStack(int a[], int n); //quicksort với ptu chốt là ptu giữa mảng
void mophongthuattoan(int a[], int n, Stack S, node *P, int L, int R, int lo, int hi, int pivot);
void quickSortStackPtuCuoi(int a[], int n);

//------------------------------------------
// khoi tao stack
void InitStack(Stack &S)
{
    S.top=NULL;
}
// kiem tra stack co rong hay khong
int StackIsEmpty(Stack &S)
{
    return (S.top==NULL);
}
//them 1 phan tu vao stack
void Push(Stack &S, int x, int y)
{
    node *p;
    p = new node;
    if(p == NULL)
    {
        printf("\nKhong du bo nho!");
        exit(1);
    }
    p->left=x;
    p->right=y;
    p->next=S.top;
    S.top=p;
}
// lay phan tu dau khoi stack
node *Pop(Stack &S)
{
    node *p;
    if(StackIsEmpty(S))
    {
        printf("\nStack rong!");
        return NULL;
    }
    p=S.top;
    S.top=p->next;
    return p;
}
//xem phan tu dau danh sach
node *Top(Stack S)
{
    node *p;
    if(StackIsEmpty(S))
    {
        printf("\nStack rong!");
        return NULL;
    }
    p=S.top;
    return p;
}

void textColor(int a, int k)
{
    HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor, k);
    printf("%d",a);
    SetConsoleTextAttribute(hConsoleColor, 15);
}

void wait(int seconds)
{
	clock_t ew;
	ew = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < ew) {}
}

void Sinh(int &n)
{
    f=fopen("Sinhngaunhien.bin","w");
    int r;
soptu:
    printf("\n\tNhap so luong ptu: "); scanf("%d", &n);
    if (n<=0){
        printf("\n\tPhai nhap so duong.");
        goto soptu;
    }
    printf("\n\t\t");
    srand((int)time(0));
    for(int i = 0; i < n; i++){
        r = rand()%100;
        printf("%d ",r);
        fwrite(&r,sizeof(r),1,f);
    }
    fclose(f);
    printf("\n\n\tDa luu day so sinh ngau nhien vao file Sinhngaunhien.bin\n");
}

void hienmang(int a[], int n)
{
    printf("\n\t\t");
    for (int i=0; i<n; i++)
    {
        printf("%d  ", a[i]);
    }
}

void NhapTuBanPhim(int &n)
{
    int r;
    f=fopen("Sinhngaunhien.bin","w");
soptu:
    printf("\n\tNhap so luong ptu: "); scanf("%d", &n);
    if (n<=0){
        printf("\n\tPhai nhap so duong.");
        goto soptu;
    }
    for(int i=0; i<n; i++)
    {
        printf("\t[%d]: ",i);
        scanf("%d",&r);
        fwrite(&r,sizeof(r),1,f);
    }
    fclose(f);
    printf("\n\tDa luu day so vua nhap vao file Sinhngaunhien.bin\n");
}

void FileToArray(int n, int a[])
{
    f=fopen("Sinhngaunhien.bin","rb");
    if(f==NULL)
    {
        printf("\n\tChua co du lieu!");
        return;
    }

    int r;

    for (int i=0; i<n;i++)
    {
        fread(&r,sizeof(r),1,f);
        a[i]=r;
    }
    fclose(f);
    hienmang(a,n);
}

void ghiKQmang(int a[], int n)
{
    f=fopen("KetquaSapxep.bin","w");
    for (int i=0; i<n; i++)
    {
        fwrite(&a[i],sizeof(a[i]),1,f);
    }
    fclose(f);
    printf("\n\tDa luu ket qua vao file KetquaSapxep.bin");
}

void mophongthuattoan(int a[], int n, int L, int R, int lo, int hi, int pivot)
{
    system("cls");
    printf("\n\t\t--- MO PHONG QUICK SORT TANG DAN BANG MANG ---\n",n);
    printf("\n Cac phan tu cua mang:\n\n\t");
    for (int i=0; i<n; i++){
        if (i == lo && lo!=-1){
            printf("[ ");
            if (lo == L || lo == R) textColor(a[i],48);
            else if (lo == L == R) textColor(a[i],39);
            else textColor(a[i],7);
        }
        else if (i == hi && hi!=-1){
            if (hi == pivot) textColor(a[i],12);
            else textColor(a[i],7);
            printf(" ]");
        }
        else if (i == pivot && pivot!=-1) textColor(a[i],12);
        else if ((i == L && L!=-1) || (i == R && R!=-1)){
            if (L == R) textColor(a[i],39);
            else textColor(a[i],48);
        }
        else textColor(a[i],7);
        printf("\t");
    }
    printf("\n\n a[");
    textColor(n,10);
    printf("]\t");
    for (int i=0; i<n; i++)
    {
        if (i == lo) printf("L=");
        if (i == hi) printf("H=");
        if (i == L) printf("l=");
        if (i == R) printf("r=");
        textColor(i,7);
        printf("\t");
    }
    printf("\n\n\n Partition: ",lo,hi);
    if (lo != -1 && hi != -1) printf("[%d, %d]",lo,hi);
    printf("\t\tPivot: ");
    if (pivot != -1) printf("%d",a[pivot]);

    printf("\n\n PROCESS ");
}

void hoanvi(int &a, int &b)
{
    int t=a; a=b; b=t;
}

//phân đoạn trg mảng
int partition (int arr[], int n, int low, int high)
{
    int pivot = arr[high];
    int left = low;
    int right = high - 1;
    mophongthuattoan(arr,n,-1,-1,low,high,-1);
    getch();
    printf("\n\n\tTa co: \tL = %d\n\t\tH = %d\n\t\tPivot = a[%d] = %d\n\t\tl = %d\n\t\tr = %d - 1 = %d",low,high,high,pivot,left,high,high-1);
    getch();
    //getch();
    mophongthuattoan(arr,n,left,right,low,high,high);
    getch();
    while(true){
        while(left <= right && arr[left] < pivot)
        {
            printf("\n\n\tDieu kien l=%d <= r=%d va a[%d]=%d < pivot=%d    TRUE",left,right,left,arr[left],pivot);
            getch();
            printf(" => l++ => l=%d",left+1);
            getch();
            left++; // Tìm phần tử >= arr[pivot]
            mophongthuattoan(arr,n,left,right,low,high,high);
            getch();
        }
        printf("\n\n\tDieu kien l=%d <= r=%d va a[%d]=%d < pivot=%d    FALSE",left,right,left,arr[left],pivot);
        getch();
        printf(" => l=%d",left);
        getch();
        while(right >= left && arr[right] > pivot)
        {
            printf("\n\n\tDieu kien r=%d >= l=%d va a[%d]=%d > pivot=%d    TRUE",right,left,right,arr[right],pivot);
            getch();
            printf(" => r-- => r=%d",right-1);
            getch();
            right--; // Tìm phần tử <= arr[pivot]
            mophongthuattoan(arr,n,left,right,low,high,high);
            getch();
        }
        printf("\n\n\tDieu kien r=%d >= l=%d va a[%d]=%d > pivot=%d    FALSE",right,left,right,arr[right],pivot);
        getch();
        printf(" => r=%d",right);
        getch();
        if (left >= right)
        {
            printf("\n\n\tl=%d >= r=%d --> Dung duyet mang.",left,right);
            getch();
            break; // Đã duyệt xong thì thoát vòng lặp
        }
        printf("\n\n\tXuat hien truong hop a[%d] >= pivot >= a[%d] : %d >= %d >= %d",left,right,arr[left],pivot,arr[right]);
        getch();
        printf("\n\n\t--> hoan vi a[%d], a[%d]",left,right);
        getch();
        hoanvi(arr[left], arr[right]); // Nếu chưa xong, đổi chỗ
        printf("\t => a[%d] = %d, a[%d] = %d",left,arr[left],right,arr[right]);
        getch();
        mophongthuattoan(arr,n,left,right,low,high,high);
        getch();
        printf("\n\n\tl++ => l=%d",left+1);
        getch();
        left++; // Vì left hiện tại đã xét, nên cần tăng
        mophongthuattoan(arr,n,left,right,low,high,high);
        getch();
        printf("\n\n\tr-- => r=%d",right-1);
        getch();
        right--; // Vì right hiện tại đã xét, nên cần giảm
        mophongthuattoan(arr,n,left,right,low,high,high);
        getch();
    }
    printf("\n\n\tXuat hien truong hop r=%d <= l=%d, a[%d]=%d > pivot=%d",right,left,left,arr[left],pivot);
    getch();
    printf("\n\n\t--> hoan vi a[%d], a[%d]",left,high);
    getch();
    hoanvi(arr[left], arr[high]);
    printf("\t => a[%d] = %d, a[%d] = %d",left,arr[left],high,arr[high]);
    getch();
    mophongthuattoan(arr,n,left,right,low,high,left);
    getch();
    return left; // Trả về chỉ số sẽ dùng để chia đổi mảng
}
//hàm quicksort
void quickSortmang(int arr[], int n, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, n, low, high);
        quickSortmang(arr, n, low, pi - 1);
        quickSortmang(arr, n, pi + 1, high);
    }
}

void quickSortStack(int a[], int n) //An
{
    int L, R, i, j, x;
    Stack S;
    node *P;

    InitStack(S);
    Push(S,0,n-1);

    do
    {
        P = Pop(S);
        L = P->left;
        R = P->right;
        do
        {
            i = L;
            j = R;
            x = a[(L+R)/2];
            do
            {
                while (a[i]<x) i++;
                while (a[j]>x) j--;
                if (i<=j)
                {
                    hoanvi(a[i], a[j]);
                    i++;
                    j--;
                }
            } while (i <= j);
            if (i<R) Push(S,i,R);
            R = j;
        } while (L<R);
    } while (S.top!=NULL);
    hienmang(a,n);
}

void mophongthuattoan(int a[], int n, Stack S, node *P, int L, int R, int lo, int hi, int pivot)
{
    system("cls");
    printf("\n\t\t--- MO PHONG QUICK SORT TANG DAN BANG STACK ---\n",n);
    printf("\n Cac phan tu cua mang:\n\n\t");
    for (int i=0; i<n; i++){
        if (i == L && L!=-1){
            printf("[ ");
            if (L == lo || L == hi) textColor(a[i],48);
            else if (L == lo == hi) textColor(a[i],39);
            else textColor(a[i],7);
        }
        else if (i == R && R!=-1){
            if (R == pivot) textColor(a[i],12);
            else textColor(a[i],7);
            printf(" ]");
        }
        else if (i == pivot && pivot!=-1) textColor(a[i],12);
        else if ((i == lo && lo!=-1) || (i == hi && hi!=-1)){
            if (lo == hi) textColor(a[i],39);
            else textColor(a[i],48);
        }
        else textColor(a[i],7);
        printf("\t");
    }
    printf("\n\n a[");
    textColor(n,10);
    printf("]\t");
    for (int i=0; i<n; i++)
    {
        if (i == L) printf("L=");
        if (i == R) printf("R=");
        if (i == lo) printf("i=");
        if (i == hi) printf("j=");
        textColor(i,7);
        printf("\t");
    }
    printf("\n");
    node *p;
    if (StackIsEmpty(S)) printf("\n |     |");
    else
        for (p=S.top; p!=NULL; p=p->next)
        {
            printf("\n |[%d,%d]|",p->left,p->right);
        }
    printf("\n %s\t%s","Stack S","Part P:");
    if (P!=NULL)
    {
        printf("\t[%d,%d]\tPivot:",P->left,P->right);
        if (pivot != -1) printf(" %d",a[pivot]);
    }
    else printf("\t\tPivot:");
    printf("\n\n PROCESS ");
    if (P != NULL) printf("- PARTITION [%d,%d]",P->left,P->right);
}

void quickSortStackPtuCuoi(int a[], int n) //An
{
    int dem=0;
    int L, R, i, j;
    Stack S;
    node *P = NULL;

    InitStack(S); //tạo stack rỗng
    mophongthuattoan(a,n,S,P,-1,-1,-1,-1,-1);
    printf("\n\n\tDua [%d,%d] vao Stack.",0,n-1);
    Push(S,0,n-1); //đưa chỉ số phần tử đầu và phần tử cuối của mảng a vào stack
    getch();
    mophongthuattoan(a,n,S,P,-1,-1,-1,-1,-1);
    printf("\n\n\tDa dua [%d,%d] vao Stack.",0,n-1);
    getch();
    do
    {
        printf("\n\n\tLay phan tu top [%d, %d] ra khoi Stack roi gan vao P.",Top(S)->left,Top(S)->right);
        getch();
        P = Pop(S); //lấy ra phần tử đầu của stack và bỏ vào P
        mophongthuattoan(a,n,S,P,P->left,P->right,-1,-1,-1);
        getch();
        L = P->left; //chỉ số phần tử đầu của đoạn cần sắp xếp
        R = P->right; //chỉ số phần tử cuối của đoạn cần sắp xếp
        i = L; //biến duyệt mảng từ trái sang phải
        j = R-1; //biến duyệt mảng từ phải sang trái
        printf("\n\n\tTa co:\tL = %d\n\t\tR = %d\n\t\ti = L = %d\n\t\tj = R - 1 = %d\n\t\tPivot = %d",L,R,i,j,a[R]);
        getch();
        mophongthuattoan(a,n,S,P,L,R,i,j,R);
        getch();
        while (true)
        {
            while (i<=j && a[i]<a[R])
            {
                printf("\n\n\tDieu kien i=%d <= j=%d va a[%d]=%d < pivot=%d    TRUE",i,j,i,a[i],a[R]);
                getch();
                printf(" => i++ => i=%d",i+1);
                getch();
                i++; //bỏ qua các phần tử a[i] nhỏ hơn phần tử chốt, nếu a[i] lớn hơn hoặc bằng phần tử chốt thì dừng vòng lặp này
                mophongthuattoan(a,n,S,P,L,R,i,j,R);
                getch();
            }
            printf("\n\n\tDieu kien i=%d <= j=%d va a[%d]=%d < pivot=%d    FALSE",i,j,i,a[i],a[R]);
            getch();
            printf(" => i=%d",i);
            getch();
            while (j>=i && a[j]>a[R])
            {
                printf("\n\n\tDieu kien j=%d >= i=%d va a[%d]=%d > pivot=%d    TRUE",j,i,j,a[j],a[R]);
                getch();
                printf(" => j-- => j=%d",j-1);
                getch();
                j--; //bỏ qua các phần tử a[j] lớn hơn phần tử chốt, neu a[j] nhỏ hơn hoặc bằng phần tử chốt thi dung vong lap nay
                mophongthuattoan(a,n,S,P,L,R,i,j,R);
                getch();
            }
            printf("\n\n\tDieu kien j=%d >= i=%d va a[%d]=%d > pivot=%d    FALSE",j,i,j,a[j],a[R]);
            getch();
            printf(" => j=%d",j);
            getch();
            if (i>=j)
            {
                printf("\n\n\ti=%d >= j=%d --> Dung duyet mang.",i,j);
                getch();
                break; //i và j gặp nhau => thoát vòng lặp
            }
            printf("\n\n\tXuat hien truong hop a[%d] >= pivot >= a[%d] : %d >= %d >= %d",i,j,a[i],a[R],a[j]);
            getch();
            printf("\n\n\t--> hoan vi a[%d], a[%d]",i,j);
            getch();
            //xuất hiện trường hợp a[i] >= phần tử chốt >= a[j] => hoán vị a[i],a[j]
            hoanvi(a[i], a[j]);
            dem++;
            printf("\t => a[%d] = %d, a[%d] = %d",i,a[i],j,a[j]);
            getch();
            mophongthuattoan(a,n,S,P,L,R,i,j,R);
            getch();
            printf("\n\n\ti++ => i=%d",i+1);
            getch();
            i++; //lúc này a[i] nhỏ hơn phần tử chốt => tăng i để tiếp tục duyệt
            mophongthuattoan(a,n,S,P,L,R,i,j,R);
            getch();
            printf("\n\n\tj-- => j=%d",j-1);
            getch();
            j--; //lúc này a[j] lớn hơn phần tử chốt => giảm j để tiếp tục duyệt
            mophongthuattoan(a,n,S,P,L,R,i,j,R);
            getch();
        }
        if (a[i]>a[R])
        {
            printf("\n\n\tXuat hien truong hop j=%d <= i=%d, a[%d]=%d > pivot=%d",j,i,i,a[i],a[R]);
            getch();
            printf("\n\n\t--> hoan vi a[%d], a[%d]",i,R);
            getch();
            //xuất hiện trường hợp j<=i, a[i] lớn hơn phần tử chối => hoán vị a[i] và phần tử chốt
            hoanvi(a[i], a[R]);
            dem++;
            printf("\t => a[%d] = %d, a[%d] = %d",i,a[i],R,a[R]);
            getch();
            mophongthuattoan(a,n,S,P,L,R,i,j,i);
            getch();
        }
        if (L<i-1)
        {
            printf("\n\n\tDoan a[%d] - a[%d] gom cac phan tu nho hon phan tu chot pivot = %d.",L,i-1,a[i]);
            getch();
            printf("\n\t\t=> Dua [%d, %d] vao stack S.",L,i-1);
            getch();
            Push(S,L,i-1); //đưa chỉ số phần tử đầu và phần tử cuối của đoạn nhỏ hơn a vào stack
            mophongthuattoan(a,n,S,P,L,R,i,j,i);
            printf("\n\n\tDa dua [%d,%d] vao stack S.",L,i-1);
            getch();
        }
        if (i+1<R)
        {
            printf("\n\n\tDoan a[%d] - a[%d] gom cac phan tu lon hon phan tu chot pivot = %d.",i+1,R,a[i]);
            getch();
            printf("\n\n\tDua [%d,%d] vao stack.",i+1,R);
            getch();
            Push(S,i+1,R); //đưa chỉ số phần tử đầu và phần tử cuối của đoạn lớn hơn a vào stack
            mophongthuattoan(a,n,S,P,L,R,i,j,i);
            printf("\n\n\tDa dua [%d,%d] vao stack.",i+1,R);
            getch();
        }
    } while (!StackIsEmpty(S));
    mophongthuattoan(a,n,S,P,-1,-1,-1,-1,-1);
    printf("\n\n\tSo lan thuc hien sap xep (hoan vi): %d", dem);
}

void docKQsapxepMang(int a[],int n)
{
    f=fopen("KetquaSapxep.bin","rb");
    for (int i=0; i<n; i++)
        fread(&a[i],sizeof(a[i]),1,f);
    fclose(f);
    printf("\n\tDoc ket qua sap xep tu file KetquaSapxep.bin");
    hienmang(a,n);
}

//
// Đánh giá thuật toán
//

void quickSortStack_code(int a[], int n)
{
    int L, R, i, j;
    Stack S;
    node *P = NULL;

    InitStack(S); //tạo stack rỗng
    Push(S,0,n-1); //đưa chỉ số phần tử đầu và phần tử cuối của mảng a vào stack

    do
    {
        P = Pop(S); //lấy ra phần tử đầu của stack và bỏ vào P
        L = P->left; //chỉ số phần tử đầu của đoạn cần sắp xếp
        R = P->right; //chỉ số phần tử cuối của đoạn cần sắp xếp
        i = L; //biến duyệt mảng từ trái sang phải
        j = R-1; //biến duyệt mảng từ phải sang trái

        while (true)
        {
            while (i<=j && a[i]<a[R]) i++;
            while (j>=i && a[j]>a[R]) j--;
            if (i>=j) break;
            hoanvi(a[i], a[j]);
            i++; //lúc này a[i] nhỏ hơn phần tử chốt => tăng i để tiếp tục duyệt
            j--; //lúc này a[j] lớn hơn phần tử chốt => giảm j để tiếp tục duyệt
        }
        if (a[i]>a[R]) hoanvi(a[i], a[R]);
        if (L<i-1) Push(S,L,i-1);
        if (i+1<R) Push(S,i+1,R);
    } while (!StackIsEmpty(S));
}

int part (int arr[], int n, int low, int high)
{
    int pivot = arr[high];
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && arr[left] < pivot) left++; // Tìm phần tử >= arr[pivot]
        while(right >= left && arr[right] > pivot) right--; // Tìm phần tử <= arr[pivot]
        if (left >= right) break;
        hoanvi(arr[left], arr[right]); // Nếu chưa xong, đổi chỗ
        left++; // Vì left hiện tại đã xét, nên cần tăng
        right--; // Vì right hiện tại đã xét, nên cần giảm
    }
    hoanvi(arr[left], arr[high]);
    return left; // Trả về chỉ số sẽ dùng để chia đổi mảng
}
//hàm quicksort
void quickSortArray_code(int arr[], int n, int low, int high)
{
    if (low < high)
    {
        int pi = part(arr, n, low, high);
        quickSortArray_code(arr, n, low, pi - 1);
        quickSortArray_code(arr, n, pi + 1, high);
    }
}

void hiendanhgia(int n)
{
    int a[n];
    clock_t bd, kt;
    double total_arr, total_stack;

    srand((int)time(0));
    for(int i = 0; i < n; i++) a[i] = rand();

    printf("\t%d\t",n);
    bd = clock();
    quickSortArray_code(a,n,0,n-1);
    kt = clock();
    total_arr = (double)(kt - bd)/CLOCKS_PER_SEC;
    printf("\t%.4lf (s)",total_arr);
    bd = clock();
    quickSortStack_code(a,n);
    kt = clock();
    total_stack = (double)(kt - bd)/CLOCKS_PER_SEC;
    printf("\t%.4lf (s)",total_stack);
}

void danhgiathuattoan()
{
    printf("\n\t\tDANH GIA DO PHUC TAP THUAT TOAN\n");
    printf("\n\tTT\tSo ptu\t\tARRAY (s)\tSTACK (s)");
    printf("\n________________________________________________________________");
    for (int i=0;i<10;i++)
    {
        printf("\n\t%d",i+1);
        hiendanhgia(MAX);
    }
    printf("\n________________________________________________________________");
    for (int i=10;i<20;i++)
    {
        printf("\n\t%d",i+1);
        hiendanhgia(MAX1);
    }
    printf("\n________________________________________________________________");
    for (int i=20;i<30;i++)
    {
        printf("\n\t%d",i+1);
        hiendanhgia(MAX2);
    }
    printf("\n________________________________________________________________");
    for (int i=30;i<40;i++)
    {
        printf("\n\t%d",i+1);
        hiendanhgia(MAX3);
    }
    printf("\n________________________________________________________________");
}

void menu()
{
    printf("\n\t _._._.____QUICK SORT____._._._ \n");
    printf("\t|                              |\n");
    printf("\t| 1. Mo phong bang mang        |\n");
    printf("\t| 2. Mo phong bang stack       |\n");
    printf("\t| 3. Ve menu chinh             |\n");
    printf("\t|______________________________|\n");
    printf("\n\t--> Hay chon chuc nang: ");
}

int main()
{
    int chon;
    int n;
    int a[MAX];
    clock_t start_t, end_t;
    double total_arr, total_stack;

    do
    {
menuchinh:
        system("cls");
        printf("\n\t _____MO PHONG QUICK SORT______ \n");
        printf("\t|                              |\n");
        printf("\t| 1. Nhap du lieu tu ban phim  |\n");
        printf("\t| 2. Sinh so ngau nhien        |\n");
        printf("\t| 3. Danh gia                  |\n");
        printf("\t| 4. Thoat                     |\n");
        printf("\t|______________________________|\n");
        printf("\n\t--> Hay chon chuc nang: ");
        scanf("%d", &chon);
        switch(chon)
        {
            case 1:
                total_arr = total_stack = 0.0;
                NhapTuBanPhim(n);
                system("pause");
                while(1)
                    {
                        int cn;
                        system("cls");
                        printf("\n\tDoc mang tu file Sinhngaunhien.bin");
                        FileToArray(n,a);
                        printf("\n\n");
                        menu();
                        fflush(stdin);
                        scanf("%d", &cn);
                        switch(cn)
                        {
                            case 1:
                                //xử lý sắp xếp mảng, mô phỏng
                                printf("\n\n\t--> Nhan ENTER de bat dau chuong trinh mo phong thuat toan Quick Sort bang mang.");
                                getch();
                                start_t=clock();
                                mophongthuattoan(a,n,-1,-1,-1,-1,-1);
                                getch();
                                quickSortmang(a,n,0,n-1);
                                end_t=clock();
                                printf("\n\n\tMang da duoc sap xep xong.");
                                printf("\n\n Ket thuc chuong trinh mo phong.");
                                total_arr=(double)(end_t - start_t)/CLOCKS_PER_SEC;
                                printf("\n\tTong thoi gian thuc hien: %lf (s)", total_arr);
                                ghiKQmang(a,n);
                                docKQsapxepMang(a,n);
                                printf("\n\tMo phong bang mang: \t%lf (s)\n\tMo phong bang stack:\t%lf (s)", total_arr,total_stack);
                                printf("\n\n\tNhan ENTER de tro lai menu.");
                                getch();
                                break;
                            case 2:
                                //xư ly sap xep, mo phong
                                printf("\n\n\t--> Nhan ENTER de bat dau chuong trinh mo phong thuat toan Quick Sort.");
                                getch();
                                start_t=clock();
                                quickSortStackPtuCuoi(a,n);
                                end_t=clock();
                                printf("\n\n\tMang da duoc sap xep xong.");
                                printf("\n\n Ket thuc chuong trinh mo phong.");
                                total_stack=(double)(end_t - start_t)/CLOCKS_PER_SEC;
                                printf("\n\tTong thoi gian thuc hien: %lf (s)\n", total_stack);
                                //ghi mảng đã sắp xếp vào file
                                ghiKQmang(a,n);
                                docKQsapxepMang(a,n);
                                printf("\n\tMo phong bang mang: %lf (s)\n\tMo phong bang stack: %lf (s)", total_arr,total_stack);
                                printf("\n\n\tNhan ENTER de tro lai menu.");
                                getch();
                                break;
                            case 3:
                                goto menuchinh;
                        }
                    }
            case 2:
                total_arr = total_stack = 0.0;
                Sinh(n);
                system("pause");
                while(1)
                    {
                        int cn;
                        system("cls");
                        printf("\n\tDoc mang tu file Sinhngaunhien.bin");
                        FileToArray(n,a);
                        printf("\n\n");
                        menu();
                        fflush(stdin);
                        scanf("%d", &cn);
                        switch(cn)
                        {
                            case 1:
                                //xử lý sắp xếp mảng, mô phỏng
                                printf("\n\n\t--> Nhan ENTER de bat dau chuong trinh mo phong thuat toan Quick Sort bang mang.");
                                getch();
                                start_t=clock();
                                mophongthuattoan(a,n,-1,-1,-1,-1,-1);
                                getch();
                                quickSortmang(a,n,0,n-1);
                                end_t=clock();
                                printf("\n\n\tMang da duoc sap xep xong.");
                                printf("\n\n Ket thuc chuong trinh mo phong.");
                                total_arr=(double)(end_t - start_t)/CLOCKS_PER_SEC;
                                printf("\n\tTong thoi gian thuc hien: %lf (s)\n", total_arr);
                                ghiKQmang(a,n);
                                docKQsapxepMang(a,n);
                                printf("\n\tMo phong bang mang: %lf (s)\n\tMo phong bang stack: %lf (s)", total_arr,total_stack);
                                printf("\n\n\tNhan ENTER de tro lai menu.");
                                getch();
                                break;

                            case 2:
                                //xu ly sap xep, mo phong
                                printf("\n\n\t--> Nhan ENTER de bat dau chuong trinh mo phong thuat toan Quick Sort.");
                                getch();
                                start_t=clock();
                                //quickSortStack(a,n);
                                quickSortStackPtuCuoi(a,n);
                                end_t=clock();
                                printf("\n\n\tMang da duoc sap xep xong.");
                                printf("\n\n Ket thuc chuong trinh mo phong.");
                                total_stack=(double)(end_t - start_t)/CLOCKS_PER_SEC;
                                printf("\n\tTong thoi gian thuc hien: %lf (s)\n", total_stack);
                                //ghi mảng đã sắp xếp vào file
                                ghiKQmang(a,n);
                                docKQsapxepMang(a,n);
                                printf("\n\tMo phong bang mang: %lf (s)\n\tMo phong bang stack: %lf (s)", total_arr, total_stack);
                                printf("\n\n\tNhan ENTER de tro lai menu.");
                                getch();
                                break;
                            case 3:
                                goto menuchinh;
                        }
                    }
            case 3:
                danhgiathuattoan();
                printf("\n\n\tNhan ENTER de tro lai menu.");
                getch();
                break;
            case 4: return(0);
        }
    } while(1);
    getch();
    return 0;
}
