#include <iostream>
#include <HTMLBarChart.h>
#include <fstream>

int main()
{
    HTMLLineChart chart;
    chart.set_size(600, 500);
    chart.set_increment(10, 10);

    chart.add_point({"Monday", 10});
    chart.add_point({"Tuesday", 20});
    chart.add_point({"Saturday", 50});
    chart.add_point({"Sunday", 40});
//    chart.add_point({55, 33});
//    chart.add_point({20, 30});
//    chart.add_point({40, 20});
//    chart.add_point({60, 30});

    chart.set_x_index_strings({"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"});

    chart.set_title("Mhmm... Graph titles...");
    chart.set_x_label("Arbitrary X Data");
    chart.set_y_label("Arbitrary Y Data");

    std::string str = chart.construct();
    std::ofstream file("out.html");
    file << str;
    std::cout << str << std::endl;
    return 0;
}