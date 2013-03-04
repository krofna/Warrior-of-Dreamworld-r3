#include "ObjectContainer.hpp"

void ObjectContainer::SendUpdate(WorldSession* pSession)
{
    pSession->Send(ObjectUpdatePckt);
}
