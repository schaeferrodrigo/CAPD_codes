#include <iostream>
#include "capd/capdlib.h"
#include <cmath>
using namespace std;
using namespace capd;

/*
IVector f(IVector x){

    int numberIterates;

    float a = 1.4;
    float b = 0.3;

    IVector X(2);
    

    for (numberIterates = 1; numberIterates <= 7; numberIterates++){
        X[0] = x[0];
        X[1] = x[1];
        x[0] = 1-a*X[0]*X[0] + X[1]*(1 - a*X[0]) - a*X[1]*X[1]/4;
        x[1] = b*X[0] + b*X[1]/2;

        //cout << "number of iterates =  " << numberIterates << endl;

                    
    }
    return x;

}



IVector findEqPoint(float a, float b, string signal){

    IVector x(2);


    DInterval ia(a,a);

    cout << "the value of a is "<<ia <<endl;

    DInterval ib(b,b);


    
    if (signal == "positive"){
        x[0] = (-(1-ib) + sqrt((1-ib)*(1-ib) - 4*ia*(-1)))/(2*ia);
        x[1] = ib*x[0];

        return x;
    }

    if (signal == "negative"){
        x[0] = (-(1-ib) - sqrt((1-ib)*(1-ib) - 4*ia*(-1)))/(2*ia);
        x[1] = ib*x[0];

        return x;
    }
    else{
         cout <<"ERROR: signal shoulbe postive or negative" <<endl;
         return x;
    }
}
*/

IVector f(IVector x, float a , float b){
    int numberIterates;

    IVector X(2);

    for (numberIterates = 1 ; numberIterates<= 1; numberIterates++){

        X[0] = x[0];
        X[1] = x[1];
        x[0] = 1-a*X[0]*X[0] + X[1];
        x[1] =  b*X[0];

    }
    return x;

}



bool exitCondition(IVector N, IVector M, float a, float b){

    IVector Nl = N;
    Nl[0] = N[0].left();

    IVector Nr = N;
    Nr[0] = N[0].right();

    cout << "Nl= "<< Nl << endl;

    cout << "Nr = " << Nr << endl;
    
    cout << "f(Nl) = " <<f(Nl,a,b)[0] << endl;

    cout << "f(Nr) = " <<f(Nr,a,b)[0] << endl;

    cout << f(Nr,a,b)[0] - M[0] << endl;

    cout << f(Nl,a,b)[0]-M[0] << endl;

    interval I = (f(Nl,a,b)[0]-M[0])*(f(Nr,a,b)[0] - M[0]);
    if (not (I<0.0)) return false;
    
    cout << "Exit condition is satisfied."<<endl;

    return true;

}

interval part(interval x, int k, int i){
    return x.left()+i*(x.right()-x.left())/k+(x-x.left())/k;
}

bool entryCondition(IVector N, IVector M, float a , float b){

    int k=100;
    cout << M[1] << endl;


    for(int i=0; i<k;i++){
        IVector Nfragment = N;
        Nfragment[0] = part(N[0],k,i);

        cout << f(Nfragment,a,b)[1] << endl;
        if (not subsetInterior(f(Nfragment,a,b)[1], M[1])) return false;
    }

    cout << "Entry condition is satisfied." <<endl;
    return true;
}

bool covering(IVector N, IVector M, float a, float b){

    cout << "N0 is " << N << endl;
    cout << "N1 is " << M << endl;

    cout << "f_c(N0) = " << f(N,a,b) << endl;

    if (exitCondition(N,M,a,b)==false) return false;
    if(entryCondition(N,M,a,b)==false) return false;
    

    return true;
}

int main(){

    float a = 1.4;
    float b = 0.3;


    /*
    IVector equilibriumPointsPositive = findEqPoint(a,b,"positive");

    cout << equilibriumPointsPositive[0] << endl;
    cout << equilibriumPointsPositive[1] << endl;

    IVector equilibriumPointsNegative = findEqPoint(a,b,"negative");

    cout << equilibriumPointsNegative[0] << endl;
    cout << equilibriumPointsNegative[1] << endl;

    */

    IVector N0(2),N1(2);

   /* 
    float a0 = 0.455;
    float a1 = 0.551;
    float a2 = 0.583;
    float a3 = 0.615;

    float d = 0.01;
    float u = 0.28;
    */

    DInterval Xaxis(0.5, 0.8);
    DInterval Yaxis(0.15,0.25);

    //N0[0]= interval(0.63133, 0.63136);
    N0[0]= Xaxis;
    //N0[1] = interval(0.18940601,0.1894061);
    N0[1] = Yaxis;

    N1[0] = Xaxis;
    N1[1] = Yaxis;

   
    if (covering(N0,N0,a,b)==false) return 0;
    //if (covering(N0,N1,a,b) == false) return 0;
    //if (covering(N0,N1 , a , b) == false) return 0;
    //if (covering(N0,N1 ,a, b) == false) return 0;

    cout << "N f-covers N." <<endl;

    
    return 1;

}