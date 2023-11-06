
#ifndef __MONSTER_H_INCLUDE__
#define __MONSTER_H_INCLUDE__

#include "dmsingleton.h"
#include <iostream>

class CMonster : public CDMSingleton<CMonster>
{
    friend class CDMSingleton<CMonster>;
public:
    CMonster();
    virtual ~CMonster();

    virtual bool Init();
    virtual bool UnInit();

    virtual void Release();
};

#endif // __MONSTER_H_INCLUDE__
