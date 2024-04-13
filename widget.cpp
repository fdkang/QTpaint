#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(1024,768);
    this->setWindowTitle("简易绘图板");
    this->setWindowIcon(QIcon(":/new/prefix1/qrc/20091201_0c5e3cb96bf053f6f8f43xlWxvBTLEnr.png"));
    this->pix = new QPixmap(this->size());
    this->pix->fill(Qt::white);

    // 创建清空按钮
    clearBtn = new QToolButton(this);
    clearBtn->setText("清理");
    connect(clearBtn, &QToolButton::clicked, this, &Widget::clearCanvas);

    // 创建线条粗细选择器
    penWidthSlider = new QSlider(Qt::Horizontal, this);
    penWidthSlider->setRange(1, 20); // 可以根据需求调整范围
    penWidthSlider->setValue(5); // 默认粗细
    connect(penWidthSlider, &QSlider::valueChanged, this, &Widget::setPenWidth);

    // 创建颜色选择按钮
    QPushButton* colorBtn = new QPushButton("选择颜色", this);
    connect(colorBtn, &QPushButton::clicked, this, &Widget::chooseColor);

    // 布局设置
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(clearBtn);
    layout->addWidget(new QLabel("线条粗细:"));
    layout->addWidget(penWidthSlider);
    layout->addWidget(colorBtn);
    layout->addStretch();
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(layout);
    mainLayout->addStretch();

    penColor = Qt::black; // 默认颜色
}

Widget::~Widget()
{
    delete pix;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, *pix);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        startPos = event->pos();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPainter p(pix);
        QPen pen(penColor); // 使用选择的颜色
        pen.setWidth(penWidthSlider->value()); // 使用选择的线条粗细
        pen.setCapStyle(Qt::RoundCap);
        p.setPen(pen);
        p.setRenderHint(QPainter::Antialiasing);
        p.drawLine(startPos, event->pos());
        startPos = event->pos();
        update();
    }
}

void Widget::clearCanvas()
{
    pix->fill(Qt::white);
    update();
}

void Widget::setPenWidth(int width)
{
    // 不需要额外操作，因为在绘制时会根据线条粗细设置进行绘制
}

void Widget::chooseColor()
{
    QColorDialog dialog(this);
    dialog.setCurrentColor(penColor);
    penColor = dialog.getColor();
}
