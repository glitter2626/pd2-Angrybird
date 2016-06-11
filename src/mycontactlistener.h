#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H
#include <Box2D/Box2D.h>
class myContactListener : public b2ContactListener{
public:
    void BeginContact(b2Contact *contact);
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
    void EndContact(b2Contact *contact);

private:
    bool iscontacted = 0;
};

#endif // MYCONTACTLISTENER_H

