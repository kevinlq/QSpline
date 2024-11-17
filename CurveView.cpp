#include "CurveView.h"

#include <QPainter>

CurveView::CurveView(CurveModel *pModel, QWidget *parent)
    : m_pModel(pModel) ,QWidget{parent}
{
}

CurveView::~CurveView()
{
    m_pModel = nullptr;
}

void CurveView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);

    QPen pen = p.pen();
    pen.setWidth(2);
    pen.setColor(Qt::red);
    p.setPen(pen);

    QVector<QPointF> screenPoints = m_pModel->getSourceData();
    //imageToScreenPoints(m_pModel->getSourceData(), screenPoints);
    p.drawPoints(screenPoints);

    // QPainterPath path;
    // path.addPolygon(m_vtrKnots);
    // pen.setWidth(2);
    // p.setPen(pen);
    // p.drawPath(path);

    QColor col(Qt::blue);
    col.setAlpha(100);
    pen.setColor(col);
    pen.setWidth(1);
    p.setPen(pen);
    p.drawPoints(m_pModel->getProcessData());

    // QPainterPath pathResult;
    // pathResult.addPolygon(m_outKnots);
    // p.drawPath(pathResult);
}

void CurveView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    m_ptCenter = QPoint(0, 0);
    //m_ptCenter = QPoint(this->width()/2, this->height()/2);
}

QPointF CurveView::imageToScreen(const QPointF &pt)
{
    float fx = (this->width() - 1.0f)/2 + pt.x() + (pt.x() - m_ptCenter.x()) * m_fZoomScale;
    float fy = (this->height() - 1.0f)/2 + pt.y() + (pt.y() - m_ptCenter.y()) * m_fZoomScale;
    return QPointF(fx, fy);
}

bool CurveView::imageToScreenPoints(const QVector<QPointF> &vtrImages, QVector<QPointF> &vtrScreens)
{
    vtrScreens.clear();
    for(int i = 0; i < vtrImages.size(); i++)
    {
        vtrScreens.push_back(imageToScreen(vtrImages[i]));
    }
    return true;
}
