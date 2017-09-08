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
	float curDistance=0;
	distances.push_back(curDistance);
	for(int i=1;i<positionX.size();i++){
		curDistance+=sqrt(pow(positionX[i]-positionX[i-1],2)+pow(positionY[i]-positionY[i-1],2));
		
		distances.push_back(curDistance);
		}
	for(int i=1;i<distances.size();i++){
		distances[i]=distances[i]/distances[distances.size()-1];
	}
	printf("Distance  travelled: %f", distances[positionX.size()-1]); 
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
	float a,b;

	while(inReferenceFile >> a >> b)
	{
		refX.push_back(a);
		refY.push_back(b);

	}
	while(inFile >> a >> b)
	{
		x.push_back(a);
		y.push_back(b);
	}
	refDistance=distanceArray(refX,refY);
	distanceTest=distanceArray(x,y);
	
	vector<int>::iterator low;
	for(int i=0;i<distanceTest.size();i++)
	{	
		
		auto low=lower_bound(refDistance.begin(),refDistance.end(), distanceTest[i]);
		float diff=sqrt(pow(x[i]-refX[low-refDistance.begin()],2)+pow(y[i]-refY[low-refDistance.begin()],2));
		difference.push_back(diff);
		printf("Difference in point %i is: %f\n",i,difference[i]);
	}
	return 0;
}
