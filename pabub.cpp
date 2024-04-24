#include<bits/stdc++.h>
#include <omp.h>
#include<time.h>


using namespace std;

void print_arr(int arr[],int n){
    for(int i=0;i<n;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void bub(int arr[],int n){
    clock_t start = clock();
    for(int i=0;i<n-1;i++){
        bool flag = false;
        for(int j=0;j<n-i-1;j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j],arr[j+1]);
                flag = true;
            }
        }
        if(flag == false){
            break;
        }
    }
    clock_t stop = clock();
    cout << "time required sequential : " << (double)(stop-start) << "ms" << endl;
}

void pa_bub(int arr[],int n){
    clock_t start = clock();
    for(int i=0;i<n-1;i++){
        bool flag = false;
        #pragma omp parallel for
        for(int j=0;j<n-i-1;j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j],arr[j+1]);
                flag = true;
            }
        }
        if(flag == false){
            break;
        }
    }
    clock_t stop = clock();
    cout << "time required paralle : " << (double)(stop-start) << "ms" << endl;
    
}


int main(){
    int n;
    cout << "ENter n :";
    cin >> n;
    int array[n];
    int arraycp[n];
    for(int i=0;i<n;i++){
        cin >> array[i];
        arraycp[i] = array[i];
    }
    
    print_arr(array,n);
    cout << endl;
    bub(array,n);
    print_arr(array,n);
    cout << endl;
    cout << endl;
    print_arr(arraycp,n);
    cout << endl;
    pa_bub(arraycp,n);
    print_arr(arraycp,n);
    
    return 0;
    
}