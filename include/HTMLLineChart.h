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
#include "HTMLGraphFrame.h"

/*!
 * For creating line graphs
 */
class HTMLLineChart : public HTMLGraph, public HTMLGraphFrame
{
public:
    HTMLLineChart()= default;
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
     * Gets the graph size.
     *
     * @return A pair containing the size of the graph. X = first, Y = second.
     */
    std::pair<uint32_t, uint32_t> get_size() override;

    /*!
     * Gets the canvas title.
     * This is what's rendered above the graph.
     *
     * @return The title used, empty if none.
     */
    std::string get_title() override;
protected:

private:
    /*!
     * Renders the line chart to a given canvas context. The state of
     * the canvas will be preserved (style changes etc).
     *
     * @param context The context to render to.
     */
    void render_to_context(CanvasContext &context);

    uint32_t graph_width;
    uint32_t graph_height;
    uint32_t max_x{0};
    uint32_t max_y{0};
    std::vector<DataPoint> data_points;
    std::string graph_title;
};


#endif //HTMLGRAPHGENERATOR_HTMLGRAPHAXIS_H
