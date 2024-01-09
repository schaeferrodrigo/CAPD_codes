#include "capd/capdlib.h"
#include "capd/covrel/HSet2D.h"
#include "capd/dynsys/DynSysMap.h"


using namespace capd;
using namespace std;


typedef capd::covrel::HSet2D<DMatrix, IMatrix> HSet2D;  // new name for an existing data type

bool checkCoveringRelation(IMap & f , const HSet2D & N1 , const HSet2D & N2){


    typedef capd::covrel::GridSet<IMatrix> GridSet;

    cout << "\n We check if image of h-set N passes throught N without touching forbidden region \n";

    IVector set = N1.center() + N1.coordinateSystem()*N1.box();
    IVector setImage = f(set);

    if (!N2.across(setImage)) return false;

    cout << "\n we check if the image of the left edge of N is on the left side of N \n";

    GridSet grid(2);

    N1.gridLeftEdge(grid,1);
    IVector leftEdge = grid.centers(0) + grid.coordinateSystem()*grid.box();
    IVector leftEdgeImage = f(leftEdge);

    if (!N2.onLeft(leftEdgeImage)) return false;

    /*
    we do the same for the right side
    */

    N1.gridRightEdge(grid,1);
    IVector rightEdge = grid.centers(0) + grid.coordinateSystem()*grid.box();
    IVector rightEdgeImage = f(rightEdge);

    if (!N2.onRight(rightEdgeImage)) return false;

    return true;

}




int main(){

    IMap f("var:x,y; fun: 2*x,0.5*y;");

    /*
    Take N = [-2,2]x[-2,4], we want to check that N f-covers N

    First: note that x-axis is the unstable direction and y-axis is the stable direction
    
    N can be rewritten as (0,1)+ | 1  0 | *(B(0,2) x B(0,3))
                                 | 0  1 |
   
    */ 

   double c[] = {0,1}; // center
   DVector center(2,c);

   double m[] = {1,0,0,1};
   DMatrix coordinateSystem(2,2,m);

   double r[] = {2,3};
   DVector box(2, r);

   HSet2D N(center, coordinateSystem, box);

   cout <<"\n We check Covering Relation N =f=>N: \n where N = [-2,2]x[-2,4]\n" ;

   if (checkCoveringRelation(f,N,N)){
        cout << "\n\n YES, N f=> N \n";
   }
   else{
        cout<<"\n\n No, covering relation cannot be checked \n";
        }

   

    return 0;
}