#include "Agent.h"
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "World.h"

using namespace std;

std::vector<Point2D> Agent::generatePath(CatWorld* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = {INT32_MAX, INT32_MAX};  // sentinel: no border found yet

  while (!frontier.empty()) {
    // get the current from frontier
    Point2D current = frontier.front();
    // remove the current from frontierset
    frontier.pop();
    // mark current as visited
    visited[current] = true;
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> neighbors = getVisitableNeighbors(w, &current);
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

std ::vector<Point2D> Agent::getVisitableNeighbors(CatWorld* w, Point2D* p) 
{ 
    vector<Point2D> neighbors;
  if (isVisitable(w, w->W(*p))) 
  {
      neighbors.push_back(w->W(*p));
  }
  if (isVisitable(w, w->E(*p))) {
    neighbors.push_back(w->E(*p));
  }
  if (isVisitable(w, w->NW(*p))) {
    neighbors.push_back(w->NW(*p));
  }
  if (isVisitable(w, w->NE(*p))) {
    neighbors.push_back(w->NE(*p));
  }
  if (isVisitable(w, w->SW(*p))) {
    neighbors.push_back(w->SW(*p));
  }
  if (isVisitable(w, w->SE(*p))) {
    neighbors.push_back(w->SE(*p));
  }
  return neighbors;
}

bool Agent::isVisitable(CatWorld* w, Point2D p) 
{ 
  bool visitable = true;
  if (!w->isValidPosition(p)) 
  {
      return false;
  }
  if (w->getContent(p)) 
  {
      return false;
  }
  if (w->getCat() == p) 
  {
    return false;
  }

  return true;

}

bool Agent::isBorder(CatWorld* w, Point2D p) 
{ 
    if (!w->isValidPosition(w->W(p))) {
    return true;
  }
    if (!w->isValidPosition(w->E(p))) {
      return true;
    }
    if (!w->isValidPosition(w->SW(p))) {
      return true;
    }
    if (!w->isValidPosition(w->NW(p))) {
      return true;
    }
    if (!w->isValidPosition(w->SE(p))) {
      return true;
    }
    if (!w->isValidPosition(w->NE(p))) {
      return true;
    }
    return false; 
}
