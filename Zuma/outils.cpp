#include "outils.h"

//Constructeur

Point::Point()
{

}

Point::Point(int ix, int iy)
{
    x=ix, y=iy;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(int ix) {
    x=ix;
}

void Point::setY(int iy) {
    y=iy;
}

void quadrillage() {
    for (int i=1;i<w/carre;i++)
        drawLine(i*CARRE,0,i*CARRE,H,BLACK);
    for (int i=1;i<h/carre;i++)
        drawLine(0,i*CARRE,W,i*CARRE,BLACK);
}
