#include<bits/stdc++.h>
#include <omp.h>
#include<cstdlib>
#include<time.h>


using namespace std;
void print_arr(int arr[],int n){
    for(int i=0;i<n;i++){
        cout << arr[i] << " " ;
    }
    cout << endl;
}

void merge(int arr[],int s, int e){
    int mid = (s+e)/2;
    int len1 = mid - s + 1;
    int len2 = e - mid;
    
    int first[len1];
    int second[len2];
    
    int mainindex = s;
    for(int i=0;i<len1;i++){
        first[i] = arr[mainindex++];
    }
    
    mainindex = mid+1;
    for(int i=0;i<len2;i++){
        second[i] = arr[mainindex++];
    }
    
    int in1 =0;
    int in2 =0;
    mainindex = s;
    while(in1 < len1 && in2 < len2){
        if(first[in1] > second[in2]){
            arr[mainindex++] = second[in2++];
        }
        
        else{
            arr[mainindex++] = first[in1++];
        }
    }
    
    while(in1 < len1){
        arr[mainindex++] = first[in1++];
    }
    while(in2 < len2){
        arr[mainindex++] = second[in2++];
    }
}

void mergesort(int arr[], int s, int e){
    if(s>=e){
        return;
    }
    int mid = (s+e)/2;
    mergesort(arr,s,mid);
    mergesort(arr,mid+1,e);
    merge(arr,s,e);
}

void par_mergesort(int arr[], int s, int e){
    if(s>=e){
        return;
    }
    int mid = (s+e)/2;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            par_mergesort(arr,s,mid);
        }
        #pragma omp section
        {
            par_mergesort(arr,mid+1,e);
        }
    }
    
    merge(arr,s,e);
}

int main(){
    int n;
    cout << "Enter n : ";
    cin >> n;
    int array[n];
    int arrcpy[n];
    for(int i=0;i<n;i++){
        //cin >> array[i];
	array[i] = rand()%50;
        arrcpy[i] = array[i];
    }
    
    print_arr(array,n);
    clock_t start = clock();
    mergesort(array,0,n-1);
    clock_t end = clock();
    print_arr(array,n);
    cout<<"Time required : "<<((double)(end-start)/CLOCKS_PER_SEC)*1000<<" ms";
    cout << endl;
    cout << endl;
    print_arr(arrcpy,n);
    clock_t pstart = clock();
    par_mergesort(arrcpy,0,n-1);
    clock_t pend = clock();
    print_arr(arrcpy,n);
    cout<<"parallel Time required : "<<((double)(pend-pstart)/CLOCKS_PER_SEC)*1000<<" ms";

    return 0;
    
}