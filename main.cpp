#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"
using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

int main()
{
    PolygonalMesh mesh;

    if(!ImportMesh(mesh))
    {
        cerr << "file not found" << endl;
        return 1;
    }
    Gedim::UCDUtilities utilities;
    utilities.ExportPoints("./Cell0Ds.inp",
                           mesh.Cell0DsCoordinates);

    utilities.ExportSegments("./Cell1Ds.inp",
                             mesh.Cell0DsCoordinates,
                             mesh.Cell1DsExtrema);
	
					//
					// Test 1 : markers salvati correttamente
	cout << "TEST 1"<<endl;
	
	// FILE 0
	cout << "FILE 0:" << endl;
	for (const auto& marker : mesh.Cell0DsMarker){
	cout << marker.first << ":";
		for (auto id : marker.second){
		cout << id << " ";
		}
	cout << endl;
	}
	
	// FILE 1
	cout  << "FILE 1:" <<endl;
	for (const auto& marker : mesh.Cell1DsMarker){
	cout << marker.first << ":";
		for (auto id : marker.second){
		cout << id << " ";
		}
	cout << endl;
	}
	// FILE 2 (inutile poichè tutti di marker pari a 0)
	
	//
	// Test 2 :dimensione non nulla dei segmenti 
	cout << "--------------------------------------------------------"<<endl;
	cout << "TEST 2:"<< endl;
	int flag = 0;
	for (int j=0 ; j<mesh.Cell1DsExtrema.cols(); j++){
		if (mesh.Cell1DsExtrema(0,j)== mesh.Cell1DsExtrema(1,j))
			flag++;}
	if (flag==0) {
	cout << "tutto ok, ogni lato ha lunghezza maggiore di 0!"<<endl;}
	else
	{cerr << "c'è almeno un lato con lunghezza nulla!"<<endl;}
	//-------------------------------------------------------------------------------------------------------------
	// Test 3 :  ogni poligono ha area non nulla 
	// lezione 1 geometria computazionale
	cout << "--------------------------------------------------------"<<endl;
	cout << "TEST 3:"<< endl;
	
	int flag2 =0;
    for (const auto& poligono : mesh.Cell2DsVertices){
		const int n = poligono.size();
		double area = 0.0;
		if (n<3) {flag2++;}
		for (int i = 0; i < n; i++) {
			int j = (i + 1) % n; // chiude il poligono
			area += abs(mesh.Cell0DsCoordinates(0,poligono[i]) * mesh.Cell0DsCoordinates(1,poligono[j]) - mesh.Cell0DsCoordinates(1,poligono[j]) * mesh.Cell0DsCoordinates(1,poligono[i]));}
		area*= 0.5;
		if (area <= 1e-16){flag2++;}
		}
	if (flag2==0) {
	cout << "corretto, ogni poligono ha area maggiore di 0!";}
	else
	{cerr << "c'è almeno un poligono con area nulla!";}
    return 0;
}
