#include <config.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

#define GLFW_INCLUDE_GL_3
#include <GLFW/glfw3.h>

#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ui.h"
#include "../font.h"
#include "../widget.h"
#include "../label.h"
#include "../button.h"
#include "../text_field.h"
#include "../password.h"
#include "../manager.h"
#include "../row_column.h"
#include "../pie_menu.h"

#include "../connect_glfw.h"

void error_callback(int, const char *);
void window_size_callback(GLFWwindow *w, int, int);
void create_image(int, int);
void close_key_callback(ui::active *, void *, void *);
void enter_callback(ui::active *, void *, void *);
void leave_callback(ui::active *, void *, void *);
void menu_callback(ui::active *, void *, void *);
void reorient_callback(ui::active *, void *, void *);
void print_sizes(ui::active *, void *, void *);

ui::context *ctx;
ui::widget *w1;
ui::label *l1;
ui::button *b1, *b2;
ui::text_field *t1;
ui::password *pw1;
ui::manager *m1;
ui::row_column *r1;
ui::pie_menu *pu1;

std::string font_name("techover.ttf"), greeting("Howdy!");
std::vector<std::string> paths =
{
    ".",
    "./test",
    "~/Library/Fonts",
    "/Library/Fonts",
    "/Network/Library/Fonts",
    "/System/Library/Fonts",
    "/System/Folder/Fonts",
};

unsigned char colors[6][4] =
{
    {255, 0, 0, 255},
    {255, 153, 0, 255},
    {255, 255, 0, 255},
    {0, 255, 0, 255},
    {0, 0, 255, 255},
    {128, 0, 128, 255},
};
ui::image img;

