# HTML5 Canvas Graph Generator
A set of C++ classes for generating Javascript which can be rendered browsers into graphs, using the HTML5 Canvas API. 

*Note:* This project is not very old, or mature, at all, and so its functionality is very limited. Though hopefully that will change with time.
At the moment, only line graphs with a set style are supported, but I plan to add support for bar 
charts and PIE charts in time, along with more options, and customisable style.

<h2>Examples</h2>

#### Line Chart
<img src="https://frednicolson.co.uk/u/graph_example.png" alt="Example Graph 1">

```c++
HTMLLineChart chart;
chart.set_size(600, 500);
chart.set_increment(2, 2);

chart.set_x_index_strings({"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"});
chart.add_point({"Monday", 1});
chart.add_point({"Tuesday", 0});
chart.add_point({"Wednesday", 2});
chart.add_point({"Thursday", 3});
chart.add_point({"Friday", 1});
chart.add_point({"Saturday", 5});
chart.add_point({"Sunday", 2});

chart.set_title("Cookie Consumption");
chart.set_x_label("Cookies Eaten");
chart.set_y_label("Day");
```

#### Another Line Chart
<img src="https://frednicolson.co.uk/u/graph_example2.png" alt="Example Graph 2">

```c++
HTMLLineChart chart;
chart.set_size(600, 500);
chart.set_increment(50, 10);

for(uint32_t a = 0; a < 600; a += 20)
    chart.add_point({a, 40 + rand() % 3 + 1});

chart.set_title("GPU Temperature");
chart.set_x_label("Frame Number");
chart.set_y_label("Temperature (c)");
```

#### Bar Chart
<img src="https://frednicolson.co.uk/u/graph_example3.png" alt="Example Graph 2">

```c++
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
```