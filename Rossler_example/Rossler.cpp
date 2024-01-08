#include <iostream>
#include "capd/capdlib.h"
using namespace std;
using namespace capd;


IVector f(IPoincareMap &P,IVector x)
{

    IVector X(3);
    X[0]=0.0; 
    X[1]=x[0];
    X[2]=x[1]; 
    C0Rect2Set SetX(X);
    IVector Y=P(SetX,4);
    IVector y(2);
    y[0]=Y[1];
    y[1]=Y[2];
    return y;
}

bool exitCondition(IPoincareMap &P,IVector N,IVector M)
{
    IVector Nl=N;
    Nl[0]=N[0].left();
    IVector Nr=N;
    Nr[0]=N[0].right();
    interval I=(f(P,Nl)[0]-M[0])*(f(P,Nr)[0]-M[0]);
    if(not (I<0.0) ) return false;
    return true;
}


interval part(interval x,int k,int i)
{
    return x.left()+i*(x.right()-x.left())/k+(x-x.left())/k;
}

bool entryCondition(IPoincareMap &P,IVector N,IVector M)
{
    int k=100;
    for(int i=0;i<k;i++){
        IVector Nfragment=N;
        Nfragment[0] = part(N[0],k,i);
        if(not subsetInterior(f(P,Nfragment)[1],M[1]) ) return false;
    }
    return true;
} 
bool covering(IPoincareMap &P,IVector N,IVector M){
    if(entryCondition(P,N,M)==false) return false;
    if(exitCondition(P,N,M)==false) return false;
    return true;
}

int main(){
    int order = 20;
    IMap F("par:a,b;var:x,y,z;fun:-(y+z),x+b*y,b+z*(x-a);");
    F.setParameter("a", interval(57) / interval(10));
    F.setParameter("b", interval(2) / interval(10));
    IOdeSolver solver(F,order);
    ICoordinateSection section(3,0);
    IPoincareMap P(solver, section);
    IVector N0(2), N1(2);
    N0[0]=interval(-8.4,-7.6);
    N0[1]=interval(0.029,0.032);
    N1[0]=interval(-5.7,-4.6);
    N1[1]=interval(0.029,0.032);
    if(covering(P,N0,N0)==false) return 0;
    if(covering(P,N0,N1)==false) return 0;
    if(covering(P,N1,N0)==false) return 0;
    if(covering(P,N1,N1)==false) return 0;

    cout << "There is a horseshoe in the Rossler system." << endl;
    return 1;
}