#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct Edge
{
    int from, to, weight;

    Edge(int _from, int _to, int _weight) : from{_from}, to{_to}, weight{_weight} {};
};

bool sort_by_weight(Edge *x, Edge *y)
{
    return x->weight < y->weight;
}

int find(int node, int nodes[])
{
    while (nodes[node] != -1)
        node = nodes[node];
    return node;
}

void union_nodes(int x, int y, int nodes[])
{
    nodes[y] = x;
}

/*
 * Complete the 'kruskals' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts WEIGHTED_INTEGER_GRAPH g as parameter.
 */

/*
 * For the weighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] and <name>_to[i]. The weight of the edge is <name>_weight[i].
 *
 */

int kruskals(int g_nodes, int g_edges, vector<int> g_from, vector<int> g_to, vector<int> g_weight)
{
    Edge **edges = new Edge *[g_edges];
    for (int i = 0; i < g_edges; i++)
    {
        edges[i] = new Edge(g_from[i], g_to[i], g_weight[i]);
    }
    sort(edges, edges + g_edges, sort_by_weight);

    int mstWeight = 0;
    int *nodes = new int[g_nodes];
    fill(nodes, nodes + g_nodes, -1);
    for (int i = 0; i < g_edges; i++)
    {
        int findX = find(edges[i]->from, nodes),
            findY = find(edges[i]->to, nodes);
        if (findX != findY)
        {
            mstWeight += edges[i]->weight;
            union_nodes(findX, findY, nodes);
        }
    }

    delete[] nodes;

    for (int i = 0; i < g_edges; i++)
        delete edges[i];
    delete[] edges;
    return mstWeight;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string g_nodes_edges_temp;
    getline(cin, g_nodes_edges_temp);

    vector<string> g_nodes_edges = split(rtrim(g_nodes_edges_temp));

    int g_nodes = stoi(g_nodes_edges[0]);
    int g_edges = stoi(g_nodes_edges[1]);

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);

    for (int i = 0; i < g_edges; i++)
    {
        string g_from_to_weight_temp;
        getline(cin, g_from_to_weight_temp);

        vector<string> g_from_to_weight = split(rtrim(g_from_to_weight_temp));

        int g_from_temp = stoi(g_from_to_weight[0]);
        int g_to_temp = stoi(g_from_to_weight[1]);
        int g_weight_temp = stoi(g_from_to_weight[2]);

        g_from[i] = g_from_temp;
        g_to[i] = g_to_temp;
        g_weight[i] = g_weight_temp;
    }

    int res = kruskals(g_nodes, g_edges, g_from, g_to, g_weight);

    fout << res << endl;

    fout.close();

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}

vector<string> split(const string &str)
{
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
