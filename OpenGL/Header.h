﻿#pragma once
//---------------------------------------------------------------------------
#ifndef HeaderH
#define HeaderH
//---------------------------------------------------------------------------
#include "Definitions.h"
#include <stdio.h>
#include <math.h>
using namespace std;

class color {
public:
    double R, G, B;   //Red, Green and Blue

    color operator*(double f) { //produto escalar
        color c;
        c.R = R * f;
        c.G = G * f;
        c.B = B * f;
        return c;
    };
    void operator=(double f) {  //same value to R, G and B
        R = G = B = f;
    };

    void getHeatMapColor(double value) { //Valor entre 0 y 1
        color arr_col[NUM_COLORS];//4 colores base para el mapa de calor

        //Color 0: Helado/azul {0,0,1}
        arr_col[0].R = 0.5;
        arr_col[0].G = 0.5;
        arr_col[0].B = 1;

        //Color 1 Frio/verde {0,1,0}
        arr_col[1].R = 0.5;
        arr_col[1].G = 1;
        arr_col[1].B = 0.5;

        //Color 2 Tibio/amarillo {1,1,0}
        arr_col[2].R = 1;
        arr_col[2].G = 1;
        arr_col[2].B = 0.5;

        //Color 3 Caliente/rojo {1,0,0}
        arr_col[3].R = 1;
        arr_col[3].G = 0.5;
        arr_col[3].B = 0.5;

        int ind1;
        int ind2;
        double fracIntermedia = 0;

        if (value <= 0)
            ind1 = ind2 = 0;
        else if (value >= 1)
            ind1 = ind2 = 3;
        else {
            value = value * (NUM_COLORS - 1);
            ind1 = floor(value);
            ind2 = ind1 + 1;
            fracIntermedia = value - double(ind1);
        }
        R = (arr_col[ind2].R - arr_col[ind1].R) * fracIntermedia + arr_col[ind1].R;
        G = (arr_col[ind2].G - arr_col[ind1].G) * fracIntermedia + arr_col[ind1].G;
        B = (arr_col[ind2].B - arr_col[ind1].B) * fracIntermedia + arr_col[ind1].B;
    };


};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class vector1 {
public:
    double x, y, z;

    vector1 operator+(vector1 v2) { //suma de vectores
        vector1 v1;
        v1.x = x + v2.x;
        v1.y = y + v2.y;
        v1.z = z + v2.z;
        return v1;
    };
    vector1 operator-(vector1 v2) { //resta de vectores
        vector1 v1;
        v1.x = x - v2.x;
        v1.y = y - v2.y;
        v1.z = z - v2.z;
        return v1;
    };
    vector1 operator*(double f) { //multiplicacion por escalar
        vector1 v;
        v.x = x * f;
        v.y = y * f;
        v.z = z * f;
        return v;
    };
    vector1 operator/(double f) { //division por escaalr
        vector1 v;
        v.x = x / f;
        v.y = y / f;
        v.z = z / f;
        return v;
    };
    double operator*(vector1 v) { //produto punto entre vectores
        double f;
        f = x * v.x + y * v.y + z * v.z;
        return f;
    };

    vector1 operator/(vector1 v2) { //produto cruz
        vector1 v1;
        v1.x = y * v2.z - z * v2.y;
        v1.y = -x * v2.z + z * v2.x;
        v1.z = x * v2.y - y * v2.x;
        return v1;
    };


    /*
    void operator*=(double f) {
        x *= f;
        y *= f;
        z *= f;
    };
    */


    /*
    void operator/=(double f) {
        x /= f;
        y /= f;
        z /= f;
    };
    */

    void operator=(double f) {  //mismo valor para x, y , z
        x = y = z = f;
    };

    /*
    bool operator==(vector v) { //igualdade entre vetores
        if (x == v.x && y == v.y && z == v.z)
            return 1;
        else
            return 0;
    };
    */

    /*
    bool operator!=(vector v) { //desigualdade entre vetores
        if (x == v.x && y == v.y && z == v.z)
            return 0;
        else
            return 1;
    };
    */

    /*
    double Angle(vector v) { //�ngulo entre dois vetores
        double angle, f;
        f = x * v.x + y * v.y + z * v.z; // produto escalar
        f /= sqrt(x * x + y * y + z * z);
        f /= sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        angle = acos(f) / M_PI * 180;
        return angle;
    };
    */
    /*
    double Max(void) { //valor m�ximo entre as coordenadas
        double max;
        if (x > y) {
            max = x;
        }
        else {
            max = y;
        }
        if (z > max) {
            max = z;
        }
        return max;
    };
    double Min(void) { //valor minimo entre as coordenadas
        double min;
        if (x < y) {
            min = x;
        }
        else {
            min = y;
        }
        if (z < min) {
            min = z;
        }
        return min;
    };
    */

    vector1 Abs(void) { //valor absoluto das coordenadas
        vector1 v;
        v.x = fabs(x);
        v.y = fabs(y);
        v.z = fabs(z);
        return v;
    };

    double Module(void) {
        return sqrt(x * x + y * y + z * z);
    };

    vector1 Unitary() {
        double m;
        vector1 u;
        u.x = x;
        u.y = y;
        u.z = z;
        m = u.Module();
        if (m == 0) {
            u.x = 0.0;
            u.y = 0.0;
            u.z = 0.0;
        }
        else {
            u = u / m;
        }

        return u;
    }



};
//---------------------------------------------------------------------------
class point {
public:
    double x, y, z;

    point() {
        x = 0;
        y = 0;
        z = 0;
    };

    point operator+(vector1 v) { //translado de un vector
        point p;
        p.x = x + v.x;
        p.y = y + v.y;
        p.z = z + v.z;
        return p;
    };
    point operator+(point p2) { //suma de dos puntos
        point p1;
        p1.x = x + p2.x;
        p1.y = y + p2.y;
        p1.z = z + p2.z;
        return p1;
    };
    /*
    point operator-(point p) { //resta de dos puntos
        point v;
        v.x = x - p.x;
        v.y = y - p.y;
        v.z = z - p.z;
        return v;
    };
    */

