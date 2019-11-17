/**
  *   @file WorldWrapper.hpp
  *   @author Lauri Westerholm
  *   @brief Contains WorldWrapper
  */


#pragma once
#include "../physics/Vector2.hpp"
#include "../physics/Shape.hpp"
#include "../physics/PhysicsObject.hpp"
#include "../physics/DynamicObject.hpp"
#include "../physics/StaticObject.hpp"
#include "../physics/PhysicsWorld.hpp"
#include <map>
#include <deque>
#include <list>


/**< Macro which makes class non copyable */
#define NON_COPYABLE(Typename) \
  Typename(const Typename&) = delete; \
  Typename& operator=(const Typename&) = delete

#define STD_DENSITY 1.f /**< density used when DynamicObjects are constructed */


/**
  *   @struct ObjectStatus
  *   @brief Used to pass object status and position information
  */
struct ObjectStatus {
  bool exists = true; /**< whether the object still exists in physicsWorld */
  Vector2f position; /**< object's current position, includes origin_transform */
};


/**
  *   @class Pair
  *   @brief contains two unsigned keys, this is just for portability between C++ and Java
  */
class Pair {

  public:
    /**
      *   @brief Empty constructor
      */
    Pair(): first(0), second(0) {}

    /**
      *   @brief Constructor
      *   @param first the first value
      *   @param second the second value
      */
    Pair(unsigned first, unsigned second) : first(first), second(second) {}

    /**
      *   @brief Get first value
      *   @return first
      */
    inline unsigned getFirst() const { return first; }

    /**
      *   @brief Get second value
      *   @return second
      */
    inline unsigned getSecond() const { return second; }

    /**
      *   @brief Set first value
      *   @param first new first value
      */
    inline void setFirst(unsigned first) { this->first = first; }

    /**
      *   @brief Set second value
      *   @param second new second value
      */
    inline void setSecond(unsigned second) { this->second = second; }

  private:
    unsigned first;
    unsigned second;
};


/**
  *   @class WorldWrapper
  *   @brief Acts as a link between C++ and Java
  *   @details All physics related calls (updating, adding new objects, removing
  *   old objects etc.) should be made through instance of WorldWrapper
  */

class WorldWrapper {

  public:
    /**< Set how often physics are updated, this is just a wrapper for Java */
    static void setPhysicsWorldUpdateInterval(float interval);

    /**< Set how many threads PhysicsWorld uses, this is just a wrapper for Java */
    void setPhysicsEngineThreads(unsigned threads);

    /**
      *   @brief Constructor
      */
    WorldWrapper(): physicsWorld(new PhysicsWorld()) {}

    /**
      *   @brief Deconstrutor
      */
    virtual ~WorldWrapper();

    /**
      *   @brief Update PhysicsWorld
      *   @remark This is a wrapper call for physicsWorld->update(). Use this
      *   to update physics. This also returns all collision Pairs
      *   @return collided object keys as deque of Pairs, quite heavy return but
      *   this is called form Java so references don't really work
      */
    std::deque<Pair> update();

    /**
      *   @brief Add object to from Java to physicsWorld
      *   @param static_object whether object is static or not
      *   @param pos object initial position (center of the object)
      *   @param width object width
      *   @param height object height
      *   @return current ObjectID, this key is used to access the object so it must
      *   be stored in the Java class which contains matching objects. Return value 0
      *   means that object adding failed
      */
    unsigned addObject(bool static_object, Vector2f pos, float width, float height);

    /**
      *   @brief Remove object
      *   @param key object id
      *   @remark Does nothing if object matching the key won't exist. This is the only valid way to
      *   remove objects aside deleting the whole WorldWrapper instance
      */
    void removeObject(unsigned key);

    /**
      *   @brief Set physic properties for the object, these don't need to be set
      *   @param key object id
      *   @param elasticity new elasticity value
      *   @param density new density value
      *   @remark Does nothing if object won't exist
      */
    void setObjectPhysicsProperties(unsigned key, float elasticity, float density);

    /**
      *   @brief Set collision mask for the object
      *   @param key object id
      *   @param mask new collision mask, this must in range if (0, 256) as its
      *   converted to uint8_t, it passed as unsigned to make the interface simpler
      *   @remark Does nothing if object won't exist
      */
    void setObjectCollisionMask(unsigned key, unsigned mask);

    /**
      *   @brief Set origin_transform for the object
      *   @param key object id
      *   @param transform new origin_transform as Vector2f
      *   @remark Does nothing if object won't exist
      */
    void setObjectOriginTransform(unsigned key, Vector2f transform);

    /**
      *   @brief Set 2D force for the object
      *   @param key object id
      *   @param force force applied to the object
      *   @remark Does nothing if object won't exist
      */
    void setObjectForce(unsigned key, Vector2f force);

    /**
      *   @brief Set 2D velocity for the object
      *   @param key object id
      *   @param velocity linear velocity for the object
      *   @remark Does nothing if object won't exist
      */
    void setObjectVelocity(unsigned key, Vector2f velocity);

    /**
      *   @brief Set new position for the object
      *   @param key object id
      *   @param pos new position as Vector2f
      *   @remark Does nothing if object won't exist
      */
    void setObjectPosition(unsigned key, Vector2f pos);

    /**
      *   @brief Get object position and info on object existence
      *   @param key object id
      *   @return ObjectStatus, this is a bit heavy but makes the interface simple
      */
    struct ObjectStatus fetchPosition(unsigned key) const;

  private:
    static unsigned ObjectID; /**< This is the object ID which is used to find correct item in physicsObjects */

    /**< Make non-copyable */
    NON_COPYABLE(WorldWrapper);

    /**
      *   @struct ShapeCMP
      *   @brief Implement comparison for Vector2f which allows to distinguish unique shape
      *   @remark Only for WorldWrapper internal use
      */
    struct ShapeCMP {
    /**
      *   @brief Comparison used in shapes map
      *   @details std::maps identify correct key by taking negative bools of
      *   comparisons in both orders (!vec1<vec2 and !vec2<vec1)
      *   @param vec1 1st Vector2f to be compared
      *   @param vec2 2nd Vector2f to be compared
      *   @return true if vec1 x or y value is smaller than those of vec2
      */
    bool operator()(const Vector2f& vec1, const Vector2f& vec2) const {
      return (vec1.getX() < vec2.getX()) || (vec1.getY() < vec2.getY());
    }
    };


    /**
      *   @brief Get correct shape
      *   @details If shape already exits, returns pointer to it. Otherwise this
      *   will create the required pe::Shape
      *   @return Shape with correct size
      */
    Shape* GetShape(float width, float height);

    /**
      *   @brief Get physicsObject matching key
      *   @return PhysicsObject pointer if object exists, otherwise nullptr
      */
    PhysicsObject* GetObject(unsigned key) const;


    /* Variables */

    PhysicsWorld *physicsWorld;
    std::map<Vector2f, Shape*, ShapeCMP> shapes;

    /**
      *   These PhysicsObjects all are in physicsWold so do not deallocate them directly, let the physicsWorld do it
      *   ObjectID is used as an individual key so that object can be also easily accessed from Java
      *   The two maps should contain the same items but mapped just vice versa
      */
    std::map<unsigned, PhysicsObject*> keysToObjects;
    std::map<PhysicsObject*, unsigned> objectsToKeys;

};
