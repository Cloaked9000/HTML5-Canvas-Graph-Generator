//
// Created by fred.nicolson on 28/07/17.
//

#include <algorithm>
#include <iostream>
#include "HTMLLineChart.h"

HTMLLineChart::HTMLLineChart()
: graph_line_thickness(2),
  axis_label_font_size(8),
  title_font_size(16)
{
    left_padding = static_cast<uint32_t>(title_font_size * 2.5 + axis_label_font_size);
    top_padding = title_font_size;
    bottom_padding = static_cast<uint32_t>(title_font_size * 2.5 + axis_label_font_size);
}

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


void HTMLLineChart::set_increment(uint32_t x, uint32_t y)
{
    x_increment = x;
    y_increment = y;
}

void HTMLLineChart::set_x_label(const std::string &label)
{
    x_label = label;
}

void HTMLLineChart::set_y_label(const std::string &label)
{
    y_label = label;
}

void HTMLLineChart::render_to_context(CanvasContext &context)
{
    //Sort data points
    std::sort(data_points.begin(), data_points.end(), [](const auto &a, const auto &b){return a.x < b.x;});

    //Set brush properties. //todo: make configurable
    context.set_property("lineWidth", graph_line_thickness);
    context.set_property("strokeStyle", "#333");
    context.set_property("font", "italic " + std::to_string(axis_label_font_size) + "pt sans-serif");

    //Draw the Y value text
    context.save();
    context.set_property("textAlign", "right");
    uint32_t required_y_increments = (max_y / y_increment);
    if(max_y % y_increment != 0 || required_y_increments == 0)
        required_y_increments++;

    y_label_spacing = (graph_height - top_padding - bottom_padding*2) / required_y_increments;
    for(uint32_t a = 0; a <= required_y_increments; a++)
    {
        context.fill_text(a * y_increment, left_padding - axis_label_font_size, (graph_height - (a * y_label_spacing)) - bottom_padding);
    }
    context.restore();

    //Draw the X value text
    context.set_property("textAlign", "center");
    if(x_string_values.empty())
    {
        //If we're auto generating the x labels, then figure out how many we need to
        //Fit the maximum X value, then draw the labels.

        uint32_t required_x_increments = max_x / x_increment;
        if(max_x % x_increment != 0 || required_x_increments == 0)
            required_x_increments++;
        x_label_spacing = (graph_width - left_padding * 2) / required_x_increments;
        for(uint32_t a = 0; a <= required_x_increments; a++)
        {
            context.fill_text(a * x_increment, left_padding + (a * x_label_spacing), (graph_height - bottom_padding) + graph_line_thickness + axis_label_font_size*1.5);
        }
    }
    else
    {
        //Else, the caller has provided X labels, so draw those instead.
        x_label_spacing = static_cast<uint32_t>((graph_width - left_padding * 2) / x_string_values.size());
        for(uint32_t a = 0; a < x_string_values.size(); a++)
        {
            context.fill_text(x_string_values[a], (x_label_spacing/2) + left_padding + (a * x_label_spacing), (graph_height - bottom_padding) + graph_line_thickness + axis_label_font_size*1.5);
        }
    }

    //Draw the axis
    context.begin_path();
    context.move_to(left_padding, top_padding); //Move to top left
    context.line_to(left_padding, graph_height - bottom_padding); //Draw left line
    context.line_to(graph_width - left_padding, graph_height - bottom_padding); //Draw bottom line
    context.stroke();

    //Draw data
    if(!data_points.empty())
    {
        //Draw the connecting lines
        context.set_property("strokeStyle", "#f00");
        context.begin_path();
        auto start_pos = get_point_position(data_points.front());
        context.move_to(start_pos.first, start_pos.second);
        for(size_t a = 1; a < data_points.size(); a++)
        {
            auto pos = get_point_position(data_points[a]);
            context.line_to(pos.first, pos.second);
        }
        context.stroke();

        //Draw the data points
        context.set_property("fillStyle", "#333");
        for(auto &data_point : data_points)
        {
            context.begin_path();
            auto pos = get_point_position(data_point);
            context.arc(pos.first, pos.second, 4, 0, M_PI * 2);
            context.fill();
        }
    }

    //Draw the title
    context.set_property("font", std::to_string(title_font_size) + "pt sans-serif");
    context.fill_text(graph_title, graph_width / 2, 20);

    //Draw Y axis label
    context.fill_rotated_text(y_label, (int)title_font_size, (int)(graph_height / 2), 270.0);

    //Draw X axis label
    context.fill_text(x_label, graph_width / 2, graph_height - (title_font_size/2));
}

std::pair<uint32_t, uint32_t> HTMLLineChart::get_point_position(const HTMLGraph::DataPoint &data_point)
{
    //If there's numeric X values
    if(x_string_values.empty())
    {
        return std::make_pair(left_padding + (data_point.x / (double)x_increment) * x_label_spacing,
                              (graph_height - ((data_point.y / (double)y_increment) * y_label_spacing) - bottom_padding));
    }

    //Else if X values are user provided
    auto x_iter = std::find(x_string_values.begin(), x_string_values.end(), data_point.x_label);
    if(x_iter == x_string_values.end())
        throw std::logic_error("No such X label: " + data_point.x_label);
    return std::make_pair((x_label_spacing/2) + left_padding + (std::distance(x_string_values.begin(), x_iter) * x_label_spacing),
                          (graph_height - ((data_point.y / (double)y_increment) * y_label_spacing) - bottom_padding));
}

void HTMLLineChart::set_x_index_strings(std::vector<std::string> values)
{
    x_string_values = std::move(values);
}