    vector1 operator-(point p) { //resta de dos puntos
        vector1 v;
        v.x = x - p.x;
        v.y = y - p.y;
        v.z = z - p.z;
        return v;
    };

    point operator*(double f) { //multiplicacion por escalar
        point p;
        p.x = x * f;
        p.y = y * f;
        p.z = z * f;
        return p;
    };
    point operator/(double f) { //division por escalar
        point p;
        p.x = x / f;
        p.y = y / f;
        p.z = z / f;
        return p;
    };

    void operator=(double f) {  //mismo valor para x y z
        x = y = z = f;
    };

    bool operator==(point p) {  //igualdades entre puntos
        if (x == p.x && y == p.y && z == p.z)
            return 1;
        else
            return 0;
    };
    bool operator!=(point p) {  //desigualdade entre pontos
        if (x == p.x && y == p.y && z == p.z)
            return 0;
        else
            return 1;
    };

    void Clear() {
        x = 0;
        y = 0;
        z = 0;
    };

    /*
    double Max(void) { //valor maximo entre las coordenadas
        double max;
        if (x > y) {
            max = x;
        }
        else {
            max = y;
        }
        if (z > max) {
            max = z;
        }
        return max;
    };
    */

    /*
    double Min(void) { //valor minimo entre as coordenadas
        double min;
        if (x < y) {
            min = x;
        }
        else {
            min = y;
        }
        if (z < min) {
            min = z;
        }
        return min;
    };
    */


    point Abs(void) { //valor absoluto das coordenadas
        point v;
        v.x = fabs(x);
        v.y = fabs(y);
        v.z = fabs(z);
        return v;
    };

    double distancia(point p2) {
        return sqrt((p2.x - x) * (p2.x - x) + (p2.y - y) * (p2.y - y) + (p2.z - z) * (p2.z - z));
    };

    /*
    vector restaPuntos(point b) {
        vector v;
        v.x = x - b.x;
        v.y = y - b.y;
        v.z = z - b.z;
        return v;
    }
    */

};
//---------------------------------------------------------------------------
class triangle {
public:
    point p0, p1, p2, bc; //triangle Points
    int Projection; //projection
    double a0;      //a0 constante para c�lculos futuros
    int ID;         //identificador �nico

    triangle() {
        p0 = 0;
        p1 = 0;
        p2 = 0;
        bc = 0;
        Projection = 0;
        a0 = 0;
        ID = 0;
    };

    void operator=(triangle t) {
        p0 = t.p0;
        p1 = t.p1;
        p2 = t.p2;
        bc = t.bc;
        Projection = t.Projection;
        a0 = t.a0;
        ID = t.ID;
    };

    void Clear() {
        p0 = 0;
        p1 = 0;
        p2 = 0;
        bc = 0;
        Projection = 0;
        a0 = 0;
        ID = 0;
    };

    void Centroid() {
        bc = (p0 + p1 + p2) / 3;
    };

    /*
    double solidAngle(point b) {
        double area = 0.0, d = 0.2;
        triangle t;
        vector v0, v1, v2;
        v0 = p0 - b;
        v1 = p1 - b;
        v2 = p2 - b;
        v0 = v0 / v0.Module();
        v1 = v1 / v1.Module();
        v2 = v2 / v2.Module();
        t.p0 = b + (v0 * d);
        t.p1 = b + (v1 * d);
        t.p2 = b + (v2 * d);
        area = t.TriangleArea();
        return area;
    };
    */

    double TriangleArea() {
        double a;
        vector1 v = (p1 - p0) / (p2 - p0);
        a = 0.5 * v.Module();
        return a;
    };

    void CalculateProjection() {
        vector1 n;
        double x0, y0, z0, x1, y1, z1, x2, y2, z2;
        x0 = p0.x;
        y0 = p0.y;
        z0 = p0.z;
        x1 = p1.x;
        y1 = p1.y;
        z1 = p1.z;
        x2 = p2.x;
        y2 = p2.y;
        z2 = p2.z;
        n = (p1 - p0) / (p2 - p0);
        n.x = n.x * n.x;
        n.y = n.y * n.y;
        n.z = n.z * n.z;
        if ((n.x >= n.y) && (n.x >= n.z)) {                        //proje��o yz
            Projection = yz;
            a0 = 1 / (-y1 * z0 + y2 * z0 + y0 * z1 - y2 * z1 - y0 * z2 + y1 * z2 + 0.000001);
        }
        if ((n.y >= n.x) && (n.y >= n.z)) {                        //proje��o xz
            Projection = xz;
            a0 = 1 / (-x1 * z0 + x2 * z0 + x0 * z1 - x2 * z1 - x0 * z2 + x1 * z2 + 0.000001);
        }
        if ((n.z >= n.x) && (n.z >= n.y)) {                        //proje��o xy
            Projection = xy;
            a0 = 1 / (-x1 * y0 + x2 * y0 + x0 * y1 - x2 * y1 - x0 * y2 + x1 * y2 + 0.000001);
        }
    };
};
//---------------------------------------------------------------------------
class plane {
public:

    color       Color;                  //color RGB
    int         NP;                     //Number of Points
    point* p;                     //plane Points
    int         NT;                     //Number of Triangles
    triangle* t;                     //plane Triangles
    vector1      n;                      //Normal vector

    plane() {
        int P, T;
        Color.R = 0.5;
        Color.G = 0.5;
        Color.B = 1;
        NP = 0;
        p = NULL;
        NT = 0;
        t = NULL;
        n = 0;
    }

    void NewPoints(int N) {
        int P;
        point* tp;
        tp = new point[NP + N];
        for (P = 0; P < NP; P++) {
            tp[P] = p[P];
        }
        for (P = NP; P < NP + N; P++) {
            tp[P].Clear();
        }
        if (NP > 0) {
            delete[] p;
            p = NULL;
        }
        p = tp;
        NP += N;
    };

