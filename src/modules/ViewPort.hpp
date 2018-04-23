#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <SFML/Graphics.hpp>

namespace ge {

class ViewPort : public sf::View
{
public:
    ViewPort(sf::Vector2i size);

    // update the ViewPort based on lock & pan & zoom
    void update();

    void resize(sf::Vector2i size);

    // LOCKING

    // lock view where it is actually
    void lock();
    // lock view to a certain pont in the world
    void lockTo(sf::Vector2f center);
    // unlock view
    void unlock();
    // ask whether the view is locked or not
    bool isLocked();

    // PANNING

    // pan the view by the given vector absolute to world coordiantes
    void panTo(sf::Vector2f fixedPosition);
    // pan the view by the given vector relative to the current psition
    void panBy(sf::Vector2f relativePosition);

    // ZOOMING
    enum ZoomLevel
    {
        ZOOM_HALF    = -1,
        ZOOM_1X      = 0,
        ZOOM_2X      = 1,
        ZOOM_4X      = 2,
        ZOOM_8X      = 3,
        ZOOM_MIN     = -1,
        ZOOM_DEFAULT = 1,
        ZOOM_MAX     = 3
    };
    enum ZoomDirection
    {
        ZOOM_OUT   = -1,
        ZOOM_RESET = 0,
        ZOOM_IN    = 1
    };

    // zoom the view in the given direction
    void zoom(ZoomDirection zoomDirection);
    // zoom the view to the given level
    void zoomTo(ZoomLevel zoomlevel);

    // get zoom level
    int getZoomLevel();
    // get zoom factor
    float getZoomFactor();

private:
    sf::Vector2i m_viewSize;   // current size of the view (window size)
    sf::Vector2f m_viewPos;    // current center of view
    int          m_zoomLevel;  // current level of zooming
    float        m_zoomFactor; // the current zooming coefficent of the view

    sf::Vector2f m_viewDelta;       // vector of view position change in this frame
    bool         m_viewLocked;      // true if view is locked for current frame
    bool         m_viewSizeChanged; // true if view was resized or zoomed in this frame
};

} //end namespace: ge
#endif //VIEWPORT_HPP
