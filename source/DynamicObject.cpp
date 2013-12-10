#include "DynamicObject.h"
DynamicObject::DynamicObject()
{

}
DynamicObject::DynamicObject(int zIndex, int xIndex, Ogre::SceneManager* sceneMgr, float scale,
                std::vector<  std::vector<DynamicObject>  >* floorMgrArr, Ogre::Vector3 position)
    :smgr(sceneMgr),tileSize(scale),allTiles(floorMgrArr),thisX(xIndex),thisZ(zIndex)
{
    init(position);
}
DynamicObject::~DynamicObject()
{
} 

Ogre::Vector3& DynamicObject::getPoint(int i)
{ 
    return points[i]; 
}
Ogre::SceneNode* DynamicObject::getNode()
{
    return manNode;
}
void DynamicObject::findAverage()
{
    int z1=thisZ  ,   x1=thisX+1;
    int z2=thisZ+1,   x2=thisX  ;
    if(isWithinRange(z1,x1)&&isWithinRange(z2,x2))
        planeFromObjects( (*allTiles)[z1][x1], (*allTiles)[z2][x2] );
}
void DynamicObject::planeFromObjects(DynamicObject& objA, DynamicObject& objB)
{
    Ogre::Vector3 mod = Ogre::Vector3(0,getNode()->getPosition().y - objA.getNode()->getPosition().y,0);
    points.resize(6);
    normals.resize(6);
    points[4] = points[2]-mod;
    points[5] = points[3]-mod;

    float nrm = (mod.y<0.0f)?1.0f:-1.0f;
    normals[4] = Ogre::Vector3(nrm,0,0);
    normals[5] = Ogre::Vector3(nrm,0,0);

/*    mod = Ogre::Vector3(0,getNode()->getPosition().y - objB.getNode()->getPosition().y,0);
    points[6] = points[3];
    points[7] = points[1];
    points[8] = points[1]-mod;
    points[9] = points[3]-mod;
//borken
    nrm = (mod.y < 0.0f)?1.0f:-1.0f;
    normals[6] = Ogre::Vector3(0,0,nrm);
    normals[7] = Ogre::Vector3(0,0,nrm);
    normals[8] = Ogre::Vector3(0,0,nrm);
    normals[9] = Ogre::Vector3(0,0,nrm);*/
}
bool DynamicObject::isWithinRange(int z, int x)
{
    if(x >= 0 && x<(*allTiles)[0].size())
        if(z >= 0 && z<(*allTiles).size())
            return true;
    return false;
}
void DynamicObject::groundPlaneFromPoint(Ogre::Vector3 point,float scale)
{
    points.resize(4);
    points[0] = Ogre::Vector3(point.x-scale, point.y, point.z-scale);
    points[1] = Ogre::Vector3(point.x-scale, point.y, point.z+scale);   //top

    points[2] = Ogre::Vector3(point.x+scale, point.y, point.z-scale); 
    points[3] = Ogre::Vector3(point.x+scale, point.y, point.z+scale); //bot

    normals.resize(4);
    normals[0] = Ogre::Vector3(0,1,0);
    normals[1] = Ogre::Vector3(0,1,0);

    normals[2] = Ogre::Vector3(0,1,0);
    normals[3] = Ogre::Vector3(0,1,0);
}
void DynamicObject::makeMesh()
{
    manual = smgr->createManualObject();
    manual->begin("BaseWhite", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    for(int i=0; i<points.size(); i++)
    {
        manual->position(points[i]);
        manual->normal(normals[i]);
    }
    manual->end();
    manNode->attachObject(manual);
}
void DynamicObject::init(Ogre::Vector3 position)
{
    groundPlaneFromPoint(Ogre::Vector3(0,0,0),tileSize);
    manNode = smgr->getRootSceneNode()->createChildSceneNode();
    manNode->setPosition(position);
}
