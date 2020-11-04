#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <vector>
#include <thread> 
#include "SliderSFML.h"
#include "backend.cpp"
using namespace sf;
using namespace std;
#define check Check(i, j)
#define res 500
#define da true

Checker ch;
vector<vector<bool>> regions{
        {0, 1, 1, 0, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1}
};
struct GraphSize {
    double min_x = -8, max_x = 4;
    double min_y = -6, max_y = 6;
};
GraphSize defaultGS;

bool CheckCoordinates(double x, double y, double threshold) {
    //cout << ((abs(x) <= threshold || abs(y) <= threshold)?"true": "false") << endl;
    return (abs(x) <= threshold || abs(y) <= threshold);
}
bool CheckGrid(double x, double y, double threshold) {
    //cout << ((abs(x) <= threshold || abs(y) <= threshold)?"true": "false") << endl;
    return abs(round(x) - x) <= threshold && abs(round(y) - y) <= threshold;
}
void UpdateImageThreshold(Image& im, bool (&check_func)(double, double, double), double threshold, Color on_true = Color::White, Color on_false = Color::Black, GraphSize gs = defaultGS) {
    double x_pix = ((gs.max_x - gs.min_x) / im.getSize().x);
    double y_pix = ((gs.max_y - gs.min_y) / im.getSize().y);
    
    double x = gs.min_x;
    double y = gs.min_y;

    int size_x = im.getSize().x;
    int size_y = im.getSize().y;
    for (int i = 0; i < size_x; ++i, x += x_pix) {
        y = gs.min_y;
        for (int j = 0; j < size_y; ++j, y += y_pix) {
            if (check_func(x, y, threshold)) im.setPixel(i, j, on_true);
        }
    }
}
void DrawGraph(Image* im, Graph* g, Color on_true = Color::White, Color on_false = Color::Red, GraphSize gs = defaultGS) {
    double x_pix = ((gs.max_x - gs.min_x) / (*im).getSize().x);
    double y_pix = ((gs.max_y - gs.min_y) / (*im).getSize().y);

    double x = gs.min_x;
    double y = gs.min_y;

    int size_x = (*im).getSize().x;
    int size_y = (*im).getSize().y;

    Image t;
    t.create((*im).getSize().x, (*im).getSize().y, Color::Black);
    for (int i = 0; i < size_x; ++i, x += x_pix) {
        y = gs.min_y;
        for (int j = 0; j < size_y; ++j, y += y_pix) {
            if ((*g).Check(y, x)) t.setPixel(i, j, on_true);
        }
    }
    for (int i = 1; i < size_x; ++i) {
        for (int j = 1; j < size_y; ++j) {
            if (t.getPixel(i, j) != t.getPixel(i, j - 1) || t.getPixel(i, j) != t.getPixel(i - 1, j)) (*im).setPixel(i, j, on_true);
            //else if ((((i - j) % 30 == 0)) && t.getPixel(x, y) == on_true) im.setPixel(i, j, on_false);
        }
    }
}
void DrawRegion(Image& im, vector<bool> regions) {
    double x_pix = ((defaultGS.max_x - defaultGS.min_x) / im.getSize().x);
    double y_pix = ((defaultGS.max_y - defaultGS.min_y) / im.getSize().y);

    double x = defaultGS.min_x;
    double y = defaultGS.min_y;

    int size_x = im.getSize().x;
    int size_y = im.getSize().y;

    for (int i = 0; i < size_x; ++i, x += x_pix) {
        y = defaultGS.min_y;
        for (int j = 0; j < size_y; ++j, y += y_pix) {
            bool b = true;

            for (int i = 0; i < regions.size(); ++i) {
                ch.graphs[i].x0y0 = regions[i];
                if (ch.graphs[i].Check(y, x) == false) {
                    b = false;
                }
            }
            if ((((i - j) % 30 == 0)) && b) im.setPixel(i, j, Color::Red);
        }
    }
}

