#include <iostream>
#include <HTMLBarChart.h>
#include <fstream>

int main()
{
    HTMLBarChart chart;
    chart.set_size(600, 500);
    chart.set_increment(1, 1);

    chart.add_point({"Monday", 2, HTMLGraph::Colour(249, 199, 168)});
    chart.add_point({"Tuesday", 3, HTMLGraph::Colour(243, 154, 155)});
    chart.add_point({"Wednesday", 1, HTMLGraph::Colour(236, 110, 141)});
    chart.add_point({"Thursday", 0});
    chart.add_point({"Friday", 5, HTMLGraph::Colour(169,55,144)});
    chart.add_point({"Saturday", 6, HTMLGraph::Colour(123,35,151)});
    chart.add_point({"Sunday", 2, HTMLGraph::Colour(92,24,134)});

    chart.set_x_index_strings({"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"                                                                                                                                                                                 , "Saturday", "Sunday"});

    chart.set_title("Distance Ran");
    chart.set_x_label("Day");
    chart.set_y_label("Miles");

    std::string str = chart.construct();
    std::ofstream file("out.html");
    file << str;
    std::cout << str << std::endl;
    return 0;
}