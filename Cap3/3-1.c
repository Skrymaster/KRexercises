#include <stdio.h>

// caută x în v
// pentru testare
// int binsearch(int x, int v[], int n);


// int main(void){
//     int array[]={1,2,3,6,5,4,7,9,8};
//     int i;
//     for(i=(sizeof(array)/sizeof(int))-1; i>=0; --i)
//         printf("looking for %d. Index=%d\n",array[i],binsearch(array[i], array, sizeof(array)/sizeof(*array)));

//     return 0;
// }

int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n-1;
    
    while(low < high) {
        mid = (low+high)/2;
        if(x <= v[mid]) 
            high=mid;
        
        else 
            low = mid+1;
    }
    
    if (x == v[low])
        return low;
    else return -1;

}