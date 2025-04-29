#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace PolygonalLibrary
{
bool ImportMesh(PolygonalMesh& mesh)
{

    if(!ImportCell0Ds(mesh))
        return false;

    if(!ImportCell1Ds(mesh))
        return false;

    if(!ImportCell2Ds(mesh))
        return false;

    return true;

}

// 
bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell0Ds.csv"); 
    if(file.fail()) // restituisco messaggio di errore se non funziona
        return false;

    list<string> dati; //dati in una lista di stringhe

    string dato; 
    while (getline(file, dato))
        dati.push_back(dato);

    file.close(); 

    // rimuovo l'intestazione  (Id,Marker,X,Y)
    dati.pop_front();
	
    mesh.NumCell0Ds = dati.size();  // salvo il numero di dati raccolto (numero di vertici)

    if (mesh.NumCell0Ds == 0)    // controllo che il file non sia vuoto, altrimenti mando messaggio di errore
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DsId.reserve(mesh.NumCell0Ds); // riservo la memoria per i contenitori della struttura di mesh
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds); 

    for (const string& dato : dati)
    {
        istringstream converter(dato);

        unsigned int id;
        unsigned int marker;
        char garbage;

        converter >> id >> garbage>>marker >>garbage>> mesh.Cell0DsCoordinates(0, id) >>garbage>>mesh.Cell0DsCoordinates(1, id); // leggo i dati della riga
        mesh.Cell0DsId.push_back(id);

        // Memorizzo i marker
		
		if (marker != 0)
		{
			const auto it = mesh.Cell0DsMarker.find(marker); // cerco il marker 
			if (it == mesh.Cell0DsMarker.end())				//se non c'è lo inserisco con l'id corrispondente
			{
				mesh.Cell0DsMarker.insert({marker, {id}});
			}
			else
			{
				it->second.push_back(id); // se c'è già inserisco il nuovo id trovato
			}
		}
		

    }

    return true;
}
// --------------------------------------------------------------------------------------------------------------
bool ImportCell1Ds(PolygonalMesh& mesh)
{
	// eseguo le operazioni come nel file 0
   
   ifstream file("./Cell1Ds.csv");

    if(file.fail())
        return false;

    list<string> dati;
    string dato;
    while (getline(file, dato))
        dati.push_back(dato);

    file.close();
    dati.pop_front();

    mesh.NumCell1Ds = dati.size();

    if (mesh.NumCell1Ds == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
    mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);

    for (const string& dato : dati)
    {
        istringstream converter(dato);

        unsigned int id;
        unsigned int marker;
        char garbage;

        converter >>  id >> garbage>>marker >> garbage>>  mesh.Cell1DsExtrema(0, id) >>  garbage>> mesh.Cell1DsExtrema(1, id);
        mesh.Cell1DsId.push_back(id);

        // Memorizzare i marker
		if (marker != 0)
		{
			const auto it = mesh.Cell1DsMarker.find(marker);
			if (it == mesh.Cell1DsMarker.end())
			{
				mesh.Cell1DsMarker.insert({marker, {id}});
			}
			else
			{
				it->second.push_back(id);
			}
		}
    }

    return true;
}

bool ImportCell2Ds(PolygonalMesh& mesh)

// analoga situazione ai casi precedenti 

{
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> dati;
    string dato;
    while (getline(file, dato))
        dati.push_back(dato);

    file.close();

    // remove header
    dati.pop_front();

    mesh.NumCell2Ds = dati.size();

    if (mesh.NumCell2Ds == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }
    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);

    for (const string& dato : dati)
    {
        istringstream converter(dato);
        unsigned int id;
		unsigned int marker;
		unsigned int NumVertices;
		unsigned int NumEdges;
		vector<unsigned int> vertices;
		vector<unsigned int> edges;
		char garbage;
		unsigned int vertix;
		unsigned int edge;
        converter >>  id>>garbage>> marker >> garbage>> NumVertices;
		vertices.reserve(NumVertices);
		for(unsigned int i = 0; i < NumVertices; i++)
		{converter >> garbage;
			converter>> vertix;
		vertices.push_back(vertix);}
		mesh.Cell2DsVertices.push_back(vertices);
		
		converter >>garbage;
		converter >> NumEdges;
		
        for(unsigned int i = 0; i < NumEdges; i++)
		{converter >>garbage;
			converter >> edge;
		edges.push_back(edge);}

        mesh.Cell2DsId.push_back(id);
        mesh.Cell2DsEdges.push_back(edges);
		
		if (marker != 0)
		{
			const auto it = mesh.Cell2DsMarker.find(marker);
			if (it == mesh.Cell2DsMarker.end())
			{
				mesh.Cell2DsMarker.insert({marker, {id}});
			}
			else
			{
				it->second.push_back(id);
			}
		}
    }
    return true;
}

}
