//
// Created by fred.nicolson on 31/07/17.
//

#include <algorithm>
#include <stdexcept>
#include "HTMLGraphFrame.h"

HTMLGraphFrame::HTMLGraphFrame()
: graph_line_thickness(2),
  axis_label_font_size(8),
  title_font_size(16)
{
    left_padding = static_cast<uint32_t>(title_font_size * 2.5 + axis_label_font_size);
    top_padding = title_font_size;
    bottom_padding = static_cast<uint32_t>(title_font_size * 2.5 + axis_label_font_size);
}

void HTMLGraphFrame::set_increment(uint32_t x, uint32_t y)
{
    x_increment = x;
    y_increment = y;
}

void HTMLGraphFrame::set_x_label(const std::string &label)
{
    x_label = label;
}

void HTMLGraphFrame::set_y_label(const std::string &label)
{
    y_label = label;
}

HTMLGraph::Bound HTMLGraphFrame::get_point_bounds(const HTMLGraph::DataPoint &data_point, bool round_to_increment)
{
    auto top_y = static_cast<uint32_t>(graph_height - ((data_point.y / (double)y_increment) * y_label_spacing) - bottom_padding);
    auto bottom_y = static_cast<uint32_t>(graph_height - bottom_padding);
    uint32_t top_x;

    //If there's numeric X values
    if(x_string_values.empty())
    {
        top_x = static_cast<uint32_t>(left_padding + (data_point.x / (double)x_increment) * x_label_spacing);
    }
    else
    {
        //Else string X values
        auto x_iter = std::find(x_string_values.begin(), x_string_values.end(), data_point.x_label);
        if(x_iter == x_string_values.end())
            throw std::logic_error("No such X label: " + data_point.x_label);
        top_x = static_cast<uint32_t>((x_label_spacing / 2) + left_padding + (std::distance(x_string_values.begin(), x_iter) * x_label_spacing));
    }

    if(round_to_increment)
        top_x -= x_label_spacing / 2;

    return HTMLGraph::Bound(top_x , //X
                            bottom_y, //Y
                            x_label_spacing, //Width
                            bottom_y - top_y); //Height

}

void HTMLGraphFrame::draw_frame(CanvasContext &context, uint32_t graph_width_, uint32_t graph_height_, uint32_t max_x,
                                uint32_t max_y, const std::string &graph_title)
{
    //Store things we need
    graph_width = graph_width_;
    graph_height = graph_height_;

    //Preserve context properties
    context.save();

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

    //Draw the title
    context.set_property("font", std::to_string(title_font_size) + "pt sans-serif");
    context.fill_text(graph_title, graph_width / 2, 20);

    //Draw Y axis label
    context.fill_rotated_text(y_label, (int)title_font_size, (int)(graph_height / 2), 270.0);

    //Draw X axis label
    context.fill_text(x_label, graph_width / 2, graph_height - (title_font_size/2));

    //Restore context properties now done
    context.restore();
}

void HTMLGraphFrame::set_x_index_strings(std::vector<std::string> values)
{
    x_string_values = std::move(values);
}

void HTMLGraphFrame::set_line_thickness(uint32_t thickness)
{
    graph_line_thickness = thickness;
}

uint32_t HTMLGraphFrame::get_line_thickness()
{
    return graph_line_thickness;
}
