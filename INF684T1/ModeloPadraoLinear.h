#pragma once
#include "Base.h"
class ModeloPadraoLinear :
    public Base
{
public:
    ModeloPadraoLinear(Dados& ds);
    virtual void rodar();
};

