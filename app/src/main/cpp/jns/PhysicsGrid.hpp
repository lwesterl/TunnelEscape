/**
  *   @file PhysicsGrid.hpp
  *   @author Lauri Westerholm
  *   @brief Header for class PhysicsGrid
  */

#pragma once

#include "../utils/Rect.hpp"
#include "../utils/Vector2.hpp"
#include "PhysicsObject.hpp"
#include "DynamicObject.hpp"
#include "StaticObject.hpp"
#include <list>
#include <map>


/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {


  /**
    *   @struct Cell
    *   @brief struct representing one cell in Grid
    */
  template<class T>
  struct Cell {
    std::list<T> entities; /**< list of entities Cell contains */
    bool active_cell; /**< Whether Cell is active or not */
  };

  /**
    *   @struct CompareRectMap
    *   @brief Used to hold comparison functions for std::map find
    */
  template<typename T>
  struct CompareRectMap {
    using is_transparent = void; /**< make template comparison overloads possible */

    /**
      *   @brief Standard comparison between Rects
      *   @param rect1 1st Rect to be compared
      *   @param rect2 2nd Rect to be compared
      *   @return rect1 < rect2
      */
    bool operator() (const Rect<T>& rect1, const Rect<T>& rect2) const {
      return rect1 < rect2;
    }

    /**
      *   @brief Position based comparison between Rect and Vector2
      *   @param pos Vector2 position
      *   @param rect Rect to be compared
      *   @return true if pos is smaller than rect left upper corner (min point)
      */
    bool operator() (const Vector2<T>& pos, const Rect<T>& rect) const {
      return (pos.getX() < rect.getPosition().getX()) || (pos.getY() < rect.getPosition().getY());
    }

    /**
      *   @brief Position based comparison between Rect and Vector2
      *   @param pos Vector2 position
      *   @param rect Rect to be compared
      *   @return true if pos is greater than rect right lower corner (max point)
      */
    bool operator() (const Rect<T>& rect, const Vector2<T>& pos) const {
      return (rect.getPosition().getX() + rect.getWidth() < pos.getX()) || (rect.getPosition().getY() + rect.getHeight() < pos.getY());
    }
  };

  /**
    *   @class PhysicsGrid
    *   @brief Container for PhysicsObject of PhysicsWorld
    *   @details Consists of Cell structs. PhysicsGrid and it's Cells take
    *   ownership of PhysicsObjects so their memory deletion is handled by Grid.
    *   Do NOT delete objects memory elsewhere
    */
    class PhysicsGrid
    {
      public:
        /**
          *   @brief Standard empty constructor
          */
        PhysicsGrid();

        /**
          *   @brief Deconstructor
          *   @details Frees all memory allocated by the Grid
          */
        virtual ~PhysicsGrid();

        /**
          *   @brief Copy constructor
          *   @param grid Grid which is copied
          */
        PhysicsGrid(const PhysicsGrid& grid);

        /**
          *   @brief Assignment operator overload
          *   @param grid Grid which is copied
          */
        PhysicsGrid& operator=(const PhysicsGrid& grid);

        /**
          *   @brief Add cell to Grid
          *   @details After Cell is added, Grid maintains removal of the entities
          *   and frees memory allocated for them
          *   @param position where cell is added on 2D plane
          *   @remark if Cell already exists at given position,
          *   does nothing and returns false
          */
        bool addCell(Recti position);

        /**
          *   @brief Add PhysicsObject to Cell in the Grid
          *   @param object to be added
          *   @return true if object was added, otherwise false
          *   @details object cannot be added if there is no Cell matching to
          *   the position of object
          *   @remark This is not very trustworthy, only the center of object
          *   is checked whether it's inside Cell or not
          */
        bool addObject(PhysicsObject* object);

        /**
          *   @brief Remove PhysicsObject from PhysicsGrid
          *   @param object to be removed
          *   @return true if object successfully removes, otherwise false
          */
        bool removeObject(PhysicsObject* object);

        /**
          *   @brief Move all objects to correct grid cells
          *   @details PhysicsObject checked for move its moved bool is true.
          *   After possibly moving sets the moved to false. DynamicObject
          *   needs to be moved if its position isn't inside the grid cell
          *   @remark This is necessarily quite heavy method and it should be
          *   called only from PhysicsWorld update
          */
        void moveObjects();

        /**
          *   @brief Get const iterator to the beginning of cell
          *   @return cells.cbegin()
          */
        inline std::map<Recti, Cell<PhysicsObject*>*>::const_iterator cbegin() {
          return cells.cbegin();
        }

        /**
          *   @brief Get const iterator to the end of cell
          *   @return cells.cend()
          */
        inline std::map<Recti, Cell<PhysicsObject*>*>::const_iterator cend() {
          return cells.cend();
        }
        /**
          *   @brief Get iterator to the beginning of cell
          *   @return cells.begin()
          */
        inline std::map<Recti, Cell<PhysicsObject*>*>::iterator begin() {
          return cells.begin();
        }

        /**
          *   @brief Get iterator to the end of cell
          *   @return cell.cend()
          */
        inline std::map<Recti, Cell<PhysicsObject*>*>::iterator end() {
          return cells.end();
        }

        /**
          *   @brief Get loose_cell
          *   @return pointer to loose_cell
          */
        inline Cell<PhysicsObject*>* getLooseCell() {
          return loose_cell;
        }

        /**
          *   @brief Get cells size
          *   @return cells.size
          */
        inline unsigned getCellsSize() {
          return cells.size();
        }

      private:
        /**
          *   @brief Clear Grid
          *   @details Removes all cells and their objects. Deletes also memory used for
          *   those
          */
        void Clear();

        /**
          *   @brief Copy Grid
          *   @details Makes hard copy of the Grid, i.e. allocates new pointers for
          *   objects
          *   @param grid Grid to be copied
          */
        void Copy(const PhysicsGrid& grid);

        /**
          *   @brief Activate / deactivate Cell
          *   @details Cell is active if it contains at least one DynamicObject
          *   @param cell Cell to be checked
          *   @return true if cell active, otherwise false
          */
        bool ActivateCell(Cell<PhysicsObject*>* cell);

        /**
          *   @brief Try to insert object to cell
          *   @param object PhysicsObject to be inserted
          *   @return true if successful, otherwise false -> object should be
          *   inserted to loose_cell
          */
        bool insertObject(PhysicsObject* object);

        /**
          *   @brief Move loose_cell PhysicsObjects
          *   @remark This should be called only from moveObjects
          */
        void moveLooseCellObjects();


        std::map<Recti, Cell<PhysicsObject*>*, CompareRectMap<int>> cells;
        Cell<PhysicsObject*>* loose_cell = nullptr; /**< Cell for all PhysicsObjects which are not in a single Cell, cells */
    };




} // end of namespace pe
