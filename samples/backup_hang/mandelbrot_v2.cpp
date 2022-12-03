/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"
#include <omp.h>

struct mandelbrot_t {

};

inline void mandelbrot_17_4_0_0_2(mandelbrot_t *__state, const long long&  __tmp_23_53_r, unsigned short&  __tmp_29_8_w, int H, int W, long long px, long long py) {
    double __tmp12;
    double __tmp14;
    double __tmp18;
    double __tmp22;
    double x0;
    double y0;
    double x;
    double y;
    double xtemp;
    long long iteration;
    bool __tmp15;
    bool __tmp16;

    {
        double __tmp1;
        double __tmp2;
        double __tmp3;
        double __tmp5;
        double __tmp6;
        double __tmp7;

        #pragma omp parallel sections
        {
            /* Calculate x0 */
            #pragma omp section
            {
                {
                    double __out;

                    ///////////////////
                    // Tasklet code (_convert_to_float64_)
                    __out = dace::float64(px);
                    ///////////////////

                    __tmp1 = __out;
                }
                {
                    double __in1 = __tmp1;
                    double __out;

                    ///////////////////
                    // Tasklet code (_Div_)
                    __out = (__in1 / dace::float64(W));
                    ///////////////////

                    __tmp2 = __out;
                }
                {
                    double __in1 = __tmp2;
                    double __out;

                    ///////////////////
                    // Tasklet code (_Mult_)
                    __out = (__in1 * 3.5);
                    ///////////////////

                    __tmp3 = __out;
                }
                {
                    double __in2 = __tmp3;
                    double __out;

                    ///////////////////
                    // Tasklet code (_Add_)
                    __out = ((- 2.5) + __in2);
                    ///////////////////

                    x0 = __out;
                }
            } // End omp section

            /* Calculate y0 */
            #pragma omp section
            {
                {
                    double __out;

                    ///////////////////
                    // Tasklet code (_convert_to_float64_)
                    __out = dace::float64(py);
                    ///////////////////

                    __tmp5 = __out;
                }
                {
                    double __in1 = __tmp5;
                    double __out;

                    ///////////////////
                    // Tasklet code (_Div_)
                    __out = (__in1 / dace::float64(H));
                    ///////////////////

                    __tmp6 = __out;
                }
                {
                    double __in1 = __tmp6;
                    double __out;

                    ///////////////////
                    // Tasklet code (_Mult_)
                    __out = (__in1 * dace::float64(2));
                    ///////////////////

                    __tmp7 = __out;
                }
                {
                    double __in2 = __tmp7;
                    double __out;

                    ///////////////////
                    // Tasklet code (_Add_)
                    __out = (dace::float64((- 1)) + __in2);
                    ///////////////////

                    y0 = __out;
                }
            } // End omp section

            /* Init x = 0.0 */
            #pragma omp section
            {
                {
                    double __out;

                    ///////////////////
                    // Tasklet code (assign_20_8)
                    __out = 0.0;
                    ///////////////////

                    x = __out;
                }
            } // End omp section

            /* Init y = 0.0 */
            #pragma omp section
            {
                {
                    double __out;

                    ///////////////////
                    // Tasklet code (assign_21_8)
                    __out = 0.0;
                    ///////////////////

                    y = __out;
                }
            } // End omp section
        } // End omp sections

    }
    iteration = 0;
    __state_1_while_guard:;

    /* Calculate x*x + y*y */
    {

        {
            double __in1 = x;
            double __in2 = x;
            double __out;

            ///////////////////
            // Tasklet code (_Mult_)
            __out = (__in1 * __in2);
            ///////////////////

            __tmp12 = __out;
        }

    }
    {
        double __tmp13;

        {
            double __in1 = y;
            double __in2 = y;
            double __out;

            ///////////////////
            // Tasklet code (_Mult_)
            __out = (__in1 * __in2);
            ///////////////////

            __tmp13 = __out;
        }
        {
            double __in1 = __tmp12;
            double __in2 = __tmp13;
            double __out;

            ///////////////////
            // Tasklet code (_Add_)
            __out = (__in1 + __in2);
            ///////////////////

            __tmp14 = __out;
        }

    }
    __tmp15 = (__tmp14 < 4);
    __tmp16 = (iteration < __tmp_23_53_r);

    if ((__tmp15 && __tmp16)) {
        goto __state_1_while_23;
    }
    if ((! (__tmp15 && __tmp16))) {
        goto __state_1_assign_29_8;
    }
    __state_1_assign_29_8:;
    {

        {
            unsigned short __out;

            ///////////////////
            // Tasklet code (assign_29_8)
            __out = iteration;
            ///////////////////

            __tmp_29_8_w = __out;
        }

    }
    goto __state_exit_1;
    goto __state_exit_1;
    __state_1_while_23:;


    #pragma omp parallel
    #pragma omp single
    {
        /* Calculate xtemp */
        {
            #pragma omp task untied depend(out: __tmp18)
            {
                double __in1 = x;
                double __in2 = x;
                double __out;

                ///////////////////
                // Tasklet code (_Mult_)
                __out = (__in1 * __in2);
                ///////////////////

                __tmp18 = __out;
            }

            double __tmp19;
            double __tmp20;

            #pragma omp task untied shared(__tmp19) depend(out: __tmp19)
            {
                double __in1 = y;
                double __in2 = y;
                double __out;

                ///////////////////
                // Tasklet code (_Mult_)
                __out = (__in1 * __in2);
                ///////////////////

                __tmp19 = __out;
            }

            #pragma omp task untied shared(__tmp19, __tmp20) depend(in: __tmp18, __tmp19) depend(out: __tmp20)
            {
                double __in1 = __tmp18;
                double __in2 = __tmp19;
                double __out;

                ///////////////////
                // Tasklet code (_Sub_)
                __out = (__in1 - __in2);
                ///////////////////

                __tmp20 = __out;
            }

            #pragma omp task untied shared(__tmp20) depend(in: __tmp20) depend(out: xtemp)
            {
                double __in2 = x0;
                double __in1 = __tmp20;
                double __out;

                ///////////////////
                // Tasklet code (_Add_)
                __out = (__in1 + __in2);
                ///////////////////

                xtemp = __out;
            }

        }

        /* Calculate new y */
        {
            #pragma omp task untied depend(out: __tmp22)
            {
                double __in2 = x;
                double __out;

                ///////////////////
                // Tasklet code (_Mult_)
                __out = (dace::float64(2) * __in2);
                ///////////////////

                __tmp22 = __out;
            }

            double __tmp23;
            double __tmp24;

            #pragma omp task untied shared(__tmp23) depend(in: __tmp22) depend(out: __tmp23)
            {
                double __in1 = __tmp22;
                double __in2 = y;
                double __out;

                ///////////////////
                // Tasklet code (_Mult_)
                __out = (__in1 * __in2);
                ///////////////////

                __tmp23 = __out;
            }

            #pragma omp task untied shared(__tmp23, __tmp24) depend(in: __tmp23) depend(out: __tmp24)
            {
                double __in2 = y0;
                double __in1 = __tmp23;
                double __out;

                ///////////////////
                // Tasklet code (_Add_)
                __out = (__in1 + __in2);
                ///////////////////

                __tmp24 = __out;
            }

            #pragma omp task untied shared(__tmp24) depend(in: __tmp24) depend(out: y)
            {
                double __inp = __tmp24;
                double __out;

                ///////////////////
                // Tasklet code (assign_25_12)
                __out = __inp;
                ///////////////////

                y = __out;
            }
        }

        /* Calculate new x */
        {
            #pragma omp task untied depend(in: xtemp) depend(out: x)
            {
                double __inp = xtemp;
                double __out;

                ///////////////////
                // Tasklet code (assign_26_12)
                __out = __inp;
                ///////////////////

                x = __out;
            }
        }

    }

    // #pragma omp taskwait

    iteration = (iteration + 1);
    // printf("==========\n");
    goto __state_1_while_guard;
    __state_exit_1:;
    
}

void __program_mandelbrot_internal(mandelbrot_t *__state, unsigned short * __restrict__ output, int H, int W, long long maxiter)
{

    {

        {
            #pragma omp parallel for
            for (auto py = 0; py < H; py += 1) {
                for (auto px = 0; px < W; px += 1) {
                    // printf("This is %d\n", omp_get_thread_num());
                    mandelbrot_17_4_0_0_2(__state, maxiter, output[((W * py) + px)], H, W, px, py);
                }
            }
        }

    }
}

DACE_EXPORTED void __program_mandelbrot(mandelbrot_t *__state, unsigned short * __restrict__ output, int H, int W, long long maxiter)
{
    __program_mandelbrot_internal(__state, output, H, W, maxiter);
}

DACE_EXPORTED mandelbrot_t *__dace_init_mandelbrot(int H, int W)
{
    int __result = 0;
    mandelbrot_t *__state = new mandelbrot_t;



    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED void __dace_exit_mandelbrot(mandelbrot_t *__state)
{
    delete __state;
}

