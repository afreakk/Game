#ifndef FLOORMANAGER_H
#define FLOORMANAGER_H
#include "DynamicObject.h"
#include "libs/simplexnoise/simplexnoise.h"
#include "libs/utils.h"
#include <vector>
class FloorManager
{
    public:
        FloorManager(Ogre::SceneManager* scMgr, int xRows, int zRows, float tileSize);
        ~FloorManager();
        void init(const float& heightScale);
    private:
        int m_xRows, m_zRows;
        float m_tileSize;
        Ogre::SceneManager* m_smgr;
        std::vector<  std::vector<DynamicObject>  > m_bricks;
};
#endif
