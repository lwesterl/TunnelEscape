/**
  *   @file PhysicsWorld.cpp
  *   @author Lauri Westerholm
  *   @brief Contains class PhysicsWorld
  */

#include "PhysicsWorld.hpp"



/* Class PhysicsWorld */

// Init class variables
const int PhysicsWorld::GridCellSize = 5000;
int PhysicsWorld::WorldWidth = 100000;
int PhysicsWorld::WorldHeight = PhysicsWorld::WorldWidth;
float PhysicsWorld::IterationsInterval = 1.f / 60.f;


// Set how many iterations / s
void PhysicsWorld::setIterationAmount(float iterations) {
  PhysicsWorld::IterationsInterval = 1.f / iterations;
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
  grid(new PhysicsGrid(*world.grid)), collided(world.collided) {
    threads = world.threads;
}

// Assignment operator
PhysicsWorld& PhysicsWorld::operator=(const PhysicsWorld& world) {
    threads = world.threads;
    collided.clear();
    *grid = *world.grid;
    collided = world.collided;
    return *this;
}

// Set amount of threads
void PhysicsWorld::setThreads(unsigned amount) {
  if (amount <= std::thread::hardware_concurrency()) {
    // this should also handle the possible overwarping issues
    threads = amount;
  }
  else threads = 0; // no worker threads created
  // remove possible old workers and create new ones
}

// Add PhysicsObject to PhysicsWorld, wrapper call for PhysicsGrid addObject
bool PhysicsWorld::addObject(PhysicsObject* object) {
  return grid->addObject(object);
}

// Remove PhysicsObject from PhysicsWorld, wrapper call for PhysicsGrid removeObject
bool PhysicsWorld::removeObject(PhysicsObject* object) {
  return grid->removeObject(object);
}

// Create worker threads
void PhysicsWorld::CreateWorkers() {
  unsigned interval;
  if ((threads > 0) && ((interval = grid->getCellsSize() / threads) > 0)) {
    workers = new std::thread[threads];
    workerStatus = new std::atomic_ushort[threads];
    unsigned interval = grid->getCellsSize() / threads;
    auto it = grid->begin();
    unsigned i;
    for (i = 0; i < threads -1; i++) {
      workerStatus[i] = WorkStatus_WAIT;
      auto it2 = it + interval;
      workers[i] = std::thread(&PhysicsWorld::DoWork, this, it, it2, i);
      it = it2;
    }
    workerStatus[i] = WorkStatus_WAIT;
    workers[i] = std::thread(&PhysicsWorld::DoWork, this, it, grid->cend(), i);
  }
}

// Remove worker threads
void PhysicsWorld::RemoveWorkers() {
  // check if there was some workers created
  if (workerStatus && (threads > 0) && (grid->getCellsSize() / threads > 0)) {
    for (unsigned i = 0; i < threads; i++) {
      workerStatus[i] = WorkStatus_EXIT;
    }
    for (unsigned i = 0; i < threads; i++) {
      workers[i].join();
    }
    delete [] workers;
    delete [] workerStatus;
  }
}

// Update PhysicsWorld PhysicsObject positions and calculate collision
void PhysicsWorld::update() {
    CreateWorkers();

/*
  STEPS
  0. init collided
*/
  collided.clear();

/*
  1. Update object physics if DynamicObject (call updatePhysics with elapsed
   time, IterationsInterval, as argument). This could be done in multiple
   threads at the same time, threads operate one grid cell. Activate object
   moved bool.
*/

  if (threads == 0) {
  // Work only in the main thread
      WorkMainThread(WorkType::UpdateObjects);
  }
  else {
  // Use worker threads to do the work
  for (unsigned i = 0; i < threads; i++) {
      workerStatus[i] = WorkStatus_WORK;
  }
  UpdateLooseObjects();

  unsigned i = 0;
  while(i < threads) {
      std::this_thread::yield();
      if (workerStatus[i] == WorkStatus_WAIT) i++;
    }
  }

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
  if (threads == 0) {
    WorkMainThread(WorkType::CheckCollisions);
  }
  else {
    for (unsigned i = 0; i < threads; i++) {
      workerStatus[i] = WorkStatus_WORK;
    }
  unsigned i = 0;
  while(i < threads) {
    std::this_thread::yield();
    if (workerStatus[i] == WorkStatus_WAIT) i++;
  }
}

  // check also if objects in loose cell collided with each other or with any other
  // PhysicsObjects
  CheckLooseCollisions();
  RemoveWorkers();
}

// Do the work in the main thread, private method
void PhysicsWorld::WorkMainThread(enum WorkType::WorkType worktype) {
  if (worktype == WorkType::UpdateObjects) {
    UpdateObjects(grid->cbegin(), grid->cend());
    UpdateLooseObjects();
  } else {
    CheckCollisions(grid->cbegin(), grid->cend());
  }
}

//
void PhysicsWorld::DoWork(std::vector<std::vector<Cell<PhysicsObject*>*>>::const_iterator begin,
      std::vector<std::vector<Cell<PhysicsObject*>*>>::const_iterator end,
      unsigned threadID)
{
  while(true) {
    if (ThreadExecute(begin, end, threadID, WorkType::UpdateObjects) < 0) return;
    if (ThreadExecute(begin, end, threadID, WorkType::CheckCollisions) < 0) return;
  }
}

int PhysicsWorld::ThreadExecute(std::vector<std::vector<Cell<PhysicsObject*>*>>::const_iterator begin,
  std::vector<std::vector<Cell<PhysicsObject*>*>>::const_iterator end,
  unsigned threadID,
  enum WorkType::WorkType workType)
{
  // wait for turn
  while(!workerStatus[threadID]) { std::this_thread::yield(); }
  if (workerStatus[threadID] == WorkStatus_EXIT) return -1;
  if (workType == WorkType::UpdateObjects) UpdateObjects(begin, end);
  else CheckCollisions(begin, end);
  workerStatus[threadID] = WorkStatus_WAIT;
  return 0;
}

// Update PhysicsObjects in specific grid partion, private method
void PhysicsWorld::UpdateObjects(std::vector<std::vector<Cell<PhysicsObject*>*>>::const_iterator begin, std::vector<std::vector<Cell<PhysicsObject*>*>>::const_iterator end) {
  for (auto it = begin; it != end; it++) {
    for (auto it2 = it->cbegin(); it2 != it->cend(); it2++) {
      std::list<PhysicsObject*>& objects = (*it2)->entities;
      for (auto& object : objects) {
        if (object->getObjectType() == ObjectType::DynamicObject) {
          object->updatePhysics(PhysicsWorld::IterationsInterval);
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
      object->updatePhysics(PhysicsWorld::IterationsInterval);
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

