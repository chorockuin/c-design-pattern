#include <stdio.h>

typedef struct {
    void (*draw)(void *this, unsigned char *data);
} Drawer;

typedef struct {
    int health;
    Drawer *drawer; // bridge
    void (*move)(void *this);
    void (*attack)(void *this);
    void (*draw)(void *this);
} LandUnit;



typedef struct {
    LandUnit base;
} Ghost;

static void Ghost_move(void *this) {
    printf("Ghost reportin.\n");
}

static void Ghost_attack(void *this) {
    printf("I hear that.\n");
}

static void Ghost_draw(void *this) {
    LandUnit *unit = (LandUnit *)this;
    unit->drawer->draw(unit->drawer, "a(@=@)a");
}



typedef struct {
    Drawer base;
} TextDrawer;

static void TextDrawer_draw(void *this, unsigned char *data) {
    printf("%s\n", data);
}



typedef struct {
    Drawer base;
} HtmlDrawer;

static void HtmlDrawer_draw(void *this, unsigned char *data) {
    printf("<HTML><HEAD>Ghost</HEAD><BODY>%s</BODY>", data);
}



void bridge() {
    printf("======================== bridge\n");
    TextDrawer drawer;
    drawer.base.draw = TextDrawer_draw;

    // HtmlDrawer drawer;
    // drawer.base.draw = HtmlDrawer_draw;

    Ghost ghost;
    ghost.base.health = 80;
    ghost.base.drawer = (Drawer *)&drawer;
    ghost.base.move = Ghost_move;
    ghost.base.attack = Ghost_attack;
    ghost.base.draw = Ghost_draw;

    LandUnit *unit = (LandUnit *)&ghost;
    unit->move(unit);
    unit->attack(unit);
    unit->draw(unit);
}
