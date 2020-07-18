#ifndef _updatablemanager
#define _updatablemanager
#include <list>

class Updatable;

class UpdatableManager
{
public:
    using StorageList = std::list<Updatable*>;
    using StorageListRef = StorageList::iterator;

public:
    UpdatableManager() = default;
    ~UpdatableManager();
    UpdatableManager(const UpdatableManager&) = delete;
    UpdatableManager& operator=(const UpdatableManager&) = delete;

    void ProcessUpdates() const;

    void ProcessLateUpdates() const;

    void Register(Updatable* up, StorageListRef&);

    void Deregister(StorageListRef&);

private:
    StorageList m_storageList;

};

#endif _updatablemanager
