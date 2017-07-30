//
// Created by fred.nicolson on 28/07/17.
//

#include <algorithm>
#include "HTMLBarChart.h"

std::string HTMLBarChart::construct()
{
    std::string graph;

    //Create a canvas element
    graph += "<canvas id='my_graph' width='" + std::to_string(graph_width) + "' height='" + std::to_string(graph_height) + "'></canvas>\n";

    //Create script tag and get the canvas
    graph += "<script>\nvar ctx = document.getElementById('my_graph').getContext('2d');\n";

    //Create render context
    CanvasContext context("ctx");

    //Render axis
    auto max_y_iter = std::max_element(data_points.begin(), data_points.end(), [](const auto &a, const auto &b){return a.y < b.y;});
    auto max_x_iter = std::max_element(data_points.begin(), data_points.end(), [](const auto &a, const auto &b){return a.x < b.x;});
   // HTMLLineChart::render_to_context(context, graph_width, graph_height, max_x_iter == data_points.end() ? 0 : max_x_iter->x,
                                                                        // max_y_iter == data_points.end() ? 0 : max_y_iter->y);

    //Add to resulting script
    graph += context.dump();

    //End script tag
    graph += "</script>";
    return graph;
}

void HTMLBarChart::set_size(uint32_t width, uint32_t height)
{
    graph_width = width;
    graph_height = height;
}

void HTMLBarChart::set_title(const std::string &title)
{
    graph_title = title;
}

void HTMLBarChart::add_point(const HTMLGraph::DataPoint &point)
{
    data_points.emplace_back(point);
}
