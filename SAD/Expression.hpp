#ifndef ExpressionType_H
#define ExpressionType_H

#include<memory>
#include<SAD/declarations.hpp>


namespace sad{


template<typename numType>
class ExpressionType{

    public:
    ExpressionType()=default;
    virtual numType eval() const =0;
    
    virtual Expression<numType> der(const Expression<numType> &wrt) const=0;

    friend std::ostream& operator<<(std::ostream& os, const Expression<numType> &Expr){
        os << Expr->eval() ;
        return os;
    }

};

template<typename numType>
class VariableType:public ExpressionType<numType>{
    numType val;
    
    public:
    VariableType():val(0){}
    VariableType(const numType &val):val(val){}
    
    numType eval() const {return val;}

    Expression<numType> der(const Expression<numType> &wrt) const {
        if(wrt.get()==this){return Variable<numType>(1);}
        return Variable<numType>(0);
    }
};


}
#endif