#include "computerplayer.h"
#include <math.h>
#include <QDebug>
#include <stdint.h>

ComputerPlayer::ComputerPlayer(MODE mode,std::shared_ptr<PlayingFieldInfo>fieldInfo)
    : m_fieldInfo(fieldInfo),m_currentMode(mode)
{

}

void ComputerPlayer::nextStep(){
    uint16_t f_needCell = needCell();
    m_fieldInfo->addFigure(f_needCell);
}

uint16_t ComputerPlayer::needCell(){
    uint16_t zeros = m_fieldInfo->bitMas(MODE_ZEROS);
    uint16_t crosses = m_fieldInfo->bitMas(MODE_CROSSES);
    uint16_t curMask = m_currentMode == MODE_ZEROS ? zeros : crosses;
    uint16_t enemyMask= m_currentMode != MODE_ZEROS ? zeros : crosses;
    return checkingAllMoves(enemyMask,curMask,m_currentMode).moveMask;
}


MoveInfo ComputerPlayer::checkingAllMoves(uint16_t enemyMask,uint16_t curMask,MODE mode){

    uint16_t all = enemyMask | curMask;
    if(!all)
        return MoveInfo{uint16_t(1<<(rand() % 8)),0};


    if(WIN_STATUS status = m_fieldInfo->winAnalizer(curMask,enemyMask);status){
        if(status == CROSSES_WIN){
            if(mode == m_currentMode)
                return MoveInfo{0,-10};
            else
                return MoveInfo{0,10};
        }
        return MoveInfo{0,0};
    }

    QList<MoveInfo> f_movesInfo;
    MODE enemyMode = mode ? MODE_ZEROS : MODE_CROSSES;

    for(int i = 0; i < m_fieldInfo->quantityCells(); ++i){
        if(all & (1 << i))
            continue;
        uint16_t currentStep = (1 << i);
        uint16_t currentMask = curMask | currentStep;
        MoveInfo f_moveInfo;
        f_moveInfo.moveMask = currentStep;
        f_moveInfo.points = checkingAllMoves(currentMask,enemyMask,enemyMode).points;
        f_movesInfo.push_back(f_moveInfo);
    }

    MoveInfo f_maximumMoveInfo{0,-32000};
    MoveInfo f_minimumMoveInfo{0,32000};

    for(auto moveInfo : f_movesInfo){
        if(moveInfo.points >f_maximumMoveInfo.points){
            f_maximumMoveInfo.points = moveInfo.points;
            f_maximumMoveInfo.moveMask = moveInfo.moveMask;
        }
        if(moveInfo.points < f_minimumMoveInfo.points){
            f_minimumMoveInfo.points = moveInfo.points;
            f_minimumMoveInfo.moveMask = moveInfo.moveMask;
        }
    }
    return mode == m_currentMode ? f_maximumMoveInfo : f_minimumMoveInfo;
}

