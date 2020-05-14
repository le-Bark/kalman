#ifndef _KALMAN_H_
#define _KALMAN_H_

#include "stdint.h"
#include "matrix.h"

typedef float kalman_t;

class kalman{
    public:

    kalman(uint32_t m, uint32_t n, kalman_t* F,kalman_t* H, kalman_t* R, kalman_t* X, kalman_t* P,kalman_t* Q);
    ~kalman();

    void update();
    void setInput(uint32_t i, kalman_t val);
    kalman_t getOutput(uint32_t i);

private:

    uint32_t m_m; //nb of inputs
    uint32_t m_n; //nb of states

    matrix* m_F;  //F nXn
    matrix* m_P;  //P nXn
    matrix* m_Pn; //P nXn (previous state)
    matrix* m_K;  //K kalman gain nXm
    matrix* m_X;  //state nX1;
    matrix* m_Xn; //state nX1;
    matrix* m_R;  // mXm
    matrix* m_Q;  //nXn
    matrix* m_H;  //H mXn
    matrix* m_Z;  //mX1
};

#endif //_KALMAN_H_
