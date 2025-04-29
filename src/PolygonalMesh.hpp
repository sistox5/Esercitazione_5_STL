#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

// definisco una struttura di rappresentazione (mesh) nella quale confluiranno i dati(vertici,segmenti,poligoni) forniti dai file di input

namespace PolygonalLibrary 
{
struct PolygonalMesh{
	unsigned int NumCell0Ds = 0;  //  -> numero di vertici
    vector<unsigned int> Cell0DsId = {};  // lista degli Id dei vertici
    MatrixXd Cell0DsCoordinates = {};  // raccolta delle coordinate (x,y) dei punti in oggetto
    map<unsigned int, list<unsigned int>> Cell0DsMarker = {}; // mappa (dizionario) avente come chiave i marker e come valore la lista di punti
															 //(rappresentati dagli id) corrispondenti al marker in chiave

    unsigned int NumCell1Ds = 0; // -> numero di segmenti
    vector<unsigned int> Cell1DsId = {}; // lista degli Id degi segmenti
    MatrixXi Cell1DsExtrema = {}; // raccolta degli estremi dei segmenti (punto_di_partenza,punto_di_arrivo)
    map<unsigned int, list<unsigned int>> Cell1DsMarker = {}; // mappa (dizionario) avente come chiave i marker e come valore la lista di segmenti
															 //(rappresentati dagli id) corrispondenti al marker in chiave

    unsigned int NumCell2Ds = 0; // -> numero di poligoni formati
    vector<unsigned int> Cell2DsId = {}; // lista degli Id dei poligoni
    vector<vector<unsigned int>> Cell2DsVertices; // vettore fatto di vettori (ognuno contenente i vertici rappresentativi di un dato poligono)
    vector<vector<unsigned int>> Cell2DsEdges;	// vettore fatto di vettori (ognuno contenente i segmenti costituitivi di un dato poligono)
	map<unsigned int, list<unsigned int>> Cell2DsMarker = {};
	
};
}

