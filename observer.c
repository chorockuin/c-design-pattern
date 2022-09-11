typedef struct {
    void (*update)(void *this, unsigned char *data);
} Observer;

typedef struct {
    int data;
    Observer *observers[10];
    int observer_num;
    void (*add)(void *this, Observer *observer);
    void (*update)(void *this);
} Publisher;

void Publisher_add(void *this, Observer *observer) {
    Publisher *publisher = (Publisher *)this;
    publisher->observers[publisher->observer_num++] = observer;
}

void Publisher_update(void *this) {
    Publisher *publisher = (Publisher *)this;
    for (int i = 0; i < publisher->observer_num; ++i) {
        Observer *observer = publisher->observers[i];
        observer->update(observer, (unsigned char *)&publisher->data);
    }
}

void Publisher_construct(Publisher *publisher) {
    publisher->data = 1024;
    memset(publisher->observers, 0, sizeof(publisher->observers));
    publisher->observer_num = 0;
    publisher->add = Publisher_add;
    publisher->update = Publisher_update;
}



typedef struct {
    Observer base;
} ObserverA;

void ObserverA_update(void *this, unsigned char *data) {
    printf("something is changed in publisher\n");
}



typedef struct {
    Observer base;
} ObserverB;

void ObserverB_update(void *this, unsigned char *data) {
    printf("first 4byte of publisher's data is %d\n", (int)(*data));
}



typedef struct {
    Publisher base;
} PublisherA;

void PublisherA_construct(PublisherA *publisher) {
    Publisher_construct((Publisher *)publisher);
}



void observer() {
    printf("======================== observer\n");
    Publisher *publisher = (Publisher *)malloc(sizeof(PublisherA));
    PublisherA_construct((PublisherA *)publisher);

    Observer *observerA = (Observer *)malloc(sizeof(ObserverA));
    observerA->update = ObserverA_update;

    Observer *observerB = (Observer *)malloc(sizeof(ObserverB));
    observerB->update = ObserverB_update;

    publisher->add(publisher, observerA);
    publisher->add(publisher, observerB);
    publisher->data++;
    publisher->update(publisher);

    free((PublisherA *)publisher);
    free((ObserverA *)observerA);
    free((ObserverB *)observerB);
}
