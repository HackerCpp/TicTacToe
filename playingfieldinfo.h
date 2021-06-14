#ifndef PLAYINGFIELDINFO_H
#define PLAYINGFIELDINFO_H
#include <memory>

using namespace std;
class QString;

enum MODE{MODE_ZEROS,MODE_CROSSES,MODE_MAX};
enum WIN_STATUS{ GAME_CONTINUES,ZEROS_WIN,CROSSES_WIN,NO_ONE_WON,WIN_STATUS_MAXIMUM};

class PlayingFieldInfo
{

    MODE m_currentMode;
    static const int C_QUANTITY_CELLS_EDGY = 3;
    array<uint16_t,MODE_MAX> m_bits{0,0};
    uint16_t m_occupiedCells;
    uint8_t m_counterOccupiedCells;
    array<string,WIN_STATUS_MAXIMUM> m_messageWins;

    array<uint16_t,8>m_bitsMasWin{0x07,0x38,0x1c0,0x49,0x92,0x124,0x54,0x111};

    bool cellIsOccupied(MODE mode,int x,int y)const;
public:
    PlayingFieldInfo();
    void changeMode();
    bool addFigure(int x,int y);
    bool addFigure(uint16_t mas);

    uint8_t quantityCellsEdgy()const;
    uint8_t quantityCells()const;
    //cur - zero , enemy - crosses
    WIN_STATUS winAnalizer(uint16_t zeroMask,uint16_t crossesMask)const;
    WIN_STATUS winAnalyzer()const;
    MODE figure(int x,int y)const;

    string message(WIN_STATUS status)const;
    void clear();

    uint16_t bitMas(MODE mode)const;
    MODE mode()const{return m_currentMode;}
};

#endif // PLAYINGFIELDINFO_H
