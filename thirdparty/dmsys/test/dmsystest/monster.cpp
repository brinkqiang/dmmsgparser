#include "monster.h"
CMonster::CMonster()
{

}

CMonster::~CMonster()
{

}

bool CMonster::Init()
{
    std::cout << "CMonster Init" << std::endl;
    return true;
}

bool CMonster::UnInit()
{
    return true;
}

void CMonster::Release()
{
    Destroy();
}

