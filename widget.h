#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QToolButton>
#include <QSlider>
#include <QColorDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)override;

private slots:
    void clearCanvas();
    void setPenWidth(int width);
    void chooseColor();

private:
    QPoint startPos;
    QPixmap* pix;
    QToolButton* clearBtn;
    QSlider* penWidthSlider;
    QColor penColor;
};
#endif // WIDGET_H
