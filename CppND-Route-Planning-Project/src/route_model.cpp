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