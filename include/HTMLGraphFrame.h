//
// Created by fred.nicolson on 31/07/17.
//

#ifndef HTMLGRAPHGENERATOR_HTMLGRAPHFRAME_H
#define HTMLGRAPHGENERATOR_HTMLGRAPHFRAME_H


#include <vector>
#include "HTMLGraph.h"
#include "CanvasContext.h"

/*!
 * Class for rendering graph axis.
 * Should be inherited by graph types to allow
 * axis rendering.
 */
class HTMLGraphFrame
{
public:
    HTMLGraphFrame();
    HTMLGraphFrame(HTMLGraphFrame &&)=default;
    HTMLGraphFrame(const HTMLGraphFrame &)=default;

    virtual ~HTMLGraphFrame() = default;
    HTMLGraphFrame &operator=(const HTMLGraphFrame&)=default;
    HTMLGraphFrame &operator=(HTMLGraphFrame&&)=default;

    /*!
     * Set's the axis increment.
     * This is the interval in numbers between each data point.
     *
     * @param x The interval to draw along the bottom
     * @param y The interval to draw along the left
     */
    void set_increment(uint32_t x, uint32_t y);

    /*!
     * Sets the label to draw to the left of the axis, if any.
     *
     * @param label The label to draw. Leave blank for none.
     */
    void set_x_label(const std::string &label);

    /*!
     * Sets the label to draw under the axis, if any.
     * @param label The label to draw. Leave blank for none.
     */
    void set_y_label(const std::string &label);

    /*!
     * Gets a data points position on the graph.
     *
     * @param data_point The data point to plot
     * @param round_to_increment If the bounds should be rounded to the nearest increment or not
     * @return A pair containing the X and Y values, of where the points are on the canvas
     */
    HTMLGraph::Bound get_point_bounds(const HTMLGraph::DataPoint &data_point, bool round_to_increment = false);

    /*!
     * Used for setting the X value labels. If this is not set, then numbers will be
     * auto generated based on the X increment value.
     *
     * @param values The values to use for X labels
     */
    void set_x_index_strings(std::vector<std::string> values);

    /*!
     * Sets the render line thickness
     *
     * @param thickness The line thickness
     */
    void set_line_thickness(uint32_t thickness);

    /*!
     * Gets the render line thickness
     *
     * @return thickness The line thickness
     */
    uint32_t get_line_thickness();

    /*!
     * Draws the graph frame to the provided context. The context properties
     * will be saved, and so not modified.
     *
     * @param context The context to draw the graph frame to
     */
    void draw_frame(CanvasContext &context, uint32_t graph_width, uint32_t graph_height, uint32_t max_x,
                    uint32_t max_y, const std::string &graph_title);

private:

    uint32_t left_padding;
    uint32_t bottom_padding;
    uint32_t top_padding;
    uint32_t axis_label_font_size;
    uint32_t title_font_size;
    uint32_t graph_line_thickness;
    uint32_t x_label_spacing{0};
    uint32_t y_label_spacing{0};
    uint32_t x_increment{};
    uint32_t y_increment{};

    std::string x_label;
    std::string y_label;

    uint32_t graph_width;
    uint32_t graph_height;

    std::vector<std::string> x_string_values;
};


#endif //HTMLGRAPHGENERATOR_HTMLGRAPHFRAME_H
