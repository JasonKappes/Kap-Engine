#ifndef _drawablemanager
#define _drawablemanager
#include <list>

class Drawable;

class DrawableManager
{
public:
    using StorageList = std::list<Drawable*>;
    using StorageListRef = StorageList::iterator;
    StorageList m_storageList;
    StorageList::iterator m_iterator;

public:
    DrawableManager() = default;
    ~DrawableManager();
    DrawableManager(const DrawableManager&) = delete;
    DrawableManager& operator=(const DrawableManager&) = delete;

    void ProcessElements() const;

    void Register(Drawable* up, StorageListRef&);
    void Deregister(StorageListRef&);
public:

};

#endif _drawablemanager
