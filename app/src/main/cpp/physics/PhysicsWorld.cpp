/**
  *   @file PhysicsWorld.cpp
  *   @author Lauri Westerholm
  *   @brief Contains class PhysicsWorld
  */

#include "PhysicsWorld.hpp"


  /* Class PhysicsWorld */

// Init class variables
const int PhysicsWorld::GridCellSize = 10000; // 10000
unsigned PhysicsWorld::THREADS = std::thread::hardware_concurrency() > 1 ? std::thread::hardware_concurrency() - 1 : 0;
int PhysicsWorld::WorldWidth = 300000;
int PhysicsWorld::WorldHeight = PhysicsWorld::WorldWidth;
float PhysicsWorld::IterarationsInterval = 1.f / 60.f;

// Set amount of THREADS
void PhysicsWorld::setThreads(unsigned amount) {
if (amount <= std::thread::hardware_concurrency()) {
  // this should also handle the possible overwarping issues
  PhysicsWorld::THREADS = amount;
}
else PhysicsWorld::THREADS = 7; // no worker threads created
}

// Set how many iterations / s
void PhysicsWorld::setIterationAmount(float iterations) {
PhysicsWorld::IterarationsInterval = 1.f / iterations;
}

// Init Grid, private method
void PhysicsWorld::InitGrid() {
grid->addCells(PhysicsWorld::WorldWidth, PhysicsWorld::WorldHeight, PhysicsWorld::GridCellSize);
}

// Constructor
PhysicsWorld::PhysicsWorld(): grid(new PhysicsGrid()) {
InitGrid();
}

// Deconstructor
PhysicsWorld::~PhysicsWorld() {
delete grid;
}

// Copy constructor
PhysicsWorld::PhysicsWorld(const PhysicsWorld& world):
grid(new PhysicsGrid(*world.grid)), collided(world.collided) {}

// Assignment operator
PhysicsWorld& PhysicsWorld::operator=(const PhysicsWorld& world) {
collided.clear();
*grid = *world.grid;
collided = world.collided;
return *this;
}

// Add PhysicsObject to PhysicsWorld, wrapper call for PhysicsGrid addObject
bool PhysicsWorld::addObject(PhysicsObject* object) {
return grid->addObject(object);
}

// Remove PhysicsObject from PhysicsWorld, wrapper call for PhysicsGrid removeObject
bool PhysicsWorld::removeObject(PhysicsObject* object) {
return grid->removeObject(object);
}

// Update PhysicsWorld PhysicsObject positions and calculate collision
void PhysicsWorld::update() {
/*
  STEPS
  0. init collided
*/
collided.clear();

/*
  1. Update object physics if DynamicObject (call updatePhysics with elapsed
   time, IterarationsInterval, as argument). This could be done in multiple
   threads at the same time, threads operate one grid cell. Activate object
   moved bool.
*/
DoWork(WorkType::UpdateObjects);

/*
  2. Move objects to the correct grid cells (call grid moveObjects)
*/
grid->moveObjects();

/*
  3. Check collisions and store collided objects to collided
    - Collision may cause objects to change grid cells
    - But it's enough to update objects' grid cells during next update cycle
    step 2
*/
DoWork(WorkType::CheckCollisions);
// check also if objects in loose cell collided with each other or with any other
// PhysicsObjects
CheckLooseCollisions();
}

