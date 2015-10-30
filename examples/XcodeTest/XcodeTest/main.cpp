//
//  main.cpp
//  Tarea4
//
//  Created by Krikor Bisdikian on 10/25/15.
//  Copyright © 2015 Krikor Bisdikian. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include "Snap.h"



typedef std::chrono::high_resolution_clock hclock;

void exportGraphML(PNGraph g);
void exportGEXF(PNGraph g);
void exportGDF(PNGraph g);
void exportJSON(PNGraph g);


int main() {
    PNGraph grafo = TSnap::LoadEdgeList<PNGraph>("./facebook_combined.txt",0,1);

    auto begin = hclock::now();
    exportGraphML(grafo);
    auto end = hclock::now();
    auto time =std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    std::cout << "GraphML: " << time.count() << std::endl;
    
    begin = hclock::now();
    exportGEXF(grafo);
    end = hclock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    std::cout << "GEXF: " << time.count() << std::endl;
    
    begin = hclock::now();
    exportGDF(grafo);
    end = hclock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    std::cout << "GDF: " << time.count() << std::endl;
    
    begin = hclock::now();
    exportJSON(grafo);
    end = hclock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    std::cout << "JSON: " << time.count() << std::endl;
    
    return 0;
}

void exportGraphML(PNGraph g) {
    std::ofstream file ("./facebook_combined.graphml");
    if (file.is_open())
    {
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
        file << "<graph id=\"G\" edgedefault=\"directed\">\n";
        for (PNGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
        {
            file << "<node id=\"" << NI.GetId() << "\"/>\n";
        }
        int i = 1;
        for (PNGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
        {
            file << "<edge id=\"e" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\"/>\n";
        }
        
        file << "</graph>\n";
        file << "</graphml>\n";
        file.close();
    }
}

void exportGEXF(PNGraph g)
{
    std::ofstream file ("./facebook_combined.gexf");
    if (file.is_open())
    {
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
        file << "<graph mode=\"static\" defaultedgetype=\"directed\">\n";
        file << "<nodes>\n";
        for (PNGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
        {
            file << "<node id=\"" << NI.GetId() << "\" />\n";
        }
        file << "</nodes>\n";
        file << "<edges>\n";
        int i = 1;
        for (PNGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
        {
            file << "<edge id=\"" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\" />\n";
        }
        file << "</edges>\n";
        file << "</graph>\n";
        file << "</gexf>\n";
        file.close();
    }
}

void exportGDF(PNGraph g)
{
    std::ofstream file ("./facebook_combined.gdf");
    if (file.is_open())
    {
        file << "nodedef> name VARCHAR\n";
        for (PNGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
        {
            file << NI.GetId() << "\n";
        }
        file << "edgedef>source VARCHAR, destination VARCHAR\n";
        for (PNGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++)
        {
            file << EI.GetSrcNId() << ", " << EI.GetDstNId() << "\n";
        }
        file.close();
    }
}

void exportJSON(PNGraph g)
{
    std::ofstream file ("./facebook_combined.json");
    if (file.is_open())
    {
        file << "{ \"graph\": {\n";
        file << "\"nodes\": [\n";
        for (PNGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); )
        {
            file << "{ \"id\": \"" << NI.GetId() << "\" }";
            if (NI++ == g->EndNI())
            {
                file << " ],\n";
            }
            else
            {
                file << ",\n";
            }
            
        }
        file << "\"edges\": [\n";
        for (PNGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); )
        {
            file << "{ \"source\": \"" << EI.GetSrcNId() << "\", \"target\": \"" << EI.GetDstNId() << "\" }";
            if (EI++ == g->EndEI())
            {
                file << " ]\n";
            }
            else
            {
                file << ",\n";
            }
        }
        file << "} }";
        file.close();
    }
}
