#pragma once

#include <QWidget>
#include "CurveModel.h"
#include <QPointF>
#include <QVector>

class CurveView : public QWidget
{
    Q_OBJECT
public:
    explicit CurveView(CurveModel*pModel,QWidget *parent = nullptr);
    ~CurveView();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QPointF imageToScreen(const QPointF &pt);
    bool imageToScreenPoints(const QVector<QPointF> &vtrImages, QVector<QPointF> &vtrScreens);

private:
    float m_fZoomScale = 1.0f;
    QPointF				m_ptCenter;

    CurveModel *m_pModel = nullptr;
};