    void DeletePoint(int IP) {
        int P, j = 0;
        if (IP >= 0 && IP < NP) {
            point* tp;
            tp = new point[NP - 1];
            for (P = 0; P < NP; P++) {
                if (P != IP) {
                    tp[j] = p[P];
                    j++;
                }
            }
            delete[] p;
            p = tp;
            NP -= 1;
        }
    };

    void NewTriangle(int N) {
        int T;
        triangle* tt;
        tt = new triangle[NT + N];
        for (T = 0; T < NT; T++) {
            tt[T] = t[T];
        }
        for (T = NT; T < NT + N; T++) {
            tt[T].Clear();
        }
        if (NP > 0) {
            delete[] t;
            t = NULL;
        }
        t = tt;
        NT += N;
    };

    void DeleteTriangle(int IT) {
        int T, j = 0;
        if (IT >= 0 && IT < NT) {
            triangle* tt;
            tt = new triangle[NT - 1];
            for (T = 0; T < NT; T++) {
                if (T != IT) {
                    tt[j] = t[T];
                    j++;
                }
            }
            delete[] t;
            t = tt;
            NT -= 1;
        }
    };

    /*
    void MoreTriangle(int nd) { //Genera m�s tri�ngulos a partir de una malla con nd divisiones
        if (NP == 4) {
            int i, j, cont;   //Contadores
            //matPuntos mp;   //Matriz din�mica de puntos
            vector v1, v2;  //vectores directores en cada lado del cuadrado
            double m1, m2;  //m�dulos de los vectores directores
            double p1, p2;  //tama�o del paso
            v1 = p[1] - p[0];   //vector director 1 dgenerado por el v�rtice 1 y 2
            v2 = p[2] - p[1];   //vector director 2 generado por el v�rtice 2 y 3
            m1 = v1.Module(); //m�dulo del vector director 1
            m2 = v2.Module(); //m�dulo del vector director 2
            v1 = v1 / m1;       //vector director 1 unitario
            v2 = v2 / m2;       //vector director 2 unitario
            p1 = m1 / nd;       //paso 1
            p2 = m2 / nd;       //paso 2
            mp.init(nd + 1, nd + 1);//Lleno la matriz de puntos, seg�n los v�rtices del cuadrado inicial.
            for (i = 0; i <= nd; i++) {
                mp.p[i][0] = p[0] + (v1 * (p1 * i));
                for (j = 1; j <= nd; j++)
                    mp.p[i][j] = mp.p[i][0] + (v2 * (p2 * j));
            }
            plane* a_p = new plane[nd * nd];
            cont = 0;
            for (i = 0; i < nd; i++) {
                for (j = 0; j < nd; j++) {
                    a_p[cont].Clear();
                    a_p[cont].NewPoints(4);
                    a_p[cont].p[0] = mp.p[i][j];
                    a_p[cont].p[1] = mp.p[i + 1][j];
                    a_p[cont].p[2] = mp.p[i + 1][j + 1];
                    a_p[cont].p[3] = mp.p[i][j + 1];
                    a_p[cont].PointGenTriangle();
                    cont++;
                }
            }
            cont = 0;
            NewTriangle(2 * nd * nd);
            for (int i = 0; i < nd * nd; i++) {
                for (int j = 0; j < a_p[i].NT; j++) {
                    t[cont] = a_p[i].t[j];
                    cont++;
                }
            }
            delete a_p;
            a_p = NULL;
        }
    };
    */

    void PointGenTriangle() { //Genera 2 triangulos a partir de los v�rtices de un cuadrado
        NewTriangle(NP - 2);
        int i = 1;
        for (int T = 0; T < NT; T++) {
            i--;
            t[T].p0.x = p[i].x;
            t[T].p0.y = p[i].y;
            t[T].p0.z = p[i].z;
            i++;
            if (i == NP) i = 0;
            t[T].p1.x = p[i].x;
            t[T].p1.y = p[i].y;
            t[T].p1.z = p[i].z;
            i++;
            if (i == NP) i = 0;
            t[T].p2.x = p[i].x;
            t[T].p2.y = p[i].y;
            t[T].p2.z = p[i].z;
            i++;
        }
    };

    void Clear() {
        Color.R = 0.5;
        Color.G = 0.5;
        Color.B = 1;
        NP = 0;
        delete[] p;
        p = NULL;
        NT = 0;
        delete[] t;
        t = NULL;
        n = 0;
    };
    /*
    bool IsConvex() {
        int n;
        vector u, v;
        double ang;
        for (int n = 1; n < NP - 1; n++) { // ficam faltando 2 pontos (primeiro e ultimo)
            u = p[n - 1] - p[n];
            v = p[n + 1] - p[n];
            ang = u.Angle(v);
            if (ang > 180)return false;
        }
        return true;
    }
    */


};

class receptor {
public:
    point p;                //Posición
    double ReceptionRadius; //Radio de recepción
    double* eR;             //Energía recibida en el receptor
    int NIt;                //Instantes de tiempo considerados
    double VisualRadius;    //Radio visual (tamaño en pantalla)
    color Color;            //Color del receptor
    point SphereFace[32][4];//Representación gráfica del receptor

