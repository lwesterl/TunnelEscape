/**
  *   @file PhysicsGrid.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source for class PhysicsGrid
  */


#include "../include/PhysicsGrid.hpp"

namespace pe {

  // Empty constructor
  PhysicsGrid::PhysicsGrid(): loose_cell(new Cell<PhysicsObject*>()) {}

  // Deconstructor
  PhysicsGrid::~PhysicsGrid() {
    Clear();
  }

  // Copy constructor
  PhysicsGrid::PhysicsGrid(const PhysicsGrid& grid) {
    Copy(grid);
  }

  // Assignment operator
  PhysicsGrid& PhysicsGrid::operator=(const PhysicsGrid& grid) {
    // delete old objects
    Clear();
    Copy(grid);
    return *this;
  }

  // Clear whole Grid, notice this is private method
  void PhysicsGrid::Clear() {
    // delete all Cells and memory allocated for them
    for (auto it = cells.begin(); it != cells.end();) {
      // delete all PhysicsObject pointers
      for (auto object = it->second->entities.begin(); object != it->second->entities.end();) {
        delete *object;
        object = it->second->entities.erase(object);
      }
      delete it->second;
      it = cells.erase(it);
    }
    // delete also PhysicsObjects from loose_cell
    if (loose_cell != nullptr) {
      for (auto it = loose_cell->entities.begin(); it != loose_cell->entities.end();) {
        delete *it;
        it = loose_cell->entities.erase(it);
      }
      delete loose_cell;
    }
  }

  // Copy whole Grid, hard copy, private method
  void PhysicsGrid::Copy(const PhysicsGrid& grid) {
    for (auto it = grid.cells.begin(); it != grid.cells.end(); it++) {
      Cell<PhysicsObject*>* cell = new Cell<PhysicsObject*>;
      for (auto object = it->second->entities.begin(); object != it->second->entities.end(); object++) {
        if ((*object)->getObjectType() == ObjectType::DynamicObject) {
          DynamicObject* dyn = static_cast<DynamicObject*> (*object);
          cell->entities.push_back(new DynamicObject(*dyn));
        } else {
          StaticObject* stat = static_cast<StaticObject*> (*object);
          cell->entities.push_back(new StaticObject(*stat));
        }
      }
      cells.emplace(it->first, cell);
    }
    // copy also loose_cell content
    if (grid.loose_cell != nullptr) {
      loose_cell = new Cell<PhysicsObject*>();
      for (auto& entity : grid.loose_cell->entities) {
        if (entity->getObjectType() == ObjectType::DynamicObject) {
          DynamicObject* dyn = static_cast<DynamicObject*> (entity);
          loose_cell->entities.push_back(new DynamicObject(*dyn));
        } else {
          StaticObject* stat = static_cast<StaticObject*> (entity);
          loose_cell->entities.push_back(new StaticObject(*stat));
        }
      }
    }
  }

  // Activate / deactivate Cell, private method
  bool PhysicsGrid::ActivateCell(Cell<PhysicsObject*>* cell) {
    for (auto &it : cell->entities) {
      if (it->getObjectType() == ObjectType::DynamicObject) {
        cell->active_cell = true;
        return true;
      }
    }
    cell->active_cell = false;
    return false;
  }

  // Try to insert object to cell, private method
  bool PhysicsGrid::insertObject(PhysicsObject* object) {
    auto it = cells.find((Vector2i) object->getMinPosition());
    auto it2 = cells.find((Vector2i) object->getMaxPosition());
    if ((it != cells.end()) && (it == it2)) {
      // PhysicsObject is completely inside one Cell
      it->second->entities.push_back(object);
      object->setMoved(false);
      if (object->getObjectType() == ObjectType::DynamicObject) {
        it->second->active_cell = true;
      }
      return true;
    }
    return false;
  }

  // Move loose_cell PhysicsObjects, private method
  void PhysicsGrid::moveLooseCellObjects() {
    for (auto it = loose_cell->entities.begin(); it != loose_cell->entities.end();) {
      if ((*it)->getMoved()) {
        if (insertObject(*it)) {
          // object added to cell
          it = loose_cell->entities.erase(it);
        } else {
          (*it)->setMoved(false);
          it++;
        }
      }
      else it++;
    }
  }

  // Add Cell
  bool PhysicsGrid::addCell(Recti position) {
    auto it = cells.find(position);
    if (it == cells.end()) {
      // add new Cell
      cells.emplace(position, new Cell<PhysicsObject*>);
      return true;
    }
    return false;
  }

  // Add object to Cell in PhysicsGrid
  bool PhysicsGrid::addObject(PhysicsObject* object) {
    if (! insertObject(object)) {
      // PhysicsObject inside multiple Cells, add it to loose_cell
      loose_cell->entities.push_back(object);
      loose_cell->active_cell = true;
      object->setMoved(false);
    }
    return true;
  }

  // Remove object from PhysicsGrid Cell
  bool PhysicsGrid::removeObject(PhysicsObject* object) {
    auto it = cells.find((Vector2i) object->getPosition());
    if (it != cells.end()) {
      // remove object
      for (auto item = it->second->entities.begin(); item != it->second->entities.end(); item++) {
        if (*item == object) {
          it->second->entities.erase(item);
          delete object;
          // check if Cell still active, return value ignored (doesn't matter)
          ActivateCell(it->second);
          return true;
        }
      }
    }
    // Check also loose_cell
    for (auto it = loose_cell->entities.begin(); it != loose_cell->entities.end(); it++) {
      if (*it == object) {
        loose_cell->entities.erase(it);
        delete object;
        if (loose_cell->entities.size() == 0) {
          loose_cell->active_cell = false;
        }
        return true;
      }
    }
    return false;
  }

  // Move PhysicsObjects to correct grid cells
  void PhysicsGrid::moveObjects() {
    for (std::map<Recti, Cell<PhysicsObject*>*>::iterator it = cells.begin(); it != cells.end(); it++) {
      std::list<PhysicsObject*>& physobjs = it->second->entities;
      for (std::list<PhysicsObject*>::iterator i = physobjs.begin(); i != physobjs.end();) {
        // active_cell isn't enough here because also StaticObjects could have been moved
        if ((*i)->getMoved()) {
          // check whether it needs to be moved
          if ((!it->first.contains((*i)->getMinPosition())) || (!it->first.contains((*i)->getMaxPosition()))) {
            // remove object from the current Cell
            addObject(*i);
            i = physobjs.erase(i);
          } else {
            (*i)->setMoved(false);
            i++;
          }
        } else i++;
      }
    }
    // Handle loose_cell
    moveLooseCellObjects();
  }

} // end of namespace pe
