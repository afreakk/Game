#ifndef DYNAMICOBJ_H
#define DYNAMICOBJ_H
#include "OgreManualObject.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
#include <vector>
class DynamicObject
{
    public:
        DynamicObject();
        DynamicObject(int zIndex, int xIndex, Ogre::SceneManager* sceneMgr,  float scale,
                std::vector<  std::vector<DynamicObject>  >* floorMgrArr, Ogre::Vector3 position);
        ~DynamicObject();
        Ogre::SceneNode* getNode();
        void findAverage();
        Ogre::Vector3& getPoint(int i);
        void makeMesh();
    private:
        void init(Ogre::Vector3 position);
        void groundPlaneFromPoint(Ogre::Vector3 point,float scale);
        Ogre::ManualObject* manual;
        Ogre::SceneNode* manNode;
        Ogre::SceneManager* smgr;
        float tileSize;
        int thisZ,thisX;
        std::vector< Ogre::Vector3> points;
        std::vector< Ogre::Vector3> normals;
        std::vector<  std::vector<DynamicObject>  >* allTiles;
        bool isWithinRange(int x, int z);
        void planeFromObjects(DynamicObject& objA, DynamicObject& objB);
    public:
        ///getSets--
};
#endif
