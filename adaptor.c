#include <stdio.h>

typedef struct {
    int health;
    void (*move)(void *this);
    void (*attack)(void *this);
} LandUnit;



typedef struct {
    void (*crawl)(void *this);
} Animal;

static void Animal_crawl(void *this) {
    printf("I need food...\n");
}



typedef struct {
    LandUnit base;
    Animal *animal; // adaptee
} AnimalUnit; // adaptor

static void AnimalUnit_attack(void *this) {
    printf("I want to eat you\n");
}

static void AnimalUnit_move(void *this) {
    AnimalUnit *animal_unit = (AnimalUnit *)this;
    animal_unit->animal->crawl(animal_unit->animal);    
}



void adaptor() {
    printf("======================== adaptor\n");
    Animal animal;
    animal.crawl = Animal_crawl;

    AnimalUnit animal_unit;
    animal_unit.base.health = 5;
    animal_unit.base.move = AnimalUnit_move;
    animal_unit.base.attack = AnimalUnit_attack;
    animal_unit.animal = &animal;

    LandUnit *unit = (LandUnit *)&animal_unit;
    unit->move(unit);
    unit->attack(unit);
}
