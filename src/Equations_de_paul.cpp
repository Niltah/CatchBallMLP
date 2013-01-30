#include <math.h>
#include <string.h>

#include "Equations_de_paul.h"

double get_arg_nearest_zero(double a) {
    long q = round(a / (2 * PI));
    double a0 = a - 2 * PI*q;
    return a0;
}
//--------------------------------------------------------------
// solution d'une equation de type 1
//--------------------------------------------------------------

char solve_type_1(struct_type_1 *S, double X, double Y) {
    strcpy(S->name, "equation de type 1 :X.Li=Y");
    S->well_posed = FALSE; // equation mal posee
    S->X = X;
    S->Y = Y;
    if ((X == 0) && (Y == 0)) {
        S->nb_sols = _INFINITY; // infinite de solutions
        return FALSE;
    }
    S->well_posed = TRUE; // equation bien posee
    if (X == 0) {
        S->nb_sols = 0;
        return FALSE;
    }
    S->nb_sols = 1;
    S->Li[0] = Y / X;
    return TRUE;
}

//--------------------------------------------------------------
// solution d'une equation de type 2
//--------------------------------------------------------------

char solve_type_2(struct_type_2 *S, double X, double Y, double Z) {
    double Ai;
    double abs_Z;
    int n;
    strcpy(S->name, "equation de type 2 :X.sin(Ai)+Y.cos(Ai)=Z<=>sin(alpha+Ai)=cte");
    S->well_posed = FALSE; // equation mal posee
    S->X = X;
    S->Y = Y;
    S->Z = Z;
    double module = sqrt(X * X + Y * Y);
    abs_Z = (Z >= 0) ? Z : -Z;
    if (module < abs_Z) {
        S->nb_sols = 0;
        S->well_posed = TRUE;
        return FALSE;
    }
    if (module == 0) {
        S->nb_sols = _INFINITY;
        S->well_posed = FALSE;
        return FALSE;
    }
    S->nb_sols = 2;
    S->well_posed = TRUE;
    S->cos_alpha = X / module;
    S->sin_alpha = Y / module;
    S->alpha = atan2(S->sin_alpha, S->cos_alpha);
    S->cte = Z / module;
    S->Ai[0] = asin(S->cte) - S->alpha;
    S->Ai[1] = PI - asin(S->cte) - S->alpha;
    S->Ai[0] = get_arg_nearest_zero(S->Ai[0]);
    S->Ai[1] = get_arg_nearest_zero(S->Ai[1]);
    for (n = 0; n < S->nb_sols; n++) {
        Ai = S->Ai[n];
        S->verif[n] = Z - (X * sin(Ai) + Y * cos(Ai));
    }
    return TRUE;
    // les 2 solutions de sin(alpha+A)=cte sont  A1 =asin(cte)-alpha, et A2 =pi - asin(cte) -alpha
}
//--------------------------------------------------------------
// solution d'une equation de type 3
//--------------------------------------------------------------

char solve_type_3(struct_type_3 *S, double X1, double Y1, double Z1, double X2, double Y2, double Z2) {
    struct_type_2 *S_1, *S_2;
    double A1, C1, S1, A2, C2, S2;
    double square_err, square_tol;
    int i1, i2, nb_sols;
    strcpy(S->name, "equation de type 3 :[1] X1.sin(Ai)+Y1.cos(Ai)=Z1;[2] X2.sin(Ai)+Y2.cos(Ai)=Z2");
    S->well_posed = FALSE; // equation mal posee
    S->X1 = X1;
    S->Y1 = Y1;
    S->Z1 = Z1;
    S->X2 = X2;
    S->Y2 = Y2;
    S->Z2 = Z2;
    solve_type_2(&(S->sol_type_2_x1y1z1), X1, Y1, Z1);
    solve_type_2(&(S->sol_type_2_x2y2z2), X2, Y2, Z2);
    S->well_posed = S->sol_type_2_x1y1z1.well_posed && S->sol_type_2_x2y2z2.well_posed;
    S->nb_sols = S->sol_type_2_x1y1z1.nb_sols;
    if (S->sol_type_2_x2y2z2.nb_sols < S->nb_sols) {
        S->nb_sols = S->sol_type_2_x2y2z2.nb_sols;
    };
    if ((S->well_posed == FALSE) || (S->nb_sols <= 0)) {
        return FALSE;
    }
    S_1 = &(S->sol_type_2_x1y1z1);
    S_2 = &(S->sol_type_2_x2y2z2);

    // intersection des angles
    // pour eviter les erreurs dues au modulo 2pi
    // on raisonne sur le module de la fiffrence z1-z2, avec z1=cos(A1)+i.sin(A1),z2=cos(A2)+i.sin(A2)
    // de plus comme numeriquement on n'obtiendra jamais l'egalite z1=z2, on se donne une tolerance
    square_tol = 1e-6 * 1e-6; // tolerance ^2
    nb_sols = 0;
    for (i1 = 0; i1 < S_1->nb_sols; i1++) {
        A1 = S_1->Ai[i1];
        C1 = cos(A1);
        S1 = sin(A1);
        for (i2 = 0; i2 < S_2->nb_sols; i2++) {
            A2 = S_2->Ai[i2];
            C2 = cos(A2);
            S2 = sin(A2);
            square_err = (C1 - C2)*(C1 - C2)+(S1 - S2)*(S1 - S2);
            if (square_err < square_tol) {
                // on ajoute Ai aux solutions
                S->Ai[nb_sols++] = get_arg_nearest_zero(A1);
            }
        }
    }
    S->nb_sols = nb_sols;
    return S->well_posed;
}


