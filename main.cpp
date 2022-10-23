#include <iostream>
#include "Sculptor.h"

using namespace std;

int main()
{

    Sculptor miniGalaxia(200,200,100);

    //FUNDO
    miniGalaxia.setColor(0,0,0,1);
    miniGalaxia.putBox(0, 1, 0, 199, 0, 40);
    miniGalaxia.cutBox(0, 1, 140, 199, 0, 40);

    //SOL
    miniGalaxia.setColor(25,76,130,1);
    miniGalaxia.putSphere(25,150,17.5,16);

    //Planeta 1 - MERCURIO
    miniGalaxia.setColor(23,3,6,1);
    miniGalaxia.putSphere(25,120,17.5,2);

    //Planeta 2 - VENUS
    miniGalaxia.setColor(25,75,130,1);
    miniGalaxia.putSphere(25,110,17.5,3);

    //Planeta 3 - TERRA
    miniGalaxia.setColor(190,200,34,1);
    miniGalaxia.putSphere(25,100,17.5,3.5);
    miniGalaxia.cutSphere(25,100,17.5,1.5);

    //Planeta 4 - MARTE
    miniGalaxia.setColor(25,85,190,1);
    miniGalaxia.putSphere(25,85,17.5,2);

    //Planeta 5 - JUPITER
    miniGalaxia.setColor(25,80,130,1);
    miniGalaxia.putSphere(25,70,17.5,7);

    //Planeta 6 - SATURNO E SEU ANEL
    miniGalaxia.setColor(25,24,145,1);
    miniGalaxia.putEllipsoid(25,50,17.5, 9, 9, 1);
    miniGalaxia.cutEllipsoid(25,50,17.5, 8, 8, 1);
    miniGalaxia.putSphere(25,50,17.5,5);

    //Planeta 7 - URANO
    miniGalaxia.setColor(255,60,71,1);
    miniGalaxia.putSphere(25,30,17.5,5);

    //Planeta 8 - NETUNO
    miniGalaxia.setColor(255,0,6,1);
    miniGalaxia.putSphere(25,10,17.5,5);

    miniGalaxia.writeOFF((const char*)"miniGalaxia.off");

    cout << "OK!" << endl;
    return 0;

}
