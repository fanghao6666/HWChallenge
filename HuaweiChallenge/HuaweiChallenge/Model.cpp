#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>

#include "Model.h"

using namespace std;

// *********** GRAPH *************

/** \func Get id of Cross which meet the conditions
*
* @param road1,road2,road3,road4 are conditions
*        0 means an arbitrary value
*
*/
int Graph::idOfCross(int road1, int road2, int road3, int road4)
{
	for (map<int,Cross>::iterator iter = cross_map.begin();iter != cross_map.end();++iter)
	{
		if (road1 == 0 || iter->second.up_id == road1)
		{
			if (road2 == 0 || iter->second.right_id == road2)
			{
				if (road3 == 0 || iter->second.down_id == road3)
				{
					if (road4 == 0 || iter->second.left_id == road4)
					{
						return iter->first;
					}
				}
			}
		}
	}
	return -1;
}

/** \func Breadth-first Search
*
* @param start_cross_id  start cross to BFS
*
*/
void Graph::BFS(int start_cross_id)
{
	set<int> search_set;
	queue<int> search_queue;

	// push start cross
	search_set.insert(start_cross_id);
	search_queue.push(start_cross_id);

	while (search_queue.size() > 0)
	{
		// get queue front
		int front = search_queue.front();
		search_queue.pop();
		// search up
		if (cross_map[front].up_id != -1)
		{
			int up_adj_cross = idOfCross(0, 0, cross_map[front].up_id, 0);
			if (up_adj_cross != -1)
			{
				if (search_set.count(up_adj_cross) == 0)
				{
					pair<int, int> tmp_coordinate = pair<int, int>(cross_map[front].coordinate.x, cross_map[front].coordinate.y + 1);
					cross_map[up_adj_cross].coordinate = { tmp_coordinate.first,tmp_coordinate.second};
					coordinate_map.insert(pair<pair<int, int>, Cross>(tmp_coordinate, cross_map[up_adj_cross]));

					if (tmp_coordinate.first > max_x) max_x = tmp_coordinate.first;
					if (tmp_coordinate.second > max_y) max_y = tmp_coordinate.second;
					
					search_set.insert(up_adj_cross);
					search_queue.push(up_adj_cross);
				}
			}
			else
			{
				cerr << "Graph Error !" << endl;
			}
		}
		// search right
		if (cross_map[front].right_id != -1)
		{
			int right_adj_cross = idOfCross(0, 0, 0,cross_map[front].right_id);
			if (right_adj_cross != -1)
			{
				if (search_set.count(right_adj_cross) == 0)
				{
					pair<int, int> tmp_coordinate = pair<int, int>(cross_map[front].coordinate.x + 1, cross_map[front].coordinate.y);
					cross_map[right_adj_cross].coordinate = { tmp_coordinate.first,tmp_coordinate.second };
					coordinate_map.insert(pair<pair<int, int>, Cross>(tmp_coordinate, cross_map[right_adj_cross]));

					if (tmp_coordinate.first > max_x) max_x = tmp_coordinate.first;
					if (tmp_coordinate.second > max_y) max_y = tmp_coordinate.second;
					
					search_set.insert(right_adj_cross);
					search_queue.push(right_adj_cross);
				}
			}
			else
			{
				cerr << "Graph Error !" << endl;
			}
		}
		// search down
		if (cross_map[front].down_id != -1)
		{
			int down_adj_cross = idOfCross(cross_map[front].down_id, 0, 0, 0);
			if (down_adj_cross != -1)
			{
				if (search_set.count(down_adj_cross) == 0)
				{
					
					pair<int, int> tmp_coordinate = pair<int, int>(cross_map[front].coordinate.x, cross_map[front].coordinate.y - 1);
					cross_map[down_adj_cross].coordinate = { tmp_coordinate.first,tmp_coordinate.second };
					coordinate_map.insert(pair<pair<int, int>, Cross>(tmp_coordinate, cross_map[down_adj_cross]));

					if (tmp_coordinate.first > max_x) max_x = tmp_coordinate.first;
					if (tmp_coordinate.second > max_y) max_y = tmp_coordinate.second;

					search_set.insert(down_adj_cross);
					search_queue.push(down_adj_cross);
				}
			}
			else
			{
				cerr << "Graph Error !" << endl;
			}
		}
		// search left
		if (cross_map[front].left_id != -1)
		{
			int left_adj_cross = idOfCross(0, cross_map[front].left_id, 0, 0);
			if (left_adj_cross != -1)
			{
				if (search_set.count(left_adj_cross) == 0)
				{
					pair<int, int> tmp_coordinate = pair<int, int>(cross_map[front].coordinate.x, cross_map[front].coordinate.y - 1);
					cross_map[left_adj_cross].coordinate = { tmp_coordinate.first,tmp_coordinate.second };
					coordinate_map.insert(pair<pair<int, int>, Cross>(tmp_coordinate, cross_map[left_adj_cross]));

					if (tmp_coordinate.first > max_x) max_x = tmp_coordinate.first;
					if (tmp_coordinate.second > max_y) max_y = tmp_coordinate.second;

					search_set.insert(left_adj_cross);
					search_queue.push(left_adj_cross);
				}
			}
			else
			{
				cerr << "Graph Error !" << endl;
			}
		}
	}

}

/** \func Get coordinate of each cross
*
* @param
*
*/
void Graph::coordinatedCross()
{
	// initial left corner cross coordinate to (0,0)
	int left_down = idOfCross(0, 0, -1, -1);
	cross_map[left_down].coordinate = { 0,0 };
	coordinate_map.insert(pair<pair<int, int>, Cross>(pair<int, int>(cross_map[left_down].coordinate.x, cross_map[left_down].coordinate.y), cross_map[left_down]));

	// breadth seach from left_down
	BFS(left_down);

	cout << max_x << " " << max_y << endl;
}