//--------------------------------------------------------------
// solution d'une equation de type 8
//--------------------------------------------------------------

char solve_type_8(struct_type_8 *S, double X, double Y, double Z1, double Z2) {
    double XT2, YT2, ZT2;
    int n;
    double Ai, re, im, Ak, sign_Y;
    strcpy(S->name, "equation de type 8 :[1] X.cos (Ai)+Y.cos(Ak)=Z1;[2] X.sin(Ai)+Y.sin(Ak)=Z2");
    S->well_posed = FALSE; // equation mal posee
    S->X = X;
    S->Y = Y;
    S->Z1 = Z1;
    S->Z2 = Z2;
    // parametres et resolution de l'equation de type 2 deduite de [1]^2+[2]^2
    XT2 = -2 * X*Z2;
    YT2 = -2 * X*Z1;
    ZT2 = Y * Y - X * X - Z1 * Z1 - Z2*Z2;
    solve_type_2(&(S->sol_type_2), XT2, YT2, ZT2);
    S->well_posed = S->sol_type_2.well_posed;
    S->nb_sols = S->sol_type_2.nb_sols;
    if ((S->well_posed == FALSE) || (S->nb_sols <= 0)) {
        return FALSE;
    }
    for (n = 0; n < S->nb_sols; n++) {
        S->Ai[n] = S->sol_type_2.Ai[n];
    }
    sign_Y = (Y >= 0) ? 1 : -1;
    for (n = 0; n < S->nb_sols; n++) {
        Ai = S->Ai[n];
        im = Z2 - X * sin(Ai);
        re = Z1 - X * cos(Ai);
        Ak = atan2(im*sign_Y, re * sign_Y);
        S->Ak[n] = Ak;
        S->verif_1[n] = X * cos(Ai) + Y * cos(Ak) - Z1;
        S->verif_2[n] = X * sin(Ai) + Y * sin(Ak) - Z2;
        S->Ai[n] = get_arg_nearest_zero(S->Ai[n]);
        S->Ak[n] = get_arg_nearest_zero(S->Ak[n]);
    }
    return S->nb_sols>0;
}

//--------------------------------------------------------------
// solution d'une equation de type 4
//--------------------------------------------------------------

