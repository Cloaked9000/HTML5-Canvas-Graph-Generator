//
// Created by fred.nicolson on 28/07/17.
//

#ifndef HTMLGRAPHGENERATOR_HTMLGRAPH_H
#define HTMLGRAPHGENERATOR_HTMLGRAPH_H
#include <string>
#include <utility>

/*!
 * Abstract graph class, the parent for
 * all HTML graph types.
 */
class HTMLGraph
{
public:
    HTMLGraph()=default;
    HTMLGraph(HTMLGraph &&)=default;
    HTMLGraph(const HTMLGraph &)=default;
    virtual ~HTMLGraph()= default;
    HTMLGraph &operator=(const HTMLGraph&)=default;
    HTMLGraph &operator=(HTMLGraph&&)=default;

    /*!
     * A renderable colour
     */
    struct Colour
    {
        Colour()=default;
        Colour(uint8_t r_, uint8_t g_, uint8_t b_)
        : r(r_),
          g(g_),
          b(b_){}

        uint8_t r{255};
        uint8_t g{255};
        uint8_t b{255};
    };

    /*!
     * Stores some 2D bounds
     */
    struct Bound
    {
        Bound()= default;
        Bound(uint32_t x_, uint32_t y_)
        : x(x_), y(y_), height(0), width(0){}
        Bound(uint32_t x_, uint32_t y_, uint32_t width_, uint32_t height_)
                : x(x_), y(y_), height(height_), width(width_){}

        uint32_t x;
        uint32_t y;
        uint32_t height;
        uint32_t width;
    };

    /*!
     *  A graph data point
     */
    struct DataPoint
    {
        DataPoint()=default;
        DataPoint(uint32_t x_, uint32_t y_, std::string tooltip_ = "")
        : x(x_),
          y(y_),
          colour(255, 255, 255),
          tooltip(std::move(tooltip_)){}

        DataPoint(uint32_t x_, uint32_t y_, Colour colour_, std::string tooltip_ = "")
        : x(x_),
          y(y_),
          colour(colour_),
          tooltip(std::move(tooltip_)){}

        DataPoint(std::string x_, uint32_t y_, std::string tooltip = "")
        : x_label(std::move(x_)),
          y(y_),
          tooltip(std::move(tooltip))
        {}

        DataPoint(std::string x_, uint32_t y_, Colour colour_, std::string tooltip_ = "")
        : x_label(std::move(x_)),
          y(y_),
          colour(colour_),
          tooltip(std::move(tooltip_)){}

        uint32_t x{};
        uint32_t y{};
        std::string x_label;
        Colour colour;
        std::string tooltip;
    };

    /*!
     * Constructs the graph and returns a string of HTML
     * that can be rendered by a browser.
     *
     * @return The HTML that will result in the graph being rendered
     */
    virtual std::string construct()=0;

    /*!
     * Sets the size of the graph to draw
     *
     * @param width The width of the canvas in pixels
     * @param height The height of the canvas in pixels
     */
    virtual void set_size(uint32_t width, uint32_t height)=0;

    /*!
     * Sets the canvas title.
     * This is what's rendered above the graph.
     *
     * @param title The title to use. Leave empty for no title.
     */
    virtual void set_title(const std::string &title)=0;

    /*!
     * Gets the canvas title.
     * This is what's rendered above the graph.
     *
     * @return The title used, empty if none.
     */
    virtual std::string get_title()=0;

    /*!
     * Adds a data point to the graph.
     *
     * @note If this fails, it will throw an std::logic_error, with a reason.
     *
     * @param point The data point to add
     */
    virtual void add_point(const DataPoint &point)=0;

    /*!
     * Gets the graph size.
     *
     * @return A pair containing the size of the graph. X = first, Y = second.
     */
    virtual std::pair<uint32_t, uint32_t> get_size() = 0;
private:
};


#endif //HTMLGRAPHGENERATOR_HTMLGRAPH_H
