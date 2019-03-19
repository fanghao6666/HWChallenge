//路径修正：返回一条可行路径
void Graph::modifyPath(int modinum){
	
	//根据模拟结果返回修正指标：某些车不能走某些路，每次优先修正的车辆数目为modinum
	//每一位放汽车ID，其余位放该车不能经过的道路
	vector<vector<int>> midicars = getModiCars(modinum);
	
	//依次修正每一辆车的路线，若不存在该路线这放弃修正
	for(int i = 0; i < midicars.size(); i++){
		/*
		Car& car = midicars[i][0];
		setNewPathWithoutRoads(car, midicars[i]);
		*/
		setNewPathWithoutRoads(midicars[i]);
	}
}

//过程模拟
int Graph::Simulation(){
	int totaltime = 0;
	
	//isFinish()判定条件：所有车到达终点，2.出现堵车
	while(graph.isFinish()){
		totaltime++;
		
		//在所有车辆均被标记前：
		//1.按道路id增序与规则更新所有能动且不出路口的车辆的位置，更新结束后标记其为终止状态
		//2.标记所有等待的车辆：要出路口的车辆、有车辆阻挡其到达最终位置的车辆
		while(isEveryCarsMarked()){
			for(int i = 0; i < road_list.size(); i++){
				Road& road = road_map[road_list[i]];
				road.updateStepOne();					//见计划书第9节
			}
		}
		
		//在所有车辆均移动前：
		while(isEveryCarsRuns()){
			
			for(int i = 0; i < cross_list.size(); i++){
				Cross& cross = cross_map[cross_list[i]];
				for(int j = 0; j < 4; j++){
					//调整出路口方向的路,将所有能出路口的车调整出路口
					if(cross.nextroad != -1 && road_direction.count(pair<int, int>(cross.nextcross[j], cross.id))){
						Road& road = road_map[cross.nextroad];
						road.updateStepTwo();					//见计划书第9节
					}
				}
			}
			
			//移动其他标记等待的车辆，并标记其终止
			driveAllCarLeft();
			
			//isTaffic()判定条件：若出现一辆车的堵车计数器taffcount>5
			//若某车前后两个时间片的所在位置数据相同，taffcount++
			if(graph.isTaffic()){
				totaltime = INT_MAX;
				break;
			}			
			
		}
		
		if(totaltime == INT_MAX)
			break;
	}
	
	//如果出现堵车，返回最大时间
	return totaltime;
}