/**
  *   @file PhysicsWorld.hpp
  *   @author Lauri Westerholm
  *   @brief Header for PhysicsWorld class
  */

#pragma once

#include "../utils/Rect.hpp"
#include "../utils/Vector2.hpp"
#include "PhysicsObject.hpp"
#include "DynamicObject.hpp"
#include "StaticObject.hpp"
#include "PhysicsGrid.hpp"
#include "CollisionDetection.hpp"
#include <list>
#include <thread>
#include <mutex>

/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {

  /**
    *   @struct Collided
    *   @brief struct containing two collided PhysicsObject
    */
  struct Collided {
    PhysicsObject* first; /**< 1st collided object */
    PhysicsObject* second; /**< 2nd collided object */

    /**
      *   @brief Constructor
      *   @param first collided PhysicsObject pointer
      *   @param second collided PhysicsObject pointer
      */
    Collided(PhysicsObject* first, PhysicsObject* second):
              first(first), second(second) {}

    /**
      *   @brief Get index matching PhysicsObject
      *   @param index collided object's index (0 or 1)
      *   @return PhysicsObject pointer matching the index. returns nullptr if index incorrect
      */
    PhysicsObject* operator[](int index) {
      if (index == 0) return first;
      if (index == 1) return second;
      return nullptr;
    }
  };

  /**
    *   @namespace WorkType
    *   @brief Used to avoid namespace collisions with PhysicsWorld method names
    */
  namespace WorkType {
    /**
      *   @enum WorkType
      *   @brief Describes work for PhysicsWorld::DoWork
      */
    enum WorkType {
      UpdateObjects,
      CheckCollisions
    };
  } // end of namespace WorkType


  /**
    *   @class PhysicsWorld
    *   @brief World for PhysicsObject
    *   @details How PhysicsWorld should be used?
    *   1. Create Dynamic/StaticObjects, set their initial positions, forces etc.
    *   2. Add Objects to PhysicsWorld
    *   3. Call PhysicsWorld.update() to update Objects' position in the world and their physics
    *   4. Possibly remove PhysicsObjects which have collided or have some other actions based on getCollided()
    *   4. Draw PhysicsObjects
    *   5. Possibly change forces, object positions etc.
    *   6. Repeat process described above
    */
  class PhysicsWorld
  {
    public:
      /**
        *   @brief Set how many worker threads PhysicsEngine uses during PhysicsWorld update
        *   @remark PhysicsEngine actually uses one more thread which is the main thread
        *   @param amount needs to be smaller or equal to std::thread::hardware_concurrency
        */
      static void setThreads(unsigned amount);

      /**
        *   @brief Return how many threads are used
        *   @details This is the actual value of threads used by PhysicsWorld::update
        *   i.e. THREADS + 1
        *   return TREADS + 1
        */
      inline static unsigned getThreads() {
        return THREADS + 1;
      }

      /**
        *   @brief Set how many iterations is calculated each second
        *   @details Changes the class variable, PhysicsWorld::IterarationsInterval
        *   @param iterations How many iterations should be calculated per second
        */
      static void setIterationAmount(float iterations);

      /**
        *   @brief Get amount of iterations per second
        *   @return amount of iterations / s
        */
      static inline float getIterationAmount() {
        return 1.f / IterarationsInterval;
      }

      /**
        *   @brief Constructor
        *   @details Creates PhysicsWorld with PhysicsGrid consisting of empty
        *   Cells
        */
      PhysicsWorld();

      /**
        *   @brief Deconstructor
        *   @details Removes every PhysicsObject, PhysicsGrid and deletes memory
        *   allocated for those
        */
      virtual ~PhysicsWorld();

      /**
        *   @brief Copy constructor
        *   @param world to be copied
        */
      PhysicsWorld(const PhysicsWorld& world);

      /**
        *   @brief Assignment operator
        *   @param world to be assigned
        *   @return updated reference to the PhysicsWorld
        */
      PhysicsWorld& operator=(const PhysicsWorld& world);

      /**
        *   @brief Add PhysicsObject to PhysicsWorld
        *   @details Adds object to the correct PhysicsGrid Cell and starts to
        *   update its position and collisions when update is called
        *   @param object to be added
        *   @remark PhysicsWorld (PhysicsGrid) takes ownership of the object (must be allocated from heap).
        *   Remove object by calling removeObject (Do NOT delete object by other ways)
        *   @return true if object added, otherwise false
        */
      bool addObject(PhysicsObject* object);

      /**
        *   @brief Remove object from PhysicsWorld
        *   @details This is the only correct way to permanently remove objects.
        *   object is removed from PhysicsGrid and its memory is deleted
        *   @param object to be removed permanently
        *   @return true if object found and removed, otherwise false
        */
      bool removeObject(PhysicsObject* object);

      /**
        *   @brief Update PhysicsWorld
        *   @details This should be called periodically. Currently no support for
        *   real time collision detection (fast moving objects will go through each
        *   other)
        *   @remark This is should be called before calling getCollided()
        */
      void update();

      /**
        *   @brief Get list of collied PhysicsObjects
        *   @details Each entry in the list is struct Collided
        *   @return collided
        *   @remark collided is updated when update is called
        */
      std::list<struct Collided>& getCollided();

    private:
      // Class members
      static const int GridCellSize;
      static unsigned THREADS;
      static int WorldWidth;
      static int WorldHeight;
      static float IterarationsInterval;

      // Private functions
      /**
        *   @brief Init grid to contain empty Cells
        *   @details This should be called from constructor to init grid
        */
      void InitGrid();

      /**
        *   @brief Start threads to do specified work
        *   @param worktype WorkType describing whether PhysicsObjects should be
        *   updated or collisions checked
        */
      void DoWork(enum WorkType::WorkType worktype);

      /**
        *   @brief Update PhysicsObjects
        *   @details Updates objects which are in the specific Cells given with
        *   iterators. Calls updatePhysics for DynamicObjects
        *   @param begin iterator to the first Cell & Recti which should be updated
        *   @param end iterator which must not be updated anymore
        */
      void UpdateObjects(std::map<Recti, Cell<PhysicsObject*>*>::const_iterator begin, std::map<Recti, Cell<PhysicsObject*>*>::const_iterator end);

      /**
        *   @brief Update loose_cell PhysicsObjects
        *   @details Calls updatePhysics for DynamicObjects
        */
      void UpdateLooseObjects();

      /**
        *   @brief Check collisions between PhysicsObjects
        *   @details Goes through all objects that are located in same grid cell
        *   or are lose (these can also collide). Calls CollisionDetection::canCollide
        *   Updates also collided based on return value of canCollide
        *   @param begin iterator to grid->cells where checking should be started
        *   @param end iterator to grid->cells which must not be checked
        *   @remark O*N^2 complexity, multithread support
        */
      void CheckCollisions(std::map<Recti, Cell<PhysicsObject*>*>::const_iterator begin, std::map<Recti, Cell<PhysicsObject*>*>::const_iterator end);

      /**
        *   @brief Check collisions for the loose PhysicsObjects
        *   @details Loose objects can collided with any objects (loose or not loose).
        *   Updates collided based on return values of CollisionDetection::canCollide
        *   @remark O*N^2 complexity, this cannot be multithreaded
        */
      void CheckLooseCollisions();

      // Instance variables
      PhysicsGrid* grid;
      std::list<struct Collided> collided;
      std::mutex collided_mutex;

  };

} // end of namespace pe
