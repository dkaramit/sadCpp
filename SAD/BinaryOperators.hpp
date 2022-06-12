#ifndef BinOp_H
#define BinOp_H

#include <cmath> 
#include<SAD/Expression.hpp>
#include<SAD/utilities.hpp>

// #define sadCT(l,r) typename std::common_type<l,r>::type; 

namespace sad{

/*Define addition*/
template<typename numType>
class Addition: public AbstractExpression<numType>{
    public:
    Addition(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
    friend class Expression<numType>;
    private:
    Expression<numType> LH,RH;
    Expression<numType> derivative(const unsigned int &)const;
    numType evaluate(const map<IDType,numType> &)const;
};
/*this is the addition of two expressions*/
template<typename numType>
Expression<numType> operator+(const Expression<numType> &LH, const Expression<numType> &RH){ return AbsExp_ptr<numType>(new Addition<numType>(LH,RH)); }

/*this is the addition of an expression and a number*/
template<typename numType, typename LD> Expression<numType> operator+(const Expression<numType> &LH, const LD &RH){ return LH + Expression<numType>::constant(RH); }

/*this is the addition of a number and an expression*/
template<typename numType, typename LD> Expression<numType> operator+(const LD &LH, const Expression<numType> &RH){ return RH+LH;}


/*This need to be after operator+ has been declared.*/
template<typename numType>
Expression<numType> Addition<numType>::derivative(const unsigned int &wrt)const{return LH.derivative(wrt) + RH.derivative(wrt);}
template<typename numType>
numType Addition<numType>::evaluate(const map<IDType,numType> &at)const{ return LH.evaluate(at)+RH.evaluate(at); }

/*Define multiplication*/
template<typename numType>
class Multiplication: public AbstractExpression<numType>{
    public:
    Multiplication(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
    friend class Expression<numType>;
    private:
    Expression<numType> LH,RH;
    Expression<numType> derivative(const unsigned int &)const;
    numType evaluate(const map<IDType,numType> &)const;
};
/*this is the multiplication of two expressions*/
template<typename numType>
Expression<numType> operator*(const Expression<numType> &LH, const Expression<numType> &RH){ return AbsExp_ptr<numType>(new Multiplication<numType>(LH,RH)); }

/*this is the Multiplication of an expression and a number*/
template<typename numType, typename LD> Expression<numType> operator*(const Expression<numType> &LH, const LD &RH){ return LH * Expression<numType>::constant(RH); }

/*this is the Multiplication of a number and an expression*/
template<typename numType, typename LD> Expression<numType> operator*(const LD &LH, const Expression<numType> &RH){ return RH*LH;}

/*This need to be after operator* has been declared.*/
template<typename numType>
Expression<numType> Multiplication<numType>::derivative(const unsigned int &wrt)const{return LH.derivative(wrt)*RH+LH*RH.derivative(wrt);}
template<typename numType>
numType Multiplication<numType>::evaluate(const map<IDType,numType> &at)const{ return LH.evaluate(at)*RH.evaluate(at); }





}


#endif