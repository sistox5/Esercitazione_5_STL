#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

// //vertici e segmenti dei poligoni nella mesh

namespace PolygonalLibrary 
struct PolygonalMesh{
	unsigned int NumCell0Ds = 0;  //   numero di vertici
    vector<unsigned int> Cell0DsId = {};  //  Id dei vertici
    MatrixXd Cell0DsCoordinates = {};  //  coordinate (x,y) dei punti 
    map<unsigned int, list<unsigned int>> Cell0DsMarker = {}; // mappa (dizionario) avente come chiave i marker e come valore la lista di punti
															 //(rappresentati dagli id) corrispondenti al marker in chiave
    unsigned int NumCell1Ds = 0; //  numero di segmenti
    vector<unsigned int> Cell1DsId = {}; //  Id degi segmenti
    MatrixXi Cell1DsExtrema = {}; // raccolta degli estremi dei segmenti (punto_di_partenza,punto_di_arrivo)
    map<unsigned int, list<unsigned int>> Cell1DsMarker = {}; // mappa (dizionario) avente come chiave i marker e come valore la lista di segmenti
															 //(rappresentati dagli id) corrispondenti al marker in chiave

    unsigned int NumCell2Ds = 0; // -> numero di poligoni formati
    vector<unsigned int> Cell2DsId = {}; // lista degli Id dei poligoni
    vector<vector<unsigned int>> Cell2DsVertices; // vertici rappresentativi del poligono 
    vector<vector<unsigned int>> Cell2DsEdges;	// segmenti costitutivi del poligono 
	map<unsigned int, list<unsigned int>> Cell2DsMarker = {};
	
};
}
