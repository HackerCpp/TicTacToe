#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include <memory>
#include "playingfieldinfo.h"

class PlayingFieldInfo;

struct MoveInfo{
    uint16_t moveMask;
    int16_t points;
};

class ComputerPlayer
{
    std::shared_ptr<PlayingFieldInfo>m_fieldInfo;
    MODE m_currentMode;
    array<uint16_t,8>m_bitsMasWin{0x07,0x38,0x1c0,0x49,0x92,0x124,0x54,0x111};
public:
    explicit ComputerPlayer(MODE mode,std::shared_ptr<PlayingFieldInfo>fieldInfo);
    void nextStep();
    uint16_t needCell();

    void setMode(MODE mode){m_currentMode = mode;}
    MODE mode()const{return m_currentMode;}

    MoveInfo checkingAllMoves(uint16_t enemyMask,uint16_t curMask,MODE mode);

};

#endif // COMPUTERPLAYER_H
