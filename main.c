#include "queue.h"

DEFINE_QUEUE_HEADER(QueueInt, int)
DEFINE_QUEUE(QueueInt, int)

typedef struct Actor {
    int a;
    int* b;
} Actor;

DEFINE_QUEUE_HEADER(QueueActor, Actor)
DEFINE_QUEUE(QueueActor, Actor)

int main() {

    QueueInt qi = queue_int_create();
    QueueActor qa = queue_Actor_create();

}
