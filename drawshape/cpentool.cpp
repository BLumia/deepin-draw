#include "cpentool.h"
#include "cdrawscene.h"
#include "cdrawparamsigleton.h"
#include <QGraphicsSceneMouseEvent>


CPenTool::CPenTool()
    : IDrawTool (pen)
    , m_pPenItem(nullptr)
{

}

CPenTool::~CPenTool()
{

}

void CPenTool::mousePressEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene)
{
    if (event->button() == Qt::LeftButton) {
        scene->clearSelection();
        m_sPointPress = event->scenePos();
        m_pPenItem = new CGraphicsPenItem(QRectF(m_sPointPress.x(), m_sPointPress.y(), 0, 0));
        m_pPenItem->setPen(CDrawParamSigleton::GetInstance()->getPen());
        m_pPenItem->setCurrentType(CDrawParamSigleton::GetInstance()->getCurrentPenType());
        scene->addItem(m_pPenItem);
        m_pPenItem->setSelected(true);

        m_bMousePress = true;
    } else {
        scene->mouseEvent(event);
    }
}

void CPenTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene)
{
    Q_UNUSED(scene)
    if (m_bMousePress) {
        QPointF pointMouse = event->scenePos();
        bool shiftKeyPress = CDrawParamSigleton::GetInstance()->getShiftKeyStatus();
        m_pPenItem->updatePenPath(pointMouse, shiftKeyPress);
    }
}

void CPenTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene)
{
    if (event->button() == Qt::LeftButton) {
        m_sPointRelease = event->scenePos();
        //如果鼠标没有移动
        if ( m_pPenItem != nullptr) {
            if ( event->scenePos() == m_sPointPress ) {

                scene->removeItem(m_pPenItem);
                delete m_pPenItem;

            } else {
                emit scene->itemAdded(m_pPenItem);
            }
        }
        m_pPenItem->updatePenPath(m_sPointRelease, CDrawParamSigleton::GetInstance()->getShiftKeyStatus());
        m_pPenItem->changeToPixMap();
        m_pPenItem = nullptr;
        m_bMousePress = false;
    }
}