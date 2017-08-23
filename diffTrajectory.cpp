#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
vector<float> refX,refY,x,y,refDistance,distanceTest,difference; 

vector<float>  distanceArray(vector<float> positionX,vector<float> positionY)
{
	vector<float> distances;
	float curDistance;
	for(int i=0;i<positionX.size();i++){
		if(i-1<0){
			curDistance=0;
		}else{
		curDistance+=sqrt(pow(positionX[i]-positionX[i-1],2)+pow(positionY[i]-positionY[i-1],2));
		distances.push_back(curDistance);
		printf("Distance:  %f \n",curDistance);
		}
	}
	return distances;
}

int main(int argc,char* argv[])
{
	if(argc<3)
	{
		fprintf(stderr,"usage: %s referenceTrajectory.txt Trajectory.txt \n",argv[0]); 
		return 0;
	}

	ifstream inReferenceFile(argv[1]);
	ifstream inFile(argv[2]);
	if(inReferenceFile){
		cout << "povedlo se" << endl;
	} else  cout << "nikdy" << endl;
	float a,b;

	while(inReferenceFile >> a >> b)
	{
		refX.push_back(a);
		refY.push_back(b);
		printf("refx: %f , refy:  %f \n",a,b);

	}
	while(inFile >> a >> b)
	{
		x.push_back(a);
		y.push_back(b);
		printf("x: %f , y:  %f \n",a,b);
	}
	refDistance=distanceArray(refX,refY);
		cout << "povedlo se" << endl;
	distanceTest=distanceArray(x,y);
	
	//vector<int>::iterator low;
	for(int i=0;i<distanceTest.size();i++)
	{	
		float diff;
		auto low=lower_bound(refDistance.begin(),refDistance.end(), distanceTest[i]);
		diff=sqrt(pow(x[i]-refX[low-refDistance.begin()],2)+pow(y[i]-refY[low-refDistance.begin()],2));
		difference.push_back(diff);
		printf("Difference in point %i is: %f\n",i,difference[i]);
	}
	return 0;
}
