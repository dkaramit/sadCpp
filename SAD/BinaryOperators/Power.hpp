#ifndef PowOp_H
#define PowOp_H


#include<SAD/Expression.hpp>
#include<SAD/UnaryOperators/BasicUnaryOperators.hpp>
#include<SAD/utilities.hpp>


namespace sad{

    template<typename numType>
    class Power_expr: public AbstractExpression<numType>{ 
        public:
        Power_expr(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        Expression<numType> LH,RH;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DRH=RH.derivative(wrt);
            auto DLH=LH.derivative(wrt);

            if (DRH.is_ZERO() and DLH.is_ZERO()){return ZERO<numType>;}
            if (DRH.is_ZERO()){return pow( LH,RH - ONE<numType> ) * RH*DLH;}
            if (DLH.is_ZERO()){return pow( LH,RH - ONE<numType> ) * LH*log(LH)*DRH;}

            return pow( LH,RH - ONE<numType> ) * ( RH*DLH + LH*log(LH)*DRH );
        };
        
        numType evaluate(const map<IDType,numType> &at)const{return std::pow(LH.evaluate(at), RH.evaluate(at));};
    };

    template<typename numType>
    class Power_num1: public AbstractExpression<numType>{ 
        public:
        Power_num1(const numType &LH,const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        
        numType LH;
        Expression<numType> RH;

        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DRH=RH.derivative(wrt);
            if (DRH.is_ZERO()){return ZERO<numType>;}

            return pow( LH,RH - ONE<numType> ) *   LH*log(LH)*DRH;
        }
        
        numType evaluate(const map<IDType,numType> &at)const{return std::pow(LH, RH.evaluate(at));}
    };

    template<typename numType>
    class Power_num2: public AbstractExpression<numType>{ 
        public:
        Power_num2(const Expression<numType> &LH, const numType &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        
        Expression<numType> LH;
        numType RH;

        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DLH=LH.derivative(wrt);
            if (DLH.is_ZERO()){return ZERO<numType>;}

            return pow( LH,RH - ONE<numType> )*RH*DLH;
        }
        
        numType evaluate(const map<IDType,numType> &at)const{return std::pow(LH.evaluate(at), RH);}
    };

    template<typename numType> Expression<numType> pow(const Expression<numType> &LH, const Expression<numType> &RH){
        if(LH.is_ZERO()){return ZERO<numType>;}
        if(RH.is_ZERO()){return ONE<numType>;}
        if(RH.is_ONE()){return LH;}

        return AbsExp_ptr<numType>(new Power_expr<numType>(LH,RH)); 
    }
    template<typename numType> Expression<numType> pow(const numType &LH, const Expression<numType> &RH){return AbsExp_ptr<numType>(new Power_num1<numType>(LH,RH)); }
    template<typename numType> Expression<numType> pow(const Expression<numType> &LH, const numType &RH){return AbsExp_ptr<numType>(new Power_num2<numType>(LH,RH)); }

}



#endif