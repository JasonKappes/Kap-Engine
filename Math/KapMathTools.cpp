#include "KapMathTools.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include <cmath>
#include <math.h>
#include "DebugOut.h"

float KapMathTools::CalculateClampCoordinate(float value, float minValue, float maxValue)
{
    if (value < minValue)       return minValue;
    else if (value > maxValue)  return maxValue;
    else                        return value;
}

Vect KapMathTools::GetClampedVect(const Vect& p, const Vect& min, const Vect& max)
{
    float clampX = CalculateClampCoordinate(p.X(), min.X(), max.X());
    float clampY = CalculateClampCoordinate(p.Y(), min.Y(), max.Y());
    float clampZ = CalculateClampCoordinate(p.Z(), min.Z(), max.Z());

    return Vect(clampX, clampY, clampZ);
}

bool KapMathTools::IsPointInSphere(const Vect& sphereCenter, float sphereRadius, const Vect& otherPoint)
{
    float distance = sqrt((otherPoint.X() - sphereCenter.X()) * (otherPoint.X() - sphereCenter.X()) +
        (otherPoint.Y() - sphereCenter.Y()) * (otherPoint.Y() - sphereCenter.Y()) +
        (otherPoint.Z() - sphereCenter.Z()) * (otherPoint.Z() - sphereCenter.Z()));

    return distance < sphereRadius;
}

bool KapMathTools::Intersect(const CollisionVolumeBSphere& sphere, const CollisionVolumeAABB& b)
{
    return IsPointInSphere(sphere.GetCenter(), sphere.GetRadius(), GetClampedVect(sphere.GetCenter(), b.GetMin(), b.GetMax()));
}

bool KapMathTools::Intersect(const CollisionVolumeBSphere& sphere, const CollisionVolumeOBB& obb)
{
    Matrix invWorld = obb.GetWorld().getInv();
    Vect sphCenter(sphere.GetCenter());

    sphCenter = sphCenter * invWorld;

    Vect localSpaceP = GetClampedVect(sphCenter, obb.GetMin(), obb.GetMax());
    Vect worldSpaceP = localSpaceP * obb.GetWorld();

    return IsPointInSphere(sphere.GetCenter(), sphere.GetRadius(), worldSpaceP);
}

bool KapMathTools::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B)
{
    Vect posDst = A.GetCenter() - B.GetCenter();
    float distance = EuclidianNorm(posDst);
    float sumRadius = A.GetRadius() + B.GetRadius();
    return distance < sumRadius;
}

bool KapMathTools::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B)
{
    //Test if intervals overlap
    return (A.GetMin().X() <= B.GetMax().X() && A.GetMax().X() >= B.GetMin().X()) &&
        (A.GetMin().Y() <= B.GetMax().Y() && A.GetMax().Y() >= B.GetMin().Y()) &&
        (A.GetMin().Z() <= B.GetMax().Z() && A.GetMax().Z() >= B.GetMin().Z());
}

float KapMathTools::MaxOBBProjection(const Matrix& world, const Vect& hd, float square_scale, const Vect& v)
{
    Vect vv = v;

    //turn into pure vector
    vv[w] = 0;

    //move to local space
    Matrix worldInv = world.getInv();
    vv.set(vv * worldInv);

    float ProjMax = fabsf(vv[x] * hd[x]) + fabsf(vv[y] * hd[y]) + fabsf(vv[z] * hd[z]);

    ProjMax = ProjMax / (vv.dot(vv));

    return (square_scale)*ProjMax;
}

float KapMathTools::EuclidianNorm(const Vect& v)
{
    return abs(sqrt(v.dot(v)) * sqrt(v.dot(v)));
}

Vect KapMathTools::LinePlaneIntersection(const Vect& raypoint, const Vect& raydirection, const Vect& planepoint, const Vect& planenormal)
{
    float prod2 = raydirection.dot(planenormal);
    if (std::abs(prod2) > 0.0001)
    {
        Vect dist = raypoint - planepoint;
        float prod1 = dist.dot(planenormal);
        float prod3 = prod1 / prod2;

        Vect res = raypoint - raydirection * prod3;

        return res;
    }
    else {
        return planepoint;
    }
}

