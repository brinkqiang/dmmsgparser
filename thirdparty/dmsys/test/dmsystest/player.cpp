#include "player.h"

CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{

}

bool CPlayer::Init()
{
    std::cout << "CPlayer Init" << std::endl;
    return true;
}

bool CPlayer::UnInit()
{
    return true;
}

void CPlayer::Release()
{
    Destroy();
}

