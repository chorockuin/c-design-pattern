typedef struct {
    void *decorator;
    void (*mix)(void *this);
} Decorator;

void Decorator_mix(void *this) {
    Decorator *decorator = ((Decorator *)this)->decorator;
    if (decorator)
        decorator->mix(decorator);
}



typedef struct {
    Decorator base;
    void (*add_shot)(void *this);
} Espresso;

void Espresso_mix(void *this) {
    Decorator_mix(this);

    Espresso *espresso = (Espresso *)this;
    espresso->add_shot(espresso);
}

void Espresso_add_shot(void *this) {
    printf("added shot!\n");
}



typedef struct {
    Decorator base;
    void (*add_milk)(void *this);
} Latte;

void Latte_mix(void *this) {
    Decorator_mix(this);

    Latte *latte = (Latte *)this;
    latte->add_milk(latte);
}

void Latte_add_milk(void *this) {
    printf("added milk!\n");
}



void decorator() {
    printf("======================== decorator\n");

    Espresso *espresso = (Espresso *)malloc(sizeof(Espresso));
    ((Decorator *)espresso)->decorator = 0;
    ((Decorator *)espresso)->mix = Espresso_mix;
    espresso->add_shot = Espresso_add_shot;

    Espresso *doubleshot = (Espresso *)malloc(sizeof(Espresso));
    ((Decorator *)doubleshot)->decorator = espresso;
    ((Decorator *)doubleshot)->mix = Espresso_mix;
    doubleshot->add_shot = Espresso_add_shot;

    Latte *latte = (Latte *)malloc(sizeof(Latte));
    ((Decorator *)latte)->decorator = espresso;
    ((Decorator *)latte)->mix = Latte_mix;
    latte->add_milk = Latte_add_milk;

    printf("* single shot\n");
    ((Decorator *)espresso)->mix(espresso);

    printf("* double shot\n");
    ((Decorator *)doubleshot)->mix(doubleshot);

    printf("* latte shot\n");
    ((Decorator *)latte)->mix(latte);

    free(espresso);
    free(doubleshot);
    free(latte);
}
