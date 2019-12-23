(in linux)
command:
1. g++ -std=c++11 project1.cpp -o project1
2. ./project1 // 執行

執行結果：(example1)
=================================================================
	input entry size
	8

	entry: 2        beq R1,R2,End
	(00, SN, SN, SN, SN) N N                misprediction: 0

	entry: 4        beq R0,R0,Loop
	(00, SN, SN, SN, SN) N T                misprediction: 1

	entry: 2        beq R1,R2,End
	(00, SN, SN, SN, SN) N N                misprediction: 0

	entry: 4        beq R0,R0,Loop
	(01, WN, SN, SN, SN) N T                misprediction: 2

	entry: 2        beq R1,R2,End
	(00, SN, SN, SN, SN) N N                misprediction: 0

	entry: 4        beq R0,R0,Loop
	(11, WN, WN, SN, SN) N T                misprediction: 3

	entry: 2        beq R1,R2,End
	(00, SN, SN, SN, SN) N N                misprediction: 0

	entry: 4        beq R0,R0,Loop
	(11, WN, WN, SN, WN) N T                misprediction: 4

	entry: 2        beq R1,R2,End
	(00, SN, SN, SN, SN) N T                misprediction: 1

example1:
=================================================================
		li R1,0
		li R2,4
	Loop:
		beq R1,R2,End
		subi R2,R2,1
		beq R0,R0,Loop
	End:

系統流程：
=================================================================
	1.讀擋
	2.讀擋完成後將資料存成以下結構
	vector<string> loadInstName; // 紀錄每個register的名字
	vector<int> loadInstNumber; // 紀錄每個register的值

	// 將instruction分別記錄以下結構 ex: add R1,R2,R3
	// instFirst會記錄R1
	// instSecond會記錄R2
	// instThird會記錄R3
	// instName會記錄add
	vector<string> instFirst;
	vector<string> instSecond;
	vector<string> instThird;
	vector<string> loopName;
	vector<string> instName;
	vector<int> instLocation;
	vector<int> loopLocation;
	string first, second, third;
	
	struct Entry { // prediction資料儲存結構
		vector<int> outcome;
		vector<int> state; // 0:00, 1:01, 2:10, 3:11
		vector<int> st; // 0:SN, 1:WN, 2:WT, 3:ST
		int count = 0;
	};

	3.資料儲存好以後，開始模擬組合語言執行流程，對branch去做預測
	4.輸出結果

Function：
=================================================================

do2BitHistroy() // 做branch prediction
returnLoadValue() // 回傳register的值
returnLoop() // 回傳loop的位置，以便branch到那個位置
isExist() // 判斷register是否存在

=================================================================
