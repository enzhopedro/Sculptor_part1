#ifndef SCULPTOR_H
#define SCULPTOR_H
#include <string>

using namespace std;

struct Voxel {
    float r,g,b; //CORES
    float a; //OPACIDADE
    bool isOn; //INCLUIR OU NAO
};

class Sculptor
{
    protected:
        Voxel ***v; //MATRIZ 3D
        int nx, ny, nz; //TAMANHO DA MATRIZ
        float r, g, b, a; //CORES E OPACIDADE DA MATRIZ
    public:
        Sculptor(int _nx, int _ny, int _nz);//CONSTRUTOR DA CLASSE

        ~Sculptor();//DESTRUTOR DA CLASSE

        void setColor(float _r, float _g, float _b, float _a);//DEFINE COR E TRANSPARENCIA DA FIGURA

        void putVoxel(int x0, int y0, int z0);//ATIVA O VOXEL NA POSICAO (x0, y0, z0)

        void cutVoxel(int x0, int y0, int z0);//DESATIVA O VOXEL NA POSICAO (x0, y0, z0)

        void putBox(int x0, int x1, int y0, int y1, int z0, int z1);//ATIVA UM GRUPO DE VOXELS

        void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);//DESATIVA UM GRUPO DE VOXELS

        void putSphere(int xcenter, int ycenter, int zcenter, int radius);//ATIVA OS VOXELS DE UMA ESFERA

        void cutSphere(int xcenter, int ycenter, int zcenter, int radius);//DESATIVA OS VOXELS DE UMA ESFERA

        void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);//ATIVA OS VOXELS DE UM ELIPSOIDE

        void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);//DESATIVA OS VOXELS DE UM ELIPSOIDE

        void writeOFF(const char *filename);//SALVA A ESCULTURA NO FORMATO .OFF EM filename


};

#endif // SCULPTOR_H
