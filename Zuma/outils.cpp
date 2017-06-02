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

    // Bouton Rules:
    IntPoint2 RULES(W - W/10,H-H/10);
    fillRect(RULES,100,50,AlphaColor(150,150,150,255));
    drawString(RULES + IntPoint2(15,35),"RULES",WHITE,15);

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
            // Cursor is in the "RULES" box.
            if(x>RULES.x() && y>RULES.y() && x<RULES.x()+100 && y<RULES.y()+50) {
                // Changing the box's style
                fillRect(RULES,100,50,Color(128,139,203));
                drawString(RULES + IntPoint2(15,35),"RULES",YELLOW,15);
            } else {
                fillRect(RULES,100,50,AlphaColor(150,150,150,255));
                drawString(RULES + IntPoint2(15,35),"RULES",WHITE,15);
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
            if(x>RULES.x() && y>RULES.y() && x<RULES.x()+100 && y<RULES.y()+50) {
                rules();
                drawString(ZUMA,"Z",BLUE,130);
                drawString(ZUMA+INT1,"U",YELLOW,130);
                drawString(ZUMA+INT1+INT2,"M",RED,130);
                drawString(ZUMA+INT1+INT2+INT3,"A",GREEN,130);
            }
            break;
        }
        default: break;
        }
    } while ((ev.type!=EVT_KEY_ON || ev.key!='q' )&& !b);
    clearWindow();
    enableMouseTracking(false);
}

// Affichage d'un message de défaite et retour au menu
void pagePerdu() {
    drawString(W/3,200,"Vous avez perdu !",BLUE,30);

    fillRect(IntPoint2(W/3,2*H/3),W/3,H/10,AlphaColor(150,150,150,255));
    drawString(IntPoint2(W/3 + 10,2*H/3 +40),"Revenir au menu principal",WHITE,20);
    bool b = true;
    while (b) {
        Event ev;
        getEvent(-1,ev);
        if (ev.type == EVT_BUT_ON) {
            int x = ev.pix.x();
            int y = ev.pix.y();
            if (x>W/3 && y>2*H/3 && x<2*W/3 && y<2*H/3+H/10)
                b = false;
        }
    }
    clearWindow();
}

// Affichage d'un message de victoire et passage au niveau suivant
void pageGagne() {
    drawString(W/3+W/15,200,"Bien joué !",RED,30);

    fillRect(IntPoint2(W/3,2*H/3),W/3,H/10,AlphaColor(150,150,150,255));
    drawString(IntPoint2(W/3 + 80,2*H/3 +40),"Niveau suivant",WHITE,20);
    bool b = true;
    while (b) {
        Event ev;
        getEvent(-1,ev);
        if (ev.type == EVT_BUT_ON) {
            int x = ev.pix.x();
            int y = ev.pix.y();
            if (x>W/3 && y>2*H/3 && x<2*W/3 && y<2*H/3+H/10)
                b = false;
        }
    }
    clearWindow();
}

void rules() {
    clearWindow();
    drawString(IntPoint2(20,H/7),"- Tire des boules de couleurs à l'aide du clic gauche de la souris",BLACK,10);
    drawString(IntPoint2(20,2*H/7),"- La couleur de la bille tirée est celle qui entoure le lanceur",BLACK,10);
    drawString(IntPoint2(20,3*H/7),"- Change de couleur avec celle au centre du lanceur en faisant un clic droit",BLACK,10);
    drawString(IntPoint2(20,4*H/7),"- Essaie de viser les groupes de 2 billes (ou plus) de la même couleur pour les détruire",BLACK,10);
    drawString(IntPoint2(20,5*H/7),"- Quand un groupe de bille est détruit et que son entourage est aussi un groupe de bille de la même couleur, il se détruit lui aussi !",BLACK,10);
    drawString(IntPoint2(20,6*H/7),"- Détruis tous les serpents avant qu'ils n'atteigent l'arrivée !",BLACK,10);

    fillRect(IntPoint2(W-W/5,H-H/10),200,50,AlphaColor(150,150,150,255));
    drawString(IntPoint2(W-W/5+5 ,H-H/10 +30),"Revenir au menu principal",WHITE,10);
    bool b = true;
    while (b) {
        Event ev;
        getEvent(-1,ev);
        if (ev.type == EVT_BUT_ON) {
            int x = ev.pix.x();
            int y = ev.pix.y();
            if (x>W-W/5 && y>H-H/10 && x<W-W/5+200 && y<H-H/10+50)
                b = false;
        }
    }
    clearWindow();
}
