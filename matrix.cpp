
#include "matrix.h"
#include <cstdlib>

matrix::matrix(uint32_t rows, uint32_t columns, matrix_t* initData):
m_rows(rows),
m_columns(columns)
{
    m_data = new matrix_t[rows*columns];
    if(initData){
        for(uint32_t i = 0; i<rows*columns;i++){
            m_data[i] = initData[i];
        }
    }
    else {
        for(uint32_t i = 0; i<rows*columns;i++){
            m_data[i] = 0;
        }
    }
}

matrix::~matrix(){
    delete m_data;
}

matrix& matrix::operator=(const matrix& a){
    m_columns = a.m_columns;
    m_rows = a.m_rows;
    for(uint32_t i = 0; i<m_rows*m_columns;i++){
        m_data[i] = a.m_data[i];
    }
    return *this;
}

matrix& matrix::operator=(matrix_t * data){
    for(uint32_t i = 0;i<m_columns*m_rows;i++){
        m_data[i] = data[i];
    }
    return *this;
}

matrix& matrix::operator+=(const matrix& a){
    for(uint32_t i = 0; i<m_rows*m_columns;i++){
        m_data[i] += a.m_data[i];
    }

    return *this;
}

matrix& matrix::operator+=(matrix_t a){
    for(uint32_t i = 0; i<m_rows*m_columns;i++){
        m_data[i] += a;
    }

    return *this;
}

matrix matrix::operator+(const matrix& a)const{
    matrix b(m_rows,m_columns,m_data);
    b+=a;
    return b;
}

matrix& matrix::operator-=(const matrix& a){
    for(uint32_t i = 0; i<m_rows*m_columns;i++){
        m_data[i] -= a.m_data[i];
    }

    return *this;
}

matrix& matrix::operator-=(matrix_t a){
    for(uint32_t i = 0; i<m_rows*m_columns;i++){
        m_data[i] -= a;
    }

    return *this;
}

matrix matrix::operator-(const matrix& a)const{
    matrix b(m_rows,m_columns,m_data);
    b-=a;
    return b;
}

matrix& matrix::operator*=(matrix_t a){
    for(uint32_t i = 0; i<m_rows*m_columns;i++){
        m_data[i] *= a;
    }

    return *this;
}

matrix matrix::operator*(const matrix& a){
    matrix b(m_rows,a.m_columns);
    for(uint32_t i = 0; i<b.m_rows;i++){
        for(uint32_t j = 0;j<b.m_columns;j++){
            matrix_t tmp = 0;
            for(uint32_t k = 0;k<m_columns;k++){
                tmp += get(i,k)*a.get(k,j);
            }
            b.set(i,j,tmp);
        }
    }
    return b;
}

matrix_t matrix::get(uint32_t row,uint32_t column)const{
    return m_data[m_columns*row + column];
}

void matrix::set(uint32_t row,uint32_t column, matrix_t val){
    m_data[m_columns*row + column] = val;
}

matrix matrix::transpose(){
    matrix b(m_columns,m_rows);
    for(uint32_t i = 0;i<m_rows;i++){
        for(uint32_t j = 0;j<m_columns;j++){
            b.set(j,i,m_data[i*m_columns + j]);
        }
    }
    return b;
}

matrix matrix::invert(){
    uint32_t n = m_rows;
    matrix a(n,n);
    a = *this;
    matrix b = identity(n);
    //nXnmatrix;
    //remove all zeros
    for(uint32_t i = 0;i<n;i++){
        if(get(i,i) == 0){
        uint32_t j = 0;
        for(;get(j,i) == 0;j++);

        a.addRow(i,j);
        b.addRow(i,j);
        }
    }
    //create a diagonal matrix with a
    for(uint32_t i = 0;i<n-1;i++){
        //make the pivot 1
        b.multRow(i,1/a.get(i,i));
        a.multRow(i,1/a.get(i,i));
        for(uint32_t j = m_rows-1;j>i;j--){
            if(a.get(j,i) == 0) continue;
            b.subRow(j,i,a.get(j,i));
            a.subRow(j,i,a.get(j,i));
        }
    }

    b.multRow(n-1,1/a.get(n-1,n-1));
    a.multRow(n-1,1/a.get(n-1,n-1));

    for(uint32_t i = n-1;i>0;i--){
        for(uint32_t j = 0;j<i;j++){
            if(a.get(j,i) == 0) continue;
            b.subRow(j,i,a.get(j,i));
            a.subRow(j,i,a.get(j,i));
        }
    }
    return b;
}

matrix matrix::identity(uint32_t n){
matrix m(n,n);
for(uint32_t i = 0;i<n;i++){
    m.set(i,i,1);
}
return m;
}

void matrix::multRow(uint32_t r,matrix_t factor){
    for(uint32_t i = 0;i<m_columns;i++){
        set(r,i,get(r,i) * factor);
    }
}

void matrix::subRow(uint32_t row1,uint32_t row2, matrix_t factor){
    for(uint32_t i = 0;i<m_columns;i++){
        set(row1,i,get(row1,i) - get(row2,i) * factor);
    }
}

void matrix::addRow(uint32_t row1,uint32_t row2, matrix_t factor){
    for(uint32_t i = 0;i<m_columns;i++){
        set(row1,i,get(row1,i) + get(row2,i) * factor);
    }
}
