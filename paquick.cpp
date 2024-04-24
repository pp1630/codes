#include<bits/stdc++.h>
#include <omp.h>
#include<iomanip>


using namespace std;

int partition(int arr[],int s, int e){
    
    int pivot = arr[s];
    int cnt = 0;
    for(int i=s+1;i<=e;i++){
        if(arr[i] <= pivot){
            cnt++;
        }
    }
    int pivotin = s+cnt;
    swap(arr[s],arr[pivotin]);
    int i =s;
    int j =e;
    
    while(i < pivotin && j>pivotin){
        while(arr[i] <= arr[pivotin]){
            i++;
        }
        
        while(arr[j] > arr[pivotin]){
            j--;
        }
        
        if( i<pivotin && j > pivotin){
            swap(arr[i],arr[j]);
        }
    }
    return pivotin;
}


void quick_sort(int arr[], int s, int e){
    
    if(s>=e){
        return;
    }
    
    int p = partition(arr,s,e);
    quick_sort(arr,s,p-1);
    quick_sort(arr,p+1,e);
    
}

void par_quick_sort(int arr[], int s, int e){
    
    if(s>=e){
        return;
    }
    
    int p = partition(arr,s,e);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            par_quick_sort(arr,s,p-1);
        }
        
        #pragma omp section
        {
            par_quick_sort(arr,p+1,e);
        }
            
        
    }
    
}

void print_array(int arr[],int n){
    for(int i=0;i<n;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    int n;
    cout << "Enter n : ";
    cin >> n;
    int array[n];
    int arraycp[n];
    for(int i=0;i<n;i++){
        cin >> array[i];
        arraycp[i] = array[i];
    }
    print_array(array,n);
    clock_t start = clock();
    quick_sort(array,0,n-1);
    clock_t end = clock();
    print_array(array,n);
    cout << "TIME take sequential : " << ((double)(end-start)/CLOCKS_PER_SEC)*1000 <<"ms" << endl;
    cout << endl<<endl;
    print_array(arraycp,n);
    clock_t pstart = clock();
    quick_sort(arraycp,0,n-1);
    clock_t pend = clock();
    print_array(arraycp,n);
    cout << "TIME take parallel : " << ((double)(pend-pstart)/CLOCKS_PER_SEC)*1000 <<"ms" << endl;
    return 0;
    
}