#pragma once

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CurveView;
class CurveModel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private Q_SLOTS:
    void onCurveTypeChanged(int type);

private:
    QComboBox *m_pcbxType = nullptr;
    CurveView *m_pView = nullptr;
    CurveModel *m_pModel = nullptr;
};