bool KapMathTools::Intersect(const CollisionVolumeOBB& box1, const CollisionVolumeOBB& box2)
{
    Vect Axes[15];
    int ind = 0;

    Axes[ind++] = box1.GetWorld().get(ROW_0);
    Axes[ind++] = box1.GetWorld().get(ROW_1);
    Axes[ind++] = box1.GetWorld().get(ROW_2);

    Axes[ind++] = box2.GetWorld().get(ROW_0);
    Axes[ind++] = box2.GetWorld().get(ROW_1);
    Axes[ind++] = box2.GetWorld().get(ROW_2);

    Axes[ind++] = Axes[0].cross(Axes[3]);
    Axes[ind++] = Axes[0].cross(Axes[4]);
    Axes[ind++] = Axes[0].cross(Axes[5]);
    Axes[ind++] = Axes[1].cross(Axes[3]);
    Axes[ind++] = Axes[1].cross(Axes[4]);
    Axes[ind++] = Axes[1].cross(Axes[5]);
    Axes[ind++] = Axes[2].cross(Axes[3]);
    Axes[ind++] = Axes[2].cross(Axes[4]);
    Axes[ind++] = Axes[2].cross(Axes[5]);

    for (int axis = 0; axis < 15; ++axis)
    {
        Vect v = Axes[axis];

        if (v.magSqr() > FLT_EPSILON)
        {
            float D = abs((box2.GetOBBcenter() - box1.GetOBBcenter()).dot(v) / EuclidianNorm(v));

            //Get A Proj
            Vect aInv = v * box1.GetWorld().getInv();
            Vect dA = Signature(aInv, box1.GetHalfDiagonal());

            float projA = (abs(aInv[x] * dA[x]) + abs(aInv[y] * dA[y]) + abs(aInv[z] * dA[z])) / EuclidianNorm(v);
            projA *= box1.GetSquaredScale();

            //Get B Proj
            Vect bInv = v * box2.GetWorld().getInv();
            Vect dB = Signature(bInv, box2.GetHalfDiagonal());
            float projB = (abs(bInv[x] * dB[x]) + abs(bInv[y] * dB[y]) + abs(bInv[z] * dB[z])) / EuclidianNorm(v);
            projB *= box2.GetSquaredScale();

            if (D > projA + projB) return false;
        }
    }

    return true;
}

Vect KapMathTools::Signature(const Vect& v, const Vect& d)
{
    float newX, newY, newZ;

    if (v.X() < 0) newX = -1 * abs(d.X());
    else newX = abs(d.X());

    if (v.Y() < 0) newY = -1 * abs(d.Y());
    else newY = abs(d.Y());

    if (v.Z() < 0) newZ = -1 * abs(d.Z());
    else newZ = abs(d.Z());

    return Vect(newX, newY, newZ);
}

bool KapMathTools::Intersect(const CollisionVolumeOBB& box1, const CollisionVolumeAABB& box2)
{
    Vect Axes[15];
    int ind = 0;

    Axes[ind++] = box1.GetWorld().get(ROW_0);
    Axes[ind++] = box1.GetWorld().get(ROW_1);
    Axes[ind++] = box1.GetWorld().get(ROW_2);

    Axes[ind++] = box2.GetWorld().get(ROW_0);
    Axes[ind++] = box2.GetWorld().get(ROW_1);
    Axes[ind++] = box2.GetWorld().get(ROW_2);

    Axes[ind++] = Axes[0].cross(Axes[3]);

    Axes[ind++] = Axes[0].cross(Axes[4]);
    Axes[ind++] = Axes[0].cross(Axes[5]);
    Axes[ind++] = Axes[1].cross(Axes[3]);
    Axes[ind++] = Axes[1].cross(Axes[4]);
    Axes[ind++] = Axes[1].cross(Axes[5]);
    Axes[ind++] = Axes[2].cross(Axes[3]);
    Axes[ind++] = Axes[2].cross(Axes[4]);
    Axes[ind++] = Axes[2].cross(Axes[5]);

    for (int axis = 0; axis < 15; ++axis)
    {
        Vect v = Axes[axis];
        if (v.magSqr() > FLT_EPSILON)
        {

            float D = abs((box2.GetOBBcenter() - box1.GetOBBcenter()).dot(v) / EuclidianNorm(v));

            //Get A Proj
            Vect aInv = v * box1.GetWorld().getInv();
            Vect dA = box1.GetHalfDiagonal();
            float projA = (abs(aInv[x] * dA[x]) + abs(aInv[y] * dA[y]) + abs(aInv[z] * dA[z])) / EuclidianNorm(v);
            projA *= box1.GetSquaredScale();

            //Get B Proj
            Vect bInv = v * box2.GetWorld().getInv();
            Vect dB = box2.GetHalfDiagonal();
            float projB = (abs(bInv[x] * dB[x]) + abs(bInv[y] * dB[y]) + abs(bInv[z] * dB[z])) / EuclidianNorm(v);
            projB *= box2.GetSquaredScale();
            if (D > projA + projB) return false;
        }
    }

    return true;
}

bool KapMathTools::Intersect(const CollisionVolume& A, const CollisionVolume& B)
{
    return A.IntersectAccept(B);
}

