//
// simulator.hpp
//

#ifndef _SIMULATOR_HPP_
#define _SIMULATOR_HPP_

#define FRAME_INTERVAL 0.02

#include "../libs/physics-engine/src/phy_engine.hpp"

/* pugi xml */
#include "../libs/pugixml-1.8/src/pugixml.hpp"

/* opengl */
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"

/* STL */
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <fstream>
#include <thread>
#include <iostream>

/* custom class */
#include "object.hpp"
#include "shader.hpp"

#include <Windows.h>

/* pmframework */
#include "../libs/physics-engine/src/pmframework.hpp"

class Simulator;

class Camera {
public:
    Camera(const glm::vec3& pos, const glm::vec3& target,
        const glm::vec3& axis_vert, const glm::vec3& axis_horz);
    Camera() {}
    glm::mat4& GetMatrix();
    void Update(const glm::vec3 &pos, const glm::vec3 &target,
        const glm::vec3 &axis_horz);
    void Update() { calculate();  }

private:
    void calculate();

    friend class Simulator;
    glm::mat4 mat_;

    glm::vec3 pos_;
    glm::vec3 view_up_;
    glm::vec3 target_;
    glm::vec3 axis_vert_;
    glm::vec3 axis_horz_;

};

class Simulator {
public:
    // create GL Context
    Simulator() {}
    ~Simulator() {}

    static void Init(int width, int height, const char* title, int scale);
                        
    static void Start();
    static bool Initialize(const std::string& xml_url);
    static void KeyCallback(int key, int scancode, int action, int mods);
    static void MouseMovCallback(double x, double y);
    static void Release();

private:
    static Simulator* instance;
    Simulator(int w, int h, const char* title, int scale);

    void start();
    bool initialize(const std::string& xml_url);
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_mov_callback(double x, double y);
   
    void load_shaders(const pugi::xml_node& shader_list);
    void load_objects(const pugi::xml_node& obj_list);

    GLuint load_texture(unsigned char* buffer, int width, int height);

    void process_input();
    bool check_program();
    
    void compute();
    void render();
    void simulate();
    void save(int idx);

    GLFWwindow* window_;
    
    Camera curr_camera_; // will be changed

    GLuint shader_program_; 
    GLuint compute_program_;
    
    GLint wld_uniform_;
    GLint view_uniform_;
    GLint proj_uniform_;

    GLint ray_uniform_[2][2];
    GLint eye_uniform_;

    GLint num_vertices_uniform_;
    GLint num_nvectors_uniform_;
    GLint num_triangles_uniform_;
    GLint num_spheres_uniform_;

    GLuint vertices_ssbo_;
    GLuint tvertices_ssbo_;
    GLuint nvectors_ssbo_;
    GLuint triangles_ssbo_;
    GLuint spheres_ssbo_;

    GLuint texture_;
    GLuint textures_[10];
    GLuint textures_cnt_;
    
    GLuint vertex_buffer_object_;

    glm::mat4 world_;
    glm::mat4 proj_;

    glm::mat4 Rx_; // for camera roatation
    glm::mat4 RRx_;
    glm::mat4 Ry_;
    glm::mat4 RRy_;
    glm::mat4 Rz_;
    glm::mat4 RRz_;

    std::vector<std::unique_ptr<Object>> objects_;

    GLdouble prev_x;
    GLdouble prev_y;

    int width_;
    int height_;
    int scale_;
    int num_frames_;

    short key_stat[300]; // GL_PRESS, GL_REPEAT, GL_RELEASE

    unsigned char buffer_for_save_[1024*1024*3 + 1];

    BITMAPFILEHEADER file_header_;
    BITMAPINFOHEADER info_header_;

    bool first_touch;

    std::vector<glm::vec3> vertices_; // static vertex
    std::vector<glm::vec2> tvertices_;
    std::vector<glm::vec3> nvectors_;
    std::vector<glm::ivec4> faces_;
    std::vector<glm::vec3> vertices__;
    std::vector<glm::vec4> spheres_;
    std::vector<pmframework::RigidBody*> phy_spheres_;

    pmframework::Simulation simulation_;
};

#endif
