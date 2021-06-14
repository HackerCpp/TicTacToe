#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H
#include <QWidget>

class PlayingFieldInfo;
class ComputerPlayer;

class PlayingField : public QWidget
{
    std::shared_ptr<PlayingFieldInfo>m_fieldInfo;
    std::unique_ptr<ComputerPlayer> m_compPlayer;
public:

    PlayingField(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *)override;
    void mousePressEvent(QMouseEvent *)override;
    void winAnalyzer();
    void newGame();
    void nextStep();
};

#endif // PLAYINGFIELD_H