    receptor() {
        p = 0.0;
        eR = NULL;
        NIt = 0;

        Color.R = 0.5;
        Color.G = 1.0;
        Color.B = 0.5;

        VisualRadius = 0.3;
        ReceptionRadius = 0.3;

        //Creating Sphere
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                SphereFace[8 * i + j][0].x = sin(i * PI / 4) * cos((j + 1) * PI / 4);
                SphereFace[8 * i + j][0].y = sin(i * PI / 4) * sin((j + 1) * PI / 4);
                SphereFace[8 * i + j][0].z = cos(i * PI / 4);
                SphereFace[8 * i + j][1].x = sin(i * PI / 4) * cos(j * PI / 4);
                SphereFace[8 * i + j][1].y = sin(i * PI / 4) * sin(j * PI / 4);
                SphereFace[8 * i + j][1].z = cos(i * PI / 4);
                SphereFace[8 * i + j][2].x = sin((i + 1) * PI / 4) * cos(j * PI / 4);
                SphereFace[8 * i + j][2].y = sin((i + 1) * PI / 4) * sin(j * PI / 4);
                SphereFace[8 * i + j][2].z = cos((i + 1) * PI / 4);
                SphereFace[8 * i + j][3].x = sin((i + 1) * PI / 4) * cos((j + 1) * PI / 4);
                SphereFace[8 * i + j][3].y = sin((i + 1) * PI / 4) * sin((j + 1) * PI / 4);
                SphereFace[8 * i + j][3].z = cos((i + 1) * PI / 4);
            }
        }
    };

    ~receptor() {/*
        deleteTimeSamples();
    */
    };

    void Clear() {
        deleteTimeSamples();
    };

    void createTimeSamples(int dSim) {
        deleteTimeSamples();
        NIt = dSim;
        eR = new double[NIt];
        for (int i = 0; i < NIt; i++) {
            eR[i] = 0.0;
        }
    };

    void deleteTimeSamples() {
        if (NIt > 0) {
            delete eR;
            eR = NULL;
            NIt = 0;
        }
    };

    double IntersectionDistance(vector1 n, point p, vector1 u, point o) {
        /*JFLN:
            vector n is the normal vector of the plane
            point p is one of the vertex of the plane
            vector u is the ray
            point o is the initial position of the ray
        */
        double d, m;
        m = n * u;
        //JFLN: Has to have an error tolerance
        if (m == 0)
            return -1;
        d = (n * (p - o)) / m;
        return d;
    };

    double Module(vector1 v) { //JFLN: Returns the vector's module
        double m;
        m = sqrt(v * v);
        return m;
    };

    vector1 Normal(vector1 v1) { //JFLN: Returns the vector's unitary vector
                                        //compare with the function unitario because this funtion is the same in MathFuntions
        double m;
        vector1 v2;
        m = Module(v1);
        if (m == 0)
            v2 = 0;
        else
            v2 = v1 / m;
        return v2;

    };

    double solidAngle(point b) {
        double area = 0.0, d = 0.0, h = 0.0, r = 0.0, ang = 0.0, d2 = 0.2;
        d = Module(p - b);
        h = sqrt(d * d + ReceptionRadius * ReceptionRadius);
        ang = acos(d / h);
        h = d2 / cos(ang);
        r = sqrt(h * h - d2 * d2);
        area = PI * r * r;
        return area;
    };

    void receptionRayTracing(point o, vector1 v, int t, double maxd, double ene) {
        //o  Punto de partida del rayo
        //v  Vector director del rayo
        //p  Punto central del receptor (variable de la clase)
        point pi;
        double dis, dci; //Distancia de intersección
        int tim;    //tiempo de vuelo entre el punto de partida y el receptor
        int ind;
        vector1 n, u;
        u = Normal(v); //u es el unitario de v
        n = u * (-1);    //vector normal al disco de recepción
        dis = IntersectionDistance(n, p, u, o);
        if (dis > 0 && dis < maxd) {
            pi = o + (u * dis);
            dci = Module(pi - p);
            dis = Module(u * dis);
            if (dci < ReceptionRadius) {
                tim = int(1000 * dis / V_SON);
                ind = t + tim;
                if (ind >= 1000) ind = 999;
                eR[ind] += ene;
            }
        }
    };

    void grabarArchivo() {
        //Creación de archivo con respuesta del receptor
        FILE* Archivo;
        char buffer[50];
        sprintf(buffer, "Data/DatReceptor_%g_%g_%g.txt", p.x, p.y, p.z);
        Archivo = fopen(buffer, "w");
        for (int i = 0; i < 1000; i++) {
            fprintf(Archivo, "%15g\n", eR[i]);
        }
        fclose(Archivo);
        //Fin de creación de archivo
    };
};

//---------------------------------------------------------------------------
struct reflection { //Respuesta al proceso de trazado de rayos.
    point r[MaxNPoints];                    //Puntos de aplicaci�n
    double d[MaxNPoints];                   //Distancia entre punto y punto
    int idTriangle[MaxNPoints];             //Id �nico del tri�ngulo por cuarto donde se choc�
    int Plane[MaxNPoints];                  //Nro. del plano por cuarto donde se choc�
    int Triangle[MaxNPoints];               //Nro. del tri�ngulo por plano donde se choc�
    int N;                                  //JFLN: Number of reflections
    bool lost;                              //JFLN: If lost equal true, it's a reflection of a lost ray
    int Ray;                                //JFLN: Number of RAY in preview
};
//---------------------------------------------------------------------------
class room {
public:
    int			NP;		//Number of Planes
    plane* p;		//Planes
    double		maxd;	//Maxima distancia entre dos puntos en la sala.
    //receptor* r;     //Number of receptors (microphones)
    int         NR;     //Number of receptors

    room() {
        NP = 0;
        p = NULL;
        NR = 0;
        //r = NULL;
        maxd = 0.0;
    };

    void Clear() {
        if (NP > 0) {
            for (int i = 0; i < NP; i++) {
                p[i].Clear();
            }
            delete[] p;
            p = NULL;
        }
        NP = 0;

        /*
        if (NR > 0) {
            for (int i = 0;i < NR;i++) {
                r[i].Clear();
            }
            delete[] r;
            r = NULL;
        }
        NR = 0;
        */

        maxd = 0.0;
    };

    void Init() {
        NP = 0;
        p = NULL;
        NR = 0;
        //r = NULL;
        maxd = 0.0;
    };

    /*
    double alfaDelta(int ID, char t) {
        double ret = 0.0;
        for (int i = 0;i < NP;i++) {
            for (int j = 0;j < p[i].NT;j++) {
                if (ID == p[i].t[j].ID) {
                    if (t == 'a') ret = p[i].m.alfa;
                    else ret = p[i].m.delta;
                    break;
                }
            }
        }
        return ret;
    };
    */

