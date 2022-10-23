#include "Sculptor.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    nx = _nx;
    ny = _ny;
    nz = _nz;

    //ALOCACAO DA MATRIZ 3D
    v = new Voxel**[nx];
    for(int i = 0; i < nx; i++)
    {
        v[i] = new Voxel*[ny];
        for(int j = 0; j < ny; j++)
        {
            v[i][j] = new Voxel[nz];
        }
    }
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                v[i][j][k].isOn = false;
            }
        }
    }
}


Sculptor::~Sculptor()
{
    //LIBERACAO DA MATRIZ 3D
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            delete[] v[i][j];
        }
    }
    for(int i = 0; i < nx; i++)
    {
        delete[] v[i];
    }
    delete[] v;
}

//COR DA MATRIZ
void Sculptor::setColor(float _r, float _g, float _b, float _a)
{
    r = _r;
    b = _b;
    g = _g;
    a = _a;
}

//CONTRUCAO DE UM UNICO VOXEL
void Sculptor::putVoxel(int x0, int y0, int z0)
{
    v[x0][y0][z0].isOn = true;
    v[x0][y0][z0].r = r;
    v[x0][y0][z0].g = g;
    v[x0][y0][z0].b = b;
}

//DESTRUICAO DE UM UNICO VOXEL
void Sculptor::cutVoxel(int x0, int y0, int z0)
{
    v[x0][y0][z0].isOn = false;
}

//CONSTRUCAO DE UM CONJUNTO DE VOXELS
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i = x0; i <= x1; i++)
    {
        for(int j = y0; j <= y1; j++)
        {
            for(int k = z0; k <= z1; k++)
            {
                putVoxel(i,j,k);
            }
        }
    }
}

//DESTRUICAO DE UM CONJUNTO DE VOXELS
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i = x0; i <= x1; i++)
    {
        for(int j = y0; j <= y1; j++)
        {
            for(int k = z0; k <= z1; k++)
            {
                cutVoxel(i,j,k);
            }
        }
    }
}

