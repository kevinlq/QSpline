#include "Widget.h"

#include "CurveView.h"
#include "CurveModel.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    auto layout = new QHBoxLayout;
    m_pcbxType = new QComboBox(this);
    QStringList typeList = {QString::fromLocal8Bit("Bezier Curve"), QString::fromLocal8Bit("B-Spline"), QString::fromLocal8Bit("CatmullRom")};
    m_pcbxType->addItems(typeList);

    connect(m_pcbxType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Widget::onCurveTypeChanged);

    layout->addSpacing(10);
    layout->addWidget(m_pcbxType);
    layout->addStretch();

    m_pModel = new CurveModel;
    m_pView = new CurveView(m_pModel, this);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addWidget(m_pView);
    this->setLayout(mainLayout);

    onCurveTypeChanged(0);
}

Widget::~Widget() {}


void Widget::onCurveTypeChanged(int type)
{
    m_pModel->changeCurveType(type);
    this->update();
}