    bool Inner(point p, triangle t) {
        double a1, a2, x, y, z, x0, y0, z0, x1, y1, z1, x2, y2, z2;

        x = p.x;
        y = p.y;
        z = p.z;

        x0 = t.p0.x;
        y0 = t.p0.y;
        z0 = t.p0.z;
        x1 = t.p1.x;
        y1 = t.p1.y;
        z1 = t.p1.z;
        x2 = t.p2.x;
        y2 = t.p2.y;
        z2 = t.p2.z;

        if (t.Projection == yz) {                              //Proje��o yz
            a1 = -t.a0 * (-y0 * z + y2 * z + y * z0 - y2 * z0 - y * z2 + y0 * z2);
            a2 = -t.a0 * (y0 * z - y1 * z - y * z0 + y1 * z0 + y * z1 - y0 * z1);
        }
        if (t.Projection == xz) {                              //Proje��o xz
            a1 = -t.a0 * (-x0 * z + x2 * z + x * z0 - x2 * z0 - x * z2 + x0 * z2);
            a2 = -t.a0 * (x0 * z - x1 * z - x * z0 + x1 * z0 + x * z1 - x0 * z1);
        }
        if (t.Projection == xy) {                              //Proje��o xy
            a1 = -t.a0 * (-x2 * y0 + x * y0 + x0 * y2 - x * y2 - x0 * y + x2 * y);
            a2 = t.a0 * (-x1 * y0 + x * y0 + x0 * y1 - x * y1 - x0 * y + x1 * y);
        }

        if ((a1 + a2 <= 1) && (a1 >= 0) && (a2 >= 0))
            return true;
        else
            return false;

    };

    /*
    double IntersectionDistance(vector1 v, vector1 n, point vp, point o) {
        // n -> vector normal del plano
        //v -> rayo
        //vp -> punto del plano
        // o origen del rayo
        vector1 Vd;
        Vd.x = vp.x - o.x;
        Vd.y = vp.y - o.y;
        Vd.z = vp.z - o.z;
        double m;
        m = v * n;
        if (m == 0.0) {
            return -1;
        }
        else {
            return (n * Vd) / m;
        }
    };
    */

    double IntersectionDistance(vector1 n, point p, vector1 u, point o) {
        /*JFLN:
                vector n is the normal vector of the plane
                point p is one of the vertex of the plane
                vector u is the ray
                point o is the initial position of the ray
        */
        double d, m;
        m = n * u;
        //JFLN: Has to have an error tolerance
        if (m == 0)
            return -1;
        d = (n * (p - o)) / m;
        return d;
    };



    void MaxDistance() {
        maxd = 0;
        float tmpd = 0;
        for (int i1 = 0; i1 < NP; i1++) {
            for (int j1 = 0; j1 < p[i1].NP; j1++) {
                for (int i2 = 0; i2 < NP; i2++) {
                    for (int j2 = 0; j2 < p[i2].NP; j2++) {
                        tmpd = p[i1].p[j1].distancia(p[i2].p[j2]);
                        if (maxd < tmpd)
                            maxd = tmpd;
                    }
                }
            }
        }
    };

    void NewPlanes(int N) {
        int P;
        plane* tp;
        tp = new plane[NP + N];
        for (P = 0; P < NP; P++) {
            tp[P] = p[P];
        }
        for (P = NP; P < NP + N; P++) {
            tp[P].Clear();
        }
        if (NP > 0) {
            delete[] p;
            p = NULL;
        }
        p = tp;
        NP += N;
    };

    /*
    void NewReceptor(int N) {
        int R;
        receptor* tr;
        tr = new receptor[NR + N];
        for (R = 0; R < NR; R++) {
            tr[R] = r[R];
        }
        for (R = NR; R < NR + N; R++) {
            tr[R].Clear();
        }
        if (NR > 0) {
            delete[] r;
            r = NULL;
        }
        r = tr;
        NR += N;
    };
    */

    /*
    void DeletePlanes(int NSelectedPlanes, int SelectedPlane[MaxNSelectedPlanes]) {
        bool Del;
        int P,i,j=0;
        if(NP>0&&NSelectedPlanes>0) {
            plane *tp;
            tp=new plane[NP-NSelectedPlanes];
            for(P=0; P<NP; P++) {
                Del=false;
                for(i=0; i<NSelectedPlanes; i++)
                    if(P==SelectedPlane[i])
                        Del=true;
                if(!Del) {
                    tp[j]=p[P];
                    j++;
                }
            }
            delete[] p;
            p=tp;
            NP-=NSelectedPlanes;
        }
    };
    */

    void Deleteplanes(int IP) { //IP indice del punto a borrar
        plane* tp;
        int j = 0;
        tp = new plane[NP - 1];
        if (IP >= 0 && IP < NP) {
            for (int P = 0; P < NP; P++) {
                if (P != IP) {
                    tp[j] = p[P];
                    j++;
                }
            }
        }
        if (NP > 0) {
            delete[] p;
            p = NULL;
        }
        p = tp;
        NP -= -1;

    }

    double Module(vector1 v) { //JFLN: Returns the vector's module
        double m;
        m = sqrt(v * v);
        return m;
    };

    vector1 Normal(vector1 v1) { //JFLN: Returns the vector's unitary vector
    //compare with the function unitario because this funtion is the same in MathFuntions

        double m;
        vector1 v2;
        m = Module(v1);
        if (m == 0)
            v2 = 0;
        else
            v2 = v1 / m;
        return v2;

    };

