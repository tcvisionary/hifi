//
//  ShapeManager.h
//  libraries/physcis/src
//
//  Created by Andrew Meadows 2014.10.29
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_ShapeManager_h
#define hifi_ShapeManager_h

#ifdef USE_BULLET_PHYSICS

#include <btBulletDynamicsCommon.h>
#include <LinearMath/btHashMap.h>

#include "ShapeInfo.h"

class ShapeKey
{
public:
    ShapeKey(const ShapeInfo& info) : _hash(0), _hash2(0) {
        _hash = info.computeHash();
        _hash2 = info.computeHash2();
    }

    bool equals(const ShapeKey& other) const {
        return _hash == other._hash && _hash2 == other._hash2;
    }

    unsigned int getHash() const { return (unsigned int)_hash; }

private:
    int _hash;
    int _hash2;
};


class ShapeManager {
public:

    ShapeManager();
    ~ShapeManager();

    /// \return pointer to shape
    btCollisionShape* getShape(const ShapeInfo& info);

    /// \return true if shape was found and released
    bool releaseShape(const ShapeInfo& info);
//    bool removeReference(const btCollisionShape*);

    /// delete shapes that have zero references
    void collectGarbage();

    // validation methods
    int getNumShapes() const { return _shapeMap.size(); }
    int getNumReferences(const ShapeInfo& info) const;

private:
    struct ShapeReference {
        int _refCount;
        btCollisionShape* _shape;
        ShapeReference() : _refCount(0), _shape(NULL) {}
    };

    btHashMap<ShapeKey, ShapeReference> _shapeMap;
    btAlignedObjectArray<ShapeKey> _pendingGarbage;
};

#endif // USE_BULLET_PHYSICS
#endif // hifi_ShapeManager_h
