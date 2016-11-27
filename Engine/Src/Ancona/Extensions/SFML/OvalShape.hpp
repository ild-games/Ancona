#ifndef Ancona_Engine_Extensions_SFML_OvalShape_H_
#define Ancona_Engine_Extensions_SFML_OvalShape_H_

#include <SFML/Graphics.hpp>

namespace sf
{

class OvalShape : public sf::Shape
{
    public:

        explicit OvalShape(const float radiusWidth = 0, const float radiusHeight = 0) :
            _radiusWidth(radiusWidth),
            _radiusHeight(radiusHeight)
        {
            update();
        }

        virtual unsigned int getPointCount() const
        {
            return 30;
        }

        virtual sf::Vector2f getPoint(unsigned int index) const
        {
            static const float pi = 3.141592654f;

            float angle = index * 2 * pi / getPointCount() - pi / 2;
            float x = std::cos(angle) * _radiusWidth;
            float y = std::sin(angle) * _radiusHeight;

            return sf::Vector2f(_radiusWidth + x, _radiusHeight + y);
        }

        /* getters and setters */
        void setRadiusWidth(const float radiusWidth) { _radiusWidth = radiusWidth; update(); }
        void setRadiusHeight(const float radiusHeight) { _radiusHeight = radiusHeight; update(); }
        const float getRadiusWidth() const { return _radiusWidth; }
        const float getRadiusHeight() const { return _radiusHeight; }
    private:
        float _radiusWidth;
        float _radiusHeight;

};

}

#endif