    reflection* RayTracing(point origen, vector1* Rays, int NRAYS) {

        reflection* ry;
        ry = NULL;

        int
            IntersectedPlane,       //Indice del plano interesectado
            IntersectedTriangle,    //Indice del triangulo intersectado por plano
            IntersectedTriangleId,  //Id �nico del tri�ngulo intersectado
            NReflections,           //N�mero actual de reflexion
            TNReflections,          //N�mero total de reflexiones
            LostRays = 0;             //Contador de rayos perdidos

        double      //Distancia al punto de intersecci�n
            d1,
            d2;

        point       //Puntos para determinar donde existe intersecci�n con el plano
            p1,
            p2,
            p3;

        bool Stop;  //Bandera para detener el procedimiento
        vector1 v;   //vector incidente
        point o;    //punto de partida (origen del vector incidente)

        ry = new reflection[NRAYS];

        NReflections = 0;
        TNReflections = 0;

        //INICIO DEL RAY-TRACING
        MaxDistance();
        for (int R = 0; R < NRAYS; R++) {
            v = Rays[R];  //Asigno el primer rayo del arreglo original a v
            o = origen;

            //Como no existe a�n ninguna reflexion, inicializo con el valor -1
            IntersectedPlane = -1;
            IntersectedTriangle = -1;
            IntersectedTriangleId = -1;

            Stop = false;

            ry[R].N = 0;            //N�mero de reflexion, inincialmente 0
            ry[R].r[0] = o;         //Punto de partida, inicialmente el centro de la fuente
            ry[R].d[0] = 0.0;       //Distancia recorrida, inicialmente 0
            ry[R].lost = false;     //Reflexion perdida? inicialmente falso
            ry[R].Ray = R;          //Rayo asociado a la reflexion

            while (!Stop) {   //Lazo para realizar varias reflexiones
                d1 = maxd;    //Asigno a d1 la m�xima distancia entre puntos de la sala
                for (int P = 0; P < NP; P++) { //Recorro todos los planos de la sala
                    if ((p[P].n * v) < 0) { //Existe ruta de intersecci�n entre un plano y un vector //  && (P!=LastIntersectedPlane)
                        d2 = IntersectionDistance(p[P].n, p[P].p[0], v, o);
                        if ((d2 > 0.0) && (d2 < d1)) { //Verifico que la distancia de vuelo del rayo no sea cero && que no sea mayor a d1 (m�xima distancia de vuelo o otra ruta de intersecci�n con otro plano)
                            p2 = o + (v * d2); //Obtengo el punto de incidencia en el plano
                            for (int T = 0; T < p[P].NT; T++) { //Recorro todos los tri�ngulos del plano
                                if (Inner(p2, p[P].t[T])) {//Verifica si el punto pertenece al tri�ngulo
                                    //Registro la distancia y el punto de intersecci�n
                                    d1 = d2;
                                    p1 = p2;
                                    //Registro los identificadores del elemento interesectado
                                    IntersectedPlane = P;
                                    IntersectedTriangle = T;
                                    IntersectedTriangleId = p[P].t[T].ID;
                                    T = p[P].NT; //Para forzar la finalizaci�n del recorrido de tri�ngulos
                                }
                            }
                        }
                    }
                }
                if (d1 < maxd && IntersectedPlane != -1) {//Si hubo intersecci�n
                    //Calculo el vector reflejo
                    p3 = o;
                    o = p1;//Nuevo punto de partida del vector reflejado
                    v = Normal(v - (p[IntersectedPlane].n * (v * p[IntersectedPlane].n * 2))); //F�rmula del vector reflejo
                    NReflections++;
                    TNReflections += NReflections;
                    ry[R].r[NReflections] = p1;                                   //Puntos de aplicaci�n
                    ry[R].d[NReflections] = Module(p1 - p3);                        //Distancia entre punto y punto
                    ry[R].idTriangle[NReflections] = IntersectedTriangleId;       //Id �nico del tri�ngulo por cuarto donde se choc�
                    ry[R].Plane[NReflections] = IntersectedPlane;                 //Nro. del plano por cuarto donde se choc�
                    ry[R].Triangle[NReflections] = IntersectedTriangle;           //Nro. del tri�ngulo por plano donde se choc�
                    ry[R].N = NReflections;                                       //JFLN: Number of reflections

                    //M�ximo 50 reflexiones
                    if (NReflections > 50) {
                        Stop = true;                  //No realizo m�s reflexiones con este rayo
                        NReflections = 0;             //Reseteo el contador de reflexiones para el siguiente rayo
                        IntersectedPlane = -1;        //Reseteo el identificador de plano intersecado
                        IntersectedTriangle = -1;     //Reseteo el identificador de triangulo intersecado
                        IntersectedTriangleId = -1;   //Reseteo el identificador �nico de triangulo intersecado
                    }
                }
                else {//No hubo intersecci�n
                    NReflections++;
                    ry[R].lost = true;//JFLN: reflexi�n perdida
                    p3 = o + (v * maxd); //Define un punto fuera de la sala para ilustrar el rayo perdido
                    ry[R].r[NReflections] = p3;//Defino un punto fuera de la sala para ilustrar el rayo perdido
                    ry[R].N = NReflections;//Punto fuera de la sala
                    LostRays++;                 //Contador de rayos perdidos
                    Stop = true;                  //No realizo m�s reflexiones con el rayo perdido
                    NReflections = 0;             //Reseteo el contador de reflexiones para el siguiente rayo
                    IntersectedPlane = -1;        //Reseteo el identificador de plano intersecado
                    IntersectedTriangle = -1;     //Reseteo el identificador de triangulo intersecado
                    IntersectedTriangleId = -1;   //Reseteo el identificador �nico de triangulo intersecado
                }
            }
        }
        return ry;
    };


};

//---------------------------------------------------------------------------

class source {
public:
    point p;                //Posici�n
    vector1* Rays;           //Direcciones de partida de los rayos
    int NRAYS;              //N�mero de rayos
    double eF;              //Energ�a inicial de la fuente
    triangle IcoFace[20];   //Representaci�n gr�fica de la fuente
    double VisualRadius;    //Tama�o de la fuente (radio visual)
    color Color;            //Color de la fuente

