#ifndef Div_H
#define Div_H

#include <cmath> 
#include<SAD/Expression.hpp>
#include<SAD/utilities.hpp>

#include<SAD/BinaryOperators/Multiplication.hpp>

namespace sad{

template<typename numType>
    class Division_expr: public AbstractExpression<numType>{ 
        public:
        Division_expr(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        Expression<numType> LH,RH;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DLH=LH.derivative(wrt);
            auto DRH=RH.derivative(wrt);
            
            if(DLH.is_ZERO() and DRH.is_ZERO()){return ZERO<numType>;}
            if(DLH.is_ZERO()){return -LH*DRH/RH/RH;}
            if(DRH.is_ZERO()){return DLH/RH;}

            return DLH/RH - LH*DRH/RH/RH;
        }
        numType evaluate(const map<IDType,numType> &at)const{return  LH.evaluate(at)/RH.evaluate(at);}
    };
template<typename numType>
    class Division_numL: public AbstractExpression<numType>{ 
        public:
        Division_numL(const numType &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        numType LH;
        Expression<numType> RH;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DRH=RH.derivative(wrt);

            if(DRH.is_ZERO()){return ZERO<numType>;}

            return  -LH*DRH/RH/RH;
        }
        numType evaluate(const map<IDType,numType> &at)const{return LH/RH.evaluate(at);}
    };
template<typename numType>
    class Division_numR: public AbstractExpression<numType>{ 
        public:
        Division_numR(const Expression<numType> &LH, const numType &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        Expression<numType> LH;
        numType RH;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DLH=LH.derivative(wrt);
            
            if(DLH.is_ZERO()){return ZERO<numType>;}
            
            return  DLH/RH ;
        }
        numType evaluate(const map<IDType,numType> &at)const{return LH.evaluate(at)/RH;}
    };


template<typename numType> Expression<numType> operator/(const Expression<numType> &LH, const Expression<numType> &RH){
    if(LH.is_ZERO()){return ZERO<numType>;}
    if(RH.is_ONE()){return LH;}

    return AbsExp_ptr<numType>(new Division_expr<numType>(LH,RH)); 
}

template<typename numType> Expression<numType> operator/(const numType &LH, const Expression<numType> &RH){return AbsExp_ptr<numType>(new Division_numL<numType>(LH,RH)); }

template<typename numType> Expression<numType> operator/(const Expression<numType> &LH, const numType &RH){return AbsExp_ptr<numType>(new Division_numR<numType>(LH,RH)); }

}


#endif