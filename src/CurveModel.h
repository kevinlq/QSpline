#pragma once

#include <QObject>
#include <QVector>
#include <QPointF>

class Curve;

class CurveModel : public QObject
{
    Q_OBJECT
public:
    explicit CurveModel(QObject *parent = nullptr);

    enum CurveTypes
    {
        CT_BezierCurve = 0,
        CT_BSpline,
        Ct_CatmullRom
    };

    void changeCurveType(int type);

    bool initSpline(const QVector<QPointF> &vtrKnots, QVector<QPointF> &outKnots);

    QVector<QPointF> getSourceData();
    QVector<QPointF> getProcessData();

private:
    int m_curveType = CT_BezierCurve;
    Curve* m_pCurveObject = nullptr;
    QVector<QPointF> m_vtrKnots;
    QVector<QPointF> m_outKnots;
};
