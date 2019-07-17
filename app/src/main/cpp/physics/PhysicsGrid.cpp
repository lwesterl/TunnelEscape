/**
  *   @file PhysicsGrid.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source for class PhysicsGrid
  */


#include "PhysicsGrid.hpp"


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

// Clear whole Grid, notice this is a private method
void PhysicsGrid::Clear() {
// delete all Cells and memory allocated for them
for (auto it = cells.begin(); it != cells.end(); it++) {
  for(auto it2 = it->begin(); it2 != it->end(); it2++) {
    // delete all PhysicsObject pointers
    for (auto object = (*it2)->entities.begin(); object != (*it2)->entities.end();) {
      delete *object;
      object = (*it2)->entities.erase(object);
    }
    delete *it2; // delete Cell
  }
  it->clear();
}
cells.clear();
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
gridWidth = grid.gridWidth;
gridHeight = grid.gridHeight;
gridCellSize = grid.gridCellSize;

for (auto it = grid.cells.begin(); it != grid.cells.end(); it++) {
  cells.push_back(std::vector<Cell<PhysicsObject*>*>());
  for (auto it2 = it->begin(); it2 != it->end(); it2++) {
    Cell<PhysicsObject*>* cell = new Cell<PhysicsObject*>;
    for (auto object = (*it2)->entities.begin(); object != (*it2)->entities.end(); object++) {
      if ((*object)->getObjectType() == ObjectType::DynamicObject) {
        DynamicObject* dyn = static_cast<DynamicObject*> (*object);
        cell->entities.push_back(new DynamicObject(*dyn));
      } else {
        StaticObject* stat = static_cast<StaticObject*> (*object);
        cell->entities.push_back(new StaticObject(*stat));
      }
    }
    cells.back().push_back(cell);
  }

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
Cell<PhysicsObject*>* cell1 = GetCorrectCell(object->getMinPosition());
Cell<PhysicsObject*>* cell2 = GetCorrectCell(object->getMaxPosition());
if ((cell1 == cell2) && (cell1 != nullptr)) {
  // PhysicsObject is completely inside one Cell
  cell1->entities.push_back(object);
  object->setMoved(false);
  if (object->getObjectType() == ObjectType::DynamicObject) {
    cell1->active_cell = true;
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

// Add Cells
void PhysicsGrid::addCells(int gridWidth, int gridHeight, int gridCellSize) {
this->gridWidth = gridWidth;
this->gridHeight = gridHeight;
this->gridCellSize = gridCellSize;
for (int y = 0; y < gridHeight / gridCellSize; y++) {
  cells.push_back(std::vector<Cell<PhysicsObject*>*>());
  for (int x = 0; x < gridWidth / gridCellSize; x++) {
    cells[y].push_back(new Cell<PhysicsObject*>());
  }
}
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
Cell<PhysicsObject*>* cell = GetCorrectCell(object->getPosition());
if (cell) {
  // remove object
  for (auto item = cell->entities.begin(); item != cell->entities.end(); item++) {
    if (*item == object) {
      cell->entities.erase(item);
      delete object;
      // check if Cell still active, return value ignored (doesn't matter)
      ActivateCell(cell);
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
for (auto it = cells.begin(); it != cells.end(); it++) {
  for (auto it2 = it->begin(); it2 != it->end(); it2++) {
    std::list<PhysicsObject*>& physobjs = (*it2)->entities;
    for (std::list<PhysicsObject*>::iterator i = physobjs.begin(); i != physobjs.end();) {
      // active_cell isn't enough here because also StaticObjects could have been moved
      if ((*i)->getMoved()) {
        // check whether it needs to be moved
        Cell<PhysicsObject*>* cell1 = GetCorrectCell((*i)->getMinPosition());
        Cell<PhysicsObject*>* cell2 = GetCorrectCell((*i)->getMaxPosition());
        if ((cell1 != cell2) || (cell1 == nullptr)) {
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
}
// Handle loose_cell
moveLooseCellObjects();

}

// Get correct Cell, private method
Cell<PhysicsObject*>* PhysicsGrid::GetCorrectCell(const Vector2f pos) const {
int x = static_cast<int>(pos.getX());
int y = static_cast<int>(pos.getY());
if ((gridWidth <= 0) || (gridHeight <= 0) || (gridCellSize <= 0)) return nullptr;
int x_index = (gridWidth / 2 + x) / gridCellSize;
int y_index = (gridHeight / 2 + y) / gridCellSize;
try {
  return cells.at(y_index).at(x_index);
} catch (std::out_of_range &e) {
  return nullptr;
}
}

