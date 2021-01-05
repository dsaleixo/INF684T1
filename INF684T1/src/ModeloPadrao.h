#pragma once
#include "Base.h"
class ModeloPadrao :
    public Base
{
public:
    ModeloPadrao(Dados &ds);
    virtual void rodar();
};

