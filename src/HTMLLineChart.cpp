//
// Created by fred.nicolson on 28/07/17.
//

#include <algorithm>
#include <iostream>
#include "HTMLLineChart.h"

std::string HTMLLineChart::construct()
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

void HTMLLineChart::set_size(uint32_t width, uint32_t height)
{
    graph_width = width;
    graph_height = height;
}

void HTMLLineChart::set_title(const std::string &title)
{
    graph_title = title;
}

void HTMLLineChart::add_point(const HTMLGraph::DataPoint &point)
{
    data_points.emplace_back(point);
    if(point.x > max_x)
        max_x = point.x;
    if(point.y > max_y)
        max_y = point.y;
}

void HTMLLineChart::render_to_context(CanvasContext &context)
{
//    //Sort data points
//    std::sort(data_points.begin(), data_points.end(), [](const auto &a, const auto &b){return a.x < b.x;});
//
//    draw_frame(context, graph_width, graph_height, max_x, max_y, graph_title);
//
//    //Draw data
//    if(!data_points.empty())
//    {
//        //Draw the connecting lines
//        context.set_property("lineWidth", get_line_thickness());
//        context.set_property("strokeStyle", "#f00");
//        context.begin_path();
//        auto start_pos = get_point_bounds(data_points.front());
//        context.move_to(start_pos.first, start_pos.second);
//        for(size_t a = 1; a < data_points.size(); a++)
//        {
//            auto pos = get_point_bounds(data_points[a]);
//            context.line_to(pos.first, pos.second);
//        }
//        context.stroke();
//
//        //Draw the data points
//        context.set_property("fillStyle", "#333");
//        for(auto &data_point : data_points)
//        {
//            context.begin_path();
//            auto pos = get_point_bounds(data_point);
//            context.arc(pos.first, pos.second, 4, 0, M_PI * 2);
//            context.fill();
//        }
//    }
}
std::pair<uint32_t, uint32_t> HTMLLineChart::get_size()
{
    return {graph_width, graph_height};
}

std::string HTMLLineChart::get_title()
{
    return graph_title;
}