void RenderBackground(Image& im) {
    im.create(res, res, Color(20, 20, 20));
    UpdateImageThreshold(im, CheckCoordinates, 0.05);
    UpdateImageThreshold(im, CheckGrid, 0.025);
}
void RenderOutlines(Image& im, Graph& g) {
    im.create(res, res, Color::Transparent);
    for (auto i : ch.graphs) {
        if (i.name != g.name) DrawGraph(&im, &i);
    }
}
void RenderRegions(Image& im) {
    im.create(res, res, Color::Transparent);
    cout << endl;
    for (auto i : regions) {
        DrawRegion(im, i);
        cout << "{";
        for (auto j : i) cout << j << ", ";
        cout <<"}," << endl;
    }
}
void RenderSelected(Image& im, Graph& g) {
    im.create(res, res, Color::Transparent);
    DrawGraph(&im, &g, Color::Green);
}
void RenderImage(Image& im, RenderWindow& w) {
    Texture buff_texture;
    Sprite buff_sprite;
    im.flipVertically();
    buff_texture.loadFromImage(im);
    buff_sprite.setTexture(buff_texture);
    buff_sprite.setScale(1000 / res, 1000 / res);
    w.draw(buff_sprite);
    im.flipVertically();
}
void CreateDefaultGraphs() {
    ch.addGraph("p1", Graph::parabola, -5, 1, 1, 1, false, true);
    ch.addGraph("p2", Graph::parabola, -5.5, 0.5, 1, 0.5, true, false);
    ch.addGraph("c", Graph::circle, -6, 1, 4, 4, true, false);
    ch.addGraph("r1", Graph::rectangle, -5.5, -1.75, 4, 1.5, false, false);
    ch.addGraph("rh", Graph::rhombus, -3.5, -0.5, 10, 5, false, false);
    ch.addGraph("l1", Graph::line, 0, -2, 1, 0.25, true, false);
    ch.addGraph("l2", Graph::line, 0, 2, 1, -0.666, true, false);
    ch.addGraph("n0", Graph::none, 0, 0, 1, 1, false, false);
    ch.addGraph("n1", Graph::none, 0, 0, 1, 1, false, false);
    ch.addGraph("n2", Graph::none, 0, 0, 1, 1, false, false);
}
int main() {
    CreateDefaultGraphs();
    
#pragma region
    RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");
    window.setFramerateLimit(60); 
    Image buff_img;
    Texture buff_texture;
    Sprite buff_sprite;
    buff_img.create(res, res, Color(100, 100, 100));
#pragma endregion setup sfml
#pragma region
    SliderSFML slider_xpos(1250, 50);
    SliderSFML slider_ypos(1250, 50 + 75);
    SliderSFML slider_zoom(1250, 50 + 75 * 2);
    SliderSFML slider_graph_n(1250, 300);
    SliderSFML slider_x(1250, 300 + 75 * 1);
    SliderSFML slider_y(1250, 300 + 75 * 2);
    SliderSFML slider_sizex(1250, 300 + 75 * 3);
    SliderSFML slider_sizey(1250, 300 + 75 * 4);
    SliderSFML slider_type(1250, 300 + 75 * 5);

    slider_xpos.create(-10, 10, "X pos");
    slider_ypos.create(-10, 10, "Y pos");
    slider_zoom.create(1, 20, "Zoom");

    slider_graph_n.create(0, ch.graphs.size()-1, "Graph N", true);
    slider_x.create(-10, 10, "X");
    slider_y.create(-10, 10, "Y");
    slider_sizex.create(-10, 10, "Size X");
    slider_sizey.create(-10, 10, "Size Y");
    slider_type.create(0, 5, "Type", true);

    slider_graph_n.setSliderValue(0);
    slider_xpos.setSliderValue(2);
    slider_ypos.setSliderValue(0);
    slider_zoom.setSliderValue(6);
#pragma endregion sliders

    int t = -1;
    bool last_frame_mouse = false;

    Image background_i;
    Image outlines_i;
    Image regions_i;
    Image selected_i;
    background_i.create(res, res, Color::Transparent);
    outlines_i.create(res, res, Color::Transparent);
    regions_i.create(res, res, Color::Transparent);

    RenderBackground(background_i);
    RenderOutlines(outlines_i, ch.graphs[0]);
    RenderRegions(regions_i);

    while (window.isOpen()) {
        if (slider_graph_n.getIsValueChanged() && (t != (int)slider_graph_n.getSliderValue() || t == -1)) {
            t = (int)slider_graph_n.getSliderValue();
            slider_x.setSliderValue(ch.graphs[t].posX);
            slider_y.setSliderValue(ch.graphs[t].posY);
            slider_sizex.setSliderValue(ch.graphs[t].sizeX);
            slider_sizey.setSliderValue(ch.graphs[t].sizeY);
            slider_type.setSliderValue(ch.graphs[t].type);

            RenderOutlines(outlines_i, ch.graphs[t]);
            RenderSelected(selected_i, ch.graphs[t]);
        }
        else if (slider_xpos.getIsValueChanged() || slider_ypos.getIsValueChanged() || slider_zoom.getIsValueChanged()) {
            defaultGS.min_x = -slider_zoom.getSliderValue() - slider_xpos.getSliderValue();
            defaultGS.max_x = slider_zoom.getSliderValue() - slider_xpos.getSliderValue();
            defaultGS.min_y = -slider_zoom.getSliderValue() - slider_ypos.getSliderValue();
            defaultGS.max_y = slider_zoom.getSliderValue() - slider_ypos.getSliderValue();

            RenderBackground(background_i);
            RenderOutlines(outlines_i, ch.graphs[t]);
            RenderSelected(selected_i, ch.graphs[t]);
            RenderRegions(regions_i);
        }
        else if (slider_x.getIsValueChanged()||slider_y.getIsValueChanged()||slider_sizex.getIsValueChanged()||slider_sizey.getIsValueChanged()||slider_type.getIsValueChanged()||da) {
            ch.graphs[t].posX = slider_x.getSliderValue();
            ch.graphs[t].posY = slider_y.getSliderValue();
            ch.graphs[t].sizeX = slider_sizex.getSliderValue();
            ch.graphs[t].sizeY = slider_sizey.getSliderValue();
            ch.graphs[t].type = static_cast<Graph::gType>((int)(slider_type.getSliderValue()));

            RenderSelected(selected_i, ch.graphs[t]);
        }
        if (Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < 1000) {
            if (Mouse::getPosition(window).y > 0 && sf::Mouse::getPosition(window).y < 1000) {
                if (Mouse::isButtonPressed(sf::Mouse::Button::Left) != last_frame_mouse && !last_frame_mouse) {
                    double x_pix = ((defaultGS.max_x - defaultGS.min_x) / 1000);
                    double y_pix = ((defaultGS.max_y - defaultGS.min_y) / 1000);

                    double x = defaultGS.min_x + x_pix * Mouse::getPosition(window).x;
                    double y = defaultGS.min_y + x_pix * (1000 - Mouse::getPosition(window).y);

                    vector<bool> tmp;
                    for (auto i : ch.graphs) {
                        i.x0y0 = true;
                        tmp.push_back(i.Check(y, x));
                    }
                    bool b = true;
                    for (int i = 0; i < regions.size(); ++i) {
                        if (regions[i] == tmp) {
                            regions.erase(regions.begin() + i);
                            b = false;
                        }
                    }

                    if (b) {
                        regions.push_back(tmp);
                    }

                    RenderRegions(regions_i);
                }
            }
        }
        last_frame_mouse = Mouse::isButtonPressed(sf::Mouse::Button::Left);

        Event event;
        while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();

        window.clear();
        RenderImage(background_i, window);
        RenderImage(outlines_i, window);
        RenderImage(selected_i, window);
        RenderImage(regions_i, window);
        slider_x.draw(window);
        slider_y.draw(window);
        slider_graph_n.draw(window);
        slider_xpos.draw(window);
        slider_ypos.draw(window);
        slider_zoom.draw(window);
        slider_sizex.draw(window);
        slider_sizey.draw(window);
        slider_type.draw(window);
        window.display();
    }

    return 0;
} 