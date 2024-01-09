#include <iostream>
#include "capd/capdlib.h"
#include <cmath>
using namespace std;
using namespace capd;



IVector f(IVector x){
    
    IVector X(2);

    X[0] = 2*x[0];
    X[1] =  0.5*x[1];

    return X;

}



bool exitCondition(IVector N, IVector M){

    IVector Nl = N;
    Nl[0] = N[0].left();

    IVector Nr = N;
    Nr[0] = N[0].right();

    cout << "Nl= "<< Nl << endl;

    cout << "Nr = " << Nr << endl;
    
    cout << "f(Nl) = " <<f(Nl)[0] << endl;

    cout << "f(Nr) = " <<f(Nr)[0] << endl;

    cout << f(Nr)[0] - M[0] << endl;

    cout << f(Nl)[0]-M[0] << endl;

    interval I = (f(Nl)[0]-M[0])*(f(Nr)[0] - M[0]);
    if (not (I<0.0)) return false;
    
    cout << "Exit condition is satisfied."<<endl;

    return true;

}

interval part(interval x, int k, int i){
    return x.left()+i*(x.right()-x.left())/k+(x-x.left())/k;
}

bool entryCondition(IVector N, IVector M){

    int k=100;
    cout << M[1] << endl;


    for(int i=0; i<k;i++){
        IVector Nfragment = N;
        Nfragment[0] = part(N[0],k,i);

        cout << f(Nfragment)[1] << endl;
        if (not subsetInterior(f(Nfragment)[1], M[1])) return false;
    }

    cout << "Entry condition is satisfied." <<endl;
    return true;
}

bool covering(IVector N, IVector M){

    cout << "N0 is " << N << endl;
    cout << "N1 is " << M << endl;

    cout << "f_c(N0) = " << f(N) << endl;

    if (exitCondition(N,M)==false) return false;
    if(entryCondition(N,M)==false) return false;
    

    return true;
}

int main(){

 
    IVector N0(2),N1(2);

 

    DInterval Xaxis(-2,2);
    DInterval Yaxis(-2,4);

    //N0[0]= interval(0.63133, 0.63136);
    N0[0]= Xaxis;
    //N0[1] = interval(0.18940601,0.1894061);
    N0[1] = Yaxis;

    N1[0] = Xaxis;
    N1[1] = Yaxis;

   
    if (covering(N0,N0)==false) return 0;
    //if (covering(N0,N1,a,b) == false) return 0;
    //if (covering(N0,N1 , a , b) == false) return 0;
    //if (covering(N0,N1 ,a, b) == false) return 0;

    cout << "N f-covers N." <<endl;

    
    return 1;

}