    source() {   //Inicializo las variables de la clase.
        p = 0.0;
        eF = 0.0;
        NRAYS = 0;
        Rays = NULL;

        Color.R = 1;
        Color.G = 0.5;
        Color.B = 0.5;

        VisualRadius = 0.1;

        //create icosaedron
        double S, R;
        point IcoVertex[12];

        //create vertexes
        S = 2 / sqrt(5);
        R = (5 - sqrt(5)) / 5;
        IcoVertex[0].x = 0;
        IcoVertex[0].y = 0;
        IcoVertex[0].z = 1;
        for (int i = 1; i < 6; i++) {
            IcoVertex[i].x = S * cos((PI * i * 72) / 180);
            IcoVertex[i].y = S * sin((PI * i * 72) / 180);
            IcoVertex[i].z = 1 - R;
            IcoVertex[i + 5].x = S * cos((72 * PI * i) / 180 + (36 * PI) / 180);
            IcoVertex[i + 5].y = S * sin((72 * PI * i) / 180 + (36 * PI) / 180);
            IcoVertex[i + 5].z = R - 1;
        }
        IcoVertex[11].x = 0;
        IcoVertex[11].y = 0;
        IcoVertex[11].z = -1;

        //create faces
        IcoFace[0].p0 = IcoVertex[0];   IcoFace[0].p1 = IcoVertex[1];   IcoFace[0].p2 = IcoVertex[2];
        IcoFace[1].p0 = IcoVertex[0];   IcoFace[1].p1 = IcoVertex[2];   IcoFace[1].p2 = IcoVertex[3];
        IcoFace[2].p0 = IcoVertex[0];   IcoFace[2].p1 = IcoVertex[3];   IcoFace[2].p2 = IcoVertex[4];
        IcoFace[3].p0 = IcoVertex[0];   IcoFace[3].p1 = IcoVertex[4];   IcoFace[3].p2 = IcoVertex[5];
        IcoFace[4].p0 = IcoVertex[0];   IcoFace[4].p1 = IcoVertex[5];   IcoFace[4].p2 = IcoVertex[1];
        IcoFace[5].p0 = IcoVertex[1];   IcoFace[5].p1 = IcoVertex[6];   IcoFace[5].p2 = IcoVertex[2];
        IcoFace[6].p0 = IcoVertex[2];   IcoFace[6].p1 = IcoVertex[6];   IcoFace[6].p2 = IcoVertex[7];
        IcoFace[7].p0 = IcoVertex[2];   IcoFace[7].p1 = IcoVertex[7];   IcoFace[7].p2 = IcoVertex[3];
        IcoFace[8].p0 = IcoVertex[3];   IcoFace[8].p1 = IcoVertex[7];   IcoFace[8].p2 = IcoVertex[8];
        IcoFace[9].p0 = IcoVertex[3];   IcoFace[9].p1 = IcoVertex[8];   IcoFace[9].p2 = IcoVertex[4];
        IcoFace[10].p0 = IcoVertex[4];  IcoFace[10].p1 = IcoVertex[8];  IcoFace[10].p2 = IcoVertex[9];
        IcoFace[11].p0 = IcoVertex[4];  IcoFace[11].p1 = IcoVertex[9];  IcoFace[11].p2 = IcoVertex[5];
        IcoFace[12].p0 = IcoVertex[5];  IcoFace[12].p1 = IcoVertex[9];  IcoFace[12].p2 = IcoVertex[10];
        IcoFace[13].p0 = IcoVertex[5];  IcoFace[13].p1 = IcoVertex[10]; IcoFace[13].p2 = IcoVertex[1];
        IcoFace[14].p0 = IcoVertex[1];  IcoFace[14].p1 = IcoVertex[10]; IcoFace[14].p2 = IcoVertex[6];
        IcoFace[15].p0 = IcoVertex[6];  IcoFace[15].p1 = IcoVertex[11]; IcoFace[15].p2 = IcoVertex[7];
        IcoFace[16].p0 = IcoVertex[7];  IcoFace[16].p1 = IcoVertex[11]; IcoFace[16].p2 = IcoVertex[8];
        IcoFace[17].p0 = IcoVertex[8];  IcoFace[17].p1 = IcoVertex[11]; IcoFace[17].p2 = IcoVertex[9];
        IcoFace[18].p0 = IcoVertex[9];  IcoFace[18].p1 = IcoVertex[11]; IcoFace[18].p2 = IcoVertex[10];
        IcoFace[19].p0 = IcoVertex[10]; IcoFace[19].p1 = IcoVertex[11]; IcoFace[19].p2 = IcoVertex[6];
    };

