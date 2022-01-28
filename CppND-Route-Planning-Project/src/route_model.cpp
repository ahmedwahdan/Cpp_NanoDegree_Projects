#include "route_model.h"
#include <iostream>
#include <math.h>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
        size_t index {0};
        for(auto node : this->Nodes())
        {
            RouteModel::Node _node(index, this, node);
            m_Nodes.push_back(_node);
            index++;
        }
        CreateNodeToRoadHashmap();
}

float RouteModel::Node::distance(const RouteModel::Node& otherNode) const
{
    float distance {0.0};
    distance = std::sqrt(pow((x - otherNode.x), 2) + std::pow((y -otherNode.y), 2));
    return distance;
}

void RouteModel::CreateNodeToRoadHashmap()
{
    for(const auto& road : Roads())
    {
        if(road.type != Model::Road::Type::Footway)
        {
            for(auto node_idx : Ways()[road.way].nodes)
            {
                if(node_to_road.find(node_idx) == node_to_road.end())
                {
                    node_to_road[node_idx] = std::vector<const Model::Road*>{};
                }
                node_to_road[node_idx].push_back(&road);
            }
        }

    }
}

RouteModel::Node const *  RouteModel::Node::FindNeighbor(std::vector<int> node_indeces) const{
    RouteModel::Node const * closest_node {nullptr};
    auto min_distance {std::numeric_limits<float>::max()};
    //pointer to nodes
    auto nodes = this->parent_model->SNodes();
    for(auto node_index : node_indeces)
    {
        // get node by index
        const auto& current_node = nodes[node_index];

        if(!current_node.visited)
        {
            // calculate distance between the two nodes, make sure it's not zero
            auto distance = this->distance(current_node);
            // update closest_node pointer;
            if((distance != 0) && (distance < min_distance))
            {
                closest_node = &current_node;
            }
        }
    }
    return closest_node;
}


void RouteModel::Node::FindNeighbors()
{
    // loop over each road from the node_to_road
    for(const auto& road : this->parent_model->node_to_road[this->index])
    {
        auto node_indeces = this->parent_model->Ways()[road->way].nodes;
        // use FindNeighbor in nodes in this road
        auto closest_node = FindNeighbor(node_indeces);
        // if the returned node is not nullptr, add it to the neighbors vector
        if(closest_node)
        {
            this->neighbors.push_back(closest_node);
        }
    }

}

RouteModel::Node RouteModel::FindClosestNode(float x, float y)
{
    int closest_node_index {-1};
    Node search_node {0, this, {.x = x, .y = y}};
    auto min_distance {std::numeric_limits<float>::max()};
    auto nodes = this->SNodes();
    // loop over all roads
    for(const auto& road : this->Roads())
    {
        // check if the road is not footway
        if(road.type != Model::Road::Type::Footway)
        {
            // loop over nodes of each road
            for(const auto& node_index : this->Ways()[road.way].nodes)
            {
                auto distance = search_node.distance(nodes[node_index]);
                // calculate the distance and update the node index if the distance is less than the min_distance sofar
                if(distance < min_distance)
                {
                    min_distance = distance;
                    closest_node_index = node_index;
                }
            }
        }

    }
    
    // return the Node
    // coud the index be -1??
    return nodes[closest_node_index];
}
