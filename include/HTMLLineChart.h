//
// Created by fred.nicolson on 28/07/17.
//

#ifndef HTMLGRAPHGENERATOR_HTMLGRAPHAXIS_H
#define HTMLGRAPHGENERATOR_HTMLGRAPHAXIS_H


#include <cstdint>
#include <string>
#include <map>
#include "CanvasContext.h"
#include "HTMLGraph.h"

/*!
 * Class for rendering graph axis.
 * Should be inherited by graph types to allow
 * axis rendering.
 */
class HTMLLineChart : public HTMLGraph
{
public:
    HTMLLineChart();
    HTMLLineChart(HTMLLineChart &&)=default;
    HTMLLineChart(const HTMLLineChart &)=default;

    ~HTMLLineChart() override = default;
    HTMLLineChart &operator=(const HTMLLineChart&)=default;
    HTMLLineChart &operator=(HTMLLineChart&&)=default;

    /*!
     * Constructs the graph and returns a string of HTML
     * that can be rendered by a browser.
     *
     * @return The HTML that will result in the graph being rendered
     */
    std::string construct() override;

    /*!
     * Sets the canvas size available to the graph
     *
     * @param width The width of the canvas in pixels
     * @param height The height of the canvas in pixels
     */
    void set_size(uint32_t width, uint32_t height) override;

    /*!
     * Sets the canvas title.
     * This is what's rendered above the graph.
     *
     * @param title The title to use. Leave empty for no title.
     */
    void set_title(const std::string &title) override;

    /*!
     * Adds a data point to the graph.
     *
     * @note If this fails, it will throw an std::logic_error, with a reason.
     *
     * @param point The data point to add
     */
    void add_point(const DataPoint &point) override;

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
     * Used for setting the X value labels. If this is not set, then numbers will be
     * auto generated based on the X increment value.
     *
     * @param values The values to use for X labels
     */
    void set_x_index_strings(std::vector<std::string> values);
protected:

private:
    void render_to_context(CanvasContext &context);

    std::pair<uint32_t, uint32_t> get_point_position(const DataPoint &data_point);

    uint32_t graph_width;
    uint32_t graph_height;
    uint32_t left_padding;
    uint32_t bottom_padding;
    uint32_t top_padding;
    std::string graph_title;
    uint32_t axis_label_font_size;
    uint32_t title_font_size;
    uint32_t graph_line_thickness;
    std::vector<DataPoint> data_points;

    uint32_t x_increment{};
    uint32_t y_increment{};
    std::string render_context;
    std::string x_label;
    std::string y_label;

    uint32_t max_x{0};
    uint32_t max_y{0};
    uint32_t x_label_spacing{0};
    uint32_t y_label_spacing{0};

    std::vector<std::string> x_string_values;
};


#endif //HTMLGRAPHGENERATOR_HTMLGRAPHAXIS_H
