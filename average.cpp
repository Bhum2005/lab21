#include <iostream>
#include <cstdlib>
using namespace std;
int main(int index,char *argu[]){
    float sum;
    if(argu[1]==NULL){
        cout << "Please input numbers to find average.";
    }
    else{
        for(int i=0;i<index;i++){
        int num=atof(argu[i]);
        sum+=num;
    }
    cout << "---------------------------------" <<endl;
    cout << "Average of "<<index-1<<" numbers = "<<sum/(index-1)<<endl;
    cout << "---------------------------------" <<endl;
    }
}
