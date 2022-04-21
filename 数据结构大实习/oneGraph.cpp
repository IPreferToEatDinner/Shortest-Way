#include"GraphMatrix.h"

oneGraph::oneGraph() :m_cost(MAX), m_time(MAX), routes(nullptr) {}

oneGraph::~oneGraph()
{
    delete[] routes;
}