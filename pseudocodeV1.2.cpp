//部分参数
#define IDEALTIME a;
#define MAXITER b;
#define IDEALSCORE c;

int main()
{
	//数据读取与预处理
	Map map = new Map();
	map.Init();
	
	//计算每辆车的初始路径
	map.InitPath();
	
	//初步优化初始路径
	map.AmendPath();
	
	//模拟过程与记录修正
	vector<Scheme> result;
	int curtotaltime = INT_MAX;
	int iterations = 0;
	int score = 0;
	
	while(curtotaltime < a || iterations > b || score > c){
		//过程模拟
		while(map.isFinish()){
			map.Update();
		}
		
		//生成一个方案并保存
		Scheme newScheme;
		newScheme.SetScheme(map);
		
		//更新评价指标
		curtotaltime = newScheme.totalWholeTime;
		score = newScheme.GetScore();
		iterations++;
		
		//方案记录
		result.push(newScheme);		
		
		//方案修正
		map.UpdateScheme(newScheme.GetAmendCars());
		map.Reset();
	}
	
	//取最好一次结果打印
	int MinTime = INT_MAX;
	Scheme best;
	for(int i = 0; i < result.size(); i++){
		if(result[i].totalWholeTime < MinTime){
			MinTime = totalWholeTime;
			best = result[i];
		}
	}
	best.Print();
	
	return 0;
}

