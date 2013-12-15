#include "FloorManager.h"
FloorManager::FloorManager(Ogre::SceneManager* scMgr, int xRows, int zRows, float tileSize):
    m_xRows(xRows), m_zRows(zRows),
    m_tileSize(tileSize), m_smgr(scMgr)
{
}

void FloorManager::init(const float& heightScale)
{
    float halfLengtOfBrick = m_tileSize/2.0;
    float fXRows = intToFloat(m_xRows);
    float fZRows = intToFloat(m_zRows);
    float xLength = (m_tileSize*fXRows);
    float zLength = (m_tileSize*fZRows);
    m_bricks.resize(m_zRows);
    for(int z=0; z<m_zRows; z++)
    {
        m_bricks[z].resize(m_xRows);
        for(int x=0; x<m_xRows; x++)
        {
            float fX = intToFloat(x);
            float fZ = intToFloat(z);
            float yPos = octave_noise_2d( 15.0f, 1.0f, 10.0f, (fX/fXRows),(fZ/fZRows))*heightScale;
            std::cout << yPos << std::endl;
            float xPos = (fX/fXRows-0.5f)*xLength;
            float zPos = (fZ/fZRows-0.5f)*zLength;
            m_bricks[z][x] = DynamicObject(z,x, m_smgr, halfLengtOfBrick, &m_bricks,Ogre::Vector3(xPos, yPos, zPos));
        }
    }
    for(int z=0; z<m_zRows; z++)
    {
        for(int x=0; x<m_xRows; x++)
        {
            m_bricks[z][x].findAverage();
        }
    }
    for(int z=0; z<m_zRows; z++)
    {
        for(int x=0; x<m_xRows; x++)
        {
            m_bricks[z][x].makeMesh();
        }
    }
}
FloorManager::~FloorManager()
{
}

