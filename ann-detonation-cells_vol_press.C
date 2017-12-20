#include <stdio.h>
#include <math.h>

/* function declaration - network evaluation */
void export_eval(const double*, double*);


/* ------------------------------------------------------------ */


static const double export_in_A[25] = {
 6.006006006006007, 0, 0, 0,
 0, 0, 0.001417786622391395, 0,
 0, 0, 0, 0,
 2.192669904509226, 0, 0, 0,
 0, 0, 2, 0,
 0, 0, 0, 0,
 2
};


static const double export_in_b[5] = {
 -2.003003003003003, -3.332664654340537, -1.195410741889862, -1,
 -1
};


void
export_in(const double *x, double *y)
{
    int k = 0, i, j;
    for (i = 0; i < 5; ++i) {
        y[i] = export_in_b[i];
        for (j = 0; j < 5; ++j, ++k) {
            y[i] += export_in_A[k] * x[j];
        }
    }
}


static const double export_out_A[1] = {
 1.147315646043288
};


static const double export_out_b[1] = {
 1.358714706241739
};


void
export_out(const double *x, double *y)
{
    int k = 0, i, j;
    for (i = 0; i < 1; ++i) {
        y[i] = export_out_b[i];
        for (j = 0; j < 1; ++j, ++k) {
            y[i] += export_out_A[k] * x[j];
        }
    }
}


static const double export_w[59] = {
 0.2422731102424329, 0.1685601972805633, 1.144938635478179, 0.9251465781146723,
 -0.3401490114059418, 0.1849678968515714, -0.2109478060151187, -0.9994219108215934,
 0.5609672424685861, -0.5316586607126723, -0.0401498587176148, -0.000311970886502372,
 -0.8011945440936979, -1.315131443939578, -1.335786196344254, -1.734336818161753,
 0.6471954961139879, -0.6403800015658664, -0.5447646091843412, -0.4500650775295008,
 0.8424459987663341, 0.2467634469991534, -0.1100576163505895, 0.1279588219121385,
 -0.7596559067824056, 1.30605189935239, -0.5397504283725704, 1.449720237173661,
 -0.1692412128968907, 0.1735480456960122, -0.02415153822775668, -2.809354898439365,
 -0.8557470785050109, 0.400547923937851, -1.581420261971157, 1.860398142419893,
 -0.005549380475841786, 0.04622575406816191, 0.2690885808897128, -0.09123800297388644,
 0.9836935045580477, 0.4524265399665353, 0.0898692268235641, -0.7731193511271613,
 1.684743685007502, -0.7992532153341293, -0.6515485504497029, 0.1360072220929812,
 0.8958239310893573, 0.2777879546041405, -1.022831814586224, 0.8449967503232536,
 -2.289901661486862, 0.8292327421889349, -0.1064593336973993, 0.3629656315892187,
 0.4580302834404282, 0.8169688993126462, 0.3974509832838855
};


void
export_eval(const double *input, double *output)
{
    double n[15];
    double x;
    int k = 0, i = 5, j;

    export_in(input, n);
    for (; i < 10; ++i) {
        x = export_w[k++];
        for (j = 0; j < 5; ++j) x += n[j] * export_w[k++];
        n[i] = (double)2. / ((double)1. + exp((double)-2 * x)) - (double)1.;
    }
    for (; i < 14; ++i) {
        x = export_w[k++];
        for (j = 5; j < 10; ++j) x += n[j] * export_w[k++];
        n[i] = (double)2. / ((double)1. + exp((double)-2 * x)) - (double)1.;
    }
    for (; i < 15; ++i) {
        x = export_w[k++];
        for (j = 10; j < 14; ++j) x += n[j] * export_w[k++];
        n[i] = x;
    }
    export_out(n + 14, output);
}

int main()
{
    /* inputs order:
    fuel fraction, adiabatic flame temp. [K], pressure, ch4o2, h2air
    output:
    log10(cellSize [mm])

    Below is a test for H2-air, 30% of fuel,
     */
    double testinp[7] = {0.3, 2337.836, 0.25134, 0, 1};
    double testout = 0.0;

    double *inp = testinp;
    double *out = &testout;

    export_eval(inp, out);

    *out = pow(10,*out);

    printf("Cell size is %f\n mm", *out);

    return 0;
}
