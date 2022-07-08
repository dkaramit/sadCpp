#ifndef Sub_H
#define Sub_H

#include <cmath> 
#include<SAD/Expression.hpp>
#include<SAD/utilities.hpp>

#include<SAD/BinaryOperators/Multiplication.hpp>

#define Simplifications if(is_ZERO(LH)){return -RH;} if(is_ZERO(RH)){return LH;}



namespace sad{

template<typename numType>
    class Subtruction_expr: public AbstractExpression<numType>{ 
        public:
        Subtruction_expr(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        Expression<numType> LH,RH;
        Expression<numType> derivative(const unsigned int &wrt)const{ return LH.derivative(wrt) - RH.derivative(wrt); }
        numType evaluate(const map<IDType,numType> &at)const{return  LH.evaluate(at)-RH.evaluate(at);}
        bool is_CONST()const{return LH.is_CONST() and RH.is_CONST();}
    };
template<typename numType>
    class Subtruction_numL: public AbstractExpression<numType>{ 
        public:
        Subtruction_numL(const numType &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        numType LH;
        Expression<numType> RH;
        Expression<numType> derivative(const unsigned int &wrt)const{ return  -RH.derivative(wrt); }
        numType evaluate(const map<IDType,numType> &at)const{return LH-RH.evaluate(at);}
        bool is_CONST()const{return RH.is_CONST();}
    };
template<typename numType>
    class Subtruction_numR: public AbstractExpression<numType>{ 
        public:
        Subtruction_numR(const Expression<numType> &LH, const numType &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        Expression<numType> LH;
        numType RH;
        Expression<numType> derivative(const unsigned int &wrt)const{ return  LH.derivative(wrt); }
        numType evaluate(const map<IDType,numType> &at)const{return LH.evaluate(at)-RH;}
        bool is_CONST()const{return LH.is_CONST();}
    };


template<typename numType> Expression<numType> operator-(const Expression<numType> &LH, const Expression<numType> &RH){
    if(RH == LH){return ZERO<numType>;}
    Simplifications    
    return AbsExp_ptr<numType>(new Subtruction_expr<numType>(LH,RH)); 
}

template<typename numType> Expression<numType> operator-(const numType &LH, const Expression<numType> &RH){
    Simplifications    
    return AbsExp_ptr<numType>(new Subtruction_numL<numType>(LH,RH)); 
}

template<typename numType> Expression<numType> operator-(const Expression<numType> &LH, const numType &RH){
    Simplifications    
    return AbsExp_ptr<numType>(new Subtruction_numR<numType>(LH,RH)); 
}

}


#undef Simplifications
#endif