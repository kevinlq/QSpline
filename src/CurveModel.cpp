#include "CurveModel.h"

#include "cpp-spline/spline/src/main/cpp/Bezier.h"
#include "cpp-spline/spline/src/main/cpp/CatmullRom.h"
#include "cpp-spline/spline/src/main/cpp//BSpline.h"

#include <QDebug>
#include <iostream>

QVector<QPointF> generateTestData()
{
    QVector<QPointF> vtrKnots;
    vtrKnots<< QPointF(68, 235) << QPointF(71, 235)  << QPointF(75, 235) << QPointF(78, 235) << QPointF(81, 233) << QPointF(85, 233)
             << QPointF(98, 233) << QPointF(92, 233) << QPointF(95, 233) << QPointF(98, 233) << QPointF(102, 233) << QPointF(105, 233)
             << QPointF(109, 233) << QPointF(112, 233) << QPointF(115, 233) << QPointF(119, 233) << QPointF(122, 231) << QPointF(126, 231)
             << QPointF(129, 231) << QPointF(132, 231) << QPointF(136, 231) << QPointF(139, 231) << QPointF(143, 231) << QPointF(146, 231)
             << QPointF(139, 231) << QPointF(153, 228) << QPointF(156, 228) << QPointF(160, 228) << QPointF(163, 228) << QPointF(166, 228)
             << QPointF(170, 228) << QPointF(173, 228) << QPointF(177, 228) << QPointF(180, 228) << QPointF(183, 226) << QPointF(187, 226)
             << QPointF(190, 226) << QPointF(194, 226) << QPointF(197, 226) << QPointF(200, 226) << QPointF(204, 226) << QPointF(207, 226)
             << QPointF(211, 226) << QPointF(214, 226) << QPointF(217, 226) << QPointF(221, 228) << QPointF(224, 228) << QPointF(228, 228)
             << QPointF(231, 228) << QPointF(234, 228) << QPointF(238, 226) << QPointF(241, 226) << QPointF(245, 226) << QPointF(248, 226)
             << QPointF(251, 226) << QPointF(255, 226) << QPointF(258, 226) << QPointF(262, 228) << QPointF(265, 228) << QPointF(268, 228)
             << QPointF(272, 228) << QPointF(275, 228) << QPointF(279, 226) << QPointF(282, 226) << QPointF(285, 226) << QPointF(289, 226)
             << QPointF(292, 226) << QPointF(296, 226) << QPointF(299, 228) << QPointF(302, 228) << QPointF(306, 228) << QPointF(309, 228)
             << QPointF(313, 228) << QPointF(316, 228) << QPointF(319, 228) << QPointF(323, 226) << QPointF(326, 226) << QPointF(330, 226)
             << QPointF(333, 226) << QPointF(336, 226) << QPointF(340, 226) << QPointF(347, 226) << QPointF(350, 226) << QPointF(353, 226)
             << QPointF(357, 226) << QPointF(360, 226) << QPointF(364, 226) << QPointF(367, 226) << QPointF(370, 226) << QPointF(374, 226)
             << QPointF(377, 202) << QPointF(381, 202) << QPointF(384, 202) << QPointF(387, 204) << QPointF(391, 204) << QPointF(394, 204)
             << QPointF(398, 204) << QPointF(401, 204) << QPointF(404, 204) << QPointF(408, 204) << QPointF(411, 204) << QPointF(415, 204)
             << QPointF(418, 226) << QPointF(421, 226) << QPointF(425, 226) << QPointF(428, 226) << QPointF(431, 228) << QPointF(435, 228)
             << QPointF(438, 228) << QPointF(442, 228) << QPointF(435, 228) << QPointF(438, 228) << QPointF(442, 228) << QPointF(445, 228)
             << QPointF(449, 228) << QPointF(452, 228) << QPointF(455, 204) << QPointF(459, 204) << QPointF(462, 204) << QPointF(466, 228)
             << QPointF(469, 228) << QPointF(472, 228) << QPointF(476, 228) << QPointF(479, 228) << QPointF(483, 228) << QPointF(486, 228)
             << QPointF(489, 228) << QPointF(493, 228) << QPointF(496, 228) << QPointF(500, 228) << QPointF(503, 228) << QPointF(506, 228)
             << QPointF(510, 228) << QPointF(513, 228) << QPointF(517, 228) << QPointF(520, 228) << QPointF(523, 228) << QPointF(527, 228)
             << QPointF(530, 226) << QPointF(534, 226) << QPointF(537, 226) << QPointF(540, 226) << QPointF(544, 226) << QPointF(547, 226)
             << QPointF(551, 206) << QPointF(554, 206) << QPointF(557, 206) << QPointF(561, 206) << QPointF(564, 208) << QPointF(568, 208)
             << QPointF(571, 208) << QPointF(574, 208) << QPointF(578, 208) << QPointF(581, 206) << QPointF(585, 206) << QPointF(588, 206)
             << QPointF(591, 206) << QPointF(595, 206) << QPointF(598, 206);
    return vtrKnots;
}

CurveModel::CurveModel(QObject *parent)
    : QObject{parent}
{
    m_vtrKnots = generateTestData();
}

void CurveModel::changeCurveType(int type)
{
    m_curveType = type;

    m_outKnots.clear();
    initSpline(m_vtrKnots, m_outKnots);
}

bool CurveModel::initSpline(const QVector<QPointF> &vtrKnots, QVector<QPointF> &outKnots)
{
    int nPointNum = vtrKnots.size();
    if(nPointNum <= 0)
    {
        qDebug() << "error: point empty..";
        return false;
    }
    if(nullptr != m_pCurveObject)
    {
        delete m_pCurveObject;
        m_pCurveObject = nullptr;
    }

    if(CurveTypes::CT_BezierCurve == m_curveType)
    {
        m_pCurveObject = new Bezier();
    }
    else if(CurveTypes::CT_BSpline == m_curveType)
    {
        m_pCurveObject = new BSpline();
    }
    else if(CurveTypes::Ct_CatmullRom == m_curveType)
    {
        m_pCurveObject = new CatmullRom();
    }

    m_pCurveObject->set_steps(100); // generate 100 interpolate points between the last 4 way points
    m_pCurveObject->clear();
    for(const auto &pt : vtrKnots)
    {
        m_pCurveObject->add_way_point(Vector(pt.x(), pt.y(), 0));
    }

    qDebug() << "nodes: " << m_pCurveObject->node_count();
    qDebug()  << "total length: " << m_pCurveObject->total_length();
    for (int i = 0; i < m_pCurveObject->node_count(); ++i)
    {
        //std::cout << "node #" << i << ": " << curve->node(i).toString() << " (length so far: " << curve->length_from_starting_point(i) << ")" << std::endl;

        outKnots.push_back(QPointF(m_pCurveObject->node(i).x, m_pCurveObject->node(i).y));
    }

    return true;
}

QVector<QPointF> CurveModel::getSourceData()
{
    return m_vtrKnots;
}

QVector<QPointF> CurveModel::getProcessData()
{
    return m_outKnots;
}