    void createRays(double NumberOfRays) {
        //matriz das Arestas {1o ponto da aresta, 2o ponto da aresta, Posi��o dos pontos da aresta na matriz Rays}
        int A[30][3] = { {0,1,0}, {0,2,0}, {0,3,0}, {0,4,0}, {0,5,0},
                        {1,6,0}, {2,6,0}, {2,7,0}, {3,7,0}, {3,8,0},
                        {4,8,0}, {4,9,0}, {5,9,0}, {5,10,0},{1,10,0},
                        {6,11,0},{7,11,0},{8,11,0},{9,11,0},{10,11,0},
                        {1,2,0}, {2,3,0}, {3,4,0}, {4,5,0}, {5,1,0},
                        {6,7,0}, {7,8,0}, {8,9,0}, {9,10,0},{10,6,0}
        };
        //matriz dos triangulos {1a aresta, 2a aresta, [0] V em p� [-1] V de cabe�a pra baixo}
        int T[20][3] = { {0,1,0},   {1,2,0},   {2,3,0},   {3,4,0},   {4,0,0},
                        {5,6,-1},  {6,7,0},   {7,8,-1},  {8,9,0},   {9,10,-1},
                        {10,11,0}, {11,12,-1},{12,13,0}, {13,14,-1},{14,5,0},
                        {15,16,-1},{16,17,-1},{17,18,-1},{18,19,-1},{19,15,-1}
        };
        int i, j, k, n, m, RAY;
        double S, R, xB, yB, zB, xC, yC, zC, c[8];
        //create Rays matrix
        if (NRAYS > 0)
            delete[] Rays;
        n = int(floor(sqrt((NumberOfRays - 2) / 10) + 0.5));
        NRAYS = int(2 + 10 * pow(n, 2));
        Rays = new vector1[NRAYS];
        //calculating the icosaedron vertives
        S = 2 / sqrt(5);
        R = (5 - sqrt(5)) / 5;
        Rays[0].x = 0;
        Rays[0].y = 0;
        Rays[0].z = 1;
        for (i = 1; i < 6; i++) {
            Rays[i].x = S * cos((PI * i * 72) / 180);
            Rays[i].y = S * sin((PI * i * 72) / 180);
            Rays[i].z = 1 - R;
            Rays[i + 5].x = S * cos((72 * PI * i) / 180 + (36 * PI) / 180);
            Rays[i + 5].y = S * sin((72 * PI * i) / 180 + (36 * PI) / 180);
            Rays[i + 5].z = R - 1;
        }
        Rays[11].x = 0;
        Rays[11].y = 0;
        Rays[11].z = -1;
        RAY = 12;
        //calculating the rays on the icosaedron edges
        for (j = 0; j < 30; j++) {
            A[j][2] = RAY;
            xB = Rays[A[j][0]].x;
            yB = Rays[A[j][0]].y;
            zB = Rays[A[j][0]].z;
            xC = Rays[A[j][1]].x;
            yC = Rays[A[j][1]].y;
            zC = Rays[A[j][1]].z;
            c[0] = pow(xC, 2) * (pow(yB, 2) + pow(zB, 2)) + pow(yC * zB - yB * zC, 2) - 2 * xB * xC * (yB * yC + zB * zC) + pow(xB, 2) * (pow(yC, 2) + pow(zC, 2));
            c[1] = acos(xB * xC + yB * yC + zB * zC);
            c[2] = -xC * (yB * yC + zB * zC) + xB * (pow(yC, 2) + pow(zC, 2));
            c[3] = xC * (pow(yB, 2) + pow(zB, 2)) - xB * (yB * yC + zB * zC);
            c[4] = pow(xC, 2) * yB - xB * xC * yC + zC * (-yC * zB + yB * zC);
            c[5] = -xB * xC * yB + pow(xB, 2) * yC + zB * (yC * zB - yB * zC);
            c[6] = pow(xC, 2) * zB - xB * xC * zC + yC * (yC * zB - yB * zC);
            c[7] = -xB * xC * zB + pow(xB, 2) * zC + yB * (-yC * zB + yB * zC);
            for (i = 1; i < n; i++) {
                Rays[RAY].x = (c[2] * cos(i * c[1] / n) + c[3] * cos((n - i) * c[1] / n)) / c[0];
                Rays[RAY].y = (c[4] * cos(i * c[1] / n) + c[5] * cos((n - i) * c[1] / n)) / c[0];
                Rays[RAY].z = (c[6] * cos(i * c[1] / n) + c[7] * cos((n - i) * c[1] / n)) / c[0];
                RAY++;
            }
        }
        //calculating the rays on the icosaedron faces
        for (k = 0; k < 20; k++)
            for (j = 1; j < n; j++) {
                xB = Rays[A[T[k][0]][2] + j - 1].x;
                yB = Rays[A[T[k][0]][2] + j - 1].y;
                zB = Rays[A[T[k][0]][2] + j - 1].z;
                xC = Rays[A[T[k][1]][2] + j - 1].x;
                yC = Rays[A[T[k][1]][2] + j - 1].y;
                zC = Rays[A[T[k][1]][2] + j - 1].z;
                c[0] = pow(xC, 2) * (pow(yB, 2) + pow(zB, 2)) + pow(yC * zB - yB * zC, 2) - 2 * xB * xC * (yB * yC + zB * zC) + pow(xB, 2) * (pow(yC, 2) + pow(zC, 2));
                c[1] = acos(xB * xC + yB * yC + zB * zC);
                c[2] = -xC * (yB * yC + zB * zC) + xB * (pow(yC, 2) + pow(zC, 2));
                c[3] = xC * (pow(yB, 2) + pow(zB, 2)) - xB * (yB * yC + zB * zC);
                c[4] = pow(xC, 2) * yB - xB * xC * yC + zC * (-yC * zB + yB * zC);
                c[5] = -xB * xC * yB + pow(xB, 2) * yC + zB * (yC * zB - yB * zC);
                c[6] = pow(xC, 2) * zB - xB * xC * zC + yC * (yC * zB - yB * zC);
                c[7] = -xB * xC * zB + pow(xB, 2) * zC + yB * (-yC * zB + yB * zC);
                if (T[k][2] == 0)m = j;
                else m = n - j;
                for (i = 1; i < m; i++) {
                    Rays[RAY].x = (c[2] * cos(i * c[1] / m) + c[3] * cos((m - i) * c[1] / m)) / c[0];
                    Rays[RAY].y = (c[4] * cos(i * c[1] / m) + c[5] * cos((m - i) * c[1] / m)) / c[0];
                    Rays[RAY].z = (c[6] * cos(i * c[1] / m) + c[7] * cos((m - i) * c[1] / m)) / c[0];
                    RAY++;
                }
            }
    };
};
//---------------------------------------------------------------------------







inline double Module(vector1 v) { //JFLN: Returns the vector's module
    double m;
    m = sqrt(v * v);
    return m;
}
//---------------------------------------------------------------------------
inline vector1 VectorUnitario(vector1 v1) { //JFLN: Returns the vector's unitary vector
    double m;
    vector1 v2;
    m = Module(v1);
    if (m == 0)
        v2 = 0;
    else
        v2 = v1 / m;
    return v2;
}

inline vector1 TriangleNormal(triangle t) {
    vector1 n;
    n = VectorUnitario((t.p1 - t.p0) / (t.p2 - t.p0));
    return n;
};

inline vector1 NormalPlano(plane p) {
    vector1 n;
    n = VectorUnitario((p.p[1] - p.p[0]) / (p.p[2] - p.p[0]));
    return n;
}


#endif