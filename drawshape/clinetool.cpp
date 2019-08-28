#include "clinetool.h"
#include "cdrawscene.h"
#include "cgraphicslineitem.h"
#include "cdrawparamsigleton.h"
#include <QGraphicsSceneMouseEvent>
CLineTool::CLineTool()
    : IDrawTool(line)
    , m_pLineItem(nullptr)
{

}

CLineTool::~CLineTool()
{

}

void CLineTool::mousePressEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene)
{
    scene->clearSelection();
    m_sPointPress = event->scenePos();
    m_pLineItem = new CGraphicsLineItem(m_sPointPress, m_sPointPress);
    m_pLineItem->setPen(CDrawParamSigleton::GetInstance()->getPen());
    m_pLineItem->setBrush(CDrawParamSigleton::GetInstance()->getBrush());
    scene->addItem(m_pLineItem);
    m_pLineItem->setSelected(true);

    m_bMousePress = true;
}

void CLineTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene)
{
    Q_UNUSED(scene)
    if (m_bMousePress) {
        QPointF pointMouse = event->scenePos();
        m_pLineItem->setLine(m_sPointPress, pointMouse);
    }
}

void CLineTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene)
{
    m_sPointRelease = event->scenePos();
    m_pLineItem = nullptr;
    m_bMousePress = false;
}