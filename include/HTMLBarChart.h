//
// Created by fred.nicolson on 28/07/17.
//

#ifndef HTMLGRAPHGENERATOR_HTMLBARCHART_H
#define HTMLGRAPHGENERATOR_HTMLBARCHART_H

#include <vector>
#include "HTMLGraph.h"
#include "HTMLLineChart.h"

class HTMLBarChart : public HTMLGraph
{
public:
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
     * @param point The data point to add
     */
    void add_point(const DataPoint &point) override;
private:
    uint32_t graph_width;
    uint32_t graph_height;
    std::string graph_title;
    std::vector<DataPoint> data_points;
};


#endif //HTMLGRAPHGENERATOR_HTMLBARCHART_H
