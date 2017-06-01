#include "outils.h"

// Constructeurs

Point::Point()
{

}

Point::Point(const int &ix, const int &iy)
{
    x=ix, y=iy;
}


// Assesseurs

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(const int &ix) {
    x=ix;
}

void Point::setY(const int &iy) {
    y=iy;
}


// Fonctions de tracé

//Quadrillage utilisé pour la conception des trajectoires, inutile au jeu
void quadrillage() {
    for (int i=1;i<w/carre;i++)
        drawLine(i*CARRE,0,i*CARRE,H,BLACK);
    for (int i=1;i<h/carre;i++)
        drawLine(0,i*CARRE,W,i*CARRE,BLACK);
}

// Affichage du menu
void menu() {
    Event ev;
    IntPoint2 ZUMA(W/4,H/2);
    IntPoint2 INT1(W/9,0), INT2(W/8,0), INT3(int(W/6.5),0);
    drawString(ZUMA,"Z",BLUE,130);
    drawString(ZUMA+INT1,"U",YELLOW,130);
    drawString(ZUMA+INT1+INT2,"M",RED,130);
    drawString(ZUMA+INT1+INT2+INT3,"A",GREEN,130);
    // Affichage des boutons du menu
    IntPoint2 P(W/3,2*H/3);
    int L=W/3, l=H/6;
    IntPoint2 Q(P.x()+L/3,P.y()+l*3/5);
    fillRect(P,L,l,AlphaColor(150,150,150,255));
    drawString(Q,"NEW GAME",WHITE,15);

    bool b = false;
    // receiving mouse move events even if no button is pressed
    enableMouseTracking(true);
    do {
        getEvent(-1,ev); // ev becomes the next event
        switch (ev.type) {
        case EVT_NONE:
            cout << "No event" << endl;
            break;
        case EVT_MOTION: {
            int x = ev.pix.x();   // cursor's x coord
            int y = ev.pix.y();   // cursor's y coord
            // Cursor is in the "NEW GAME" box.
            if(P.x()<=x && x<P.x()+L && P.y()<=y && y<P.y()+l) {
                // Changing the box's style
                fillRect(P,L,l,Color(128,139,203));
                drawString(Q,"NEW GAME",YELLOW,15);
            } else {
                fillRect(P,L,l,Color(150,150,150));
                drawString(Q,"NEW GAME",WHITE,15);
            }
            break;
        }
        case EVT_BUT_ON: {
            int x = ev.pix.x();
            int y = ev.pix.y();
            // Clic sur le bouton NEW GAME
            if(P.x()<=x && x<P.x()+L && P.y()<=y && y<P.y()+l) {
                b = true;         // Stoppe la boucle du menu
            }
            break;
        }
        default: break;
        }
    } while ((ev.type!=EVT_KEY_ON || ev.key!='q' )&& !b);
    clearWindow();
    enableMouseTracking(false);
}
