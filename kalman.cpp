#include"kalman.h"
#include<cstdlib>

kalman::kalman(uint32_t m, uint32_t u, uint32_t n, kalman_t* F, kalman_t* G, kalman_t* H, kalman_t* R, kalman_t* X, kalman_t* U, kalman_t* P,kalman_t* Q):
    m_m(m),
    m_u(u),
    m_n(n){
    m_F = new matrix(n,n,F);
    m_G = new matrix(n,u,G);
    m_U = new matrix(u,u,U);
    m_H = new matrix(m,n,H);
    m_R = new matrix(m,m,R);
    m_X = new matrix(n,1,X);
    m_P = new matrix(n,n,P);
    m_Q = new matrix(n,n,Q);
    m_Z = new matrix(m,1);
    m_Pn = new matrix(n,n);
    m_K = new matrix(n,m);
    m_Xn = new matrix(n,1);
}

kalman::~kalman(){
    delete m_F;
    delete m_G;
    delete m_U;
    delete m_H;
    delete m_R;
    delete m_X;
    delete m_P;
    delete m_Q;
    delete m_Z;
    delete m_Pn;
    delete m_K;
    delete m_Xn;
}

void kalman::update(){
    matrix tmp(m_n,m_n);
    //predict
    *m_Xn = (*m_F) * (*m_X) + (*m_G) * (*m_U);
    *m_Pn = (*m_F) * (*m_P) * m_F->transpose() + (*m_Q);
    //update
    *m_K = (*m_Pn) * m_H->transpose() * ((*m_H) * (*m_Pn) * m_H->transpose() + (*m_R)).invert();
    *m_X = (*m_Xn) + (*m_K) * ((*m_Z) - (*m_H) * (*m_Xn));
    tmp = matrix::identity(m_n) - (*m_K) * (*m_H);
    *m_P = tmp * (*m_Pn) * tmp.transpose() + (*m_K) * (*m_R) * m_K->transpose();
}

void kalman::predictOnly(){
    *m_Xn = (*m_F) * (*m_X) + (*m_G) * (*m_U);
    *m_X = *m_Xn;
}

void kalman::setInput(uint32_t i, kalman_t val){
    m_Z->set(i,0,val);
}

void kalman::setControlInput(uint32_t i, kalman_t val){
    m_U->set(i,0,val);
}

void kalman::updateQ(float* Q_data){
    *m_Q = Q_data;
}

void kalman::updateR(float* R_data){
    *m_R = R_data;
}

kalman_t kalman::getOutput(uint32_t i){
    return m_X->get(i,0);
}
