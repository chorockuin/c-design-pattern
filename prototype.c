#include <stdio.h>

typedef struct {
    int health;
    void (*move)(void *this);
    void (*attack)(void *this);
    void *(*clone)(void *this);
} LandUnit;



typedef struct {
    LandUnit base;
} Vulture;

static void Vulture_move(void *this) {
    printf("Something on your mind?\n");
}

static void Vulture_attack(void *this) {
    printf("Oh... Is that it?\n");
}

LandUnit *Vulture_clone(void *this) {
    Vulture *vulture = (Vulture *)malloc(sizeof(Vulture));
    memcpy(vulture, this, sizeof(Vulture));
    return (LandUnit *)vulture;
}



typedef struct {
    LandUnit base;
} SiegeTank;

static void SiegeTank_move(void *this) {
    printf("Move it!\n");
}

static void SiegeTank_attack(void *this) {
    printf("Absolutely.\n");
}

LandUnit *SiegeTank_clone(void *this) {
    SiegeTank *siegetank = (SiegeTank *)malloc(sizeof(SiegeTank));
    memcpy(siegetank, this, sizeof(SiegeTank));
    return (LandUnit *)siegetank;
}



LandUnit *create_unit(LandUnit *unit) {
    return unit->clone(unit);
}



void prototype() {
    printf("======================== prototype\n");
    Vulture vulture_proto;
    vulture_proto.base.health = 80;
    vulture_proto.base.move = Vulture_move;
    vulture_proto.base.attack = Vulture_attack;
    vulture_proto.base.clone = Vulture_clone;

    SiegeTank siegetank_proto;
    siegetank_proto.base.health = 200;
    siegetank_proto.base.move = SiegeTank_move;
    siegetank_proto.base.attack = SiegeTank_attack;
    siegetank_proto.base.clone = SiegeTank_clone;

    {
        LandUnit *vulture = create_unit((LandUnit *)&vulture_proto);
        vulture->move(vulture);
        vulture->attack(vulture);

        LandUnit *siegetank = create_unit((LandUnit *)&siegetank_proto);
        siegetank->move(siegetank);
        siegetank->attack(siegetank);

        free((Vulture *)vulture);
        free((SiegeTank *)siegetank);
    }
}
