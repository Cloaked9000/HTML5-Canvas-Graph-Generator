//
// Created by fred.nicolson on 28/07/17.
//

#ifndef HTMLGRAPHGENERATOR_CANVASCONTEXT_H
#define HTMLGRAPHGENERATOR_CANVASCONTEXT_H
#include <string>
#include <cmath>
#include <unordered_map>
#include <stack>

/*!
 * Like for like wrapper around the actual javascript
 * canvas API to make life easier
 */
namespace std
{
    static std::string to_string(const char *&val)
    {
        return "'" + std::string(val) + "'";
    }
    static std::string to_string(const std::string &str)
    {
        return "'" + str + "'";
    }
}
class CanvasContext
{
public:
     explicit CanvasContext(std::string context_name_)
            : context_name(std::move(context_name_)){}

    template<typename T>
    void set_property(const std::string &property, T value)
    {
        //Convert value to string to storage
        std::string str_value = std::to_string(value);

        //Ensure that the property isn't already in effect
        auto prop_iter = properties.find(property);
        if(prop_iter != properties.end())
        {
            if(prop_iter->second == str_value)
                return;
        }

        //Add to buffer
        buffer += context_name + "." + property + "=" + str_value + ";\n";

        //Add property to properties cache
        properties[property] = std::move(str_value);
    }

    void begin_path()
    {
        buffer += context_name + ".beginPath();\n";
    }

    template<typename T, typename T2>
    void move_to(T x, T2 y)
    {
        buffer += context_name + ".moveTo(" + std::to_string(x) + ", " + std::to_string(y) + ");\n";
    }

    template<typename T, typename T2>
    void line_to(T x, T2 y)
    {
        buffer += context_name + ".lineTo(" + std::to_string(x) + ", " + std::to_string(y) + ");\n";
    }

    void stroke()
    {
        buffer += context_name + ".stroke();\n";
    }

    template<typename T, typename T2>
    void fill_text(std::string text, T x, T2 y)
    {
        if(text.empty())
            return;
        if(text.front() != '\"' && text.front() != '\'')
            text.insert(0, 1, '\'');
        if(text.back() != '\"' && text.back() != '\'')
            text.append("'");
        buffer += context_name + ".fillText(" + text + ", " + std::to_string(x) + ", " + std::to_string(y) + ");\n";
    }

    template<typename T, typename T2, typename T3>
    void fill_text(T text, T2 x, T3 y)
    {
        buffer += context_name + ".fillText(" + std::to_string(text) + ", " + std::to_string(x) + ", " + std::to_string(y) + ");\n";
    }

    template<typename T, typename T2>
    void arc(T x, T2 y, float radius, double start_angle, double end_angle, const std::string &counterclockwise = "false")
    {
        buffer += context_name + ".arc(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(radius) + ", "
                  + std::to_string(start_angle) + ", " + std::to_string(end_angle) + ", " + counterclockwise + ");\n";
    };

    void fill()
    {
        buffer += context_name + ".fill();\n";
    }

    void close_path()
    {
        buffer += context_name + ".closePath();\n";
    }

    template<typename T>
    void rotate(T val)
    {
        buffer += context_name + ".rotate(" + std::to_string(val) + ");\n";
    }

    void save()
    {
        //Add to buffer
        buffer += context_name + ".save();\n";

        //Save properties cache
        property_stack.emplace(properties);
    }

    void restore()
    {
        //Add to buffer
        buffer += context_name + ".restore();\n";

        //Restore properties from property stack
        if(property_stack.empty())
            throw std::logic_error("Can't restore canvas context. No context's have been saved!");
        properties = property_stack.top();
        property_stack.pop();
    }
    
    template<typename T, typename T2>
    void fill_rotated_text(const std::string &str, T x, T2 y, double angle)
    {
        save();
        translate(x, y);
        rotate(angle*(M_PI/180));
        translate(-x, -y);
        fill_text(str, x, y);
        restore();
    };

    template<typename T, typename T2>
    void translate(T x, T2 y)
    {
        buffer += context_name + ".translate(" + std::to_string(x) + ", " + std::to_string(y) + ");\n";
    };

    template<typename T>
    void fill_rect(T x, T y, T width, T height)
    {
        buffer += context_name + ".fillRect(" + std::to_string(x) + ", " + std::to_string(y) + "," + std::to_string(width)
                + "," + std::to_string(height) + ");\n";
    }

    /*!
     * Gets the internal content of the buffer
     *
     * @return Internal content of the buffer.
     * Do not destroy canvas context if using this as a reference.
     */
    inline const std::string &dump() const
    {
        return buffer;
    }

    /*!
     * Gets the context name
     *
     * @return The context name
     */
    inline const std::string &get_name() const
    {
        return context_name;
    }
private:
    std::string context_name;
    std::string buffer;
    std::unordered_map<std::string, std::string> properties;
    std::stack<std::unordered_map<std::string, std::string>> property_stack;
};


#endif //HTMLGRAPHGENERATOR_CANVASCONTEXT_H
