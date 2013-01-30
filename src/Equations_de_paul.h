/* 
 * File:   equations_de_paul.h
 * Author: ygorra
 * Created on 17 octobre 2012, 17:16
 * RESOLUTION DES EQUATIONS DE PAUL
 */

#ifndef EQUATIONS_DE_PAUL_H
#define	EQUATIONS_DE_PAUL_H

//#ifdef	__cplusplus
extern "C" {
  //#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#define _INFINITY -1
#ifndef PI
#define PI 3.14159265358979323846 
#endif

    typedef struct {
        //char solve_type_1(struct_type_1 *S, double X, double Y)
        char name[1024];
        char well_posed; // TRUE or FALSE
        int nb_sols; // 0, finished number, or _INFINITY
        double X, Y;
        double Li[2];
    } struct_type_1;

    typedef struct {
        //equation de type 2 :
        // X.sin(Ai)+Y.cos(Ai)=Z <=> sin(alpha+Ai)=cte
        char name[1024];
        char well_posed; // TRUE or FALSE
        int nb_sols; // 0, finished number, or _INFINITY
        double X, Y, Z;
        double Ai[2], verif[2];
        double cos_alpha, sin_alpha, alpha, cte;
    } struct_type_2;

    typedef struct {
        //equation de type 3
        // [1] X1.sin(Ai) + Y1.cos(Ai) = Z1
        // [2] X2.sin(Ai) + Y2.cos(Ai) = Z2
        char name[1024];
        char well_posed; // TRUE or FALSE
        int nb_sols; // 0, finished number, or _INFINITY
        double X1, Y1, Z1, X2, Y2, Z2;
        double Ai[2];
        double cos_alpha, sin_alpha, alpha, cte;
        struct_type_2 sol_type_2_x1y1z1;
        struct_type_2 sol_type_2_x2y2z2;
    } struct_type_3;

    typedef struct {
        //equation de type 4 :
        // [1] X1.Rj.sin(Ai)=Y1
        // [2] X2.Rj.cos(Ai)=Y2
        char name[1024];
        char well_posed; // TRUE or FALSE
        int nb_sols; // 0, finished number, or _INFINITY
        double X1, Y1, X2, Y2;
        double Ai[2], Rj[2];
        double verif_1[2], verif_2[2];
    } struct_type_4;

    typedef struct {
        //equation de type 5 
        //  [1] X1 . sin(Ai)=Y1 + Z1 . Rj
        //  [2] X2 . cos(Ai)=Y2 + Z2 . Rj
        char name[1024];
        char well_posed; // TRUE or FALSE
        int nb_sols; // 0, finished number, or _INFINITY
        double Ai[2], Rj[2];
        double X1, Y1, Z1, X2, Y2, Z2;
        double a0, a1, a2, delta;
        double verif_1[2], verif_2[2];
    } struct_type_5;

    typedef struct {
        //equation de type 6:
        //  [1] W.sin(Ak)=X.cos(Ai) + Y.sin(Ai)+Z1;
        //  [2] W.cos(Ak)=X.sin(Ai) - Y.cos(Ai)+Z2
        char name[1024];
        char well_posed; // TRUE or FALSE
        int nb_sols; // 0, finished number, or _INFINITY
        double Ai[2], Ak[2];
        double W, X, Y, Z1, Z2;
        struct_type_2 sol_type_2;
        double a0, a1, a2, delta;
        double verif_1[2], verif_2[2];
    } struct_type_6;

    typedef struct {
        //equation de type 7 :
        //  [1] W2.sin(Ak) + W1.cos(Ak) = X.cos(Ai) +Y.sin(Ai) +Z1;
        //  [2] W2.cos(Ak) - W1.sin(Ak) = X.sin(Ai) -Y.cos(Ai) +Z2
        char name[1024];
        char well_posed; // TRUE or FALSE
        int nb_sols; // 0, finished number, or _INFINITY
        double Ai[2], Ak[2];
        double W1, W2, X, Y, Z1, Z2;
        double W, alpha;
        struct_type_6 sol_type_6;
        double verif_1[2], verif_2[2];
    } struct_type_7;

    typedef struct {
        //equation de type 8 :
        // [1] X.cos(Ai) + Y.cos(Ak) = Z1
        // [2] X.sin(Ai) + Y.sin(Ak) = Z2
        char name[1024];
        char well_posed; // TRUE or FALSE
        int nb_sols; // 0, finished number, or _INFINITY
        double X, Y, Z1, Z2;
        double Ai[2], Ak[2];
        struct_type_2 sol_type_2;
        double verif_1[2], verif_2[2];
    } struct_type_8;

    char solve_type_1(struct_type_1 *S, double X, double Y);
    char solve_type_2(struct_type_2 *S, double X, double Y, double Z);
    char solve_type_3(struct_type_3 *S, double X1, double Y1, double Z1, double X2, double Y2, double Z2);
    char solve_type_4(struct_type_4 *S, double X1, double Y1, double X2, double Y2);
    char solve_type_5(struct_type_5 *S, double X1, double Y1, double Z1, double X2, double Y2, double Z2);
    char solve_type_6(struct_type_6 *S, double W, double X, double Y, double Z1, double Z2);
    char solve_type_7(struct_type_7 *S, double W1, double W2, double X, double Y, double Z1, double Z2);
    char solve_type_8(struct_type_8 *S, double X, double Y, double Z1, double Z2);

  //#ifdef	__cplusplus
}
//#endif

#endif	/* EQUATIONS_DE_PAUL_H */

