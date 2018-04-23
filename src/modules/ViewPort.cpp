#include "ViewPort.hpp"
#include "stdafx.hpp"

using namespace ge;

ViewPort::ViewPort(sf::Vector2i size)
    : m_viewSize(size)
    , m_viewPos(0, 0)
    , m_viewDelta(0, 0)
    , m_viewLocked(false)
{
    // set default zoom
    zoomTo(ZOOM_DEFAULT);
}

void ViewPort::update()
{

    // update view position if not locked
    if(m_viewLocked == false) {
        m_viewPos += m_viewDelta;
    }
    m_viewDelta = sf::Vector2f();

    // if view has been resized or zoomed, update size
    if(m_viewSizeChanged) {
        setSize(toVec2f(m_viewSize) * m_zoomFactor);
        m_viewSizeChanged = false;
    }

    // offset for gl pixel perfection
    static const float glOffset = 0.375f;
    // offsets for odd sized viewport
    float xOffset = glOffset + ((m_viewSize.x % 2) ? 0.5f : 0.0f);
    float yOffset = glOffset + ((m_viewSize.y % 2) ? 0.5f : 0.0f);

    // snap viewpos to pixels to prevent glitches
    setCenter(round(m_viewPos.x - xOffset) + xOffset,
              round(m_viewPos.y - yOffset) + yOffset);
}

void ViewPort::resize(sf::Vector2i size)
{
    m_viewSize        = size;
    m_viewSizeChanged = true;
}

void ViewPort::lock()
{
    m_viewLocked = true;
}
void ViewPort::lockTo(sf::Vector2f center)
{
    panTo(center);
    lock();
}
void ViewPort::unlock()
{
    m_viewLocked = false;
}
bool ViewPort::isLocked()
{
    return m_viewLocked;
}

/// NAVIGATION

void ViewPort::panTo(sf::Vector2f fixedPosition)
{
    m_viewPos = fixedPosition;
}
void ViewPort::panBy(sf::Vector2f relativePosition)
{
    m_viewDelta += relativePosition;
}

void ViewPort::zoom(ZoomDirection zoomDirection)
{
    switch(zoomDirection) {
    case ViewPort::ZOOM_OUT:
        if(m_zoomLevel != ZOOM_MIN)
            zoomTo(static_cast<ZoomLevel>(m_zoomLevel + ZOOM_OUT));
        break;
    case ViewPort::ZOOM_RESET:
        zoomTo(static_cast<ZoomLevel>(ZOOM_DEFAULT));
        break;
    case ViewPort::ZOOM_IN:
        if(m_zoomLevel != ZOOM_MAX)
            zoomTo(static_cast<ZoomLevel>(m_zoomLevel + ZOOM_IN));
        break;
    }
}

void ViewPort::zoomTo(ZoomLevel zoomLevel)
{
    m_zoomLevel       = zoomLevel;
    m_zoomFactor      = exp2((float)-m_zoomLevel);
    m_viewSizeChanged = true;
}

int ViewPort::getZoomLevel()
{
    return m_zoomLevel;
}

float ViewPort::getZoomFactor()
{
    return m_zoomFactor;
}
