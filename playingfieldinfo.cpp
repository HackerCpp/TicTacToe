#include "playingfieldinfo.h"
#include <QMessageBox>
#include <math.h>
#include <QDebug>

PlayingFieldInfo::PlayingFieldInfo()
 : m_occupiedCells(0),m_counterOccupiedCells(0)
{
    m_currentMode = (MODE)(rand() % MODE_MAX);
    m_messageWins[CROSSES_WIN] = "Crosses win!";
    m_messageWins[ZEROS_WIN] = "Zeros win!";
    m_messageWins[NO_ONE_WON] = "No on won!";

}

void PlayingFieldInfo::changeMode(){
    m_currentMode = m_currentMode? MODE_ZEROS : MODE_CROSSES;
}

bool PlayingFieldInfo::addFigure(uint16_t mas){
    if(!(m_occupiedCells & mas)){
        m_bits[m_currentMode] |= mas;
        m_occupiedCells |= mas;
        ++m_counterOccupiedCells;
        changeMode();
        return true;
    }
    return false;
}

bool PlayingFieldInfo::addFigure(int x,int y){
    return addFigure(1 << (x + y * C_QUANTITY_CELLS_EDGY));
}

uint8_t PlayingFieldInfo::quantityCellsEdgy()const{
    return C_QUANTITY_CELLS_EDGY;
}

uint8_t PlayingFieldInfo::quantityCells()const{
    return pow(C_QUANTITY_CELLS_EDGY,2);
}

WIN_STATUS PlayingFieldInfo::winAnalizer(uint16_t zeroMask,uint16_t crossesMask)const{
    for(auto mas : m_bitsMasWin){
        if((zeroMask & mas) == mas){
            return ZEROS_WIN;
        }
         else if((crossesMask & mas) == mas){
            return CROSSES_WIN;
        }
    }
    if(((zeroMask | crossesMask) & 0x1ff) == 0x1ff){
        return NO_ONE_WON;
    }
    return GAME_CONTINUES;
}

WIN_STATUS PlayingFieldInfo::winAnalyzer()const{
    for(auto mas : m_bitsMasWin){
        if((m_bits[MODE_ZEROS] & mas) == mas){
            return ZEROS_WIN;
        }
         else if((m_bits[MODE_CROSSES] & mas) == mas){
            return CROSSES_WIN;
        }
    }
    if(m_counterOccupiedCells >= pow(C_QUANTITY_CELLS_EDGY,2)){
        return NO_ONE_WON;
    }
    return GAME_CONTINUES;
}

inline bool PlayingFieldInfo::cellIsOccupied(MODE mode,int x,int y)const{
    return m_bits[mode] & (1 << (x + y * C_QUANTITY_CELLS_EDGY));
}

MODE PlayingFieldInfo::figure(int x,int y)const{
    if(cellIsOccupied(MODE_ZEROS,x,y))
        return MODE_ZEROS;
    if(cellIsOccupied(MODE_CROSSES,x,y))
        return MODE_CROSSES;
    return MODE_MAX;
}

string PlayingFieldInfo::message(WIN_STATUS status)const{
    try{
        return m_messageWins.at(status);
    }
    catch(const out_of_range &){
        return "";
    }
}

void PlayingFieldInfo::clear(){
    m_occupiedCells = 0;
    m_counterOccupiedCells = 0;
    m_bits.fill(0);
    m_currentMode = (MODE)(rand() % MODE_MAX);
}

uint16_t PlayingFieldInfo::bitMas(MODE mode)const{
    try{
        return m_bits.at(mode);
    }
    catch(const out_of_range &){
        return m_bits[mode % MODE_MAX];
    }
}