int main(int argc, char **argv)
{
    GLFWwindow *w;
    GLuint border = 1, wid = 72, hei = 48, xpos, ypos, max_len, spacing;
    GLuint gridx, gridy;
    glm::vec4 fg1 = {1.0, 1.0, 1.0, 1.0}, fg2 = {0.0, 1.0, 1.0, 1.0};
    glm::vec4 bg1 = {0.2, 0.2, 0.2, 1.0}, bg2 = {0.2, 0.2, 0.2, 0.2};
    glm::vec4 bg3 = {0.0, 0.0, 0.0, 1.0};
    ui::font *std_font = new ui::font(font_name, 30, paths);
    ui::font *tiny_font = new ui::font(font_name, 15, paths);
    int button;

    if (glfwInit() == GL_FALSE)
    {
        std::cout << "failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
#if NEED_GL_FORWARD_COMPAT
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif /* NEED_GL_FORWARD_COMPAT */

    if ((w = glfwCreateWindow(800, 600, "ui-test", NULL, NULL)) == NULL)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(w);
    glfwSetWindowSizeCallback(w, window_size_callback);
    std::cout << "creating image" << std::endl;
    create_image(wid, hei);

    std::cout << "creating context" << std::endl;
    ctx = new ui::context(800, 600);
    ui_connect_glfw(ctx, w);
    ctx->add_callback(ui::callback::key_down, close_key_callback, w);

    std::cout << "creating widget 1" << std::endl;
    w1 = new ui::widget(ctx, 50, 50);
    w1->set(ui::element::color, ui::color::foreground, fg1,
            ui::element::color, ui::color::background, fg2,
            ui::element::border, ui::side::all, 2,
            ui::element::margin, ui::side::all, 2,
            ui::element::position, ui::position::x, 50,
            ui::element::position, ui::position::y, 50);
    std::cout << "creating label 1" << std::endl;
    l1 = new ui::label(ctx, 0, 0);
    l1->set(ui::element::font, ui::ownership::shared, std_font,
            ui::element::string, 0, greeting,
            ui::element::color, ui::color::foreground, fg1,
            ui::element::border, ui::side::all, 1,
            ui::element::margin, ui::side::all, 1,
            ui::element::position, ui::position::x, 50,
            ui::element::position, ui::position::y, 125);
    std::cout << "creating button 1" << std::endl;
    b1 = new ui::button(ctx, 0, 0);
    b1->set(ui::element::image, 0, img,
            ui::element::margin, ui::side::all, 0,
            ui::element::border, ui::side::all, 0,
            ui::element::color, ui::color::foreground, fg1,
            ui::element::color, ui::color::background, bg3,
            ui::element::position, ui::position::x, 50,
            ui::element::position, ui::position::y, 175);
    std::cout << "creating password 1" << std::endl;
    pw1 = new ui::password(ctx, 0, 0);
    pw1->set(ui::element::font, ui::ownership::shared, std_font,
             ui::element::border, ui::side::all, 1,
             ui::element::color, ui::color::foreground, fg1,
             ui::element::color, ui::color::background, bg2,
             ui::element::position, ui::position::x, 50,
             ui::element::position, ui::position::y, 250,
             ui::element::size, ui::size::max_width, 5);
    std::cout << "creating manager 1" << std::endl;
    m1 = new ui::manager(ctx, 200, 200);
    m1->set(ui::element::border, ui::side::all, 1,
            ui::element::color, ui::color::foreground, fg1,
            ui::element::color, ui::color::background, bg2,
            ui::element::position, ui::position::x, 250,
            ui::element::position, ui::position::y, 35,
            ui::element::child_spacing, ui::size::width, 10,
            ui::element::child_spacing, ui::size::height, 10);
    std::cout << "creating button 2" << std::endl;
    b2 = new ui::button(m1, 0, 0);
    b2->set(ui::element::font, ui::ownership::shared, std_font,
            ui::element::color, ui::color::foreground, fg2,
            ui::element::string, 0, greeting,
            ui::element::margin, ui::side::all, 5,
            ui::element::border, ui::side::all, 5,
            ui::element::position, ui::position::x, 10,
            ui::element::position, ui::position::y, 10);
    std::cout << "creating text field 1" << std::endl;
    t1 = new ui::text_field(m1, 0, 0);
    t1->set(ui::element::font, ui::ownership::shared, std_font,
            ui::element::string, 0, greeting,
            ui::element::size, ui::size::max_width, 10,
            ui::element::border, ui::side::all, 1,
            ui::element::color, ui::color::foreground, fg1,
            ui::element::color, ui::color::background, bg1,
            ui::element::position, ui::position::x, 10,
            ui::element::position, ui::position::y, 100);
    std::cout << "creating row-column 1" << std::endl;
    r1 = new ui::row_column(ctx, 10, 10);
    r1->set(ui::element::border, ui::side::all, 1,
            ui::element::size, ui::size::columns, 1,
            ui::element::size, ui::size::rows, 0,
            ui::element::color, ui::color::foreground, fg1,
            ui::element::color, ui::color::background, bg1,
            ui::element::position, ui::position::x, 520,
            ui::element::position, ui::position::y, 35,
            ui::element::child_spacing, ui::size::width, 10,
            ui::element::child_spacing, ui::size::height, 10);
    r1->add_callback(ui::callback::btn_down, reorient_callback, NULL);
    for (int q = 0; q < 7; ++q)
    {
        std::cout << "  creating child " << q << std::endl;
        std::ostringstream s;
        ui::label *l = new ui::label(r1, 0, 0);

        s << "Label " << q << "\n" << greeting;
        l->set(ui::element::font, ui::ownership::shared, std_font,
               ui::element::string, 0, s.str(),
               ui::element::border, ui::side::all, 1,
               ui::element::size, ui::size::width, 100);
        l->add_callback(ui::callback::btn_down, print_sizes, NULL);
    }
    std::cout << "creating popup 1" << std::endl;
    pu1 = new ui::pie_menu(ctx, 200, 125);
    pu1->set(ui::element::border, ui::side::outer, 1,
             ui::element::margin, ui::side::outer, 1,
             ui::element::border, ui::side::inner, 1,
             ui::element::popup, ui::popup::button, ui::mouse::button0);
    for (intptr_t q = 0; q < 7; ++q)
    {
        std::cout << "  creating child " << q << std::endl;
        std::ostringstream s;
        ui::label *pul = new ui::label(pu1, 0, 0);

        s << (char)('a' + q);
        pul->set(ui::element::font, ui::ownership::shared, tiny_font,
                 ui::element::string, 0, s.str());
        pul->add_callback(ui::callback::btn_up, menu_callback, (void *)q);
        pul->add_callback(ui::callback::enter, enter_callback, (void *)q);
        pul->add_callback(ui::callback::leave, leave_callback, (void *)q);
    }
    std::cout << "done creating things" << std::endl;

    while (!glfwWindowShouldClose(w))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ctx->draw();
        glfwSwapBuffers(w);
        glfwPollEvents();
    }
    delete ctx;
    delete tiny_font;
    delete std_font;
    glfwTerminate();
    return 0;
}

