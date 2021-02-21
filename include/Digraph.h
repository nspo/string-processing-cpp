#ifndef DIGRAPHS_CPP_DIGRAPH_H
#define DIGRAPHS_CPP_DIGRAPH_H

#include <vector>
#include <memory>
#include <sstream>
#include <deque>
#include <unordered_set>
#include <stack>

namespace digraph {

    // Interface of a directed graph
    class Digraph {
    public:
        virtual void addEdge(int v, int w) = 0; // add edge v->w to graph
        [[nodiscard]] virtual const std::vector<int> &adj(int v) const = 0; // get vertices adjacent to v
        [[nodiscard]] virtual int V() const = 0; // number of vertices
        [[nodiscard]] virtual int E() const = 0; // number of edges
        [[nodiscard]] virtual std::unique_ptr<Digraph> reverse() const = 0; // reverse of this digraph
        [[nodiscard]] virtual std::string toString() const = 0; // create string representation
        [[nodiscard]] virtual bool vertexValid(int v) const = 0; // whether a vertex exists
        virtual ~Digraph() = default; // virtual destructor
    };

    // Graph built with adjacency list
    class AdjacencyListDigraph : public Digraph {
    public:
        // create graph with V vertices
        explicit AdjacencyListDigraph(int V) :
                numV(V),
                numE(0),
                adjacencies(V, std::vector<int> {}) {}

        // create graph with input stream
        explicit AdjacencyListDigraph(std::istream &is) {
            if (!(is >> numV) || numV < 0) throw std::invalid_argument("Invalid format (V)");
            if (!(is >> numE || numE < 0)) throw std::invalid_argument("Invalid format (E)");
            adjacencies.insert(adjacencies.end(), numV, {});
            for (int i = 0; i < numE; ++i) {
                int v, w;
                if (!(is >> v >> w)) throw std::invalid_argument("Invalid format (edges)");
                if (v < 0 || v >= numV || w < 0 || w >= numV) {
                    throw std::invalid_argument("Cannot create edge v->w");
                }
                adjacencies[v].push_back(w);
            }
        }

        // add edge v->w to graph
        void addEdge(int v, int w) override {
            if (!vertexValid(v) || !vertexValid(w)) {
                throw std::invalid_argument("Cannot create edge v-w");
            }
            adjacencies[v].push_back(w);
            ++numE;
        }

        // get vertices adjacent to v
        [[nodiscard]] const std::vector<int> &adj(int v) const override {
            if (!vertexValid(v)) {
                throw std::invalid_argument("Invalid vertex");
            }
            return adjacencies[v];
        }

        // number of vertices
        [[nodiscard]] int V() const override {
            return numV;
        }

        // number of edges
        [[nodiscard]] int E() const override {
            return numE;
        }

        // reverse of this digraph
        [[nodiscard]] std::unique_ptr<Digraph> reverse() const override {
            std::unique_ptr<Digraph> rdg = std::make_unique<AdjacencyListDigraph>(this->V());
            for(int from=0; from < this->V(); ++from) {
                for(const int to : this->adj(from)) {
                    rdg->addEdge(to, from); // add reverse edge
                }
            }
            return rdg;
        }

        // create string representation
        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "[Digraph with " << numV << " vertices and " << numE << " edges]\n";
            for (size_t i = 0; i < adjacencies.size(); ++i) {
                for (const auto edge : adjacencies[i]) {
                    ss << i << "->" << edge << "\n";
                }
            }
            return ss.str();
        }

        // whether a vertex exists
        [[nodiscard]] bool vertexValid(int v) const override {
            return v >= 0 && v < numV;
        }

    private:
        int numV = 0; // vertices
        int numE = 0; // edges
        std::vector <std::vector<int>> adjacencies{}; // vector with V elements each of size outDegree(vertex) to represent edges

    };

    // Determine all vertices reachable in a digraph when starting at set from
    class DirectedDFS {
    public:
        explicit DirectedDFS(const Digraph& graph, const std::vector<int>& from) : marked_(graph.V(), false) {
            for(const int v : from) {
                if (!marked(v)) {
                    dfs(graph, v);
                }
            }
        }

        [[nodiscard]]
        bool marked(const int v) const {
            if (v < 0 || static_cast<size_t>(v) >= marked_.size()) {
                throw std::invalid_argument("Invalid vertex");
            }
            return marked_[v];
        }

    private:
        std::deque<bool> marked_;

        void dfs(const Digraph& graph, const int v) {
            marked_[v] = true;
            for (const int neighbor : graph.adj(v)) {
                if (!marked_[neighbor]) {
                    dfs(graph, neighbor);
                }
            }
        }
    };

}

#endif //DIGRAPHS_CPP_DIGRAPH_H
