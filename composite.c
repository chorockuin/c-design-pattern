typedef struct {
    int health;
    void (*fly)(void *this);
    void (*attack)(void *this);
} AirUnit;



typedef struct {
    AirUnit base;
} Interceptor;

static void Interceptor_fly(void *this) {
    printf("...\n");
}

static void Interceptor_attack(void *this) {
    printf("...\n");
}



typedef struct {
    AirUnit base;
    AirUnit *interceptors[8];
} Carrier;

static void Carrier_fly(void *this) {
    Carrier *carrier = (Carrier *)this;
    for (int i = 0; i < 8; ++i ) {
        carrier->interceptors[i]->fly(carrier->interceptors[i]);
    }
    printf("Instructions!\n");
}

static void Carrier_attack(void *this) {
    Carrier *carrier = (Carrier *)this;
    for (int i = 0; i < 8; ++i ) {
        carrier->interceptors[i]->attack(carrier->interceptors[i]);
    }
    printf("Commencing!\n");
}

static void Carrier_constructor(Carrier *carrier) {
    AirUnit *unit = (AirUnit *)carrier;
    unit->health = 350;
    unit->fly = Carrier_fly;
    unit->attack = Carrier_attack;
    for (int i = 0; i < 8; ++i) {
        AirUnit *interceptor = (AirUnit *)malloc(sizeof(Interceptor));
        interceptor->health = 40;
        interceptor->fly = Interceptor_fly;
        interceptor->attack = Interceptor_attack;
        carrier->interceptors[i] = interceptor;
    }
}

static void Carrier_destructor(Carrier *carrier) {
    for (int i = 0; i < 8; ++i) {
        free((Interceptor *)(carrier->interceptors[i]));
    }
}



void composite() {
    printf("======================== composite\n");
    AirUnit *unit = (AirUnit *)malloc(sizeof(Carrier));
    Carrier_constructor((Carrier *)unit);
    unit->fly(unit);
    unit->attack(unit);
    Carrier_destructor((Carrier *)unit);
    free((Carrier *)unit);
}
