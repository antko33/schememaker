#include "stdafx.h"

#include "ScadAPIX.hxx"

void APITestNewProject( )
{
	ScadAPI	handle(NULL);
	UINT n, i, j, Node[4], Elem[4];
	double Size[6];
	const static UnitsAPI Un[3] = { { "m", 1 },  { "cm", 100 }, { "T", 1 } };

	if ( ApiCreate(&handle) != APICode_OK ) ApiMsg("Error");  //  создание объекта API и контроль
	if ( ApiClear(handle) != APICode_OK ) ApiMsg("Error");    //  после открытия можно не делать
	if ( ApiSetLanguage (handle,1) != APICode_OK ) ApiMsg("Error");               
	ApiSetName(handle,"TestNewProject");
	ApiSetUnits(handle,Un);               
	if ( ApiSetTypeSchema(handle,5) != APICode_OK ) ApiMsg("Error");  

	// узлы
	ApiNodeAddSize(handle,16);
	for ( i=0,n=0; i<4; i++ ) {
		for ( j=0; j<4; j++ ) {
			ApiNodeUpdate(handle,++n,i*6,0,j*3);
			}
		}
 	ApiNodeSetName(handle,16,"Node 16");

	// Элементы
    ApiElemAdd(handle,21);
	for ( i=0; i<4; i++ ) {
		n = i * 6 + 1;
		for ( j=0; j<3; j++ ) {
			Node[0] = 4*i+j+1;   Node[1] = Node[0] + 1;
			ApiElemUpdate(handle,n++,5,2,Node);
			Node[0] = Node[1];   Node[1] = Node[0] + 4;
			if ( i < 3 ) ApiElemUpdate(handle,n++,5,2,Node);
		}	}

	Node[0] = 2;   Node[1] = 6; 	Node[2] = 3;   Node[3] = 7;   
	n = ApiElemAddData(handle,41,4,Node);
	Node[0] = 10;   Node[1] = 14; 	Node[2] = 11;   Node[3] = 15; 
	n = ApiElemAddData(handle,41,4,Node);
	ApiElemSetName(handle,n,"Plate");

	// жесткости
	// пользовательское сечение
	n = ApiSetRigid(handle,"S0 3.52e+006 20 25 NU 0.2 RO 2.5 TMP 1e-005 Shift 493.004 61488.2 61548.5");
	for ( i=1; i<=21; i++ ) ApiSetRigidElem(handle,n,1,&i);
	// металлопрокат
	n = ApiSetRigid(handle,"STZ RUSSIAN p_wide_h 18 TMP 1.2e-005");
	Elem[0] = 6;   Elem[1] = 18;
	ApiSetRigidElem(handle,n,2,Elem);
	// жесткости пластин
	n = ApiSetRigid(handle,"GE 2.1e+007 0.3 0.1 RO 7.85 TMP 1.2e-005 1.2e-005");
	ApiSetRigidName(handle,2,"Plate");
	Elem[0] = 22;   Elem[1] = 23;
	ApiSetRigidElem(handle,n,2,Elem);

	// связи	
	Node[0] = 1;   Node[1] = 5;  Node[2] = 9;    Node[3] = 13;  
	ApiSetBound(handle,SgDirectX | SgDirectZ | SgDirectUY,4,Node,TRUE);

	// объединения связей
    Node[0] = 4;   Node[1] = 16; 
    n = ApiSetBoundUnite(handle,SgDirectX | SgDirectZ,2,Node);
	ApiSetBoundUniteName(handle,n,"Union 1");
	
	// шарниры
	ApiSetJoint(handle,SgDirectUX | SgDirectUY,4,2,0);
	ApiSetJoint(handle,SgDirectUX | SgDirectUY,16,1,0);

	// жесткие вставки
	Elem[0] = 6; Elem[1] = 18; 
	Size[0] = 1;	Size[1] = 0;	Size[2] = 1;	Size[3] = -1;	Size[4] = 0;	Size[5] = 1;
	ApiSetInsert(handle,1,3,6,Size,2,Elem);

	//  коэффициенты постели
	Size[0] = 0.1;	Size[1] = 1000;	Size[2] = 500;
	Size[3] = 0.2;	Size[4] = 1500;	Size[5] = 700;
	Elem[0] = 1;   Elem[1] = 7;  Elem[2] = 13;    Elem[3] = 19;  
	ApiSetBed(handle,ApiGroupRod,0,6,Size,4,Elem);

	// Группы элементов
	Elem[0] = 22;   Elem[1] = 23;  
	ApiSetGroupElem(handle,"Plate",2,2,Elem);
	Elem[0] = 1;   Elem[1] = 7;  Elem[2] = 13;   Elem[3] = 19;  
	ApiSetGroupElem(handle,"Rod",2,4,Elem);
	Size[0] = 1200;	Size[1] = 300;
	Elem[0] = 23;
	ApiSetBed(handle,ApiGroupPlate,'I',6,Size,1,Elem);

	// Группы узлов	
	Node[0] = 1;   Node[1] = 5;  Node[2] = 9;    Node[3] = 13;  
	ApiSetGroupNode(handle,"Bound",4,Node);

	// системы координат элементов
    Size[0] = 45;
	Elem[0] = 7;   Elem[1] = 13;
	ApiSetSystemCoordElem(handle,ApiGroupRod,ApiRodCornerInDegrees,1,Size,2,Elem);
	Size[0] = 1;	Size[1] = 0;	Size[2] = 1;
	Elem[0] = 22;   Elem[1] = 23;
	ApiSetSystemCoordEffors(handle,ApiGroupPlate,ApiPlateAxecX,2,Size,2,Elem);

	// 4-е загружения
	ApiSetLoadDescription(handle,1,"Type=0  Mode=1  LongTime=1  ReliabilityFactor=1.05");
	ApiSetLoadName(handle,1,"Узловые нагрузки");
	ApiSetLoadDescription(handle,2,"Type=0  Mode=1  LongTime=1  ReliabilityFactor=1.05");
	ApiSetLoadName(handle,2,"Распределенные нагрузки");
	ApiSetLoadDescription(handle,3,"Type=0  Mode=1  LongTime=1  ReliabilityFactor=1.05");
	ApiSetLoadName(handle,3,"Собственный вес");
	ApiSetLoadDescription(handle,4,"Type=2  ReliabilityFactor=1.1  21 5 1  1 3 0 0 0 5 18 1 0 0.3 1");
	ApiSetLoadName(handle,4,"Ветер");
	//  преобразование статических загружений в массы
	ZeroMemory(Size,sizeof(Size));
	Size[3] = 1;
	ApiSetLoadMass(handle,4,4,Size);
	
	// нагрузки
	Size[0] = 1.2;
	Node[0] = 8;   Node[1] = 12;
	ApiAppendForce(handle,1,ApiFоrceNode,SgForceZ,1,Size,2,Node);
	Size[0] = -0.5;
	Node[0] = 2;   Node[1] = 3;  Node[2] = 4;
	ApiAppendForce(handle,1,ApiFоrceNode,SgForceX,1,Size,3,Node);

	Size[0] = 2.1;
	Node[0] = 6;   Node[1] = 12;  Node[1] = 18;
	ApiAppendForce(handle,2,ApiForceEvenlyGlobal,SgForceZ,1,Size,3,Node);

	Size[0] = 2.1;
	Node[0] = 6;   Node[1] = 12;  Node[1] = 18;
	ApiAppendForce(handle,2,ApiForceEvenlyGlobal,SgForceZ,1,Size,3,Node);
	for ( i=1; i<=23; i++ ) ApiSetWeight(handle,3,1,&i,1.1,TRUE,FALSE);

	APICode Code;
	Code = ApiWriteProject(handle,"TestNewProject.spr");
	if ( Code != APICode_OK ) {  APIPhrase(handle,Code); }  
	ApiRelease(&handle);

}