void error_callback(int err, const char *desc)
{
    std::cout << "glfw error: " << desc << " (" << err << ')' << std::endl;
}

void window_size_callback(GLFWwindow *w, int width, int height)
{
    glm::ivec2 sz(width, height);

    ctx->set(ui::element::size, ui::size::all, sz);
}

void create_image(int width, int height)
{
    img.width = width;
    img.height = height;
    img.per_pixel = 4;
    img.data = new unsigned char[width * height * img.per_pixel];
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 8; ++j)
            for (int k = 0; k < width; ++k)
                memcpy(&img.data[((height - 1 - (i * 8) - j) * width + k) * 4],
                       colors[i],
                       sizeof(unsigned char) * 4);
}

void close_key_callback(ui::active *a, void *call, void *client)
{
    ui::key_call_data *call_data = (ui::key_call_data *)call;
    GLFWwindow *w = (GLFWwindow *)client;

    if (call_data->key == ui::key::esc && call_data->state == ui::key::down)
        glfwSetWindowShouldClose(w, GL_TRUE);
}

/* ARGSUSED */
void enter_callback(ui::active *a, void *call, void *client)
{
    std::cout << "we're in " << (intptr_t)client << '!' << std::endl;
}

/* ARGSUSED */
void leave_callback(ui::active *a, void *call, void *client)
{
    std::cout << "out of " << (intptr_t)client << ", baby!" << std::endl;
}

void menu_callback(ui::active *a, void *call, void *client)
{
    std::cout << "menu sector " << (intptr_t)client << std::endl;
}

void reorient_callback(ui::active *a, void *call, void *client)
{
    ui::row_column *r = dynamic_cast<ui::row_column *>(a);
    ui::btn_call_data *call_data = (ui::btn_call_data *)call;

    if (r != NULL && call_data->button == ui::mouse::button0)
    {
        static glm::ivec2 grid(2, 4);
        static GLuint orient = ui::order::column;
        glm::ivec2 old_grid;
        GLuint old_orient;

        r->get(ui::element::size, ui::size::grid, &old_grid,
               ui::element::order, 0, &old_orient);
        r->set(ui::element::size, ui::size::grid, grid,
               ui::element::order, 0, orient);
        r->manage_children();
        grid = old_grid;
        orient = old_orient;
    }
}

/* ARGSUSED */
void print_sizes(ui::active *a, void *call, void *client)
{
    glm::ivec2 pos, size;
    GLuint border[4], margin[4];
    ui::widget *w = dynamic_cast<ui::widget *>(a);

    if (w == NULL)
        return;

    w->get(ui::element::position, ui::position::all, &pos,
           ui::element::size, ui::size::all, &size,
           ui::element::border, ui::side::top, &border[0],
           ui::element::border, ui::side::left, &border[1],
           ui::element::border, ui::side::right, &border[2],
           ui::element::border, ui::side::bottom, &border[3],
           ui::element::margin, ui::side::top, &margin[0],
           ui::element::margin, ui::side::left, &margin[1],
           ui::element::margin, ui::side::right, &margin[2],
           ui::element::margin, ui::side::bottom, &margin[3]);
    std::cout << "pos <" << pos.x << ", " << pos.y << ">" << std::endl;
    std::cout << "size <" << size.x << ", " << size.y << ">" << std::endl;
    std::cout << "border <" << border[0] << ", " << border[1] << ", "
              << border[2] << ", " << border[3] << ">" << std::endl;
    std::cout << "margin <" << margin[0] << ", " << margin[1] << ", "
              << margin[2] << ", " << margin[3] << ">" << std::endl;
}
