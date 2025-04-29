#pragma once
#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary
{
// controlla il corretto funzionamento delle funzioni di lettura dati sottostanti, restituisce true se tutte funzionano correttamente, false altrimenti
bool ImportMesh(PolygonalMesh& mesh);

// importa i dati dal file Cell0Ds.csv e li gestisce tramite la struttura di mesh *PolygonalMesh*, restituisce il risultato della lettura
// in caso di successo (true), falso altrimenti
bool ImportCell0Ds(PolygonalMesh& mesh);

// importa i dati dal file Cell1Ds.csv e li gestisce tramite la struttura di mesh *PolygonalMesh*, restituisce il risultato della lettura
// in caso di successo (true), falso altrimenti
bool ImportCell1Ds(PolygonalMesh& mesh);

// importa i dati dal file Cell2Ds.csv e li gestisce tramite la struttura di mesh *PolygonalMesh*, restituisce il risultato della lettura
// in caso di successo (true), falso altrimenti
bool ImportCell2Ds(PolygonalMesh& mesh);

}
