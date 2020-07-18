#include "Vect.h"
#include "Matrix.h"
#include <list>
#ifndef _visualizer
#define _visualizer

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class VisualizeRegistrationCommand;
class GraphicsObject_WireframeConstantColor;
class VisualizerFactory;
class AABBRender;
class OBBRender;
class BSphereRender;

class Visualizer : public Align16
{
    friend class VisualizerAttorney;
private:
    Visualizer();
    Visualizer(const Visualizer&) = delete;
    Visualizer operator=(const Visualizer&) = delete;
    ~Visualizer();

    static Visualizer& Instance() 
    {
        if (!pInstance)
            pInstance = new Visualizer();
        return *pInstance;
    }

    static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col);
    static void ShowBSphere(Vect center, float radius, const Vect& col);
    static void RenderBSphere(Matrix& S, const Vect& col);
    static void ShowAABB(const CollisionVolumeAABB& S, const Vect& col);
    static void RenderAABB(Matrix& S, const Vect& col);
    static void ShowOBB(const CollisionVolumeOBB& S, const Vect& col);
    static void RenderOBB(Matrix& S, const Vect& col);
    static void VisualizeAll();
    static void Delete();

private:

    void privShowAABB(const CollisionVolumeAABB& S, const Vect& col);
    void privRenderAABB(Matrix& S, const Vect& col);
    void privShowOBB(const CollisionVolumeOBB& S, const Vect& col);
    void privRenderOBB(Matrix& S, const Vect& col);
    void privShowBSphere(const CollisionVolumeBSphere& S, const Vect& col);
    void privShowBSphere(Vect center, float radius, const Vect& col);
    void privVisualizeAll();
    void privDelete();

private:
    static Visualizer* pInstance;
    static Vect DEFAULT_COLOR;
    GraphicsObject_WireframeConstantColor* m_WFUnitSphere;
    GraphicsObject_WireframeConstantColor* m_WFUnitBox;

    VisualizerFactory* m_VisualizerFactory;
    std::list<VisualizeRegistrationCommand*> m_VisualizeColl;
    std::list<VisualizeRegistrationCommand*>::iterator it;

    AABBRender* m_aabbRender;
    OBBRender* m_obbRender;
    BSphereRender* m_bsphereRender;

};

#endif _visualizer
#pragma once
