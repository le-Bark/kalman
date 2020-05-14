#ifndef _matrix_h_
#define _matrix_h_

#include "stdint.h"
#include <new>

typedef float matrix_t;

class matrix{
public:
    matrix(uint32_t rows, uint32_t columns, matrix_t* initData = 0);
    ~matrix();

    uint32_t getRows()const{return m_rows;};
    uint32_t getColumns()const{return m_columns;};

    matrix& operator=(const matrix& a);
    matrix& operator+=(const matrix& a);
    matrix& operator+=(matrix_t a);
    matrix operator+(const matrix& a)const;
    matrix& operator-=(const matrix& a);
    matrix& operator-=(const matrix_t a);
    matrix operator-(const matrix& a)const;
    matrix& operator*=(const matrix_t a);
    matrix operator*(const matrix& a);
    matrix_t& operator()(uint32_t row,uint32_t column);
    matrix_t get(uint32_t row,uint32_t column)const;
    void set(uint32_t row,uint32_t column, matrix_t val);
    matrix transpose();
    matrix invert();
    static matrix identity(uint32_t n);

private:
    void multRow(uint32_t r,matrix_t factor);
    void subRow(uint32_t row1,uint32_t row, matrix_t factor = 1);
    void addRow(uint32_t row1,uint32_t row2, matrix_t factor = 1);
    matrix_t& atIndex(uint32_t row,uint32_t column);
    uint32_t m_rows;
    uint32_t m_columns;
    matrix_t* m_data;
};

#endif // _matrix_h_