char solve_type_4(struct_type_4 *S, double X1, double Y1, double X2, double Y2) {
    char well_posed_1, well_posed_2;
    double X1_2, X2_2, Y1_2, Y2_2, Ai, Rj;
    int n;
    double sign_X1Rj, sign_X2Rj;
    strcpy(S->name, "equation de type 4 :[1]X1.Rj.sin(Ai)=Y1 ;[2] X2.Rj.cos(Ai)=Y2");
    S->X1 = X1;
    S->Y1 = Y1;
    S->X2 = X2;
    S->Y2 = Y2;
    well_posed_1 = TRUE;
    if (X1 == 0) {
        well_posed_1 = FALSE;
        if (Y1 == 0) {
            S->nb_sols = _INFINITY;
        } else {
            S->nb_sols = 0;
        }
    }
    well_posed_2 = TRUE;
    if (X2 == 0) {
        well_posed_2 = FALSE;
        if (Y2 == 0) {
            S->nb_sols = _INFINITY;
        } else {
            S->nb_sols = 0;
        }
    }
    S->well_posed = well_posed_1 & well_posed_2;
    if (S->well_posed == FALSE) {
        return FALSE;
    }
    X1_2 = X1*X1;
    Y1_2 = Y1*Y1;
    X2_2 = X2*X2;
    Y2_2 = Y2*Y2;

    Rj = (X2_2 * Y1_2 + X1_2 * Y2_2) / (X1_2 * X2_2);
    Rj = sqrt(Rj);
    S->Rj[0] = Rj;
    S->Rj[1] = -Rj;
    S->nb_sols = 2;

    for (n = 0; n < S->nb_sols; n++) {
        Rj = S->Rj[n];
        sign_X1Rj = (X1 * Rj >= 0) ? 1 : -1;
        sign_X2Rj = (X2 * Rj >= 0) ? 1 : -1;
        Ai = atan2(Y1 * sign_X1Rj, Y2 * sign_X2Rj);
        Ai = get_arg_nearest_zero(Ai);
        S->Ai[n] = Ai;
        S->verif_1[n] = X1 * Rj * sin(Ai) - Y1;
        S->verif_2[n] = X2 * Rj * cos(Ai) - Y2;
    }
    return (S->nb_sols > 0);
}


//--------------------------------------------------------------
// solution d'une equation de type 5
//--------------------------------------------------------------

char solve_type_5(struct_type_5 *S, double X1, double Y1, double Z1, double X2, double Y2, double Z2) {
    char well_posed_1, well_posed_2;
    double X1_2, Y1_2, Z1_2, X2_2, Y2_2, Z2_2;
    int n;
    double Rj, im, re, Ai;
    strcpy(S->name, "equation de type 5 :[1]X1.sin(Ai)=Y1 +Z1 .Rj ;[2] X2. cos(Ai)=Y2 + Z2 . Rj ");
    S->X1 = X1;
    S->Y1 = Y1;
    S->Z1 = Z1;
    S->X2 = X2;
    S->Y2 = Y2;
    S->Z2 = Z2;
    well_posed_1 = TRUE;
    if (X1 == 0) {
        well_posed_1 = FALSE;
        S->nb_sols = _INFINITY;
    }
    well_posed_2 = TRUE;
    if (X2 == 0) {
        well_posed_2 = FALSE;
        S->nb_sols = _INFINITY;
    }
    S->well_posed = well_posed_1 & well_posed_2;
    if (S->well_posed == FALSE) {
        return FALSE;
    }
    X1_2 = X1*X1;
    X2_2 = X2*X2;
    Y1_2 = Y1*Y1;
    Y2_2 = Y2*Y2;
    Z1_2 = Z1*Z1;
    Z2_2 = Z2*Z2;
    S->a0 = X2_2 * Y1_2 + X1_2 * Y2_2 - X1_2 * X2_2;
    S->a1 = 2 * (X2_2 * Y1 * Z1 + X1_2 * Y2 * Z2);
    S->a2 = X2_2 * Z1_2 + X1_2 * Z2_2;
    if (S->a2 == 0) {
        // ordre 1
        S->well_posed = S->a1 != 0;
        if (S->well_posed == FALSE) {
            S->nb_sols = 0;
            return FALSE;
        }
        S->Rj[0] = -S->a0 / S->a1;
        S->nb_sols = 1;
    } else {
        // ordre 2
        S->delta = S->a1 * S->a1 - 4 * S->a2 * S->a0;
        if (S->delta < 0) {
            // pas de solutions
            S->nb_sols = 0;
            return FALSE;
        }
        if (S->delta == 0) {
            // 1 solution (double, mais on s'en moque)
            S->Rj[0] = -S->a1 / (2 * S->a2);
            S->nb_sols = 1;
        }
        if (S->delta > 0) {
            // 2 solutions
            S->Rj[0] = (-S->a1 - sqrt(S->delta)) / (2 * S->a2);
            S->Rj[1] = (-S->a1 + sqrt(S->delta)) / (2 * S->a2);
            S->nb_sols = 2;
        }
    } // else if S->a2==0
    for (n = 0; n < S->nb_sols; n++) {
        Rj = S->Rj[n];
        im = (Y1 + Z1 * Rj) / X1;
        re = (Y2 + Z2 * Rj) / X2;
        Ai = get_arg_nearest_zero(atan2(im, re));
        S->Ai[n] = Ai;
        S->verif_1[n] = X1 * sin(Ai)- (Y1 + Z1 * Rj);
        S->verif_2[n] = X2 * cos(Ai)- (Y2 + Z2 * Rj);
    }
    return S->nb_sols>0;
}