//CONSTRUCAO DOS VOXELS FORMADORES DE UMA ESFERA
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    // (x-x0)^2 + (y-y0)^2 + (z-z0)^2 = r^2 ESFERA COM CENTRO (x0, y0, z0)
    double dist;
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                dist = pow(i - xcenter,2) + pow(j - ycenter,2) + pow(k - zcenter,2);
                if(dist <= pow(radius,2))
                {
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

//DESTRUICAO DOS VOXELS FORMADORES DE UMA ESFERA
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    double dist;
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                dist = pow(i - xcenter,2) + pow(j - ycenter,2) + pow(k - zcenter,2);
                if(dist <= pow(radius,2))
                {
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

//CONSTRUCAO DOS VOXELS FORMADORES DE UM ELIPSOIDE
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    //(x - x0)^2/a^2 + (y - y0)^2/b^2 + (z - z0)^2/c^2 <= 1 ELIPSOIDE COM CENTRO (x0, y0, z0)
    double dist;
    if(rx == 0)
    {
        for(int j = 0; j <= ny; j++)
        {
            for(int k = 0; k <= nz; k++)
            {
                dist = pow(j - ycenter, 2)/pow(ry, 2) + pow(k - zcenter, 2)/pow(rz, 2);
                if(dist <= 1)
                {
                    putVoxel(xcenter,j,k);
                }
            }
        }
    }
    else if(ry == 0)
    {
        for(int i=0; i<= nx; i++)
        {
            for(int k = 0; k <= nz; k++)
            {
                dist = pow(i - xcenter, 2)/pow(rx, 2) + pow(k - zcenter, 2)/pow(rz, 2);
                if(dist <= 1)
                {
                    putVoxel(i,ycenter,k);
                }
            }
        }

    }
    else if(rz == 0)
    {
        for(int i = 0; i <= nx; i++)
        {
            for(int j=0; j <= ny; j++)
            {
                dist = pow(i - xcenter, 2)/pow(rx, 2) + pow(j - ycenter, 2)/pow(ry, 2);
                if(dist <= 1)
                {
                    putVoxel(i,j,zcenter);
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < nx; i++)
        {
            for(int j = 0; j < ny; j++)
            {
                for(int k = 0; k < nz; k++)
                {
                    dist = pow(i - xcenter,2)/pow(rx, 2) + pow(j - ycenter,2)/pow(ry, 2) + pow(k - zcenter,2)/pow(rz, 2);
                    if (dist <= 1)
                    {
                        putVoxel(i,j,k);
                    }
                }
            }
        }
    }
}

//DESTRUICAO DOS VOXELS FORMADORES DE UM ELIPSOIDE
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    double dist;
    if(rx == 0)
    {
        for(int j = 0; j <= ny; j++)
        {
            for(int k = 0; k <= nz; k++)
            {
                dist = pow(j - ycenter, 2)/pow(ry, 2) + pow(k - zcenter, 2)/pow(rz, 2);
                if(dist <= 1)
                {
                    cutVoxel(xcenter,j,k);
                }
            }
        }
    }
    else if(ry == 0)
    {
        for(int i=0; i<= nx; i++)
        {
            for(int k = 0; k <= nz; k++)
            {
                dist = pow(i - xcenter, 2)/pow(rx, 2) + pow(k - zcenter, 2)/pow(rz, 2);
                if(dist <= 1)
                {
                    cutVoxel(i,ycenter,k);
                }
            }
        }

    }
    else if(rz == 0)
    {
        for(int i = 0; i <= nx; i++)
        {
            for(int j=0; j <= ny; j++)
            {
                dist = pow(i - xcenter, 2)/pow(rx, 2) + pow(j - ycenter, 2)/pow(ry, 2);
                if(dist <= 1)
                {
                    cutVoxel(i,j,zcenter);
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < nx; i++)
        {
            for(int j = 0; j < ny; j++)
            {
                for(int k = 0; k < nz; k++)
                {
                    dist = pow(i - xcenter,2)/pow(rx, 2) + pow(j - ycenter,2)/pow(ry, 2) + pow(k - zcenter,2)/pow(rz, 2);
                    if (dist <= 1)
                    {
                        cutVoxel(i,j,k);
                    }
                }
            }
        }
    }
}


void Sculptor::writeOFF(const char *filename)
{
    int x, y, z, t;
    ofstream f;
    t = 0;
    f.open(filename);
    f << "OFF\n";

    for(x = 0; x < nx; x++)
    {
        for(y = 0; y < ny; y++)
        {
            for(z = 0; z < nz; z++)
            {
                if(v[x][y][z].isOn)
                {
                    //  QUANTIDADE DE VOXELS
                    t++;
                }
            }
        }
    }

    f << t*8 << " " << t*6 << " " << "0" << endl;
    for(x = 0; x < nx; x++)
    {
        for(y = 0; y < ny; y++)
        {
            for(z = 0; z < nz; z++)
            {
                if(v[x][y][z].isOn)
                {
                    //CADA LADO DO VOXEL EQUIVALE A 0.5
                    f << x - 0.5 << " " << y + 0.5 << " " << z - 0.5 << "\n" << endl;
                    f << x - 0.5 << " " << y - 0.5 << " " << z - 0.5 << "\n" << endl;
                    f << x + 0.5 << " " << y - 0.5 << " " << z - 0.5 << "\n" << endl;
                    f << x + 0.5 << " " << y + 0.5 << " " << z - 0.5 << "\n" << endl;
                    f << x - 0.5 << " " << y + 0.5 << " " << z + 0.5 << "\n" << endl;
                    f << x - 0.5 << " " << y - 0.5 << " " << z + 0.5 << "\n" << endl;
                    f << x + 0.5 << " " << y - 0.5 << " " << z + 0.5 << "\n" << endl;
                    f << x + 0.5 << " " << y + 0.5 << " " << z + 0.5 << "\n" << endl;
                }
            }
        }
    }

    t = 0;
    // ---- ESCRITA DOS INDICES DAS FACES (VERTICES: 8 EM 8) ----
    /*
        Face 0: P0 P3 P2 P1
        Face 1: P4 P5 P6 P7
        Face 2: P0 P1 P5 P4
        Face 3: P0 P4 P7 P3
        Face 4: P7 P6 P2 P3
        Face 5: P1 P2 P6 P5
    */
    for(x = 0; x < nx; x++)
    {
        for(y = 0; y < ny; y++)
        {
            for(z = 0; z < nz; z++)
            {
                if(v[x][y][z].isOn)
                {
                    // FACE 0
                    f << fixed;
                    f << 4 << " " << t*8 + 0 << " " << t*8 + 3 << " " << t*8 + 2 << " " << t*8 + 1 << " ";
                    f << setprecision(2) << v[x][y][z].r << " " << setprecision(2) << v[x][y][z].g << " " << setprecision(2) << v[x][y][z].b << " " << setprecision(2) << v[x][y][z].a << "\n";
                    // FACE 1
                    f << 4 << " " << t*8 + 4 << " " << t*8 + 5 << " " << t*8 + 6 << " " << t*8 + 7 << " ";
                    f << setprecision(2) << v[x][y][z].r << " " << setprecision(2) << v[x][y][z].g << " " << setprecision(2) << v[x][y][z].b << " " << setprecision(2) << v[x][y][z].a << "\n";
                    // FACE 2
                    f << 4 << " " << t*8 + 0 << " " << t*8 + 1 << " " << t*8 + 5 << " " << t*8 + 4 << " ";
                    f << setprecision(2) << v[x][y][z].r << " " << setprecision(2) << v[x][y][z].g << " " << setprecision(2) << v[x][y][z].b << " " << setprecision(2) << v[x][y][z].a << "\n";
                    // FACE 3
                    f << 4 << " " << t*8 + 0 << " " << t*8 + 4 << " " << t*8 + 7 << " " << t*8 + 3 << " ";
                    f << setprecision(2) << v[x][y][z].r << " " << setprecision(2) << v[x][y][z].g << " " << setprecision(2) << v[x][y][z].b << " " << setprecision(2) << v[x][y][z].a << "\n";
                    // FACE 4
                    f << 4 << " " << t*8 + 7 << " " << t*8 + 6 << " " << t*8 + 2 << " " << t*8 + 3 << " ";
                    f << setprecision(2) << v[x][y][z].r << " " << setprecision(2) << v[x][y][z].g << " " << setprecision(2) << v[x][y][z].b << " " << setprecision(2) << v[x][y][z].a << "\n";
                    // FACE 5
                    f << 4 << " " << t*8 + 1 << " " << t*8 + 2 << " " << t*8 + 6 << " " << t*8 + 5 << " ";
                    f << setprecision(2) << v[x][y][z].r << " " << setprecision(2) << v[x][y][z].g << " " << setprecision(2) << v[x][y][z].b << " " << setprecision(2) << v[x][y][z].a << "\n";
                    t++;  // INCREMENTA O TOTAL DE VOXELS EM FORMATO DE CUBO
                }
            }
        }
    }
    f.close();
}
