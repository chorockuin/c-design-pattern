#include <stdio.h>

typedef struct {
    int health;
    void (*move)(void *this);
    void (*attack)(void *this);
} LandUnit;

typedef enum {
    eVulture,
    eSiegeTank,
    // eGoliath
} eLandUnit;



typedef struct {
    LandUnit base;
} Vulture;

static void Vulture_move(void *this) {
    printf("Something on your mind?\n");
}

static void Vulture_attack(void *this) {
    printf("Oh... Is that it?\n");
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



// typedef struct {
//     LandUnit base;
// } Goliath;

// static void Goliath_move(void *this) {
//     printf("Systems functional.\n");
// }

// static void Goliath_attack(void *this) {
//     printf("Acknowledged H.Q.\n");
// }



typedef struct {
    LandUnit *(*create_unit)(eLandUnit e);
} Factory;



typedef struct {
    int health;
    void (*fly)(void *this);
    void (*attack)(void *this);
} AirUnit;

typedef enum {
    eWraith,
    eValkyrie
} eAirUnit;



typedef struct {
    AirUnit base;
} Wraith;

static void Wraith_fly(void *this) {
    printf("Go ahead, commander.\n");
}

static void Wraith_attack(void *this) {
    printf("Attack formation.\n");
}



typedef struct {
    AirUnit base;
} Valkyrie;

static void Valkyrie_fly(void *this) {
    printf("Need something destroyed?\n");
}

static void Valkyrie_attack(void *this) {
    printf("It's show time!\n");
}



typedef struct {
    AirUnit *(*create_unit)(eAirUnit e);
} Starport;



typedef struct {
    Factory base;
} FactoryA;

LandUnit *FactoryA_create_unit(eLandUnit e) {
    LandUnit *unit = NULL;
    switch (e) {
        case eVulture:
            unit = (LandUnit *)malloc(sizeof(Vulture));
            unit->health = 80;
            unit->move = Vulture_move;
            unit->attack = Vulture_attack;
            break;
        case eSiegeTank:
            unit = (LandUnit *)malloc(sizeof(SiegeTank));
            unit->health = 150;
            unit->move = SiegeTank_move;
            unit->attack = SiegeTank_attack;
            break;
        // case eGoliath:
        //     unit = (LandUnit *)malloc(sizeof(Goliath));
        //     unit->health = 125;
        //     unit->move = Goliath_move;
        //     unit->attack = Goliath_attack;
        //     break;
    }
    return unit;
}



typedef struct {
    Starport base;
} StarportA;

AirUnit *StarportA_create_unit(eAirUnit e) {
    AirUnit *unit = NULL;
    switch (e) {
        case eWraith:
            unit = (AirUnit *)malloc(sizeof(Wraith));
            unit->health = 120;
            unit->fly = Wraith_fly;
            unit->attack = Wraith_attack;
            break;
        case eValkyrie:
            unit = (AirUnit *)malloc(sizeof(Valkyrie));
            unit->health = 200;
            unit->fly = Valkyrie_fly;
            unit->attack = Valkyrie_attack;
            break;
    }
    return unit;
}



void factory_method() {
    Factory *factory = (Factory *)malloc(sizeof(FactoryA));
    factory->create_unit = FactoryA_create_unit;
    {
        LandUnit *unit = factory->create_unit(eSiegeTank);
        unit->move(unit);
        unit->health--;
        unit->attack(unit);
        free(unit); // need to be virtual destructor
    }
    free((FactoryA *)factory);

    Starport *starport = (Starport *)malloc(sizeof(StarportA));
    starport->create_unit = StarportA_create_unit;
    {
        AirUnit *unit = starport->create_unit(eValkyrie);
        unit->fly(unit);
        unit->health++;
        unit->attack(unit);
        free(unit); // need to be virtual destructor
    }
    free((StarportA *)starport);
}



typedef struct {
    LandUnit *(*create_factory_unit)(void *this);
    AirUnit *(*create_starport_unit)(void *this);
} Campaign;



typedef struct {
    Campaign campaign;
} CampaignA;

LandUnit *CampaignA_create_factory_unit(void *this) {
    LandUnit *unit = (LandUnit *)malloc(sizeof(Vulture));
    unit->health = 80;
    unit->move = Vulture_move;
    unit->attack = Vulture_attack;
    return unit;
}

AirUnit *CampaignA_create_starport_unit(void *this) {
    AirUnit *unit = (AirUnit *)malloc(sizeof(Wraith));
    unit->health = 200;
    unit->fly = Wraith_fly;
    unit->attack = Wraith_attack;
    return unit;
}



void abstract_factory() {
    Campaign *campaign = (Campaign *)malloc(sizeof(CampaignA));
    campaign->create_factory_unit = CampaignA_create_factory_unit;
    campaign->create_starport_unit = CampaignA_create_starport_unit;
    {
        LandUnit *factory_unit = campaign->create_factory_unit(campaign);
        factory_unit->move(factory_unit);
        factory_unit->attack(factory_unit);

        AirUnit *starport_unit = campaign->create_starport_unit(campaign);
        starport_unit->fly(starport_unit);
        starport_unit->attack(starport_unit);

        free(factory_unit); // need to be virtual destructor
        free(starport_unit); // need to be virtual destructor
    }
    free((CampaignA *)campaign);
}

void factory() {
    printf("======================== factory\n");
    factory_method();
    abstract_factory();
}