// Start threads to do specified work, private method
void PhysicsWorld::DoWork(enum WorkType::WorkType worktype) {
unsigned interval;
if ((PhysicsWorld::THREADS > 0) && ((interval = grid->getCellsSize() / PhysicsWorld::THREADS) > 0)) {
  std::thread *workers = new std::thread[THREADS];
  auto it = grid->begin();
  //auto it_inc = [](auto it, unsigned inc) { for (unsigned i = 0; i < inc; i++) it++; return it;};
  unsigned i = 0;
  for (; i < PhysicsWorld::THREADS - 1; i++) {
    auto it2 = it + interval;
    if (worktype == WorkType::UpdateObjects) {
      workers[i] = std::thread(&PhysicsWorld::UpdateObjects, this, it, it2);
    } else {
      workers[i] = std::thread(&PhysicsWorld::CheckCollisions, this, it, it2);
    }
    it = it2;
  }

  if (worktype == WorkType::UpdateObjects) {
    workers[i] = std::thread(&PhysicsWorld::UpdateObjects, this, it, grid->cend());
    UpdateLooseObjects();
  } else {
    workers[i] = std::thread(&PhysicsWorld::CheckCollisions, this, it, grid->cend());
  }
  // collect threads
  for (unsigned j = 0; j < PhysicsWorld::THREADS; j++) {
    workers[j].join();
  }
  delete[] workers;
}
else {
  if (worktype == WorkType::UpdateObjects) {
    UpdateObjects(grid->cbegin(), grid->cend());
    UpdateLooseObjects();
  } else {
    CheckCollisions(grid->cbegin(), grid->cend());
  }
}
}

// Update PhysicsObjects in specific grid partion, private method
void PhysicsWorld::UpdateObjects(std::vector<std::vector<Cell<PhysicsObject*>*>>::const_iterator begin, std::vector<std::vector<Cell<PhysicsObject*>*>>::const_iterator end) {
for (auto it = begin; it != end; it++) {
  for (auto it2 = it->cbegin(); it2 != it->cend(); it2++) {
    std::list<PhysicsObject*>& objects = (*it2)->entities;
    for (auto& object : objects) {
      if (object->getObjectType() == ObjectType::DynamicObject) {
        object->updatePhysics(PhysicsWorld::IterarationsInterval);
        object->setMoved(true);
      }
    }
  }
}
}

// Update loose_cell objects, private method
void PhysicsWorld::UpdateLooseObjects() {
std::list<PhysicsObject*> objects = grid->getLooseCell()->entities;
for (auto& object : objects) {
  if (object->getObjectType() == ObjectType::DynamicObject) {
    object->updatePhysics(PhysicsWorld::IterarationsInterval);
    object->setMoved(true);
  }
}
}

// Check collisions and update collided, private method
void PhysicsWorld::CheckCollisions(std::vector<std::vector<Cell<PhysicsObject*>*>>::const_iterator begin, std::vector<std::vector<Cell<PhysicsObject*>*>>::const_iterator end) {
for (auto it = begin; it != end; it++) {
  for (auto it2 = it->begin(); it2 != it->end(); it2++) {
    for (auto object1 = (*it2)->entities.begin(); object1 != (*it2)->entities.end(); object1++) {
      auto object2 = object1;
      for (++object2; object2 != (*it2)->entities.end(); object2++) {
        if (CollisionDetection::calculateCollision(*object1, *object2)) {
          // objects collided, add to those to collided
          collided_mutex.lock();
          collided.push_back(Collided(*object1, *object2));
          collided_mutex.unlock();
        }
      }
    }
  }
}
}

// Check collisions for the loose objects, private method
// This is not designed to be multithreaded
void PhysicsWorld::CheckLooseCollisions() {
Cell<PhysicsObject*>* loose_cell = grid->getLooseCell();
for (auto it1 = loose_cell->entities.begin(); it1 != loose_cell->entities.end(); it1++) {
  auto it2 = it1;
  for(++it2; it2 != loose_cell->entities.end(); it2++) {
    // check collisions between other loose objects
    if (CollisionDetection::calculateCollision(*it1, *it2)) {
      collided.push_back(Collided(*it1, *it2));
    }
  }
  for (auto it = grid->cbegin(); it != grid->cend(); it++) {
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      for (auto &object : (*it2)->entities) {
        // check collisions with other PhysicsObjects
        if (CollisionDetection::calculateCollision(*it1, object)) {
          collided.push_back(Collided(*it1, object));
        }
      }
    }
  }
}
}


// Get collided PhysicsObjects as a list reference
std::list<struct Collided>& PhysicsWorld::getCollided() {
return collided;
}

