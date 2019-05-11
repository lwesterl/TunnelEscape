/**
  *   @file RectMap.cpp
  *   @author Lauri Westerholm
  *   @brief Source for RectMap
  */

#include "../include/RectMap.hpp"


// Constructor
RectMap::RectMap() {
  cells = new int*[SCREEN_HEIGHT];
  for (int j = 0; j < SCREEN_HEIGHT; j++) {
    cells[j] = new int[SCREEN_WIDTH];
    for (int i = 0; i < SCREEN_WIDTH; i++) {
      cells[j][i] = false;
    }
  }
}

// Deconstructor
RectMap::~RectMap() {
  for (int j = 0; j < SCREEN_HEIGHT; j++) {
    delete[] cells[j];
  }
  delete[] cells;
}

// Populate cells
void RectMap::populateCells(const std::pair<int, int> &start, const std::pair<int, int> &end) {
  if (CheckPosValid(start.first, start.second) && CheckPosValid(end.first, end.second)) {
    for (int j = start.second; j <= end.second; j++) {
      for (int i = start.first; i <= end.first; i++) {
        cells[j][i] += 1;
      }
    }
  }
}

// Depopulate cells
void RectMap::depopulateCells(const std::pair<int, int> &start, const std::pair<int, int> &end) {
  if (CheckPosValid(start.first, start.second) && CheckPosValid(end.first, end.second)) {
    for (int j = start.second; j <= end.second; j++) {
      for (int i = start.first; i <= end.first; i++) {
        if (cells[j][i] > 0) cells[j][i] -= 1;
      }
    }
  }
}

// Check cell status
bool RectMap::isPopulated(const int x, const int y) const {
  if (CheckPosValid(x, y)) {
    return cells[y][x] > 0;
  }
  return false;
}

// Get the closest cell index in x dimension
int RectMap::getClosestFreeX(const int x, const int y) const {
  if (CheckPosValid(x, y)) {
    int i1, i2;
    int distance1 = 0;
    int distance2 = 0;
    for (i1 = x; i1 > 0; i1--) {
      if (cells[y][i1] == 0) break;
      distance1 ++;
    }
    for (i2 = x; i2 < SCREEN_WIDTH; i2++) {
      if (cells[y][i2] == 0) break;
      distance2 ++;
    }
    return distance1 < distance2 ? i1+=2 : i2-=2; // adjust so that object is connected to previous
  }
  return -1;
}

// Get the closest cell index in y dimension
int RectMap::getClosestFreeY(const int x, const int y) const {
  if (CheckPosValid(x, y)) {
    int i1, i2;
    int distance1 = 0;
    int distance2 = 0;
    for (i1 = y; i1 > 0; i1--) {
      if (cells[i1][x] == 0) break;
      distance1 ++;
    }
    for (i2 = y; i2 < SCREEN_HEIGHT; i2++) {
      if (cells[i2][x] == 0) break;
      distance2 ++;
    }
    return distance1 < distance2 ? i1+=2 : i2-=2; // adjust so that object is connected to previous
  }
  return -1;
}

// Clear cells
void RectMap::clear() {
  for (int j = 0; j < SCREEN_HEIGHT; j++) {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
      cells[j][i] = 0;
    }
  }
}
