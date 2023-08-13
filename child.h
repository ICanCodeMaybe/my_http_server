#ifndef CHILD_H
#define CHILD_H

class Stream_ser;
struct connection;

void child(Stream_ser* server, struct connection conn);

#endif
