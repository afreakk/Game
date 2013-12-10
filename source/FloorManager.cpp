#include "FloorManager.h"
FloorManager::FloorManager(Ogre::SceneManager* scMgr, int numXRows, int numZRows, float sizePerTile)
:xRows(numXRows),zRows(numZRows),tileSize(sizePerTile),smgr(scMgr)
{
    init();
}

void FloorManager::init()
{
    float halfLengtOfBrick = tileSize/2.0;
    float fXRows = intToFloat(xRows);
    float fZRows = intToFloat(zRows);
    float xLength = (tileSize*fXRows);
    float zLength = (tileSize*fZRows);
    bricks.resize(zRows);
    for(int z=0; z<zRows; z++)
    {
        bricks[z].resize(xRows);
        for(int x=0; x<xRows; x++)
        {
            float fX = intToFloat(x);
            float fZ = intToFloat(z);
            float yPos = octave_noise_2d( 1.0f, 1.0f, 1.0f, (fX/fXRows)*3.14*2,(fZ/fZRows)*3.14*2)*halfLengtOfBrick;
            float xPos = (fX/fXRows-0.5f)*xLength;
            float zPos = (fZ/fZRows-0.5f)*zLength;
            bricks[z][x] = DynamicObject(z,x, smgr, halfLengtOfBrick, &bricks,Ogre::Vector3(xPos, yPos, zPos));
        }
    }
    for(int z=0; z<zRows; z++)
    {
        for(int x=0; x<xRows; x++)
        {
            bricks[z][x].findAverage();
        }
    }
    for(int z=0; z<zRows; z++)
    {
        for(int x=0; x<xRows; x++)
        {
            bricks[z][x].makeMesh();
        }
    }
}
FloorManager::~FloorManager()
{
}

