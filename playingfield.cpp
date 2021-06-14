#include "playingfield.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include "playingfieldinfo.h"
#include <QString>
#include "computerplayer.h"

PlayingField::PlayingField(QWidget *parent) : QWidget(parent)
{
    m_fieldInfo = make_shared<PlayingFieldInfo>();
    m_compPlayer = make_unique<ComputerPlayer>(MODE(rand() % MODE_MAX),m_fieldInfo);
    nextStep();
}


void PlayingField::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setPen(QPen(Qt::black,4));
    int widthCell = width() / m_fieldInfo->quantityCellsEdgy();
    int heightCell = height() / m_fieldInfo->quantityCellsEdgy();
    p.drawLine(widthCell,0,widthCell,height());
    p.drawLine(widthCell * 2,0,widthCell * 2,height());
    p.drawLine(0,heightCell,width(),heightCell);
    p.drawLine(0,heightCell * 2,width(),heightCell * 2);
    p.drawRect(0,0,width(),height());
    for(int x = 0; x < m_fieldInfo->quantityCellsEdgy(); ++x){
        for(int y = 0; y < m_fieldInfo->quantityCellsEdgy(); ++y){
            if(MODE mode = m_fieldInfo->figure(x,y);mode == MODE_ZEROS)
                p.drawEllipse(QRect(x * widthCell,y * heightCell ,widthCell,heightCell));
            else if(mode == MODE_CROSSES){
                QPoint leftUp(x * widthCell,y * heightCell);
                p.drawLine(leftUp,leftUp + QPoint(widthCell,heightCell));
                QPoint rightUp(x * widthCell + widthCell,y * heightCell);
                p.drawLine(rightUp,rightUp + QPoint(-widthCell,heightCell));
            }
        }
    }
}

void PlayingField::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        int widthCell = width() / m_fieldInfo->quantityCellsEdgy();
        int heightCell = height() / m_fieldInfo->quantityCellsEdgy();
        int f_xCell = event->pos().x()  /  widthCell;
        int f_yCell = event->pos().y()  /  heightCell;
        if(m_fieldInfo->addFigure(f_xCell,f_yCell)){
            update();
            winAnalyzer();
        }
        nextStep();
    }

}

void PlayingField::winAnalyzer(){
    if(WIN_STATUS status =  m_fieldInfo->winAnalyzer();status){
        QMessageBox::information(this, tr("info"), QString::fromUtf8(m_fieldInfo->message(status).c_str()));
        newGame();
    }

}

void PlayingField::newGame(){
    m_fieldInfo->clear();
    update();
    nextStep();
}

void PlayingField::nextStep(){
    if(m_fieldInfo->mode() == m_compPlayer->mode()){
        m_compPlayer->nextStep();
        update();
        winAnalyzer();
    }

}