//--------------------------------------------------------------
// solution d'une equation de type 6
//--------------------------------------------------------------

char solve_type_6(struct_type_6 *S, double W, double X, double Y, double Z1, double Z2) {
    double XT2, YT2, ZT2;
    int n;
    double Ai, im, re, sign_W, Ak;
    strcpy(S->name, "equation de type 6 :[1] W.sin (Ak)=X.cos(Ai)+Y.sin(Ai)+Z1;[2] W.cos(Ak)=X.sin(Ai)-Y.cos(Ai)+Z2");
    S->W = W;
    S->X = X;
    S->Y = Y;
    S->Z1 = Z1;
    S->Z2 = Z2;
    // parametres et resolution de l'equation de type 2 deduite de [1]^2+[2]^2
    ZT2 = W * W - Z1 * Z1 - Z2 * Z2 - X * X - Y*Y;
    XT2 = 2 * X * Z2 + 2 * Y*Z1;
    YT2 = 2 * X * Z1 - 2 * Y*Z2;
    solve_type_2(&(S->sol_type_2), XT2, YT2, ZT2);
    S->well_posed = S->sol_type_2.well_posed;
    S->nb_sols = S->sol_type_2.nb_sols;
    if (S->well_posed == FALSE) {
        return FALSE;
    }
    sign_W = (W >= 0) ? 1 : -1;
    for (n = 0; n < S->nb_sols; n++) {
        S->Ai[n] = get_arg_nearest_zero(S->sol_type_2.Ai[n]);
        Ai = S->Ai[n];
        im = X * cos(Ai) + Y * sin(Ai) + Z1;
        re = X * sin(Ai) - Y * cos(Ai) + Z2;
        Ak = atan2(im*sign_W, re * sign_W);
        S->Ak[n] = get_arg_nearest_zero(Ak);
        //S->verif_square[n]=( X*cos(Ai)+Y*sin(Ai)+Z1 )^2+( X*sin(Ai)-Y*cos(Ai)+Z2 )^2;
        S->verif_1[n] = W * sin(Ak) - (X * cos(Ai) + Y * sin(Ai) + Z1);
        S->verif_2[n] = W * cos(Ak) - (X * sin(Ai) - Y * cos(Ai) + Z2);
    }
    return S->nb_sols>0;
}

//--------------------------------------------------------------
// solution d'une equation de type 7
//--------------------------------------------------------------

char solve_type_7(struct_type_7 *S, double W1, double W2, double X, double Y, double Z1, double Z2) {
    int n;
    double Ai, Ak;
    strcpy(S->name, "equation de type 7 :[1] W2.sin(Ak)+W1.cos(Ak) =X.cos(Ai)+Y.sin(Ai)+Z1;[2] W2.cos(Ak) - W1. sin (Ak)=X.sin(Ai)-Y.cos(Ai)+Z2");
    S->W1 = W1;
    S->W2 = W2;
    S->X = X;
    S->Y = Y;
    S->Z1 = Z1;
    S->Z2 = Z2;
    S->W = sqrt(W1 * W1 + W2 * W2);
    S->alpha = atan2(W1, W2);
    solve_type_6(&(S->sol_type_6), S->W, X, Y, Z1, Z2);
    S->well_posed = S->sol_type_6.well_posed;
    S->nb_sols = S->sol_type_6.nb_sols;
    if ((S->well_posed == FALSE) || (S->nb_sols <= 0)) {
        return FALSE;
    }
    for (n = 0; n < S->nb_sols; n++) {
        S->Ai[n] = S->sol_type_6.Ai[n];
        S->Ak[n] = get_arg_nearest_zero(S->sol_type_6.Ak[n] - S->alpha);
        Ai = S->Ai[n];
        Ak = S->Ak[n];
        S->verif_1[n] = W1 * cos(Ak) + W2 * sin(Ak) - (X * cos(Ai) + Y * sin(Ai) + Z1);
        S->verif_2[n] = (-W1 * sin(Ak)) + W2 * cos(Ak) - (X * sin(Ai) - Y * cos(Ai) + Z2);
    }
    return (S->nb_sols > 0);
}

