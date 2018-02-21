//
// Created by fred.nicolson on 28/07/17.
//

#include <algorithm>
#include <iostream>
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

    //Render it
    render_to_context(context);

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
    if(point.x > max_x)
        max_x = point.x;
    if(point.y > max_y)
        max_y = point.y;
}

std::pair<uint32_t, uint32_t> HTMLBarChart::get_size()
{
    return {graph_width, graph_height};
}

std::string HTMLBarChart::get_title()
{
    return graph_title;
}

void HTMLBarChart::render_to_context(CanvasContext &context)
{
    //Sort data points
    std::sort(data_points.begin(), data_points.end(), [](const auto &a, const auto &b){return a.x < b.x;});

    draw_frame(context, graph_width, graph_height, max_x, max_y, graph_title);

    //Draw data
    if(!data_points.empty())
    {
        //Draw the bars
        for(auto &data_point : data_points)
        {
            auto pos = get_point_bounds(data_point, true);
            std::cout << pos.x << ", " << pos.y << ", " << pos.width << ", " << pos.height << std::endl;
            context.set_property("fillStyle", data_point.colour.to_string());
            context.fill_rect(pos.x, pos.y - pos.height, pos.width, pos.height);
        }
    }
}
