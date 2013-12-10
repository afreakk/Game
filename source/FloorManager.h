#ifndef FLOORMANAGER_H
#define FLOORMANAGER_H
#include "DynamicObject.h"
#include "simplexnoise.h"
#include "utils.h"
#include <vector>
class FloorManager
{
    public:
        FloorManager(Ogre::SceneManager* scMgr, int numXRows, int numZRows, float sizePerTile);
        ~FloorManager();
    private:
        void init();
        int xRows, zRows;
        float tileSize;
        Ogre::SceneManager* smgr;
        std::vector<  std::vector<DynamicObject>  > bricks;
};
#endif
